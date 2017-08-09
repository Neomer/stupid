#include <cryptopp-lib/cryptlib.h>
#include <cryptopp-lib/hex.h>

#include "ICrypto.h"
#include <src/core/Logger.h>
/*
using namespace CryptoPP;

QByteArray ICrypto::hashBlake2b(QByteArray &data)
{
	LOG_TRACE << data.count();
	
	BLAKE2b blake;
	byte dig[BLAKE2b::DIGESTSIZE];
	blake.CalculateDigest(dig, (const byte *)data.constData(), data.length());
	
	return QByteArray((const char *)dig, BLAKE2b::DIGESTSIZE);
}

QByteArray ICrypto::hashMD5(QByteArray &data)
{
	LOG_TRACE << data.count();
	
	byte digest[MD5::DIGESTSIZE];
	_md5.CalculateDigest(digest, (const byte *) data.constData(), data.length());
	
	return QByteArray((const char *)digest, MD5::DIGESTSIZE);
}

QByteArray ICrypto::hashSHA(QByteArray &data)
{
	LOG_TRACE << data.count();

	byte digest[SHA256::DIGESTSIZE];
	_sha256.CalculateDigest(digest, (const byte *) data.constData(), data.length());
	
	return QByteArray((const char *)digest, SHA256::DIGESTSIZE);
}

QString ICrypto::hex(QByteArray &data)
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
}

ICrypto::ICrypto()
{
	LOG_TRACE;
	
	
}
*/
