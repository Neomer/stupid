#ifndef ICRYPTO_H
#define ICRYPTO_H

#include <QByteArray>

#include <cryptopp-lib/blake2.h>
#include <cryptopp-lib/sha.h>
#include <cryptopp-lib/md5.h>


class ICrypto
{
public:
	static ICrypto& instance()
    {
        static ICrypto s;
        return s;
    }
	
	QByteArray hashBlake2b(QByteArray &data);
	QByteArray hashMD5(QByteArray &data);
	QByteArray hashSHA(QByteArray &data);
	
	QString hex(QByteArray &data);
	
private:
	ICrypto();
	~ICrypto();
	
	ICrypto(ICrypto const&); 
	ICrypto& operator= (ICrypto const&); 
	
	CryptoPP::SHA256 _sha256;
	CryptoPP::MD5 _md5;
	CryptoPP::BLAKE2b _blake2b;
};

typedef ICrypto Crypto;

#endif // ICRYPTO_H
