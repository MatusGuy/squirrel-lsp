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
	Logger::get().log(MessageType::Info, QString("buffer: %1").arg(buffer).toUtf8());

	BufState bufstate{buffer.toStdString().data(), buffer.size(), 0};
	lexer->Init(vm->_sharedstate, bufLexfeed, &bufstate, squirrelError, nullptr);
	SQInteger start = 0;
	do {
		Logger::get().log(MessageType::Info, "Yoohoo");
		SQInteger token = lexer->Lex();

		Range range{lexer->_currentline, start, lexer->_currentcolumn};
		resp.append({range, token});

		start = lexer->_currentcolumn;
		Logger::get().log(MessageType::Info, QString("start: %1").arg(start).toUtf8());
	} while (lexer->_currdata != SQUIRREL_EOB);

	qDebug() << "EXITED";

	return resp;
}
