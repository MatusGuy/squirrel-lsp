#include "languageservermodule.h"

LanguageServerModule::LanguageServerModule(QObject* parent):
	QLanguageServerModule(parent)
{}

void LanguageServerModule::registerHandlers(QLanguageServer* server, QLanguageServerProtocol* protocol) {
	m_server = server;
	m_protocol = protocol;
}
