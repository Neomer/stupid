#ifndef IDATABASERECORD_H
#define IDATABASERECORD_H

#include <QObject>

class IDatabaseRecord : public QObject
{
	Q_OBJECT
	
public:
	explicit IDatabaseRecord(QObject *parent = 0);
	
	QByteArray toDatabaseRecord();
	void fromDatabaseRecord(QByteArray data);
	void setDefaults();
	
};

#endif // IDATABASERECORD_H
