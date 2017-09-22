QT += core network
QT -= gui

TARGET = stupid
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    src/model/Node.cpp \
    src/core/ConsoleProc.cpp \
    src/core/Logger.cpp \
    src/core/IBus.cpp \
    src/core/EventBroker.cpp \
    src/core/IContext.cpp \
    src/core/App.cpp \
    src/model/Peer.cpp \
    src/model/Account.cpp \
    src/viewmodel/AccountManager.cpp \
    src/model/Transaction.cpp \
    src/viewmodel/NodeSpotter.cpp \
    src/core/db/Database.cpp \
    src/model/Block.cpp \
    src/core/db/IDatabaseRecord.cpp \
    src/core/db/DatabaseInfo.cpp \
    src/core/ICrypto.cpp \
    src/core/ISerializable.cpp \
    src/core/db/IDatabaseIndex.cpp \
    src/core/db/DatabaseBlockIndex.cpp \
    src/model/Deal.cpp

HEADERS += \
    src/model/Node.h \
    src/core/ConsoleProc.h \
    src/core/Logger.h \
    src/core/IBus.h \
    src/core/EventBroker.h \
    src/core/IContext.h \
    src/core/App.h \
    src/model/Peer.h \
    src/model/Account.h \
    src/viewmodel/AccountManager.h \
    src/model/Transaction.h \
    src/core/Singleton.h \
    src/viewmodel/NodeSpotter.h \
    src/core/db/Database.h \
    src/model/Block.h \
    src/core/db/IDatabaseRecord.h \
    src/core/db/DatabaseInfo.h \
    src/core/ICrypto.h \
    src/core/ISerializable.h \
    src/core/db/IDatabaseIndex.h \
    src/core/db/DatabaseBlockIndex.h \
    src/model/Deal.h

INCLUDEPATH += $$PWD

UI_DIR = tmp
OBJECTS_DIR = tmp
MOC_DIR = tmp

#[CryptoPP libs]
unix:!macx {
    LIBS += -L/usr/lib/cryptopp-lib/cryptopp-lib -lcryptopp
    INCLUDEPATH += /usr/lib/cryptopp-lib
}
win32 {
    LIBS += -LC:/cryptopp565/release -lcryptopp
    INCLUDEPATH += C:/cryptopp565
}

#[/CryptopPP]
