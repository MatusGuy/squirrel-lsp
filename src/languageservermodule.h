#ifndef LANGUAGESERVERMODULE_H
#define LANGUAGESERVERMODULE_H

#include <qlanguageserver_p.h>

class LanguageServerModule : public QLanguageServerModule
{
public:
	virtual void registerHandlers(QLanguageServer* server,
								  QLanguageServerProtocol* protocol) override;

	inline QLanguageServer* server() { return m_server; }
	inline QLanguageServerProtocol* protocol() { return m_server; }

private:
	QLanguageServer* m_server;
	QLanguageServerProtocol* m_protocol;
};

#endif // LANGUAGESERVERMODULE_H
