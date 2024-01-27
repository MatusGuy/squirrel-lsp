#ifndef SEMANTICHIGHLIGHTING_H
#define SEMANTICHIGHLIGHTING_H

#include <iostream>

#include <QMap>
#include <QFile>

#include <QtLanguageServer>
#include <qlanguageserver_p.h>

#include <squirrel.h>
#include <squirrel/sqvm.h>

#include "squirrelenv.h"
#include "semantictokens.h"

using namespace QLspSpecification;

//TODO: "Modules" namespace
class SemanticHighlighting : public QLanguageServerModule {
	Q_OBJECT
public:
	explicit SemanticHighlighting(QObject *parent = nullptr);

	QString name() const;
	void registerHandlers(QLanguageServer* server,
						  QLanguageServerProtocol* protocol);
	void setupCapabilities(const InitializeParams& clientInfo,
						   InitializeResult& result);
	static void semanticTokensRequest(const QByteArray&, const SemanticTokensParams& params,
							   LSPPartialResponse<std::variant<SemanticTokens, std::nullptr_t>,
												  SemanticTokensPartialResult>&& resp);
};

#endif // SEMANTICHIGHLIGHTING_H
