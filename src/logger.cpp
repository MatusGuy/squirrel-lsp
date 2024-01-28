#include "logger.h"

QString Logger::name() const {
	return "Logger";
}

void Logger::log(MessageType type, QByteArray msg) {
	protocol()->notifyShowMessage({type, msg});
}
