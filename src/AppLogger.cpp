#include "AppLogger.h"


AppLogger::AppLogger(QObject *parent) : IController(parent),
    mLogAmount{10},
    mMaxLogSize{2048},
    mLogFolder("logs"),
    mInternalDebugging(false)
{

}

AppLogger::~AppLogger()
{

}

void AppLogger::appendMsg(const QString &_msg, MsgType _type)
{
    switch (_type) {
    case MsgType::DEBUG:
        LOG4CPLUS_DEBUG(mLog, _msg.toLocal8Bit().data());
        break;
    case MsgType::ERROR:
        LOG4CPLUS_ERROR(mLog, _msg.toLocal8Bit().data());
        break;
    case MsgType::INFO:
        LOG4CPLUS_INFO(mLog, _msg.toLocal8Bit().data());
        break;
    case MsgType::WARNING:
        LOG4CPLUS_WARN(mLog, _msg.toLocal8Bit().data());
        break;
    default:
        break;
    }
}

bool AppLogger::internalDebugging() const
{
    return mInternalDebugging;
}

void AppLogger::setInternalDebugging(bool internalDebugging)
{
    mInternalDebugging = internalDebugging;
}

QString AppLogger::logFolder() const
{
    return mLogFolder;
}

void AppLogger::setLogFolder(const QString &logFolder)
{
    mLogFolder = logFolder;
}

qint32 AppLogger::maxLogSize() const
{
    return mMaxLogSize;
}

void AppLogger::setMaxLogSize(const qint32 &maxLogSize)
{
    mMaxLogSize = maxLogSize;
}

qint32 AppLogger::logAmount() const
{
    return mLogAmount;
}

void AppLogger::setLogAmount(const qint32 &logAmount)
{
    mLogAmount = logAmount;
}

int AppLogger::init(const QCoreApplication *_app)
{
    // Путь к директории c исполняемым файлом
    QString _appDir = _app->applicationDirPath();
    // Путь к директории c журналами
    QString _dirPath = QString("%1/%2").arg(_appDir).arg(mLogFolder);

    QDir _d(_dirPath);

    if(!_d.exists())
    {
        if(!_d.mkpath(_dirPath))
        {
            return ResultCode::MKDIR_ERROR;
        }
    }

    QString _name = "ATS";

    QString _path = QString("%1/%2.log").arg(_dirPath).arg(_name);

    log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(mInternalDebugging);
    log4cplus::SharedAppenderPtr appender(new log4cplus::RollingFileAppender(_path.toStdString(),
                                                                             (mMaxLogSize * 100) * 1024,
                                                                              mLogAmount));

    appender->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(LOG4CPLUS_TEXT("%d %-5p %c %x - %m%n"))));
    appender->setName(LOG4CPLUS_TEXT("Common"));

    mLog = log4cplus::Logger::getInstance(_name.toStdString());
    mLog.addAppender(appender);

    return ResultCode::ALL_RIGHT;
}
