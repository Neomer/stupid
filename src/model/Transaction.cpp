#include "Transaction.h"
#include <src/core/Logger.h>

Transaction::Transaction(QObject *parent) : 
	ISerializable(parent)
{
	LOG_TRACE;
}

void Transaction::addDeal(Deal *deal)
{
	m_deals.append(deal);
}


void Transaction::deserialize(QJsonObject data)
{
	LOG_TRACE;
	ISerializable::deserialize(data);
	if (data.contains("deals"))
	{
		QList<Deal *> tl;
		QJsonArray arr = data["deals"].toArray();
		foreach (QJsonValue val, arr)
		{
			if (val.isObject())
			{
				Deal *v = new Deal();
				v->deserialize(val.toObject());
				tl.append(v);
			}
			else
				LOG_WARN << "Неизвестное значение!";
			
		}
		setDeals(tl);
	}
}
