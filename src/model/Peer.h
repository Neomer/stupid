#ifndef PEER_H
#define PEER_H

#include <QObject>
#include <QTcpSocket>

#include <src/core/EventBroker.h>

class Peer : public QObject, public EventBroker
{
	Q_OBJECT
public:
	explicit Peer(QTcpSocket *socket, QObject *parent = 0);
	
private slots:
	void readBytes();
	
private:
	QTcpSocket *_socket;
	
	// EventBroker interface
protected:
	bool onCommand(QString command, QVariant data);
};

#endif // PEER_H
