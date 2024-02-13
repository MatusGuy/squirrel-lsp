#include "squirrelreader.h"

/*
SquirrelReader::SquirrelReader() {
	vm = sq_open(1024);
	//compiler = new SQCompiler(vm, bufLexfeed, "", sourcename, raiseerror, lineinfo);
	lexer = new SQLexer;
}

SquirrelReader::~SquirrelReader() {
	delete lexer;
	//delete compiler;

	sq_close(vm);
}

void SquirrelReader::squirrelError(void* ud, const SQChar* s) {
	qCritical() << "A Squirrel error has occured: " << s;
}

QList<QPair<SquirrelReader::Range, SQInteger>> SquirrelReader::lex(const QString& buffer) {
	QList<QPair<Range, SQInteger>> resp;
	Logger::info(QString("buffer: %1 (%2)").arg(buffer).arg(buffer.size()));

	char* rawdata = buffer.toStdString().data();
	BufState bufstate{rawdata, buffer.size(), 0};

	lexer->Init(vm->_sharedstate, bufLexfeed, &bufstate, squirrelError, nullptr);

	int start = 0;
	do {
		start = static_cast<int>(lexer->_currentcolumn);
		SQInteger token = lexer->Lex();

		if (token != 0) {
			Range range{static_cast<int>(lexer->_currentline),
						start,
						static_cast<int>(lexer->_currentcolumn)};
			resp.append({range, token});
		}


		Logger::info(QString("token: %1 (%2)").arg(QChar(static_cast<int>(token))).arg(token));
	} while (lexer->_currdata != SQUIRREL_EOB);

	Logger::info(QString("tokens: %1").arg(resp.size()));

	return resp;
}
*/

SquirrelReader::SquirrelReader(const QString& filepath):
	QObject(nullptr),
	m_good(true),
	m_filepath(filepath),
	m_file(m_filepath)
{
	std::reverse(std::begin(m_highlighters), std::end(m_highlighters));

	Logger::log(QString("Opening %1").arg(filePath()));

	// Open the file in ReadOnly mode
	if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		// Report an error if the file couldn't be opened
		Logger::error(QString("Error opening file: %1").arg(m_file.errorString()));
		m_good = false;
		return;
	}
}

SquirrelReader::~SquirrelReader()
{
	m_file.close();
}

SquirrelReader* SquirrelReader::read(QString filepath) {
	auto reader = new SquirrelReader(filepath);
	reader->sync();
	return reader;
}

void SquirrelReader::sync()
{
	// Create a QTextStream to read from the file
	QTextStream in(&m_file);

	// Read all text from the file
	QString content = in.readAll();

	// Check for errors during reading
	if (in.status() != QTextStream::Ok) {
		Logger::error(QString("Error reading file: %1").arg(in.status()));
		m_good = false;
		return;
	}

	lexer(content);

	emit syncFinished();
}

void SquirrelReader::lexer(QString buffer)
{
	for (const Highlighter &highlighter : m_highlighters) {
		QRegularExpressionMatchIterator i = highlighter.regex.globalMatch(buffer);
		while (i.hasNext()) {
			QRegularExpressionMatch match = i.next();

			if (!match.hasMatch()) return;

			Range range = {
				{
					countLines(buffer, match.capturedStart()),
					getPosInLine(buffer, match.capturedStart())
				},
				{
					countLines(buffer, match.capturedEnd()),
					getPosInLine(buffer, match.capturedEnd())
				}
			};
			Logger::log(QString("%1 %2 %3 %4").arg(range.start.line).arg(range.end.line).arg(range.start.character).arg(range.end.character));
			m_tokens.append({range, highlighter.type});
		}
	}

	/*
	// highlight multiline comments
	QRegularExpressionMatchIterator i = m_highlighters[4].regex.globalMatch(buffer);
	while (i.hasNext()) {
		QRegularExpressionMatch match = i.next();
		if (match.hasMatch()) {
			Range range = {
				{
					.line = countLines(buffer, match.capturedStart()),
					.character = getPosInLine(buffer, match.capturedStart())
				},
				{
					.line = countLines(buffer, match.capturedEnd()),
					.character = getPosInLine(buffer, match.capturedEnd())
				}
			};
			m_tokens.append({range, SemanticTokenTypes::Comment});
		}
	}
	*/
}

int SquirrelReader::countLines(QString str, int start)
{
	str.truncate(start);
	return str.count('\n');
}

int SquirrelReader::getPosInLine(const QString& str, int start)
{
	int lastNewline = str.lastIndexOf('\n', start);
	return lastNewline != -1 ? lastNewline : start;
}
