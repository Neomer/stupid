#ifndef PEER_H
#define PEER_H

#include <QObject>
#include <QTcpSocket>

class Peer : public QObject
{
	Q_OBJECT
public:
	explicit Peer(QTcpSocket *socket, QObject *parent = 0);
	
private slots:
	void readBytes();
	
private:
	QTcpSocket *_socket;
};

#endif // PEER_H
