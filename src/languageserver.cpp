#include "languageserver.h"

LanguageServer::LanguageServer(const QJsonRpcTransport::DataHandler& h,
							   QObject* parent)
	: QLanguageServer(h, parent)
{
	addServerModule(&Logger::get());

	// force init
	SquirrelEnv::get();

	addServerModule(&m_sync);
	addServerModule(&m_semantichighlighting);
	finishSetup();
}
