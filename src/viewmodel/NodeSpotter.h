#ifndef NODESPOTTER_H
#define NODESPOTTER_H

#include <QObject>

#include <src/core/EventBroker.h>


///
/// \brief The NodeSpotter class gives functions for searching nodes on the web
///
class NodeSpotter : public QObject, public EventBroker
{
	Q_OBJECT
public:
	explicit NodeSpotter(QObject *parent = 0);
	
signals:
	
public slots:
	///
	/// \brief updatePeers Update peers' list
	///
	void updatePeers();
	
	// EventBroker interface
protected:
	bool onCommand(QString command, QVariant data);
};

#endif // NODESPOTTER_H
