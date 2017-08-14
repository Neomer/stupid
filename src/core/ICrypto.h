#ifndef ICRYPTO_H
#define ICRYPTO_H

#include <QByteArray>
#include <QJsonObject>

#include <cryptopp-lib/blake2.h>
#include <cryptopp-lib/sha.h>

#define BLOCK_HASH_SIZE		64

class ICrypto
{
public:
	static ICrypto& instance()
    {
        static ICrypto s;
        return s;
    }
	
	QByteArray hashBlake2b(const QByteArray &data);
	QByteArray hashBlake2b(const QJsonObject &data);

	QByteArray hashSHA(const QByteArray &data);
	QByteArray hashSHA(const QJsonObject &data);

	QString hex(const QByteArray &data);
	QByteArray fromHex(const QString &data);
	
	quint16 blockHashSize();
	
private:
	ICrypto();
	~ICrypto();
	
	ICrypto(ICrypto const&); 
	ICrypto& operator= (ICrypto const&); 
	
	CryptoPP::SHA256 _sha256;
	CryptoPP::BLAKE2b _blake2b;
};

typedef ICrypto Crypto;

#endif // ICRYPTO_H
