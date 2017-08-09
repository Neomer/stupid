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
	Q_PROPERTY(TransactionList * transactions READ transactions)
	
public:
	explicit Block(Block *prev = 0, QObject *parent = 0);
	
	QString hash() { return _blockhash; }
	Block *previous() { return _prev; }
	TransactionList *transactions() { return _transactions; }
	
private:
	QString _blockhash;
	Block *_prev;
	TransactionList *_transactions;
};

#endif // BLOCK_H
