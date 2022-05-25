#include "application.h"

#include <iostream>

#include <QStyleFactory>

Application::Application(int &argc, char *argv[])
    : QApplication(argc, argv)
{
    setObjectName("application");
    setStyle(QStyleFactory::create("Fusion"));
}

bool Application::notify(QObject *object, QEvent *event)
{
    try
    {
        return QApplication::notify(object, event);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "unknown exception" << std::endl;
    }

    std::cerr << qPrintable(object->objectName()) << std::endl;
    return false;
}
