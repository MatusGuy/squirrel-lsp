#ifndef LOGGER_H
#define LOGGER_H

#include "languageservermodule.h"
#include "singleton.h"

class Logger : public LanguageServerModule, public Singleton<Logger>
{
public:
	QString name() const;
	void setupCapabilities(const QLspSpecification::InitializeParams&,
								   QLspSpecification::InitializeResult&) {}

	void log(MessageType type, QByteArray msg);
};

#endif // LOGGER_H
