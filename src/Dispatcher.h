#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>

#include "global_defs.h"
#include "AppLogger.h"
#include "AutoClickController.h"
#include "Configurator.h"
#include "Models.h"

class Dispatcher : public IController
{
    Q_OBJECT
public:
    explicit Dispatcher(QObject *parent = nullptr);
    ~Dispatcher();
    /*!
     * \brief Запуск подсистемы диспетчеризации
     * \return
     */
    int run();
    /*!
     * \brief Останов подсистемы диспетчеризации
     */
    void stop();

protected slots:
    void onMessage(QString _msg, MsgType _type) override;

    // IController interface
public:
    int init(const QCoreApplication *_app) override;

private:
    AppLogger *pAppLogger;     /*!< Логгер */
    AutoClickController *pAcc; /*!< Робот */
    QThread *pThreadAcc;       /*!< Поток для робота */
    Configurator *config;      /*!< Экземпляр конфигуратора приложения */
    /*!
     * \brief Метод для инициализации сигнально-слотовых соединений
     * контроллера
     * \param _thr - Экземпляр потока
     * \param _ctrl - Экземпляр контроллера
     */
    void initThreadCtrl(QThread *_thr, IThreadController *_ctrl);
};

Q_DECLARE_METATYPE(MsgType)

#endif // DISPATCHER_H
