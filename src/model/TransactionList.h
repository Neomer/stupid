#ifndef TRANSACTIONLIST_H
#define TRANSACTIONLIST_H

#include <QObject>

#include <src/core/ISerializable.h>
#include <src/model/Transaction.h>

class TransactionList : public ISerializable
{
	Q_OBJECT
	
public:
	explicit TransactionList(QObject *parent = 0);
	TransactionList(const TransactionList &other);
	TransactionList &operator= (TransactionList const&); 
	
	
private:
	QList<Transaction *> _trList;
};

typedef TransactionList *	TransactionListPtr;

Q_DECLARE_METATYPE(TransactionList)
Q_DECLARE_METATYPE(TransactionListPtr)

#endif // TRANSACTIONLIST_H
