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

void ISerializable::deserialize(QJsonObject data)
{
	LOG_TRACE;
	
	const QMetaObject *meta = this->metaObject();
	
	for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) 
	{
        QMetaProperty property = meta->property(i);
        if (!property.isWritable() || !data.contains(property.name()))
		{
			continue;
		}
		
        auto value = jsonValueToProperty(property, data.value(property.name()));
        property.write(this, value);
    }
}

QByteArray ISerializable::toByteArray(const QJsonObject &object, bool compact)
{
	LOG_TRACE;
	QJsonDocument json(object);
	if (compact)
		return json.toJson(QJsonDocument::Compact);
	else
		return json.toJson();
}

QJsonObject ISerializable::fromByteArray(const QByteArray &data)
{
	LOG_TRACE;
	QJsonParseError err;
	QJsonDocument json = QJsonDocument::fromJson(data, &err);
	if (err.error != QJsonParseError::NoError)
	{
		LOG_CRIT << err.errorString();
		throw std::runtime_error("Json corrupted! View logs form detailed information!");
	}
	if (!json.isObject())
	{
		LOG_CRIT << "Json is not object!";
		throw std::runtime_error("Json is not object!");
	}
	return json.object();
}


QVariant ISerializable::jsonValueToProperty(QMetaProperty &property, QJsonValue value)
{
	LOG_TRACE << QString(property.typeName());
	int type = property.userType();

	if (value.isArray()) 
	{
		QString sType = QString(property.typeName());
		if (sType.indexOf("QList") == 0) 
		{
			sType = sType.mid(6, sType.length() - 7);
		}
		type = QMetaType::type(sType.toUtf8().constData());
		if (type == QMetaType::UnknownType)
		{
			LOG_WARN << "Unregistered type" << sType;
			return QVariant();
		}
		QJsonArray arr = value.toArray();
		QVariantList list;
        for (int i = 0; i < arr.count(); i++)
		{
			const QMetaObject *o = QMetaType::metaObjectForType(type);
			ISerializable *iSer = qobject_cast<ISerializable *>(o->newInstance());
			if (!iSer)
			{
				LOG_CRIT << "Can't create QObject!";
				return QVariant();
			}
			
			QJsonValue arrVal = arr.at(i);
			if (arrVal.isObject())
			{
				iSer->deserialize(arrVal.toObject());
				if (type == QMetaType::UnknownType) 
				{
					LOG_WARN << "Unknown type!" << arrVal.toObject()["classname"].toString().toUtf8().constData();
					continue;
				}
				list << QVariant::fromValue(iSer);
			}
		}
		return list;
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

