#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QDataStream>
#include <QThread>
#include <QProcess>


namespace ResultCode
{
    static const int ALL_RIGHT       = 0;
    static const int ERROR           = 1;
    static const int INIT_ERROR      = 2;
    static const int MKDIR_ERROR     = 3;
    static const int EXEC_ERROR      = 4;
    static const int FILE_NOT_EXISTS = 5;
}

enum class ResName : quint32
{
    UNDEF  = 0,
    HH     = 1,
    YA     = 2,
    GOOGLE = 3,
};

enum class MsgType : quint8
{
    UNDEF   = 0,
    INFO    = 1,
    ERROR   = 2,
    DEBUG   = 3,
    WARNING = 4
};



#endif // GLOBAL_DEFS_H
