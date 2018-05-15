#ifndef FRIEND_H
#define FRIEND_H

#include <QObject>

#include <chat-lib_global.h>
#include <data/enumerator-decorator.h>
#include <data/string-decorator.h>
#include <data/datetime-decorator.h>
#include <data/entity.h>

namespace chat {
namespace models {

class CHATLIBSHARED_EXPORT Friend : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(chat::data::StringDecorator* ui_reference MEMBER reference CONSTANT)
    Q_PROPERTY(chat::data::EnumeratorDecorator* ui_status MEMBER status NOTIFY statusChanged)
    Q_PROPERTY(chat::data::StringDecorator* ui_friendName MEMBER friendName CONSTANT)
    Q_PROPERTY(chat::data::DateTimeDecorator* ui_lastVisit MEMBER lastVisit NOTIFY lastVisitChanged)

public:
    enum eStatus
    {
        Unknown = 0,
        Online,
        Offline
    };

public:
    explicit Friend(QObject* parent = nullptr);
    Friend(QObject *parent, const QJsonObject& json);
    Friend(QObject *parent, const Friend* other);

    Friend(QObject *parent, const QString& newReference,
                            const QString& newFriendName,
                            const QString& newFriendIp,
                            Friend::eStatus newStatus,
                            const QDateTime& newLastVisit);

    data::StringDecorator* reference{nullptr};
    data::EnumeratorDecorator* status{nullptr};
    data::StringDecorator* friendName{nullptr};
    data::StringDecorator* friendIp{nullptr};
    data::DateTimeDecorator* lastVisit{nullptr};

    static std::map<int, QString> statusMapper;
    
signals:

    void friendAdded();
    void statusChanged();
    void lastVisitChanged();
};

}
}


#endif // FRIEND_H
