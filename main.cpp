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
#include <src/core/db/Database.h>

using namespace std;
using namespace CryptoPP;

int main(int argc, char *argv[])
{
	App a(argc, argv);
	QString config = a.applicationDirPath().append("/config.conf");
	QString dbpath;
	
	LOG_DEBUG << "Parse command-line arguments...";
	
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "--config"))
		{
			config = argv[i];
		}
		else if (!strcmp(argv[i], "--config"))
		{
			dbpath = argv[i];
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
		Context::instance().lockMainFolder();
	}
	catch (std::exception &ex) {
		LOG_DEBUG << "Exception:" << ex.what();
		return -1;
	}
	LOG_DEBUG << "Settings ready";
	
	LOG_DEBUG << "Initializing database";
	try {
		Database::instance().open();
//		Block b;
//		for (int i = 0; i < 10; i++)
//		{
//			b.setBlockNumber(i);
//			b.setDateTime(QDateTime::currentDateTime());
//			Database::instance().appendBlock(b);
//		}
		
//		Block b;
//		b.setTT(new Transaction());
//		QList<Transaction *> list;
//		Transaction t(&b);
//		Deal d(&t);
//		d.setSender("neomer");
//		d.setRecipient("musor");
//		d.setAmount(4.26);
//		t.addDeal(&d);
//		list.append(&t);
//		b.setTransactions(list);
//		Database::instance().appendBlock(b);
				
		Block block;
		if (Database::instance().findBlock("cb8b27eb8e633b727e446ff6a7808700afd46f1f4c7a9553bd911f2da3abe022fb6f58b8ab544169b24463d67c8d2b6ef06f8e2804e9a9fa8567611e4bfefcab", &block))
		{
			block.printBlockInfo();
		}
		else
		{
			LOG_INFO << "Block not found!";
		}
	}
	catch (std::exception &ex) {
		LOG_CRIT << "Exception:" << ex.what();
		return -1;
	}

	LOG_DEBUG << "database ready";
	
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

