#include <QJsonDocument>

#include <cryptopp-lib/cryptlib.h>
#include <cryptopp-lib/hex.h>

#include "ICrypto.h"
#include <src/core/Logger.h>

using namespace CryptoPP;

QByteArray ICrypto::hashBlake2b(const QByteArray &data)
{
	LOG_TRACE << data.count();
	
	BLAKE2b blake;
	byte dig[BLAKE2b::DIGESTSIZE];
	blake.CalculateDigest(dig, (const byte *)data.constData(), data.length());
	
	return QByteArray((const char *)dig, BLAKE2b::DIGESTSIZE);
}

QByteArray ICrypto::hashBlake2b(const QJsonObject &data)
{
	LOG_TRACE;
	QJsonDocument json(data);
	return hashBlake2b(json.toJson());
}

QByteArray ICrypto::hashSHA(const QByteArray &data)
{
	LOG_TRACE << data.count();

	byte digest[SHA256::DIGESTSIZE];
	_sha256.CalculateDigest(digest, (const byte *) data.constData(), data.length());
	
	return QByteArray((const char *)digest, SHA256::DIGESTSIZE);
}

QByteArray ICrypto::hashSHA(const QJsonObject &data)
{
	LOG_TRACE;
	QJsonDocument json(data);
	return hashSHA(json.toJson());
}

QString ICrypto::hex(const QByteArray &data)
{
	LOG_TRACE << data.count();
	
	HexEncoder encoder;
	encoder.Put((const byte*)data.constData(), data.count());
	encoder.MessageEnd();
	
	std::string dig;
	word64 size = encoder.MaxRetrievable();
	if(size)
	{
	    dig.resize(size);		
	    encoder.Get((byte*)dig.data(), dig.size());
	}
	
	return QString::fromStdString(dig);
}

quint16 ICrypto::blockHashSize()
{
	LOG_TRACE;
	return BLAKE2b::DIGESTSIZE;
}

ICrypto::ICrypto()
{
	LOG_TRACE;
	
	
}

ICrypto::~ICrypto()
{
	LOG_TRACE;
}

