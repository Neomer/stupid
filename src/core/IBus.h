#ifndef IBUS_H
#define IBUS_H

#include <QObject>
#include <QMap>
#include <QMutex>

#include <src/core/EventBroker.h>

///
/// \brief The IBus class is `data tube`
///
class IBus
{

public:
	static IBus& instance()
    {
        static IBus s;
        return s;
    }
	
	///
	/// \brief subscribe method allow classes receive incoming events
	/// \param event Event name to receive
	/// \param broker 
	///
	void subscribe(QString event, EventBroker *broker);

	///
	/// \brief unsubscribe Remove catcher from event tube
	/// \param event Event name to receive
	/// \param broker 
	///
	void unsubscribe(QString event, EventBroker *broker);
	
	///
	/// \brief publish sends event on the tube
	/// \param event Event name
	/// \param data Some data
	///
	void publish(QString event, QVariant data = QVariant());
	
	
	
private:
	IBus() {  } 
	~IBus() {  } 
	
	IBus(IBus const&); 
	IBus& operator= (IBus const&); 
	
	QMap<QString, QList<EventBroker *>> _map;
	QMutex _mtx;
};

typedef IBus		busConsole;

#endif // IBUS_H
