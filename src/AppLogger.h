#ifndef APPLOGGER_H
#define APPLOGGER_H

#include <QObject>
#include <QCoreApplication>
#include <QDir>

#include <log4cplus/fileappender.h>
#include <log4cplus/logger.h>
#include <log4cplus/layout.h>
#include <log4cplus/ndc.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/helpers/loglog.h>

#include "global_defs.h"
#include "Models.h"

class AppLogger : public IController
{
    Q_OBJECT
public:
    AppLogger(QObject *parent = nullptr);
    virtual ~AppLogger() final;

    qint32 logAmount() const;
    void setLogAmount(const qint32 &logAmount);
    qint32 maxLogSize() const;
    void setMaxLogSize(const qint32 &maxLogSize);
    QString logFolder() const;
    void setLogFolder(const QString &logFolder);
    bool internalDebugging() const;
    void setInternalDebugging(bool internalDebugging);

    void appendMsg(const QString &_msg, MsgType _type);

private:
    qint32 mLogAmount;       /*!< Максимальное количество хранимых лог-файлов. По-умолчанию = 10 */
    qint32 mMaxLogSize;      /*!< Максимальный размер одного лог-файла. По-умолчанию = 2048 */
    QString mLogFolder;      /*!< Директория для хранения лог-файлов. По-умолчанию = logs */
    bool mInternalDebugging; /*!<  */
    log4cplus::Logger mLog;  /*!<  */


    // IController interface
public:
    int init(const QCoreApplication *_app) override;


};

#endif // APPLOGGER_H
