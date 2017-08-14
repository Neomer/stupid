#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

#include <src/model/Peer.h>
#include <src/core/EventBroker.h>

class Node : public QTcpServer, public EventBroker
{
	Q_OBJECT
	
public:
	static Node& instance()
    {
        static Node s;
        return s;
    }
	
private slots:
	void applyConnection();
	
private:
	Node();
	~Node();
	
	Node(Node const&); 
	Node& operator= (Node const&); 
	
	QVector<Peer *> _peers;
	
	// EventBroker interface
protected:
	bool onCommand(QString command, QVariant data);
};

typedef Node		singletonNode;

#endif // NODE_H
