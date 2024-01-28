#include "languageserver.h"

LanguageServer::LanguageServer(const QJsonRpcTransport::DataHandler& h,
							   QObject* parent)
	: QLanguageServer(h, parent)
{
	// force init
	SquirrelEnv::get();

	addServerModule(&Logger::get());
	addServerModule(&m_sync);

	addServerModule(&m_semantichighlighting);
	finishSetup();
}

QString SyncModule::name() const
{
	return "Sync";
}

void SyncModule::setupCapabilities(const InitializeParams&, InitializeResult& result)
{
	result.capabilities.textDocumentSync = TextDocumentSyncKind::Full;
}
