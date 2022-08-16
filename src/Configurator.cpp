#include "Configurator.h"

Configurator::Configurator(QObject *parent) :
    QObject(parent),
    pSettings{nullptr}
{

}

quint32 Configurator::getRefreshTimeout()
{
    int _rt = 100;

    if(pSettings)
    {
        pSettings->beginGroup("App");
        _rt = pSettings->value("refresh_timeout", 120).toInt();
        pSettings->endGroup();
    }

    return _rt;
}

QString Configurator::getResAddr(const ResName &_resName)
{
    QString _groupName = "UNDEF";
    QString _value = "UNDEF";

    if(pSettings)
    {
        switch (_resName) {
        case ResName::HH:
            _groupName = "HH";
            break;
        case ResName::YA:
            _groupName = "YA";
            break;
        default:
            break;
        }

        pSettings->beginGroup(_groupName);
        _value = pSettings->value("address", "UNDEF").toString();
        pSettings->endGroup();
    }

    return _value;
}

QString Configurator::getResLogin(const ResName &_resName)
{
    QString _groupName = "UNDEF";
    QString _value = "UNDEF";

    if(pSettings)
    {
        switch (_resName) {
        case ResName::HH:
            _groupName = "HH";
            break;
        case ResName::YA:
            _groupName = "YA";
            break;
        default:
            break;
        }

        pSettings->beginGroup(_groupName);
        _value = pSettings->value("login", "UNDEF").toString();
        pSettings->endGroup();
    }

    return _value;
}

QString Configurator::getResPasswd(const ResName &_resName)
{
    QString _groupName = "UNDEF";
    QString _value = "UNDEF";

    if(pSettings)
    {
        switch (_resName) {
        case ResName::HH:
            _groupName = "HH";
            break;
        case ResName::YA:
            _groupName = "YA";
            break;
        default:
            break;
        }

        pSettings->beginGroup(_groupName);
        _value = pSettings->value("password", "UNDEF").toString();
        pSettings->endGroup();
    }

    return _value;
}


int Configurator::init(const QCoreApplication *_app)
{
    QString _fileName = _app->applicationDirPath().append("/ats.conf");

    QFile _f(_fileName);

    if(_f.exists())
    {
        pSettings = new QSettings(_fileName, QSettings::IniFormat);
    }
    else
    {
        return ResultCode::FILE_NOT_EXISTS;
    }


    return ResultCode::ALL_RIGHT;
}
