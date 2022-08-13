#include "Dispatcher.h"

Dispatcher::Dispatcher(QObject *parent) :
    IController(parent),
    pAppLogger{new AppLogger(this)},
    pAcc{new AutoClickController()},
    pThreadAcc{new QThread()},
    config{new Configurator(this)}
{
    qRegisterMetaType<MsgType>();

    connect(pAppLogger, SIGNAL(message(QString, MsgType)),
            this, SLOT(onMessage(QString, MsgType)));

    connect(this, SIGNAL(message(QString, MsgType)),
            this, SLOT(onMessage(QString, MsgType)));

    initThreadCtrl(pThreadAcc, pAcc);

}

Dispatcher::~Dispatcher()
{
    pAppLogger->deleteLater();
}

int Dispatcher::run()
{
    pAcc->moveToThread(pThreadAcc);
    pThreadAcc->start();

    emit message("Выполнен запуск подсистемы диспетчеризации",
                 MsgType::INFO);

    return ResultCode::ALL_RIGHT;
}

void Dispatcher::stop()
{
    pAppLogger->appendMsg("Завершение работы приложения",
                          MsgType::INFO);

    this->~Dispatcher();
}


void Dispatcher::onMessage(QString _msg, MsgType _type)
{
    pAppLogger->appendMsg(_msg, _type);
}


int Dispatcher::init(const QCoreApplication *_app)
{

    int _res = pAppLogger->init(_app);

    if(_res != ResultCode::ALL_RIGHT)
    {
        return _res;
    }
    else
    {
        emit message("Выполнена инициализация "
                     "подсистемы журналирования",
                     MsgType::INFO);
    }

    _res = config->init(_app);

    if(_res != ResultCode::ALL_RIGHT)
    {
        return _res;
    }

    pAcc->setConfig(config);
    _res = pAcc->init(_app);

    if(_res != ResultCode::ALL_RIGHT)
    {
        return _res;
    }

    emit message("Выполнена инициализация "
                 "подсистемы диспетчеризации",
                 MsgType::INFO);

    return ResultCode::ALL_RIGHT;
}

void Dispatcher::initThreadCtrl(QThread *_thr, IThreadController *_ctrl)
{
    connect(_thr, SIGNAL(started()),
            _ctrl, SLOT(onStartThread()));

    connect(_ctrl, SIGNAL(message(QString, MsgType)),
            this, SLOT(onMessage(QString, MsgType)));

    connect(_ctrl, SIGNAL(finished()),
            _thr, SLOT(quit()));

    connect(_thr, SIGNAL(finished()),
            _ctrl, SLOT(deleteLater()));
}
