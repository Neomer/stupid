#include <QFile>


#include "Account.h"

#include <src/core/IBus.h>
#include <src/core/Logger.h>
#include <src/core/IContext.h>

#include <cryptopp-lib/rsa.h>
#include <cryptopp-lib/cryptlib.h>
#include <cryptopp-lib/osrng.h>
#include <cryptopp-lib/files.h>
#include <cryptopp-lib/hex.h>

using namespace CryptoPP;

Account::Account(QObject *parent) : QObject(parent)
{
	LOG_TRACE;
}

bool Account::open(QString password)
{
	//TODO: cделать открытие аккаунта
	LOG_TRACE << password; 
	
	return false;
}

void Account::create(QString password)
{
	LOG_TRACE;
	
	CryptoPP::AutoSeededRandomPool rng;
	
	InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(rng, 3072);
	
	RSA::PrivateKey privateKey;
	privateKey.GenerateRandomWithKeySize(rng, 3072);
	RSA::PublicKey publicKey(privateKey);
	
	
	ByteQueue queue;
	privateKey.Save(queue);
	
	QDir dir("/home/user/.stupid/keystore/");
	if (!dir.exists())
	{
		throw std::runtime_error("Keystore directory not exists!");
	}
	
	SHA256 sha;
	byte digest[SHA256::DIGESTSIZE];
	sha.CalculateDigest(digest, 
						(const byte *)password.toUtf8().constData(), 
						password.toUtf8().length());
	HexEncoder encoder;
	encoder.Put(digest, SHA256::DIGESTSIZE);
	encoder.MessageEnd();
	
	std::string pwd;
	word64 size = encoder.MaxRetrievable();
	if(size)
	{
	    pwd.resize(size);		
	    encoder.Get((byte*)pwd.data(), pwd.size());
	}
	;
	
	FileSink file(QString("/home/user/.stupid/keystore/" + QString::fromStdString(pwd) + "_private.key").toUtf8().constData());
    queue.CopyTo(file);
    file.MessageEnd();
	
	publicKey.Save(queue);
	FileSink filepub(QString("/home/user/.stupid/keystore/" + QString::fromStdString(pwd) + "_public.key").toUtf8().constData());
    queue.CopyTo(filepub);
    filepub.MessageEnd();
	
	LOG_INFO << "Account successfully created!\nKeys has been written!\nPrivate key: /home/user/.stupid/keystore/" + QString::fromStdString(pwd) + "_private.key\nPublic key: /home/user/.stupid/keystore/" + QString::fromStdString(pwd) + "_public.key";
}

bool Account::onCommand(QString command, QVariant data)
{
	LOG_TRACE << command << data;
	
	return true;
}

