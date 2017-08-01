#include <QFile>


#include "Account.h"

#include <src/core/IBus.h>
#include <src/core/Logger.h>
#include <src/core/IContext.h>

#include <cryptopp/rsa.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>

using namespace CryptoPP;

Account::Account(QObject *parent) : QObject(parent)
{
	LOG_TRACE;
}

bool Account::load(QString password)
{
	LOG_TRACE;
}

void Account::create(QString password)
{
	LOG_TRACE;
	
	CryptoPP::AutoSeededRandomPool rng;
	
	InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(rng, 3072);
	
	RSA::PrivateKey privateKey(params);
	RSA::PublicKey publicKey(params);
	
	ByteQueue queue;
	privateKey.Save(queue);
	
	QDir dir("/home/user/.stupid/keystore/");
	if (!dir.exists())
	{
		throw std::runtime_error("Keystore directory not exists!");
	}
	
	FileSink file("/home/user/.stupid/keystore/private_rsa.key");
    queue.CopyTo(file);
    file.MessageEnd();
	
	publicKey.Save(queue);
	FileSink filepub("/home/user/.stupid/keystore/public_rsa.key");
    queue.CopyTo(file);
    filepub.MessageEnd();
	
	LOG_INFO << "Account successfully created!\nKeys has been written!\nPrivate key: /home/user/.stupid/keystore/private_rsa.key\nPublic key: /home/user/.stupid/keystore/public_rsa.key";
}

bool Account::onCommand(QString command, QVariant data)
{
	LOG_TRACE << command << data;
}

