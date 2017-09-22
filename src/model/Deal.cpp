#include "Deal.h"
#include <src/core/Logger.h>

Deal::Deal(QObject *parent) : 
	ISerializable(parent)
{
	LOG_TRACE;
}

Deal::Deal(const Deal &other) : 
	ISerializable(other.parent())
{
	LOG_TRACE;
}

Deal &Deal::operator=(const Deal &)
{
	return *this;
}

QString Deal::getSender() const
{
	return m_sender;
}

QString Deal::getRecipient() const
{
	return m_recipient;
}

double Deal::getAmount() const
{
	return m_amount;
}

void Deal::setSender(QString sender)
{
	m_sender = sender;
}

void Deal::setRecipient(QString recipient)
{
	m_recipient = recipient;
}

void Deal::setAmount(double amount)
{
	m_amount = amount;
}

