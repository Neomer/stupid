#ifndef ICONTEXT_H
#define ICONTEXT_H

#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDir>
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
	AccountManager * accountManager() const { return _accMgr; }
	ConsoleProc * consoleProcessor() const { return _procConsole; }
	
private:
	IContext(); 
	~IContext(); 
	
	IContext(IContext const&); 
	IContext& operator= (IContext const&); 
	
	AccountManager *_accMgr;
	ConsoleProc *_procConsole;
};

typedef IContext Context;

#endif // ICONTEXT_H
