#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QThread>

class Logger : public QObject
{
	Q_OBJECT
public:
	explicit Logger(QObject *parent = 0);
	
signals:
	
public slots:
};


#define LOG_INFO	qDebug() 

#define LOG_DEBUG	qDebug() << "DEBUG" \
							 << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") \
							 << (quintptr) QThread::currentThreadId() 

#define LOG_WARN	qDebug() << "WARN " \
							 << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") \
							 << (quintptr) QThread::currentThreadId() 

#define LOG_CRIT	qDebug() << "CRIT " \
							 << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") \
							 << (quintptr) QThread::currentThreadId() 

#ifndef __DISABLE_TRACE__
#define LOG_TRACE	qDebug() << "TRACE" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") \
							 << (quintptr) QThread::currentThreadId() \
							 << Q_FUNC_INFO
#else
#define LOG_TRACE
#endif

#endif // LOGGER_H
