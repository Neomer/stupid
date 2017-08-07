#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QFile>

#include <src/model/Block.h>
#include <src/core/EventBroker.h>
#include <src/core/db/DatabaseInfo.h>

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
	
private:
	Database();
	~Database();
	
	Database(Database const&); 
	Database& operator= (Database const&); 
	
	QFile _file;
	QFile _finfo;
	
	DatabaseInfo _dbi;
	
	// EventBroker interface
protected:
	bool onCommand(QString command, QVariant data);
};

typedef Database	db;

#endif // DATABASE_H
