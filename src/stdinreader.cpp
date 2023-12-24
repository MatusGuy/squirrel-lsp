#include "stdinreader.h"

void StdinReader::run() {
	auto guard = qScopeGuard([this]() { emit eof(); });
	const constexpr qsizetype bufSize = 1024;
	qsizetype bytesInBuf = 0;
	char bufferData[2 * bufSize];
	char *buffer = static_cast<char *>(bufferData);

	auto trySend = [this, &bytesInBuf, buffer]() {
		if (bytesInBuf == 0)
			return;
		qsizetype toSend = bytesInBuf;
		bytesInBuf = 0;
		QByteArray dataToSend(buffer, toSend);
		emit receivedData(dataToSend);
	};
	QHttpMessageStreamParser streamParser(
			[](const QByteArray &, const QByteArray &) { /* just a header, do nothing */ },
			[&trySend](const QByteArray &) {
				// message body
				trySend();
			},
			[&trySend](QtMsgType, QString) {
				// there was an error
				trySend();
			},
			QHttpMessageStreamParser::UNBUFFERED);

	while (std::cin.get(buffer[bytesInBuf])) { // should poll/select and process events
		qsizetype readNow = std::cin.readsome(buffer + bytesInBuf + 1, bufSize) + 1;
		QByteArray toAdd(buffer + bytesInBuf, readNow);
		bytesInBuf += readNow;
		if (bytesInBuf >= bufSize)
			trySend();
		streamParser.receiveData(toAdd);
	}
	trySend();
}
