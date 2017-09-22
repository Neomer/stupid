#include "Block.h"
#include <src/core/Logger.h>

Block::Block(Block *prev, QObject *parent) : 
	ISerializable(parent),
	_prev(prev)
{
	
}

void Block::printBlockInfo()
{
	LOG_INFO << "Block info:" << "\n"
			 << "Number:" << this->blockNumber() << "\n"
			 << "Hash:" << this->hash() << "\n"
			 << "Creation time:" << this->dateTimeString() << "\n"
			 << "Previous block:" << this->prevBlockHash() << "\n"
			 << "Transactions:" << this->transactions().count();
}


void Block::deserialize(QJsonObject data)
{
	LOG_TRACE;
	
	ISerializable::deserialize(data);
	if (data.contains("transactions"))
	{
		QList<Transaction *> tl;
		QJsonArray arr = data["transactions"].toArray();
		foreach (QJsonValue val, arr)
		{
			if (val.isObject())
			{
				Transaction *v = new Transaction(this);
				v->deserialize(val.toObject());
				tl.append(v);
			}
			else
				LOG_WARN << "Неизвестное значение!";
			
		}
		setTransactions(tl);
	}
}
