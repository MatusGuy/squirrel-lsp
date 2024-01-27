#include "languageservermodule.h"

void LanguageServerModule::registerHandlers(QLanguageServer* server, QLanguageServerProtocol* protocol)
{
	m_server = server;
	m_protocol = protocol;
}
