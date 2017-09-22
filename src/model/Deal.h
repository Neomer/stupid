#ifndef DEAL_H
#define DEAL_H

#include <QObject>

#include <src/model/Account.h>
#include <src/core/ISerializable.h>

class Deal : public ISerializable
{
	Q_OBJECT
	
	Q_PROPERTY(QString sender READ getSender WRITE setSender)
	Q_PROPERTY(QString recipient READ getRecipient WRITE setRecipient)
	Q_PROPERTY(double amount READ getAmount WRITE setAmount)
	
	QString m_sender;
	QString m_recipient;
	double m_amount;
	
public:
	Q_INVOKABLE  Deal(QObject *parent = 0);
	Q_INVOKABLE Deal(const Deal &other);
	Deal &operator= (Deal const&); 
	
	QString getSender() const;
	QString getRecipient() const;
	double getAmount() const;
	
public slots:
	void setSender(QString sender);
	void setRecipient(QString recipient);
	void setAmount(double amount);
};

Q_DECLARE_METATYPE(Deal)

#endif // DEAL_H
