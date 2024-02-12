#ifndef SYNCMODULE_H
#define SYNCMODULE_H

#include "languageservermodule.h"

#include "squirrelreader.h"

class SyncModule : public LanguageServerModule {
public:
	QString name() const override;
	void registerHandlers(QLanguageServer* server, QLanguageServerProtocol* protocol) override;
	void setupCapabilities(const InitializeParams&, InitializeResult& result) override;
};

#endif // SYNCMODULE_H
