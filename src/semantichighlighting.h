#ifndef SEMANTICHIGHLIGHTING_H
#define SEMANTICHIGHLIGHTING_H

#include <iostream>

#include <QMap>

#include <QtLanguageServer>
#include <qlanguageserver_p.h>

#include <squirrel.h>
#include <squirrel/sqvm.h>

#include "semantictokens.h"

using namespace QLspSpecification;

class SemanticHighlighting : public QLanguageServerModule {
	Q_OBJECT
public:
	explicit SemanticHighlighting(QObject *parent = nullptr);

	QString name() const;
	void registerHandlers(QLanguageServer* server,
						  QLanguageServerProtocol* protocol);
	void setupCapabilities(const InitializeParams& clientInfo,
						   InitializeResult& result);
	void semanticTokensRequest(const QByteArray&, const SemanticTokensParams& params,
							   LSPPartialResponse<std::variant<SemanticTokens, std::nullptr_t>,
												  SemanticTokensPartialResult>&& resp);
};

#endif // SEMANTICHIGHLIGHTING_H
