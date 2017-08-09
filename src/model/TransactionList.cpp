#include "TransactionList.h"

#include <src/core/Logger.h>

TransactionList::TransactionList(QObject *parent) : 
	ISerializable(parent)
{
	LOG_TRACE;
}

TransactionList::TransactionList(const TransactionList &other) :
	ISerializable(other.parent())
{
	LOG_TRACE;
}

TransactionList &TransactionList::operator=(const TransactionList &)
{
	LOG_TRACE;
	return *this;
}


