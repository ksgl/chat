#ifndef FRIENDCONTROLLER_H
#define FRIENDCONTROLLER_H

#include <QObject>
#include <QString>
#include <QScopedPointer>

#include <chat-lib_global.h>
#include <models/friend.h>
#include <models/user-model.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT FriendController : public QObject
{
    Q_OBJECT

public:

    explicit FriendController(QObject* parent = nullptr, models::UserModel* _user = nullptr);
    ~FriendController();

public slots:

    void addFriend(const chat::models::Friend* _friend);
    void addFriend(const QString& reference, const QString& friendName, const QString& friendIp,
                   const models::Friend::eStatus _status, const QDateTime& lastVisit);

    models::Friend* getFriend(const QString& friendReference) const;
    models::Friend* getFriendByName(const QString& friendName) const;
    models::Friend::eStatus getFriendStatus(const QString& friendReference) const;
    QList<models::Friend*>& getFriendList() const;
    QList<models::Friend*>* getFriendListByStatus(const models::Friend::eStatus status) const;

    void changeFriendStatus(const QString& friendReference, const models::Friend::eStatus _newStatus);
    void changeFriendStatus(models::Friend* _friend, const models::Friend::eStatus _newStatus);
    void changeLastVisit(const QString& friendReference, const QDateTime& newLastVisit);
    void changeLastVisit(models::Friend* _friend, const QDateTime& newLastVisit);

signals:

    void friendAdded();
    void statusChanged();
    void lastVisitChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}
#endif // FRIENDCONTROLLER_H
