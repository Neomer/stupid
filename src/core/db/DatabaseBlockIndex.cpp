#include "DatabaseBlockIndex.h"
#include <src/core/Logger.h>

DatabaseBlockIndex::DatabaseBlockIndex(QObject *parent) :
	IDatabaseIndex(parent)
{
	LOG_TRACE;
}

bool DatabaseBlockIndex::find(QString hash, BlockIndexRecord *ret)
{
	LOG_TRACE << hash;
	return find(QByteArray::fromHex(hash.toUtf8()), ret);
}

bool DatabaseBlockIndex::find(QByteArray hash, BlockIndexRecord *ret)
{
	LOG_TRACE << hash.count() << "byte(s)";

	//TODO: сделать бинарный поиск
	
	if (this->isEmpty())
		return false;
	
	this->begin();
	BlockIndexRecord rec;
	memset(&rec, 0, sizeof(rec));
	do 
	{
		this->readCurrentBlock(&rec);
		if (!memcmp(rec._hash, hash.constData(), BLOCK_HASH_SIZE))
		{
			LOG_DEBUG << "Block was found!" 
					  << "Offset:" << rec._offset
					  << "Size:" << rec._length;
			if (ret)
			{
				*ret = rec;
			}
			return true;
		}
	}
	while (this->next());
	
	
	return false;
}

bool DatabaseBlockIndex::writeBlock(quint64 offset, quint64 length, QString hash)
{
	LOG_TRACE << offset << hash;
	
	QByteArray baHash = QByteArray::fromHex(hash.toUtf8());
	
	if (find(baHash))
	{
		return false;
	}
	
	BlockIndexRecord rec;
	rec._offset = offset;
	rec._length = length;
	memcpy(rec._hash, baHash.constData(), BLOCK_HASH_SIZE);
	
	
	//TODO: сделать сортировку для бинарного поиска
	this->end();
	IDatabaseIndex::writeBlock((void *)&rec);
	return true;
}


