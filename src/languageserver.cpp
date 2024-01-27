#include "languageserver.h"

LanguageServer::LanguageServer(const QJsonRpcTransport::DataHandler& h,
							   QObject* parent)
	: QObject(parent)
	, m_server(h, this)
{
	// force init
	SquirrelEnv::get();

	m_server.addServerModule(&m_semantichighlighting);
	m_server.finishSetup();
}
