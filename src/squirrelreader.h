#ifndef SQUIRRELENV_H
#define SQUIRRELENV_H

#include <QUrl>
#include <QFile>
#include <QMap>
#include <QDebug>

#include "qlspcustomtypes_p.h"
using namespace QLspSpecification;

//#include <squirrel.h>
//#include <squirrel/sqvm.h>
//#include <squirrel/sqcompiler.h>
//#include <squirrel/sqlexer.h>

#include "logger.h"

//class SQCompiler;

class SquirrelReader : public QObject {
	Q_OBJECT
public:
	struct Highlighter {
		Highlighter(const QString& exp, SemanticTokenTypes typ):
			regex(exp, QRegularExpression::DotMatchesEverythingOption | QRegularExpression::MultilineOption),
			type(typ)
		{}

		QRegularExpression regex;
		SemanticTokenTypes type;
	};

	typedef QPair<Range, SemanticTokenTypes> Token;

	SquirrelReader(const QString& filepath);
	~SquirrelReader();

	/*
	struct BufState {
		const SQChar *buf;
		SQInteger size;
		SQInteger ptr;
	};

	/// ripped from sqapi.cpp
	static SQInteger bufLexfeed(SQUserPointer file) {
		BufState* buf = (BufState*) file;
		if(buf->size < (buf->ptr + 1)) {
			Logger::info("heheheha");
			return 0;
		}
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
	*/

	static SquirrelReader* read(QString filepath);
	void sync();
	void lexer(QString buffer);
	//TODO: void syncAutocomplete();

	inline bool good() { return m_good; }
	inline QString filePath() { return m_filepath; }

	inline const QList<Token>& tokens() { return m_tokens; }

signals:
	void syncFinished();

private:
	bool m_good;
	QString m_filepath;
	QFile m_file;

	int countLines(QString str, int start);
	int getPosInLine(const QString& str, int start);

	QList<Token> m_tokens;

	std::array<Highlighter,5> m_highlighters = {
		Highlighter(R"(((//|#).*|/\*(.*?)\*/))", SemanticTokenTypes::Comment),
		Highlighter(R"(".*")", SemanticTokenTypes::String),
		Highlighter(R"((0[xXbB])?\d+)", SemanticTokenTypes::Number),
		Highlighter(R"(\b(base|break|case|catch|class|clone|con(tinue|st(ructor)?)|default|delete|else|enum|extends|for|foreach|function|if|in|local|null|resume|return|switch|this|throw|try|typeof|while|yield|instanceof|true|false|static|__LINE__|__FILE__|rawcall)\b)", SemanticTokenTypes::Keyword),
		Highlighter(R"(\w+(?=\())", SemanticTokenTypes::Function)
	};
};

#endif // SQUIRRELENV_H
