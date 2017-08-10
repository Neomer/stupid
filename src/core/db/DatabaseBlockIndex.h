#ifndef DATABASEBLOCKINDEX_H
#define DATABASEBLOCKINDEX_H

#include <src/core/db/IDatabaseIndex.h>

#define BLOCK_HASH_SIZE			64

class DatabaseBlockIndex : public IDatabaseIndex
{
	Q_OBJECT
	
public:
	DatabaseBlockIndex(QObject *parent = 0);
	
	///
	/// \brief find search block in index-file. Returns true and offset of block-record in 
	/// the database file if record was found.
	/// \param hash hash of block needed
	/// \param ret offset in bytes of block-record in database file
	/// \return TRUE if record was found, otherwise false
	///
	bool find(QString hash, quint64 *ret = 0);
	bool find(QByteArray hash, quint64 *ret = 0);
	bool writeBlock(quint64 offset, quint64 length, QString hash);

private:
	struct BlockIndexRecord {
		quint64 _offset;
		quint64 _length;
		char _hash[BLOCK_HASH_SIZE];
	};
	
	// IDatabaseIndex interface
protected:
	quint32 blockLength() { return sizeof(BlockIndexRecord); }
};

#endif // DATABASEBLOCKINDEX_H
