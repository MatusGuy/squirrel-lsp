#include "squirrelenv.h"

SquirrelEnv::SquirrelEnv() {
	vm = sq_open(1024);
	//compiler = new SQCompiler(vm, bufLexfeed, "", sourcename, raiseerror, lineinfo);
	lexer = new SQLexer;
}

SquirrelEnv::~SquirrelEnv() {
	delete lexer;
	//delete compiler;

	sq_close(vm);
}

void SquirrelEnv::squirrelError(void* ud, const SQChar* s) {
	qCritical() << "A Squirrel error has occured: " << s;
}

QList<QPair<SquirrelEnv::Range, SQInteger>> SquirrelEnv::lex(const QString& buffer) {
	QList<QPair<Range, SQInteger>> resp;
	Logger::get().log(MessageType::Info, QString("buffer: %1 (%2)").arg(buffer).arg(buffer.size()));

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


		Logger::get().log(MessageType::Info, QString("token: %1 (%2)").arg(QChar(static_cast<int>(token))).arg(token));
	} while (lexer->_currdata != SQUIRREL_EOB);

	Logger::get().log(MessageType::Info, QString("tokens: %1").arg(resp.size()));

	return resp;
}
