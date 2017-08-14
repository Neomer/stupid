#ifndef EVENTBROKER_H
#define EVENTBROKER_H

#include <QString>
#include <QVariant>

class EventBroker
{
	friend class IBus;
	
public:
	EventBroker();
	
	///
	/// \brief parseArguments Cтатическая функция. Возращает список аргументов.
	/// \param data
	/// \return 
	///
	static QStringList parseArguments(QString data);
	///
	/// \brief parseMethod Статическая функция. Возвращает наименование метода.
	/// \param data
	/// \return 
	///
	static QString parseMethod(QString data);
	
protected:
	///
	/// \brief onCommand Вызывается в случае получения команды
	/// \param command Команда
	/// \param data Данные
	/// \return TRUE - если системе необходимо послать это сообщение далее по шине
	/// FALSE - если команда персональная и далее ее обработка не требуется
	///
	virtual bool onCommand(QString command, QVariant data = QVariant()) = 0;
};

#endif // EVENTBROKER_H
