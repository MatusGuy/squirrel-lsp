#ifndef SQUIRRELENV_H
#define SQUIRRELENV_H

#include <QString>
#include <QDebug>

#include <squirrel.h>
#include <squirrel/sqvm.h>
#include <squirrel/sqcompiler.h>
#include <squirrel/sqlexer.h>

template <typename T>
class Singleton {
public:
	static T& get() {
		static T instance{};
		return instance;
	}

protected:
	Singleton() = default;
	~Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

class SQCompiler;

class SquirrelEnv : public Singleton<SquirrelEnv> {
public:
	SquirrelEnv();
	~SquirrelEnv();

	struct BufState {
		const SQChar *buf;
		SQInteger size;
		SQInteger ptr;
	};

	/// ripped from sqapi.cpp
	static SQInteger bufLexfeed(SQUserPointer file) {
		BufState *buf=(BufState*)file;
		if(buf->size<(buf->ptr+1))
			return 0;
		return buf->buf[buf->ptr++];
	}

	static void squirrelError(void* ud, const SQChar* s);


	struct Range {
		int line;
		int start;
		int end;
	};

	QList<QPair<Range, SQInteger>> lex(const QString& buffer);

	SQVM* vm;
	//SQCompiler* compiler;
	SQLexer* lexer;
};

#endif // SQUIRRELENV_H
