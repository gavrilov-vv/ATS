#include "AutoClickController.h"

AutoClickController::AutoClickController(QObject *parent) :
    IThreadController(parent),
    updateTimer{new QTimer(this)}
{
    setObjectName("AutoClickController");
    connect(updateTimer, SIGNAL(timeout()),
            this, SLOT(onUpdateTimer()));

}


int AutoClickController::init(const QCoreApplication *_app)
{
    if(!pConfig) return ResultCode::INIT_ERROR;

    QString _path = QString("%1/%2")
                    .arg(_app->applicationDirPath())
                    .arg("scripts/main.py");


    mFile.setFileName(_path);

    if(!mFile.exists())
    {
        return ResultCode::FILE_NOT_EXISTS;
    }

    emit message("Выполнена инициализация подсистемы "
                 "автоподнятия резюме",
                 MsgType::INFO);

    return ResultCode::ALL_RIGHT;
}

void AutoClickController::onStartThread()
{
    // Переводим в миллисекунды
    int _sec = pConfig->getRefreshTimeout() * 1000;

    updateTimer->start(_sec);

    emit message(QString("Выполнен запуск потока подсистемы "
                         "автоподнятия резюме, Timeout=%1").arg(_sec),
                 MsgType::INFO);

    onUpdateTimer();
}



void AutoClickController::onUpdateTimer()
{
    if(mFile.exists())
    {
        try
        {
            QString _cmd = "python3 %1 --clicker hh -l %2 -p %3 -a %4";

            runSystemCommand(_cmd
                             .arg(mFile.fileName())
                             .arg(pConfig->getResLogin(ResName::HH))
                             .arg(pConfig->getResPasswd(ResName::HH))
                             .arg(pConfig->getResAddr(ResName::HH)));

            emit message("Выполнена команда - "
                         "Поднять в поиске.",
                         MsgType::INFO);

        }
        catch (Exception e)
        {
            emit message(e.descr,
                         MsgType::ERROR);
        }

    }
    else
    {
        emit message("Файл скрипта не найден",
                     MsgType::ERROR);
    }
}
