#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QFile>
#include <memory>

#include <src/model/Block.h>
#include <src/core/EventBroker.h>
#include <src/core/db/DatabaseInfo.h>
#include <src/core/db/DatabaseBlockIndex.h>

class Database : public EventBroker
{
	
public:
	static Database& instance()
    {
        static Database s;
        return s;
    }
	
	bool open(QString path = "");
	bool create(QString path = "");
	bool remove(QString path = "");
	void close();
	
	void appendBlock(Block &block);
	std::shared_ptr<Block> findBlock(QString hash);
	
private:
	Database();
	~Database();
	
	Database(Database const&); 
	Database& operator= (Database const&); 
	
	QFile _file;
	QFile _finfo;
	
	DatabaseInfo _dbi;
	DatabaseBlockIndex *_blockIndex;
	
	// EventBroker interface
protected:
	bool onCommand(QString command, QVariant data);
};

typedef Database	db;

#endif // DATABASE_H
