#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>

#include "qtservice.h"
#include "Dispatcher.h"

class Service : public  QtService<QCoreApplication>
{
public:
    explicit Service(int argc, char **argv);
    ~Service();


    // QtServiceBase interface
protected:
    void start() override;
    void stop() override;

private:
    Dispatcher *dispatcher;
};

#endif // SERVICE_H
