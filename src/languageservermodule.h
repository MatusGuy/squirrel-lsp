#ifndef LANGUAGESERVERMODULE_H
#define LANGUAGESERVERMODULE_H

#include <functional>

#include <qlanguageserver_p.h>

using namespace QLspSpecification;

using namespace std::placeholders;
#define REQ_HANDLER(func, ...) std::bind(&func, this, __VA_ARGS__)

class LanguageServerModule : public QLanguageServerModule
{
public:
	explicit LanguageServerModule(QObject* parent = nullptr);

	virtual void registerHandlers(QLanguageServer* server,
								  QLanguageServerProtocol* protocol) override;

	QLanguageServer* server() { return m_server; }
	QLanguageServerProtocol* protocol() { return m_protocol; }

protected:
	QLanguageServer* m_server = nullptr;
	QLanguageServerProtocol* m_protocol = nullptr;
};

#endif // LANGUAGESERVERMODULE_H
