#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QList>

#include <src/core/db/IDatabaseRecord.h>
#include <src/model/Transaction.h>

class Block : public ISerializable
{
	Q_OBJECT
	
	Q_PROPERTY(QString hash READ hash WRITE setHash)
	Q_PROPERTY(QList<Transaction *> transactions READ transactions WRITE setTransactions)
	Q_PROPERTY(quint64 blockNumber READ blockNumber WRITE setBlockNumber)
	Q_PROPERTY(QString prevBlock READ prevBlockHash WRITE setPrevBlockHash)
	Q_PROPERTY(QString dateTimeString READ dateTimeString WRITE setDateTimeString)
	Q_PROPERTY(Transaction *tt READ tt WRITE setTT)
	
public:
	Q_INVOKABLE Block(Block *prev = 0, QObject *parent = 0);
	
	QString hash() { return _blockHash; }
	void setHash(QString value) { _blockHash = value; }
	
	Block *previous() { return _prev; }
	
	QList<Transaction *> transactions() { return _transactions; }
	void setTransactions(QList<Transaction *> value) { _transactions = value; }
	
	quint64 blockNumber() { return _blockNumber; }
	void setBlockNumber(quint64 value) { _blockNumber = value; } 

	QString prevBlockHash() { return _prevBlockHash; } 
	void setPrevBlockHash(QString value) { _prevBlockHash = value; }
	
	QDateTime dateTime() { return _dateTime; }
	void setDateTime(QDateTime value) { _dateTime = value; }
	
	QString dateTimeString() { return _dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz"); }
	void setDateTimeString(QString value) { _dateTime = QDateTime::fromString(value, "yyyy-MM-dd hh:mm:ss.zzz"); }
	
	void printBlockInfo();
	
	Transaction * tt() const
	{
		return m_tt;
	}
	
public slots:
	void setTT(Transaction * tt)
	{
		m_tt = tt;
	}
	
private:
	QString _blockHash;
	Block *_prev;
	QString _prevBlockHash;
	QList<Transaction *> _transactions;
	quint64 _blockNumber;
	QDateTime _dateTime;
	Transaction * m_tt;
};

#endif // BLOCK_H
