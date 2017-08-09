#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QObject>
#include <QVariant>

class ISerializable : public QObject
{
	Q_OBJECT
public:
	explicit ISerializable(QObject *parent = 0);
	
	QJsonObject serialize();
	void deserialize(QByteArray data);
	
	static QByteArray toByteArray(const QJsonObject &object);
	
};

#endif // ISERIALIZABLE_H