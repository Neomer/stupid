#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>

#include <src/core/db/IDatabaseRecord.h>

class Block : public IDatabaseRecord
{
	Q_OBJECT
	
	Q_PROPERTY(QString hash READ hash)
	
public:
	explicit Block(QObject *parent = 0);
	
	QString hash() { return _blockhash; }
	
private:
	QString _blockhash;
	
};

#endif // BLOCK_H
