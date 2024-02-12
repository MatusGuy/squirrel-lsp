#include "syncmodule.h"

QString SyncModule::name() const {
	return "Sync";
}

void SyncModule::registerHandlers(QLanguageServer* server, QLanguageServerProtocol* protocol) {
	LanguageServerModule::registerHandlers(server, protocol);

	//protocol->registerDidChangeTextDocumentNotificationHandler([this](const QByteArray &,
	//																  const DidChangeTextDocumentParams& params) {
	//	SquirrelReader::get().sync();
	//});
}

void SyncModule::setupCapabilities(const InitializeParams& clientInfo, InitializeResult& result) {
	result.capabilities.textDocumentSync = TextDocumentSyncKind::Full;
}
