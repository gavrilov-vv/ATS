#include <QCoreApplication>

#include "Service.h"

int main(int argc, char *argv[])
{
    Service _service(argc, argv);

    return _service.exec();
}
