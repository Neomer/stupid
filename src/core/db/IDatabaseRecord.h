#ifndef IDATABASERECORD_H
#define IDATABASERECORD_H

#include <QObject>

#include <src/core/ISerializable.h>

class IDatabaseRecord : public ISerializable
{
	Q_OBJECT
	
public:
	explicit IDatabaseRecord(QObject *parent = 0);
	
	QByteArray toDatabaseRecord();
	void fromDatabaseRecord(QByteArray data);
	void setDefaults();
	
};

#endif // IDATABASERECORD_H
