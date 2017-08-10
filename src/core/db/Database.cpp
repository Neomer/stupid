#include "Database.h"
#include <QDir>

#include <src/core/IBus.h>
#include <src/core/IContext.h>


Database::Database()
{
	LOG_TRACE;
	
	busConsole::instance().subscribe("system.exit", this);
}

Database::~Database()
{
	LOG_TRACE;
}

bool Database::onCommand(QString command, QVariant data)
{
	if (data.isValid())
		LOG_TRACE << command << data;
	else
		LOG_TRACE << command;
	
	if (command == "system.exit")
	{
		close();
	}
	
	return true;
}

bool Database::open(QString path)
{
	LOG_TRACE << path;
	
	if (path.isEmpty())
	{
		path = Context::instance().getDefaultDatabasePath();
	}
	
	QDir dir(path);
	if (!dir.exists())
	{
		LOG_DEBUG << "Database is not created!";
		create(path);
	}

	_finfo.setFileName(dir.absoluteFilePath(".db"));
	if (!_finfo.exists())
	{
		//TODO:  сделать валидное пересоздание файла
		throw std::runtime_error("Database system information file is missing!");
	}

	if (!_finfo.open(QIODevice::ReadWrite))
	{
		throw std::runtime_error("Database system information file is busy by other process!");
	}
	
	_dbi.fromDatabaseRecord(_finfo.readAll());
	
	_file.setFileName(dir.absoluteFilePath(_dbi.currentFile()));
	if (!_file.open(QIODevice::ReadWrite | QIODevice::Unbuffered))
	{
		throw std::runtime_error("Database file is busy by other process!");
	}
	
	
	return true;
}

bool Database::create(QString path)
{
	LOG_TRACE << path;
	
	if (path.isEmpty())
	{
		path = Context::instance().getDefaultDatabasePath();
	}
	
	QDir dir(path);
	if (dir.exists())
	{
		throw std::runtime_error("Database is not empty! You should remove database first!");
	}
	
	if (!dir.mkdir(path))
	{
		throw std::runtime_error("Can't create database folder!");
	}
	
	_finfo.setFileName(dir.absoluteFilePath(".db"));
	if (!_finfo.open(QIODevice::ReadWrite))
	{
		//TODO:  сделать валидное пересоздание файла
		throw std::runtime_error("Database system information file is missing!");
	}
	
	_dbi.setPreallocatedBytes(1000);
	_dbi.setCurrentFile("db.001");
	
	_file.setFileName(dir.absoluteFilePath(_dbi.currentFile()));
	if (!_file.open(QIODevice::ReadWrite))
	{
		throw std::runtime_error("Database file is busy by other process!");
	}
	_file.resize(1000);
	_file.close();

	if (!_finfo.write(_dbi.toDatabaseRecord()))
	{
		throw std::runtime_error("Not all data were written!");
	}

	return true;
}

bool Database::remove(QString path)
{
	LOG_TRACE << path;
	
	if (path.isEmpty())
	{
		path = Context::instance().getDefaultDatabasePath();
	}
	
	QDir dir(path);
	if (!dir.exists())
	{
		throw std::runtime_error("Database is not created!");
	}

	return true;
}

void Database::close()
{
	LOG_TRACE;
	
	_file.close();
}

void Database::appendBlock(Block &block)
{
	LOG_TRACE << block.hash();
	
	_file.seek(0);
	_file.write(ISerializable::toByteArray(block.serialize()));
	
}

std::shared_ptr<Block> Database::findBlock(QString hash)
{
	LOG_TRACE << hash;
	
	std::shared_ptr<Block> ret(new Block());
	ret->deserialize(QByteArray());
	
	return ret;
}

