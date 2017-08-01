#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

#include <src/model/Peer.h>

class Node : public QTcpServer
{
	Q_OBJECT
	
public:
	explicit Node(QObject *parent = 0);
	
private slots:
	void applyConnection();
	
private:
	QVector<Peer *> _peers;
};

#endif // NODE_H
