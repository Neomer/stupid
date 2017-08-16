#include "Test.h"
#include <src/core/Logger.h>

Test::Test() :
	ISerializable()
{
	LOG_TRACE;
}

Test::Test(const Test &other) :
	ISerializable()
{
	LOG_TRACE;
	
	m_name = other.m_name;
	m_list = other.m_list;
	m_listPtr = other.m_listPtr;
}

Test &Test::operator=(const Test &other)
{
	LOG_TRACE;
	
	m_name = other.m_name;
	m_list = other.m_list;
	m_listPtr = other.m_listPtr;
	
	return *this;
}


