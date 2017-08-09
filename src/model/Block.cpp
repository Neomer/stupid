#include "Block.h"

Block::Block(Block *prev, QObject *parent) : 
	ISerializable(parent),
	_prev(prev)
{
	_blockhash = "dfdfdf";
	_transactions = new TransactionList(this);
}

QList<Transaction *> Block::transactions() 
{ 
	QList<Transaction *> l; 
	l << new Transaction() << new Transaction() << new Transaction(); 
	Transaction * t = new Transaction();
	t->addDeal(new Deal());
	return l;
}

