#ifndef SEMANTICTOKENS_H
#define SEMANTICTOKENS_H

#include <QList>
#include <QByteArray>

#include <QtLanguageServer/private/qlanguageserverspectypes_p.h>

#include <squirrel.h>
#include <squirrel/sqobject.h>
#include <squirrel/sqcompiler.h>

using namespace QLspSpecification;

const QList<QByteArray> SEMANTIC_TOKEN_TYPES = {
	"namespace",
	"type",
	"class",
	"enum",
	"interface",
	"struct",
	"typeParameter",
	"parameter",
	"variable",
	"property",
	"enumMember",
	"event",
	"function",
	"method",
	"macro",
	"keyword",
	"modifier",
	"comment",
	"string",
	"number",
	"regexp",
	"operator"
};

// TODO: maybe we can use http://squirrel-lang.org/squirreldoc/reference/language/classes.html#class-attributes
// for some semantic token types

/**
 * @brief sqtk_to_semtk
 *
 * Convert Squirrel lexer token to SemanticTokenType
 *
 * @param sqtk - lexer token
 * @return
 */
std::optional<SemanticTokenTypes> lextkToSemtk(SQInteger sqtk);

#endif // SEMANTICTOKENS_H
