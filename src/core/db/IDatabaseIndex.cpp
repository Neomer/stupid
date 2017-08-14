
#include "IDatabaseIndex.h"
#include <src/core/Logger.h>

IDatabaseIndex::IDatabaseIndex(QObject *parent) : 
	QObject(parent)
{
	LOG_TRACE;
}

void IDatabaseIndex::openFile(QString filename)
{
	LOG_TRACE << filename;
	
	_device.setFileName(filename);
	if (!_device.exists())
	{
		throw std::runtime_error("File not found!");
	}
	
	if (!_device.open(QIODevice::ReadWrite | QIODevice::Unbuffered))
	{
		throw std::runtime_error("File is busy!");
	}
}

void IDatabaseIndex::close()
{
	LOG_TRACE;
	_device.close();
}

bool IDatabaseIndex::isEmpty()
{
	return _device.size() == 0;
}

void IDatabaseIndex::begin()
{
	//LOG_TRACE;
	_device.seek(0);
}

void IDatabaseIndex::end()
{
	//LOG_TRACE;
	_device.seek(_device.size());
}

bool IDatabaseIndex::next()
{
	//LOG_TRACE;
	if (_device.pos() + blockLength() > _device.size())
	{
		return false;
	}
	return _device.seek(_device.pos() + blockLength());
}

bool IDatabaseIndex::prev()
{
	//LOG_TRACE;
	return _device.seek(_device.pos() - blockLength());
}

void IDatabaseIndex::readCurrentBlock(void *buffer)
{
	//LOG_TRACE;
	_device.read((char *)buffer, blockLength());
}

void IDatabaseIndex::writeBlock(void *block)
{
	//LOG_TRACE;
	_device.write((const char *)block, blockLength());
}

