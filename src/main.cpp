#include <iostream>

#include <QCoreApplication>
#include <QTimer>
#include <QThreadPool>
#include <QMutex>

#include <QtJsonRpc/private/qhttpmessagestreamparser_p.h>

#include "stdinreader.h"
#include "languageserver.h"

int main(int argc, char* argv[]) {
	QCoreApplication app(argc, argv);

	QMutex writeMutex;
	auto handler = [&writeMutex](const QByteArray &data) {
		QMutexLocker l(&writeMutex);
		std::cout.write(data.constData(), data.size());
		std::cout.flush();
	};
	LanguageServer srv(handler);
	StdinReader r;
	QObject::connect(&r, &StdinReader::receivedData,
					 &srv, &QLanguageServer::receiveData);
	QObject::connect(&r, &StdinReader::eof, &app, [&app]() {
		QTimer::singleShot(100, &app, []() {
			QCoreApplication::processEvents();
			QCoreApplication::exit();
		});
	});
	QThreadPool::globalInstance()->start([&r]() { r.run(); });

	return app.exec();
}
