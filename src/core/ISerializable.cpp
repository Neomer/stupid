#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>

#include "ISerializable.h"
#include <src/core/Logger.h>

ISerializable::ISerializable(QObject *parent) : 
	QObject(parent)
{
	
}

QJsonObject ISerializable::serialize()
{
	LOG_TRACE;
	
	QJsonObject ret;
	
	const QMetaObject *meta = this->metaObject();
	
	
	LOG_INFO << "Serialize meta-object:\n" 
			 << "Name:" << meta->className() << "\n"
			 << "Super-classes:" << meta->superClass()->className();
	
	LOG_INFO << "Methods:";
	for (int i = meta->methodOffset(); i < meta->methodCount(); ++i)
	{	
		QMetaMethod prop = meta->method(i);
		LOG_INFO << QString(prop.name());
	}		
	LOG_INFO << "Properties:";
	for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
	{
		QMetaProperty prop = meta->property(i);
		QVariant v = prop.read(this);
		LOG_INFO << "Property" << prop.name()
				 << "[ " << prop.typeName() << "] =" 
				 << v;
		
		if (QString(prop.typeName()).indexOf("QList") == 0)
		{
			LOG_INFO << "List detected";
			QVariantList vl = v.value<QVariantList>();
			QJsonArray jsonArr;
			foreach (QVariant val, vl)
			{
				ISerializable *obj = qvariant_cast<ISerializable *>(val);
				if (obj)
				{
					jsonArr << obj->serialize();
				}
				else
				{	
					jsonArr << QJsonValue::fromVariant( val );
				}
				ret[ prop.name() ] = jsonArr;
			}
		}
		else
		{
			ISerializable *obj = qvariant_cast<ISerializable *>(v);
			if (obj)
			{
				ret[ prop.name() ] = obj->serialize();
			}
			else
			{	
				ret[ prop.name() ] = QJsonValue::fromVariant( v );
			}
		}
	}
	
	return ret;
	
//	QJsonDocument json;
//	json.setObject(ret);
	
//	QByteArray ba = json.toJson(QJsonDocument::Compact);
	
//	return ba;

}

void ISerializable::deserialize(QByteArray data)
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

QByteArray ISerializable::toByteArray(const QJsonObject &object)
{
	QJsonDocument json(object);
	return json.toJson(QJsonDocument::Compact);
}

