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
    src/model/Deal.cpp \
    src/model/Transaction.cpp \
    src/viewmodel/NodeSpotter.cpp

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
    src/model/Deal.h \
    src/model/Transaction.h \
    src/core/Singleton.h \
    src/viewmodel/NodeSpotter.h

INCLUDEPATH += $$PWD

#cryptopp settings
CRYPTOPP_PATH = /home/user/Документы/QT/cryptopp
LIBS += -L /usr/lib/ -l cryptopp
