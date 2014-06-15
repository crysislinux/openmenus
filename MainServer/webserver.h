#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>


class WebServer : public QObject
{
    Q_OBJECT
public:
    explicit WebServer(const QString &param = QString(), QObject *parent = 0);
    ~WebServer();
    void start();
signals:
    
public slots:

private:
    int startWebServer(int argc, char *argv[]);
};

#endif // WEBSERVER_H
