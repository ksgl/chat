#ifndef SERVICECONTROLLER_H
#define SERVICECONTROLLER_H

#include <QObject>

class ServiceController : public QObject
{
    Q_OBJECT
public:
    explicit ServiceController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SERVICECONTROLLER_H