#ifndef MODELS_H
#define MODELS_H

#include <QObject>
#include <QProcess>
#include <QCoreApplication>

#include "global_defs.h"
#include "Configurator.h"

/*!
 * \brief Класс исключений
 */
class Exception
{
public:
    Exception(int _err, QString _descr);

    int err;       /*!< Код исключения */
    QString descr; /*!< Описание исключения */

};

/*!
 * \brief Базовый класс для контроллеров
 */
class IController : public QObject
{
    Q_OBJECT
public:
    IController(QObject *parent = nullptr);
    virtual ~IController();
    /*!
     * \brief Инициализация
     * \param Указатель _app
     * \return
     */
    virtual int init(const QCoreApplication *_app) = 0;
    /*!
     * \brief Установка конфигуратора
     * \param value - Экземпляр конфигуратора
     */
    virtual void setConfig(Configurator *value);

signals:
    void message(const QString &_msg, MsgType _type);

protected slots:
    /*!
     * \brief Обработчик сигнала message
     * \param _msg - Сообщения
     * \param _type - Тип сообщения
     */
    virtual void onMessage(QString _msg, MsgType _type);

protected:
    Configurator *pConfig;  /*!< Конфигурация приложения */
    /*!
     * \brief Вызов и выполнение системной команды
     * \param _cmd - Команда
     * \return
     */
    virtual QString runSystemCommand(const QString &_cmd);

};

/*!
 * \brief Базовый класс для контроллеров,
 * работающих в отдельных вычислительных потоках
 */
class IThreadController : public IController
{
    Q_OBJECT
public:
    IThreadController(QObject *parent);
    virtual ~IThreadController();

signals:
    void finished();

protected slots:
    virtual void onStartThread() = 0;
};


#endif // MODELS_H
