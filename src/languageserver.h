#ifndef LANGUAGESERVER_H
#define LANGUAGESERVER_H

#include "squirrelenv.h"
#include "semantichighlighting.h"

#include <QtJsonRpc/private/qjsonrpctransport_p.h>

class LanguageServer : public QObject
{
	Q_OBJECT
public:
	LanguageServer(const QJsonRpcTransport::DataHandler& h,
				   QObject *parent = nullptr);

	QLanguageServer* server() { return &m_server; }

private:
	QLanguageServer m_server;
	SemanticHighlighting m_semantichighlighting;
};

#endif // LANGUAGESERVER_H
