#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QObject>

class Thread : public QThread
{
    Q_OBJECT

protected:
    void run()
    {
        //QObject* myObject = new QObject();
        //connect(myObject, &QObject::,
         //       this, &Thread::doWork);
        //exec();
    }

private slots:
    void doWork();
};

#endif // THREAD_H
