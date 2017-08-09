#include "Block.h"

Block::Block(Block *prev, QObject *parent) : 
	ISerializable(parent),
	_prev(prev)
{
	_blockhash = "dfdfdf";
	_transactions = new TransactionList(this);
}

