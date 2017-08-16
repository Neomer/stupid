#ifndef TESTLIST_H
#define TESTLIST_H

#include <QObject>

template <typename T>
class TestList :  public QObject, public QList<T>
{
	Q_OBJECT
	
public:
	TestList() :
		QList<T>() {}
	
	TestList(const TestList &other) :
		QList<T>(other) {}
};

typedef TestList<int> TestListint;

Q_DECLARE_METATYPE(TestListint)

#endif // TESTLIST_H
