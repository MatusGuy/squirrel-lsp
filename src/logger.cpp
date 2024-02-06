#include "logger.h"

QString Logger::name() const {
	return "Logger";
}

void Logger::log(MessageType type, QString msg) {
	protocol()->notifyShowMessage({type, msg.toUtf8()});
}
