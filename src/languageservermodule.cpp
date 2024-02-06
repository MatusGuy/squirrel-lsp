#include "languageservermodule.h"

void LanguageServerModule::registerHandlers(QLanguageServer* server, QLanguageServerProtocol* protocol) {
	m_server = server;
	m_protocol = protocol;

	protocol->notifyLogMessage({MessageType::Log, QString("Loading %1 module.").arg(name()).toUtf8()});
}
