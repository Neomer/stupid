#ifndef DATABASEBLOCKINDEX_H
#define DATABASEBLOCKINDEX_H

#include <cryptopp-lib/blake2.h>

#include <src/core/db/IDatabaseIndex.h>


class DatabaseBlockIndex : public IDatabaseIndex
{
	Q_OBJECT
	
public:
	DatabaseBlockIndex(QObject *parent = 0);
	
	quint64 find(QString hash);
	void writeBlock(quint64 offset, QString hash);

private:
	struct BlockIndexRecord {
		quint64 _offset;
		char _hash[CryptoPP::BLAKE2b::DIGESTSIZE];
	};
	
	// IDatabaseIndex interface
protected:
	quint32 blockLength() { return sizeof(BlockIndexRecord); }
};

#endif // DATABASEBLOCKINDEX_H
