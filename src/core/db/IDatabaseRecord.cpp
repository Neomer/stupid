#include "IDatabaseRecord.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QJsonObject>

#include <src/core/Logger.h>

IDatabaseRecord::IDatabaseRecord(QObject *parent) : 
	ISerializable(parent)
{
	LOG_TRACE;
	

}

QByteArray IDatabaseRecord::toDatabaseRecord()
{
	LOG_TRACE;
	
	QJsonObject ret;
	
	const QMetaObject *meta = this->metaObject();
	
	for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++)
	{
		QMetaProperty prop = meta->property(i);
		
		//LOG_DEBUG << prop.name() << "[" << prop.typeName() << "]";
		
		ret[ prop.name() ] = QJsonValue::fromVariant( prop.read(this) );
	}
	
	QJsonDocument json;
	json.setObject(ret);
	
	QByteArray ba = json.toJson(QJsonDocument::Compact);
	
	return ba;
}

void IDatabaseRecord::fromDatabaseRecord(QByteArray data)
{
	LOG_TRACE << data.count() << "byte(s)";
	
	QJsonDocument json = QJsonDocument::fromJson(data);
	if (json.isEmpty() || json.isNull())
	{
		throw std::runtime_error("Invalid json data!");
	}
	
	QJsonObject obj = json.object();
	
	
	const QMetaObject *meta = this->metaObject();
	
	for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++)
	{
		QMetaProperty prop = meta->property(i);
		
		//LOG_DEBUG << prop.name() << "[" << prop.typeName() << "]";
		
		QJsonValue value;
		if (obj.contains(prop.name()))
		{
			value = obj.value(prop.name());
		}
		else
		{
			continue;
		}
		if (value.isString())
		{
			prop.write(this, value.toString());
		}
		else if (value.isDouble())
		{
			prop.write(this, value.toDouble());
		}
		else if (value.isBool())
		{
			prop.write(this, value.toBool());
		}
		else if (value.isArray() || value.isNull() || value.isObject() || value.isUndefined())
		{
			continue;
		}
		else
		{
			prop.write(this, value.toInt());
		}
	}
	
}

void IDatabaseRecord::setDefaults()
{
	LOG_TRACE;
	
	LOG_DEBUG << "Setup default values...";	
	const QMetaObject *meta = this->metaObject();
	
	for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++)
	{
		QMetaProperty prop = meta->property(i);
		
		switch (prop.type())
		{
			case QVariant::String:
				prop.write(this, "");
				break;
				
			case QVariant::Int: case QVariant::UInt: case QVariant::LongLong: case QVariant::ULongLong:
			case QVariant::Double:
				prop.write(this, 0);
				break;
			
			default:
				continue;
		}
	}
}

