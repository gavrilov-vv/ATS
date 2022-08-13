#ifndef AUTOCLICKCONTROLLER_H
#define AUTOCLICKCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QFile>

#include "global_defs.h"
#include "Configurator.h"
#include "Models.h"

/*!
 * \brief Робот
 */
class AutoClickController : public IThreadController
{
    Q_OBJECT
public:
    explicit AutoClickController(QObject *parent = nullptr);

    // IController interface
public:
    int init(const QCoreApplication *_app) override;

    // IThreadController interface
protected slots:
    void onStartThread() override;

private:
    QTimer *updateTimer;    /*!< Таймер срабатывания робота */
    QFile mFile;            /*!< Файл со скриптами */


private slots:
    /*!
     * \brief Обработчик срабатывания таймера
     */
    void onUpdateTimer();
};

#endif // AUTOCLICKCONTROLLER_H
