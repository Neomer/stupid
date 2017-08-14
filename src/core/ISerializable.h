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
	
private:
	QObject *fromJson(const QMetaObject *meta, QByteArray& data);
	QObject *fromJson(const QMetaObject* meta, QJsonObject& jsonObject, QObject *object = 0);
	QVariant jsonValueToProperty(QObject* object, QMetaProperty& property, QJsonValue value);
};

typedef QList<int>		QIntList;

Q_DECLARE_METATYPE(QIntList)

#endif // ISERIALIZABLE_H
