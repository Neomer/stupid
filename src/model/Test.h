#ifndef TEST_H
#define TEST_H

#include <src/core/ISerializable.h>

class Test : public ISerializable
{
	Q_OBJECT
	
	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(QList<Test> list READ list WRITE setList)
	Q_PROPERTY(QList<Test*> listPtr READ listPtr WRITE setListPtr)
	
	QString m_name;
	QList<Test> m_list;
	
	QList<Test*> m_listPtr;

public:
	Test();
	Test(const Test &other);
	Test &operator= (const Test &other); 
	
	QString name() const
	{
		return m_name;
	}
	
	QList<Test> list() const
	{
		return m_list;
	}
	
	
	QList<Test*> listPtr() const
	{
		return m_listPtr;
	}
	
public slots:
	void setName(QString name)
	{
		m_name = name;
	}
	void setList(QList<Test> list)
	{
		m_list = list;
	}
	void setListPtr(QList<Test*> listPtr)
	{
		m_listPtr = listPtr;
	}
};

Q_DECLARE_METATYPE(Test)

#include <src/core/Logger.h>

#include <QDataStream>

QDataStream &operator<<(QDataStream &out, const Test &value)
{
	LOG_TRACE;
    QByteArray u = value.name().toUtf8();
    out << u;
    return out;
}

QDataStream &operator>>(QDataStream &in, Test &value)
{
	LOG_TRACE;
    QByteArray u;
    in >> u;
	value.setName(QString::fromUtf8(u));
    return in;
}


QDataStream &operator<<(QDataStream &out, const QList<Test> &value)
{
	LOG_TRACE;
    QByteArray u;
    out << u;
    return out;
}

QDataStream &operator>>(QDataStream &in, QList<Test> &value)
{
	LOG_TRACE;
    QByteArray u;
	in >> u;
    return in;
}


#endif // TEST_H
