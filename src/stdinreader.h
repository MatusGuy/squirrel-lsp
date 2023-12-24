#ifndef STDINREADER_H
#define STDINREADER_H

#include <iostream>

#include <QObject>

#include <QtJsonRpc>
#include <QtJsonRpc/private/qhttpmessagestreamparser_p.h>

class StdinReader : public QObject {
	Q_OBJECT

public:
	void run();

signals:
	void receivedData(const QByteArray &data);
	void eof();
};

#endif // STDINREADER_H
