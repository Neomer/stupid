#ifndef ICONTEXT_H
#define ICONTEXT_H

#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDir>
#include <QHostAddress>
#include <QList>
#include <QUrl>

#include <src/viewmodel/AccountManager.h>
#include <src/core/ConsoleProc.h>

///
/// \brief The IContext class Application settings and global variables
///
class IContext
{
public:
	static IContext& instance()
    {
        static IContext s;
        return s;
    }
	
	void loadSettings(QString filename = "settings.conf");
	void saveSettings(QString filename = "settings.conf");
	
	AccountManager * accountManager() const { return _accMgr; }
	ConsoleProc * consoleProcessor() const { return _procConsole; }
	
	QHostAddress getNodeHostAddress() { return _nodeHostAddress; }
	quint16 getNodePort() { return _nodePort; }
	QList<QUrl> nodeList() { return _nodeList; }
	void addNode(QUrl node);
	
	QRegExp &getUrlValidator()  { return _urlValidator; }
	QString getDefaultPath();
	QString getDefaultDatabasePath();
	
	///
	/// \brief lockMainFolder Locks main folder for single-access operations
	///
	void lockMainFolder();
	///
	/// \brief unlockMainFolder Unlocks main folder for single-access operations
	///
	void unlockMainFolder();
	///
	/// \brief startTime returns DateTime when program were started
	/// \return 
	///
	QDateTime startTime();

	
private:
	IContext(); 
	~IContext(); 
	
	IContext(IContext const&); 
	IContext& operator= (IContext const&); 
	
	AccountManager *_accMgr;
	ConsoleProc *_procConsole;
	QHostAddress _nodeHostAddress;
	quint16 _nodePort;
	QList<QUrl> _nodeList;
	QRegExp _urlValidator;
	QFile _lockFile;
	QDateTime _startTime;
};

typedef IContext Context;

#endif // ICONTEXT_H
