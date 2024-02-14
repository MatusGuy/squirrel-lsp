#ifndef LOGGER_H
#define LOGGER_H

#include "languageservermodule.h"
#include "singleton.h"

#define LOGGER_CATEGORY(name, val) static void name(const QString& message) { return get().msg(MessageType::val, message); }

class Logger : public LanguageServerModule, public Singleton<Logger> {
public:
	QString name() const;
	void setupCapabilities(const QLspSpecification::InitializeParams&,
								   QLspSpecification::InitializeResult&) {}

	void msg(MessageType type, QString message);

	LOGGER_CATEGORY(log, Log)
	LOGGER_CATEGORY(info, Info)
	LOGGER_CATEGORY(warning, Warning)
	LOGGER_CATEGORY(error, Error)
};

#endif // LOGGER_H
