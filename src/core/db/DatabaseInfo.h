#ifndef DATABASEINFO_H
#define DATABASEINFO_H

#include <src/core/db/IDatabaseRecord.h>


class DatabaseInfo : public IDatabaseRecord
{
	Q_OBJECT
	
	Q_PROPERTY(quint64 preallocatedBytes READ preallocatedBytes WRITE setPreallocatedBytes)
	Q_PROPERTY(quint64 memoryUsed READ memoryUsed WRITE setMemoryUsed)
	Q_PROPERTY(quint32 totalBlocksCount READ totalBlocksCount WRITE setTotalBlocksCount)
	Q_PROPERTY(QString currentFile READ currentFile WRITE setCurrentFile)
	
public:
	DatabaseInfo();
	
	quint64 preallocatedBytes() { return _prealloc; }
	quint64 memoryUsed() { return _memused; }
	quint32 totalBlocksCount() { return _totalblocks; }
	QString currentFile() { return _currFile; }

	void setPreallocatedBytes(quint64 value) { _prealloc = value; }
	void setMemoryUsed(quint64 value) { _memused = value; }
	void setTotalBlocksCount(quint32 value) { _totalblocks = value; }
	void setCurrentFile(QString value) { _currFile = value; }
	
private:
	
	quint64 _prealloc;
	quint64 _memused;
	quint32 _totalblocks;
	QString _currFile;
};

#endif // DATABASEINFO_H
