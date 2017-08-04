#include <QDebug>
#include <QDir>
#include <stdio.h>
#include <iostream>

#include <cryptopp/base64.h>

#include <src/core/Logger.h>
#include <src/core/ConsoleProc.h>
#include <src/core/IContext.h>
#include <src/core/App.h>
#include <src/model/Node.h>
#include <src/viewmodel/NodeSpotter.h>

using namespace std;
using namespace CryptoPP;

int main(int argc, char *argv[])
{
	App a(argc, argv);
	QString config = a.applicationDirPath().append("/config.conf");
	
	LOG_DEBUG << "Parse command-line arguments...";
	
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "--config"))
		{
			config = argv[i];
		}
		else 
		{
			LOG_WARN << "Unknown argument" << argv[i];
		}
	}
	
	LOG_DEBUG << "Command-line arguments ready";
	
	LOG_DEBUG << "Loading progaram settings...";
	try {
		Context::instance().loadSettings(config);
	}
	catch (std::exception &ex) {
		LOG_DEBUG << "Exception:" << ex.what();
		return -1;
	}
	LOG_DEBUG << "Settings ready";
	
	LOG_DEBUG << "Initializing node...";
	try {
		singletonNode::instance();
	}
	catch (std::exception &ex) {
		LOG_DEBUG << "Exception:" << ex.what();
		return -1;
	}

	LOG_DEBUG << "Node ready";
	
	LOG_DEBUG << "Initializing node-spotter...";
	NodeSpotter nsp(&a);
	LOG_DEBUG << "Node-spotter ready";
	
	return a.exec();
}

