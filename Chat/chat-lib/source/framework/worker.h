#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>

class Worker : public QObject {
    Q_OBJECT

public:
    Worker(QObject* parent) : QObject(parent){}
    virtual ~Worker(){}
    virtual void init() = 0;

public slots:
    virtual void process() = 0;

signals:
    virtual void finished() = 0;
    virtual void error(QString err) = 0;

private:
    // add your variables here
};

#endif // WORKER_H
