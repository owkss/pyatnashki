#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int &argc, char *argv[]);
    bool notify(QObject *object, QEvent *event) override;
};

#endif // APPLICATION_H
