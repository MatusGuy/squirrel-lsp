#include "squirrelreader.h"

#include "semantictokens.h"
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

QList<QPair<SquirrelReader::TokenCoords, SQInteger>> SquirrelReader::lex(const QString& buffer) {
	QList<QPair<TokenCoords, SQInteger>> resp;
	Logger::info(QString("buffer: %1 (%2)").arg(buffer).arg(buffer.size()));

	char* rawdata = buffer.toStdString().data();
	BufState bufstate{rawdata, buffer.size(), 0};

	lexer->Init(vm->_sharedstate, bufLexfeed, &bufstate, squirrelError, nullptr);

	int start = 0;
	SQInteger token = 0;
	forever {
		start = static_cast<int>(lexer->_currentcolumn);
		token = lexer->Lex();
		Logger::info(QString("token: %1 (%2, %3)").arg(QChar(static_cast<int>(token)))
												  .arg(token)
												  .arg(lextkToSemtk(token).has_value() ? SEMANTIC_TOKEN_TYPES.at((int)(lextkToSemtk(token).value())) : ""));

		if (token == 0) {
			// EOB
			break;
		}

		TokenCoords range{static_cast<int>(lexer->_currentline),
					start,
					static_cast<int>(lexer->_currentcolumn)};
		resp.append({range, token});

	}

	Logger::info(QString("tokens: %1").arg(resp.size()));

	return resp;
}

/*
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
	int index = 0;
	for (const Highlighter& highlighter : m_highlighters) {
		QRegularExpressionMatchIterator i = highlighter.regex.globalMatch(buffer);
		while (i.hasNext()) {
			QRegularExpressionMatch match = i.next();

			if (!match.hasMatch()) break;

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
			Logger::log(QString("%0 %1 %2 %3 %4").arg(index).arg(range.start.line).arg(range.end.line).arg(range.start.character).arg(range.end.character));
			m_tokens.append({range, highlighter.type});
		}
		index++;
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
	/

	std::sort(m_tokens.begin(), m_tokens.end(), [](const Token& a, const Token& b) {
		Logger::log(QString("%1 %2 %3 %4").arg(a.first.start.line).arg(a.first.end.line).arg(a.first.start.character).arg(a.first.end.character));
		if (a.first.start.line != b.first.start.line) {
			return a.first.start.line > b.first.start.line;
		} else {
			return a.first.start.character > b.first.start.character;
		}
	});
}

int SquirrelReader::countLines(QString str, int start)
{
	str.truncate(start);
	return str.count('\n');
}

int SquirrelReader::getPosInLine(const QString& str, int start)
{
	int lastNewline = str.lastIndexOf('\n', start);
	return lastNewline != -1 ? start - lastNewline : start;
}
*/
