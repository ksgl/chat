#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QRunnable>
#include <QPointF>
#include <QSize>
#include <QAtomicInteger>

/*
namespace chat {
namespace framework {

template <class T>
class Job : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Job(QObject *parent = 0, T processElem = 0);
    virtual ~Job();
    virtual void run() = 0;

signals:
    virtual void jobCompleted() = 0;

public slots:
    virtual void abort() = 0;

private:
    QAtomicInteger<bool> Abort;

};
*/
//}}

#endif // JOB_H
