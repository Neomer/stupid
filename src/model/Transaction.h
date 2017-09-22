#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include <src/core/ISerializable.h>
#include <src/model/Deal.h>

class Transaction : public ISerializable
{
    Q_OBJECT
	
	Q_PROPERTY(QList<Deal *> deals READ getDeals WRITE setDeals)
	
	QList<Deal *> m_deals;

public:
    Transaction(QObject *parent = 0);
	
	QList<Deal *> getDeals() const
	{
		return m_deals;
	}
	
	void addDeal(Deal *deal);
	
public slots:
	void setDeals(QList<Deal *> deals)
	{
		m_deals = deals;
	}
	
	// ISerializable interface
public:
	void deserialize(QJsonObject data);
};

#endif // TRANSACTION_H
