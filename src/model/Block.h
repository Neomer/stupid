#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QList>

#include <src/core/db/IDatabaseRecord.h>
#include <src/model/TransactionList.h>
#include <src/model/Transaction.h>

class Block : public ISerializable
{
	Q_OBJECT
	
	Q_PROPERTY(QString hash READ hash)
	Q_PROPERTY(QList<Transaction *> transactions READ transactions)
	Q_PROPERTY(quint64 blockNumber READ blockNumber WRITE setBlockNumber)
	
public:
	Block(Block *prev = 0, QObject *parent = 0);
	
	QString hash() { return _blockHash; }
	Block *previous() { return _prev; }
	QList<Transaction *> transactions() { return _transactions; }
	quint64 blockNumber() { return _blockNumber; }
	void setBlockNumber(quint64 value) { _blockNumber = value; } 
	
private:
	QString _blockHash;
	Block *_prev;
	QList<Transaction *> _transactions;
	quint64 _blockNumber;
};

#endif // BLOCK_H
