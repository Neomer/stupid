#include "DatabaseBlockIndex.h"
#include <src/core/Logger.h>

DatabaseBlockIndex::DatabaseBlockIndex(QObject *parent) :
	IDatabaseIndex(parent)
{
	LOG_TRACE;
}

quint64 DatabaseBlockIndex::find(QString hash)
{
	LOG_TRACE << hash;
	
	//TODO: сделать бинарный поиск
	
	if (this->isEmpty())
		return -1;
	
	this->begin();
	BlockIndexRecord rec;
	memset(&rec, 0, sizeof(rec));
	do 
	{
		this->readCurrentBlock(&rec);
		if (!memcmp(rec._hash, hash.toUtf8().constData(), CryptoPP::BLAKE2b::DIGESTSIZE))
		{
			return rec._offset;
		}
	}
	while (this->next());
	
	
	return -1;
}

void DatabaseBlockIndex::writeBlock(quint64 offset, QString hash)
{
	LOG_TRACE << offset << hash;
	
	BlockIndexRecord rec;
	rec._offset = offset;
	memcpy(rec._hash, hash.toUtf8().constData(), CryptoPP::BLAKE2b::DIGESTSIZE);
	
	this->end();
	IDatabaseIndex::writeBlock((void *)&rec);
}


