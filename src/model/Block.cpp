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
			 << "Previous block:" << this->prevBlockHash();
}


