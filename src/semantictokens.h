#ifndef SEMANTICTOKENS_H
#define SEMANTICTOKENS_H

#include <QMap>
#include <QString>

#include <squirrel.h>
#include <squirrel/sqobject.h>
#include <squirrel/sqcompiler.h>

// TODO: maybe we can use http://squirrel-lang.org/squirreldoc/reference/language/classes.html#class-attributes
// for the ones I commented
enum struct SemanticTokenType {
	Identifier = -1,
	Namespace, //
	Type,
	Class,
	Enum,
	Interface, //
	Struct, //
	Parameter,
	Variable,
	Property,
	EnumMember,
	Event, //
	Function,
	Method,
	Keyword,
	Comment,
	String,
	Number,
	Operator,
};

const QList<QByteArray> SEMANTIC_TOKEN_NAMES = {
	"class",
	"enum",
	"parameter",
	"variable",
	"property",
	"enumMember",
	"function",
	"method",
	"keyword",
	"comment",
	"string",
	"number",
	"operator"
};

/**
 * @brief sqtk_to_semtk
 *
 * Convert Squirrel lexer token to SemanticTokenType
 *
 * @param sqtk - lexer token
 * @return
 */
/*
SemanticTokenType lextk_to_semtk(int sqtk) {
	switch (sqtk) {
	case TK_IDENTIFIER:
		return SemanticTokenType::Identifier;

	case TK_STRING_LITERAL:
		return SemanticTokenType::String;

	case TK_INTEGER:
	case TK_FLOAT:
		return SemanticTokenType::Number;

	case TK_EQ:
	case TK_NE:
	case TK_LE:
	case TK_GE:
	case TK_ARROW:
	case TK_AND:
	case TK_OR:
	case TK_NEWSLOT:
	case TK_MODULO:
	case TK_UMINUS:
	case TK_PLUSEQ:
	case TK_MINUSEQ:
	case TK_SHIFTL:
	case TK_SHIFTR:
	case TK_DOUBLE_COLON:
	case TK_PLUSPLUS:
	case TK_MINUSMINUS:
	case TK_VARPARAMS:
	case TK_DIVEQ:
	case TK_MULEQ:
	case TK_MODEQ:
	case TK_ATTR_OPEN:
	case TK_ATTR_CLOSE:
		return SemanticTokenType::Operator;

	case TK_BASE:
	case TK_SWITCH:
	case TK_IF:
	case TK_ELSE:
	case TK_WHILE:
	case TK_BREAK:
	case TK_FOR:
	case TK_DO:
	case TK_NULL:
	case TK_FOREACH:
	case TK_IN:
	case TK_LOCAL:
	case TK_CLONE:
	case TK_FUNCTION:
	case TK_RETURN:
	case TK_TYPEOF:
	case TK_CONTINUE:
	case TK_YIELD:
	case TK_TRY:
	case TK_CATCH:
	case TK_THROW:
	case TK_RESUME:
	case TK_CASE:
	case TK_DEFAULT:
	case TK_THIS:
	case TK_CLASS:
	case TK_EXTENDS:
	case TK_CONSTRUCTOR:
	case TK_INSTANCEOF:
	case TK___LINE__:
	case TK___FILE__:
	case TK_TRUE:
	case TK_FALSE:
	case TK_STATIC:
	case TK_ENUM:
	case TK_CONST:
	case TK_RAWCALL:
		return SemanticTokenType::Keyword;
	}
	return SemanticTokenType::Identifier;
}
*/

#endif // SEMANTICTOKENS_H
