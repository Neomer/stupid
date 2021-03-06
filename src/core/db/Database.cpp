#include "Database.h"
#include <QDir>

#include <src/core/IBus.h>
#include <src/core/IContext.h>


Database::Database()
{
	LOG_TRACE;
	
	_blockIndex = new DatabaseBlockIndex();
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
	
	_blockIndex->openFile(Context::instance().getDefaultDatabaseDirectory().absoluteFilePath(".index"));
	
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
	
	_dbi.setPreallocatedBytes(0);
	_dbi.setCurrentFile("db.001");
	
	_file.setFileName(dir.absoluteFilePath(_dbi.currentFile()));
	if (!_file.open(QIODevice::ReadWrite))
	{
		throw std::runtime_error("Database file is busy by other process!");
	}
	_file.resize(0);
	_file.close();

	if (!_finfo.write(_dbi.toDatabaseRecord()))
	{
		throw std::runtime_error("Not all data were written!");
	}

	_file.setFileName(Context::instance().getDefaultDatabaseDirectory().absoluteFilePath(".index"));
	if (!_file.open(QIODevice::ReadWrite))
	{
		throw std::runtime_error("Database file is busy by other process!");
	}
	_file.close();
	
	
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
	
	//TODO: сделать заполнение хэша в модели
	QJsonObject jObj = block.serialize();
	QByteArray baObj = ISerializable::toByteArray(jObj);

	if (_blockIndex->writeBlock(_file.size(), baObj.size(), jObj["hash"].toString()))
	{
		_file.seek(_file.size());
		_file.write(baObj);
	}
	else
	{
		LOG_CRIT << "Block already exists!";
		return;
	}
}

bool Database::findBlock(QString hash, Block* ret)
{
	LOG_TRACE << hash;
	
	DatabaseBlockIndex::BlockIndexRecord index;
	if (_blockIndex->find(hash, &index))
	{
		if (ret)
		{
			_file.seek(index._offset);
			ret->deserialize(ISerializable::fromByteArray(_file.read(index._length)));
		}
		return true;
	}
	
	return false;
}

