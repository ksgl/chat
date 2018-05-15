#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QScopedPointer>

#include <models/user-model.h>
#include <models/chat-model.h>
#include <models/message.h>
#include <models/friend.h>

namespace chat {
namespace controllers {

class DatabaseController : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseController(QObject *parent = nullptr);
    ~DatabaseController();

    //bool createUserTable(const UserModel* );
    bool addFriend();

signals:

public slots:
};

}
}

#endif // DATABASECONTROLLER_H
