#ifndef SEMANTICTOKENS_H
#define SEMANTICTOKENS_H

#include <QMap>
#include <QString>

#include <QtLanguageServer/private/qlanguageserverspectypes_p.h>

#include <squirrel.h>
#include <squirrel/sqobject.h>
#include <squirrel/sqcompiler.h>

using namespace QLspSpecification;

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
