#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QObject>
#include <QSettings>
#include <QFile>

#include "global_defs.h"

/*!
 * \brief Конфигуратор приложения
 *
 * Содержит методы для чтения конфигурационных параметров
 */
class Configurator : public QObject
{
    Q_OBJECT
public:
    explicit Configurator(QObject *parent = nullptr);
    quint32 getRefreshTimeout();

    QString getResAddr(const ResName &_resName);
    QString getResLogin(const ResName &_resName);
    QString getResPasswd(const ResName &_resName);

    // IController interface
public:
    int init(const QCoreApplication *_app);

private:
    QSettings *pSettings;
};

#endif // CONFIGURATOR_H
