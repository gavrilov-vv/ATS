#include "Service.h"


Service::Service(int argc, char **argv) :
    QtService<QCoreApplication>(argc, argv, "ATS"),
    dispatcher{new Dispatcher()}
{
    setServiceDescription("Automatic Tools Service");
    setServiceFlags(QtServiceBase::CanBeSuspended);
}

Service::~Service()
{
    dispatcher->deleteLater();
}

void Service::start()
{
    QCoreApplication *app = application();

    int _res = dispatcher->init(app);

    if( _res == ResultCode::ALL_RIGHT)
    {
        _res = dispatcher->run();

        if( _res != ResultCode::ALL_RIGHT)
        {
            app->exit(_res);
        }
    }
    else
    {
        app->exit(_res);
    }
}


void Service::stop()
{
    dispatcher->stop();
}
