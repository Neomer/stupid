#ifndef DATABASEINDEX_H
#define DATABASEINDEX_H

#include <QObject>
#include <QFile>

class IDatabaseIndex : public QObject
{
	Q_OBJECT
	
public:

	explicit IDatabaseIndex(QObject *parent = 0);
	void openFile(QString filename); 
	void close();
	
	bool isEmpty();

protected:
	// [Virtual table] - should be implemented!
	virtual quint32 blockLength() = 0;
	// [/Virtual table]

	void readCurrentBlock(void *buffer);
	void writeBlock(void *block);
	void begin();
	void end();
	bool next();
	bool prev();
	
private:
	QFile _device;
};

#endif // DATABASEINDEX_H
