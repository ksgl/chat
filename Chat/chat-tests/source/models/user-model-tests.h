#ifndef USERMODELTESTS_H
#define USERMODELTESTS_H

#include <QtTest>
#include <QJsonObject>

#include <models/user-model.h>
#include <test-suite.h>

namespace chat {
namespace models {

class UserModelTests : public TestSuite{
    Q_OBJECT
public:
    UserModelTests();

private slots:

    void constructor_givenParent_setsParentAndDefaultProperties();
    void constructor_givenParentAndJsonObject_setsParentAndProperties();
    void toJson_withDefaultProperties_constructsJson();
    void toJson_withSetProperties_constructsJson();
    void update_givenJsonObject_updatesProperties();
    void update_givenEmptyJsonObject_updatesPropertiesToDefaults();
    void id_givenPrimaryKeyWithNoValue_returnsUuid();
    void id_givenPrimaryKeyWithValue_returnsPrimaryKey();

private:

    void verifyFriends(const QJsonObject& jsonObject);
    void verifyDefaultFriends(const QJsonObject& jsonObject);
    void verifyFriends(const QList<Friend*>& appointments);
    void verifyDefaultFriends(const QList<Friend*>& appointments);

    void verifyChats(const QJsonObject& jsonObject);
    void verifyDefaultChats(const QJsonObject& jsonObject);
    void verifyChats(const QList<ChatModel*>& contacts);
    void verifyDefaultChats(const QList<ChatModel*>& contacts);

    void verifyMessagesChat1(const QJsonObject& jsonObject);
    void verifyMessagesChat2(const QJsonObject& jsonObject);
    void verifyDefaultMessages(const QJsonObject& jsonObject);
    void verifyMessagesChat1(const QList<Message*>& messages);
    void verifyMessagesChat2(const QList<Message*>& messages);
    void verifyDefaultMessages(const QList<Message*>& messages);

    QByteArray jsonByteArray = R"({
                               "reference": "USR0001",
                               "name": "Mr Test Testerson",
                               "publicKey": "h1h1h1h1h1",
                               "friends": [{
                                       "reference": "FR0001",
                                       "friendName": "Frienderson",
                                       "friendIp": "127.01.02.44",
                                       "lastVisit": "2017-08-20T13:00:00",
                                       "status": 1                                 },
                                   {
                                       "reference": "FR0002",
                                       "friendName": "Friend Friend",
                                       "friendIp": "127.01.02.45",
                                       "lastVisit": "2017-08-21T10:30:00",
                                       "status": 2
                                   }
                               ],
                               "chats": [{
                                       "reference": "CHT0001",
                                       "friendInChatReference": "FR0001",
                                       "messages": [{
                                               "reference": "MS0001",
                                               "sender": "FR0001",
                                               "receiver": "USR0001",
                                               "sendAt": "2017-08-20T13:40:00",
                                               "receivedAt": "2017-08-20T13:50:00",
                                               "messageType": 1,
                                               "messageStatus": 3,
                                               "messageData": "Hello!"
                                           },
                                           {
                                               "reference": "MS0002",
                                               "sender": "USR0001",
                                               "receiver": "FR0001",
                                               "sendAt": "2017-08-20T14:00:00",
                                               "receivedAt": "2017-08-20T14:00:00",
                                               "messageType": 2,
                                               "messageStatus": 2,
                                               "messageData": "Hello back!"
                                           }
                                       ]
                                   },
                                   {
                                       "reference": "CHT0002",
                                       "friendInChatReference": "FR0002",
                                       "messages": [{
                                               "reference": "MS0003",
                                               "sender": "USR0001",
                                               "receiver": "FR0002",
                                               "sendAt": "2017-08-20T13:20:00",
                                               "receivedAt": "2017-08-20T13:30:00",
                                               "messageType": 2,
                                               "messageStatus": 3,
                                               "messageData": "Lets Go!"
                                           },
                                           {
                                               "reference": "MS0004",
                                               "sender": "FR0002",
                                               "receiver": "USR0001",
                                               "sendAt": "2017-08-20T13:05:00",
                                               "receivedAt": "2017-08-20T13:10:00",
                                               "messageType": 1,
                                               "messageStatus": 2,
                                               "messageData": "Go!"
                                           }
                                       ]
                                   }
                               ]
                           })";
};



}}

#endif // USERMODELTESTS_H
