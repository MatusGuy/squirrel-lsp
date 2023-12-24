#ifndef SEMANTICHIGHLIGHTING_H
#define SEMANTICHIGHLIGHTING_H

#include <iostream>

#include <QMap>

#include <QtLanguageServer>
#include <QtLanguageServer/private/qlanguageserver_p.h>

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
};

#endif // SEMANTICHIGHLIGHTING_H
