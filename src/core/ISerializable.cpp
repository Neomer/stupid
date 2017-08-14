#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>

#include "ISerializable.h"

#include <src/core/Logger.h>
#include <src/core/ICrypto.h>

ISerializable::ISerializable(QObject *parent) : 
	QObject(parent)
{
	
}

QJsonObject ISerializable::serialize()
{
	LOG_TRACE;
	
	QJsonObject ret;
	
	const QMetaObject *meta = this->metaObject();
	
	
//	LOG_INFO << "Serialize meta-object:\n" 
//			 << "Name:" << meta->className() << "\n"
//			 << "Super-classes:" << meta->superClass()->className();
	
//	LOG_INFO << "Methods:";
//	for (int i = meta->methodOffset(); i < meta->methodCount(); ++i)
//	{	
//		QMetaMethod prop = meta->method(i);
//		LOG_INFO << QString(prop.name());
//	}		
//	LOG_INFO << "Properties:";
	for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
	{
		QMetaProperty prop = meta->property(i);
		QVariant v = prop.read(this);
//		LOG_INFO << "Property" << prop.name()
//				 << "[ " << prop.typeName() << "] =" 
//				 << v;
		
		if (QString(prop.typeName()).indexOf("QList") == 0)
		{
//			LOG_INFO << "List detected";
			QVariantList vl = v.value<QVariantList>();
			QJsonArray jsonArr;
			foreach (QVariant val, vl)
			{
				ISerializable *obj = qvariant_cast<ISerializable *>(val);
				if (obj)
				{
					QJsonObject jObj = obj->serialize();
					jObj["hash"] = Crypto::instance().hex(Crypto::instance().hashBlake2b(jObj));
					jObj["classname"] = obj->metaObject()->className();
					jsonArr << jObj;
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
				QJsonObject jObj = obj->serialize();
				jObj["hash"] = Crypto::instance().hex(Crypto::instance().hashBlake2b(jObj));
				jObj["classname"] = obj->metaObject()->className();
				ret[ prop.name() ] = jObj;
			}
			else
			{	
				ret[ prop.name() ] = QJsonValue::fromVariant( v );
			}
		}
	}
	ret["hash"] = Crypto::instance().hex(Crypto::instance().hashBlake2b(ret));
	ret["classname"] = this->metaObject()->className();
	
	return ret;
	
//	QJsonDocument json;
//	json.setObject(ret);
	
//	QByteArray ba = json.toJson(QJsonDocument::Compact);
	
//	return ba;

}

void ISerializable::deserialize(QByteArray data)
{
	LOG_TRACE << data.count() << "byte(s)";
	fromJson(this->metaObject(), data);
}

QByteArray ISerializable::toByteArray(const QJsonObject &object)
{
	QJsonDocument json(object);
	return json.toJson(/*QJsonDocument::Compact*/);
}

QObject *ISerializable::fromJson(const QMetaObject *meta, QByteArray &data)
{
	LOG_TRACE;
	
	QJsonParseError err;
	QJsonDocument json = QJsonDocument::fromJson(data, &err);
	if (err.error != QJsonParseError::NoError)
	{
		throw std::runtime_error(QString("Json parsing error! ").append(err.errorString()).toStdString());
	}
	if (!json.isObject())
	{
		throw std::runtime_error("Wrong JSON format");
	}
	auto jsonObject = json.object();
    return fromJson(meta, jsonObject, this);
}

QObject *ISerializable::fromJson(const QMetaObject *meta, QJsonObject &jsonObject, QObject *object)
{
	LOG_TRACE;
	if (!object)
	{
		object = meta->newInstance();
	}
	
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) 
	{
        QMetaProperty property = meta->property(i);
        if (!property.isWritable() || !jsonObject.contains(property.name()))
		{
			continue;
		}
		
        auto value = jsonValueToProperty(object, property, jsonObject.value(property.name()));
        property.write(object, value);
    }
    return object;

}

QVariant ISerializable::jsonValueToProperty(QObject *object, QMetaProperty &property, QJsonValue value)
{
	Q_UNUSED(object);
	LOG_TRACE << QString(property.typeName());
	int type = property.userType();
	type = QMetaType::type(property.typeName());
    if (value.isArray()) 
	{
		QJsonArray arr = value.toArray();
		QVariantList list;
        for (int i = 0; i < arr.count(); i++)
		{
			QJsonValue arrVal = arr.at(i);
			if (arrVal.isObject())
			{
				type = QMetaType::type(arrVal.toObject()["classname"].toString().toUtf8().constData());
				if (type == QMetaType::UnknownType) 
				{
					LOG_WARN << "Unknown type!" << arrVal.toObject()["classname"].toString().toUtf8().constData();
					continue;
				}
			}
			//list << jsonValueToProperty(object, property, arr.at(i));
		}
		return arr;
    } 
	else if (value.isObject()) 
	{
        switch (type) 
		{
        default:
            auto jsonObject = value.toObject();
            return QVariant::fromValue(fromJson(QMetaType::metaObjectForType(type), jsonObject));
            break;
        }
    } 
	else 
	{
        return value.toVariant();
    }
	return QVariant();
}

