#include "App.h"
#include <src/core/Logger.h>
#include <src/core/IContext.h>

App::App(int argc, char *argv[]) :
	QCoreApplication(argc, argv)
{
	LOG_TRACE;
	busConsole::instance().subscribe("console.input", this);
	busConsole::instance().subscribe("net.newPeer", this);
}

bool App::onCommand(QString command, QVariant data)
{
	LOG_TRACE;
	if (command == "console.input" && data.toString() == "exit")
	{
		busConsole::instance().publish("system.exit");
		Context::instance().unlockMainFolder();
		//this->quit();
		return false;
	}
	else if (command == "net.newPeer") 
	{
		LOG_TRACE << "New peer";
		return false;
	}
	return true;
}

