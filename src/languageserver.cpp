#include "languageserver.h"

LanguageServer::LanguageServer(const QJsonRpcTransport::DataHandler& h,
							   QObject* parent)
	: QObject(parent)
	, m_server(h, this)
{
	m_server.addServerSemantichighlighting(&m_semantichighlighting);
	m_server.finishSetup();
}
