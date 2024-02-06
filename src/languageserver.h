#ifndef LANGUAGESERVER_H
#define LANGUAGESERVER_H

#include "squirrelenv.h"

#include "syncmodule.h"
#include "semantichighlighting.h"

#include <QJsonObject>

#include <QtJsonRpc/private/qjsonrpctransport_p.h>

class LanguageServer : public QLanguageServer {
public:
	LanguageServer(const QJsonRpcTransport::DataHandler& h,
				   QObject *parent = nullptr);

private:
	SyncModule m_sync;
	SemanticHighlighting m_semantichighlighting;
};

#endif // LANGUAGESERVER_H
