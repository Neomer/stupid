#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>

class ISerializable : public QObject
{
	Q_OBJECT
public:
	explicit ISerializable(QObject *parent = 0);
	
	QJsonObject serialize();
	virtual void deserialize(QJsonObject data);
	
	static QByteArray toByteArray(const QJsonObject &object, bool compact = true);
	static QJsonObject fromByteArray(const QByteArray &data);
	
private:
	QObject *fromJson(const QMetaObject *meta, QByteArray& data);
	QObject *fromJson(QJsonObject& jsonObject);
	QVariant jsonValueToProperty(QMetaProperty& property, QJsonValue value);
};

typedef QList<int>		QIntList;

Q_DECLARE_METATYPE(QIntList)

#endif // ISERIALIZABLE_H
