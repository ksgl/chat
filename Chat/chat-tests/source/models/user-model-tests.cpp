#include "user-model-tests.h"

#include <QString>
#include <QtTest>

#include <QJsonArray>
#include <QJsonDocument>

#include <models/user-model.h>

using namespace chat::models;

namespace chat {
namespace models { // Structors

static UserModelTests instance;

UserModelTests::UserModelTests()
    : TestSuite( "UserModelTests" )
{
}

}

namespace models { // Tests

void UserModelTests::constructor_givenParent_setsParentAndDefaultProperties()
{
    UserModel userModelTest(this);

    QCOMPARE(userModelTest.parent(), this);
    QCOMPARE(userModelTest.reference->value(), QString(""));
    QCOMPARE(userModelTest.name->value(), QString(""));
    QCOMPARE(userModelTest.publicKey->value(), QString(""));

    verifyDefaultFriends(userModelTest.friends->derivedEntities());
    verifyDefaultChats(userModelTest.chats->derivedEntities());
}

void UserModelTests::constructor_givenParentAndJsonObject_setsParentAndProperties()
{
    UserModel testUserModel(this, QJsonDocument::fromJson(jsonByteArray).object());

    QCOMPARE(testUserModel.parent(), this);
    QCOMPARE(testUserModel.reference->value(), QString("USR0001"));
    QCOMPARE(testUserModel.name->value(), QString("Mr Test Testerson"));
    QCOMPARE(testUserModel.publicKey->value(), QString("h1h1h1h1h1"));

    verifyFriends(testUserModel.friends->derivedEntities());
    verifyChats(testUserModel.chats->derivedEntities());
}

void UserModelTests::toJson_withDefaultProperties_constructsJson()
{
    UserModel testUserModel(this);

    QJsonDocument jsonDoc(testUserModel.toJson());

    QVERIFY(jsonDoc.isObject());

    QJsonObject jsonObject = jsonDoc.object();

    QVERIFY(jsonObject.contains("reference"));
    QCOMPARE(jsonObject.value("reference").toString(), QString(""));
    QVERIFY(jsonObject.contains("name"));
    QCOMPARE(jsonObject.value("name").toString(), QString(""));
    QVERIFY(jsonObject.contains("publicKey"));
    QCOMPARE(jsonObject.value("publicKey").toString(), QString(""));

    verifyDefaultFriends(jsonObject);
    verifyDefaultChats(jsonObject);
}

void UserModelTests::toJson_withSetProperties_constructsJson()
{
    UserModel testUserModel(this, QJsonDocument::fromJson(jsonByteArray).object());

    QCOMPARE(testUserModel.reference->value(), QString("USR0001"));
    QCOMPARE(testUserModel.name->value(), QString("Mr Test Testerson"));
    QCOMPARE(testUserModel.publicKey->value(), QString("h1h1h1h1h1"));

    verifyFriends(testUserModel.friends->derivedEntities());
    verifyChats(testUserModel.chats->derivedEntities());

    QJsonDocument jsonDoc(testUserModel.toJson());

    QVERIFY(jsonDoc.isObject());

    QJsonObject jsonObject = jsonDoc.object();

    QVERIFY(jsonObject.contains("reference"));
    QCOMPARE(jsonObject.value("reference").toString(), QString("USR0001"));
    QVERIFY(jsonObject.contains("name"));
    QCOMPARE(jsonObject.value("name").toString(), QString("Mr Test Testerson"));
    QVERIFY(jsonObject.contains("publicKey"));
    QCOMPARE(jsonObject.value("publicKey").toString(), QString("h1h1h1h1h1"));

    verifyFriends(jsonObject);
    verifyChats(jsonObject);
}

void UserModelTests::update_givenJsonObject_updatesProperties()
{
    UserModel testUserModel(this);

    testUserModel.update(QJsonDocument::fromJson(jsonByteArray).object());

    QCOMPARE(testUserModel.reference->value(), QString("USR0001"));
    QCOMPARE(testUserModel.name->value(), QString("Mr Test Testerson"));
    QCOMPARE(testUserModel.publicKey->value(), QString("h1h1h1h1h1"));

    verifyFriends(testUserModel.friends->derivedEntities());
    verifyChats(testUserModel.chats->derivedEntities());
}

void UserModelTests::update_givenEmptyJsonObject_updatesPropertiesToDefaults()
{
    UserModel testUserModel(this, QJsonDocument::fromJson(jsonByteArray).object());

    QCOMPARE(testUserModel.reference->value(), QString("USR0001"));
    QCOMPARE(testUserModel.name->value(), QString("Mr Test Testerson"));
    QCOMPARE(testUserModel.publicKey->value(), QString("h1h1h1h1h1"));

    verifyFriends(testUserModel.friends->derivedEntities());
    verifyChats(testUserModel.chats->derivedEntities());

    testUserModel.update(QJsonObject());

    QCOMPARE(testUserModel.reference->value(), QString(""));
    QCOMPARE(testUserModel.name->value(), QString(""));

    verifyDefaultFriends(testUserModel.friends->derivedEntities());
    verifyDefaultChats(testUserModel.chats->derivedEntities());
}

void UserModelTests::id_givenPrimaryKeyWithNoValue_returnsUuid()
{
    UserModel testUserModel(this);

    // Using individual character checks
    QCOMPARE(testUserModel.id().left(1), QString("{"));
    QCOMPARE(testUserModel.id().mid(9, 1), QString("-"));
    QCOMPARE(testUserModel.id().mid(14, 1), QString("-"));
    QCOMPARE(testUserModel.id().mid(19, 1), QString("-"));
    QCOMPARE(testUserModel.id().mid(24, 1), QString("-"));
    QCOMPARE(testUserModel.id().right(1), QString("}"));

    // Using regular expression pattern matching
    QVERIFY(QRegularExpression("\\{.{8}-(.{4})-(.{4})-(.{4})-(.{12})\\}").match(testUserModel.id()).hasMatch());
}

void UserModelTests::id_givenPrimaryKeyWithValue_returnsPrimaryKey()
{
    UserModel testUserModel(this, QJsonDocument::fromJson(jsonByteArray).object());
    QCOMPARE(testUserModel.reference->value(), QString("USR0001"));
    QCOMPARE(testUserModel.id(), testUserModel.reference->value());
}

void UserModelTests::verifyFriends(const QJsonObject& jsonObject)
{
    QVERIFY(jsonObject.contains("friends"));
    QJsonArray friends = jsonObject.value("friends").toArray();

    QCOMPARE(friends.size(), 2);
    QVERIFY(friends.at(0).isObject());
    QVERIFY(friends.at(1).isObject());

    QJsonObject friend1 = (friends.at(0).toObject());
    QVERIFY(friend1.contains("reference"));
    QCOMPARE(friend1.value("reference").toString(), QString("FR0001"));
    QVERIFY(friend1.contains("friendName"));
    QCOMPARE(friend1.value("friendName").toString(), QString("Frienderson"));
    QVERIFY(friend1.contains("friendIp"));
    QCOMPARE(friend1.value("friendIp").toString(), QString("127.01.02.44"));
    QVERIFY(friend1.contains("lastVisit"));
    QCOMPARE(friend1.value("lastVisit").toString(), QString("2017-08-20T13:00:00"));
    QVERIFY(friend1.contains("status"));
    QCOMPARE(friend1.value("status").toInt(), static_cast<int>(Friend::eStatus::Online));

    QJsonObject friend2 = (friends.at(1).toObject());
    QVERIFY(friend2.contains("reference"));
    QCOMPARE(friend2.value("reference").toString(), QString("FR0002"));
    QVERIFY(friend2.contains("friendName"));
    QCOMPARE(friend2.value("friendName").toString(), QString("Friend Friend"));
    QVERIFY(friend2.contains("friendIp"));
    QCOMPARE(friend2.value("friendIp").toString(), QString("127.01.02.45"));
    QVERIFY(friend2.contains("lastVisit"));
    QCOMPARE(friend2.value("lastVisit").toString(), QString("2017-08-21T10:30:00"));
    QVERIFY(friend2.contains("status"));
    QCOMPARE(friend2.value("status").toInt(), static_cast<int>(Friend::eStatus::Offline));

}

void UserModelTests::verifyDefaultFriends(const QJsonObject& jsonObject)
{
    QVERIFY(jsonObject.contains("friends"));
    QJsonArray friends = jsonObject.value("friends").toArray();

    QCOMPARE(friends.size(), 0);
}

void UserModelTests::verifyFriends(const QList<Friend*>& friends)
{
    QCOMPARE(friends.size(), 2);

    QCOMPARE(friends.size(), 2);
    QCOMPARE(friends.at(0)->reference->value(), QString("FR0001"));
    QCOMPARE(friends.at(0)->friendName->value(), QString("Frienderson"));
    QCOMPARE(friends.at(0)->friendIp->value(), QString("127.01.02.44"));
    QCOMPARE(friends.at(0)->lastVisit->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 0)));
    QCOMPARE(friends.at(0)->status->value(), static_cast<int>(Friend::eStatus::Online));

    QCOMPARE(friends.at(1)->reference->value(), QString("FR0002"));
    QCOMPARE(friends.at(1)->friendName->value(), QString("Friend Friend"));
    QCOMPARE(friends.at(1)->friendIp->value(), QString("127.01.02.45"));
    QCOMPARE(friends.at(1)->lastVisit->value(), QDateTime(QDate(2017, 8, 21), QTime(10, 30)));
    QCOMPARE(friends.at(1)->status->value(), static_cast<int>(Friend::eStatus::Offline));
}

void UserModelTests::verifyDefaultFriends(const QList<Friend*>& friends)
{
    QCOMPARE(friends.size(), 0);
}

void UserModelTests::verifyChats(const QJsonObject& jsonObject)
{
    QVERIFY(jsonObject.contains("chats"));
    QJsonArray chats = jsonObject.value("chats").toArray();

    QCOMPARE(chats.size(), 2);
    QVERIFY(chats.at(0).isObject());
    QVERIFY(chats.at(1).isObject());

    QJsonObject chat1 = (chats.at(0).toObject());
    QVERIFY(chat1.contains("reference"));
    QCOMPARE(chat1.value("reference").toString(), QString("CHT0001"));
    QVERIFY(chat1.contains("friendInChatReference"));
    QCOMPARE(chat1.value("friendInChatReference").toString(), QString("FR0001"));
    verifyMessagesChat1(chat1);

    QJsonObject chat2 = (chats.at(1).toObject());
    QVERIFY(chat2.contains("reference"));
    QCOMPARE(chat2.value("reference").toString(), QString("CHT0002"));
    QVERIFY(chat2.contains("friendInChatReference"));
    QCOMPARE(chat2.value("friendInChatReference").toString(), QString("FR0002"));
    verifyMessagesChat2(chat2);
}

void UserModelTests::verifyDefaultChats(const QJsonObject& jsonObject)
{
    QVERIFY(jsonObject.contains("chats"));
    QJsonArray chats = jsonObject.value("chats").toArray();

    QCOMPARE(chats.size(), 0);
}

void UserModelTests::verifyChats(const QList<ChatModel*>& chats)
{
    QCOMPARE(chats.size(), 2);
    QCOMPARE(chats.at(0)->reference->value(), QString("CHT0001"));
    QCOMPARE(chats.at(0)->friendInChatReference->value(), QString("FR0001"));
    verifyMessagesChat1(chats.at(0)->messages->derivedEntities());

    QCOMPARE(chats.at(1)->reference->value(), QString("CHT0002"));
    QCOMPARE(chats.at(1)->friendInChatReference->value(), QString("FR0002"));
    verifyMessagesChat2(chats.at(1)->messages->derivedEntities());
}

void UserModelTests::verifyDefaultChats(const QList<ChatModel*>& chats)
{
    QCOMPARE(chats.size(), 0);
}

void UserModelTests::verifyMessagesChat1(const QJsonObject& jsonObject)
{
    QVERIFY(jsonObject.contains("messages"));
    QJsonArray messages = jsonObject.value("messages").toArray();

    QCOMPARE(messages.size(), 2);
    QVERIFY(messages.at(0).isObject());
    QVERIFY(messages.at(1).isObject());

    QJsonObject message1 = (messages.at(0).toObject());
    QVERIFY(message1.contains("reference"));
    QCOMPARE(message1.value("reference").toString(), QString("MS0001"));
    QVERIFY(message1.contains("sender"));
    QCOMPARE(message1.value("sender").toString(), QString("FR0001"));
    QVERIFY(message1.contains("receiver"));
    QCOMPARE(message1.value("receiver").toString(), QString("USR0001"));
    QVERIFY(message1.contains("sendAt"));
    QCOMPARE(message1.value("sendAt").toString(), QString("2017-08-20T13:40:00"));
    QVERIFY(message1.contains("receivedAt"));
    QCOMPARE(message1.value("receivedAt").toString(), QString("2017-08-20T13:50:00"));
    QVERIFY(message1.contains("messageType"));
    QCOMPARE(message1.value("messageType").toInt(), static_cast<int>(Message::eMessageType::Incoming));
    QVERIFY(message1.contains("messageStatus"));
    QCOMPARE(message1.value("messageStatus").toInt(), static_cast<int>(Message::eMessageStatus::Read));
    QVERIFY(message1.contains("messageData"));
    QCOMPARE(message1.value("messageData").toString(), QString("Hello!"));

    QJsonObject message2 = (messages.at(1).toObject());
    QVERIFY(message2.contains("reference"));
    QCOMPARE(message2.value("reference").toString(), QString("MS0002"));
    QVERIFY(message2.contains("sender"));
    QCOMPARE(message2.value("sender").toString(), QString("USR0001"));
    QVERIFY(message2.contains("receiver"));
    QCOMPARE(message2.value("receiver").toString(), QString("FR0001"));
    QVERIFY(message2.contains("sendAt"));
    QCOMPARE(message2.value("sendAt").toString(), QString("2017-08-20T14:00:00"));
    QVERIFY(message2.contains("receivedAt"));
    QCOMPARE(message2.value("receivedAt").toString(), QString("2017-08-20T14:00:00"));
    QVERIFY(message2.contains("messageType"));
    QCOMPARE(message2.value("messageType").toInt(), static_cast<int>(Message::eMessageType::Outgoing));
    QVERIFY(message2.contains("messageStatus"));
    QCOMPARE(message2.value("messageStatus").toInt(), static_cast<int>(Message::eMessageStatus::Delivered));
    QVERIFY(message2.contains("messageData"));
    QCOMPARE(message2.value("messageData").toString(), QString("Hello back!"));
}

void UserModelTests::verifyMessagesChat2(const QJsonObject& jsonObject)
{
    QVERIFY(jsonObject.contains("messages"));
    QJsonArray messages = jsonObject.value("messages").toArray();

    QCOMPARE(messages.size(), 2);
    QVERIFY(messages.at(0).isObject());
    QVERIFY(messages.at(1).isObject());

    QJsonObject message1 = (messages.at(0).toObject());
    QVERIFY(message1.contains("reference"));
    QCOMPARE(message1.value("reference").toString(), QString("MS0003"));
    QVERIFY(message1.contains("sender"));
    QCOMPARE(message1.value("sender").toString(), QString("USR0001"));
    QVERIFY(message1.contains("receiver"));
    QCOMPARE(message1.value("receiver").toString(), QString("FR0002"));
    QVERIFY(message1.contains("sendAt"));
    QCOMPARE(message1.value("sendAt").toString(), QString("2017-08-20T13:20:00"));
    QVERIFY(message1.contains("receivedAt"));
    QCOMPARE(message1.value("receivedAt").toString(), QString("2017-08-20T13:30:00"));
    QVERIFY(message1.contains("messageType"));
    QCOMPARE(message1.value("messageType").toInt(), static_cast<int>(Message::eMessageType::Outgoing));
    QVERIFY(message1.contains("messageStatus"));
    QCOMPARE(message1.value("messageStatus").toInt(), static_cast<int>(Message::eMessageStatus::Read));
    QVERIFY(message1.contains("messageData"));
    QCOMPARE(message1.value("messageData").toString(), QString("Lets Go!"));

    QJsonObject message2 = (messages.at(1).toObject());
    QVERIFY(message2.contains("reference"));
    QCOMPARE(message2.value("reference").toString(), QString("MS0004"));
    QVERIFY(message2.contains("sender"));
    QCOMPARE(message2.value("sender").toString(), QString("FR0002"));
    QVERIFY(message2.contains("receiver"));
    QCOMPARE(message2.value("receiver").toString(), QString("USR0001"));
    QVERIFY(message2.contains("sendAt"));
    QCOMPARE(message2.value("sendAt").toString(), QString("2017-08-20T13:05:00"));
    QVERIFY(message2.contains("receivedAt"));
    QCOMPARE(message2.value("receivedAt").toString(), QString("2017-08-20T13:10:00"));
    QVERIFY(message2.contains("messageType"));
    QCOMPARE(message2.value("messageType").toInt(), static_cast<int>(Message::eMessageType::Incoming));
    QVERIFY(message2.contains("messageStatus"));
    QCOMPARE(message2.value("messageStatus").toInt(), static_cast<int>(Message::eMessageStatus::Delivered));
    QVERIFY(message2.contains("messageData"));
    QCOMPARE(message2.value("messageData").toString(), QString("Go!"));
}

void UserModelTests::verifyDefaultMessages(const QJsonObject& jsonObject)
{
    QVERIFY(jsonObject.contains("messages"));
    QJsonArray messages = jsonObject.value("messages").toArray();

    QCOMPARE(messages.size(), 0);
}

void UserModelTests::verifyMessagesChat1(const QList<Message*>& messages)
{
    QCOMPARE(messages.size(), 2);

    QCOMPARE(messages.at(0)->reference->value(), QString("MS0001"));
    QCOMPARE(messages.at(0)->sender->value(), QString("FR0001"));
    QCOMPARE(messages.at(0)->receiver->value(), QString("USR0001"));
    QCOMPARE(messages.at(0)->sendAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 40)));
    QCOMPARE(messages.at(0)->receivedAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 50)));
    QCOMPARE(messages.at(0)->messageType->value(), static_cast<int>(Message::eMessageType::Incoming));
    QCOMPARE(messages.at(0)->messageStatus->value(), static_cast<int>(Message::eMessageStatus::Read));
    QCOMPARE(messages.at(0)->messageData->value(), QString("Hello!"));

    QCOMPARE(messages.at(1)->reference->value(), QString("MS0002"));
    QCOMPARE(messages.at(1)->sender->value(), QString("USR0001"));
    QCOMPARE(messages.at(1)->receiver->value(), QString("FR0001"));
    QCOMPARE(messages.at(1)->sendAt->value(), QDateTime(QDate(2017, 8, 20), QTime(14, 00)));
    QCOMPARE(messages.at(1)->receivedAt->value(), QDateTime(QDate(2017, 8, 20), QTime(14, 00)));
    QCOMPARE(messages.at(1)->messageType->value(), static_cast<int>(Message::eMessageType::Outgoing));
    QCOMPARE(messages.at(1)->messageStatus->value(), static_cast<int>(Message::eMessageStatus::Delivered));
    QCOMPARE(messages.at(1)->messageData->value(), QString("Hello back!"));
}

void UserModelTests::verifyMessagesChat2(const QList<Message*>& messages)
{
    QCOMPARE(messages.size(), 2);

    QCOMPARE(messages.at(0)->reference->value(), QString("MS0003"));
    QCOMPARE(messages.at(0)->sender->value(), QString("USR0001"));
    QCOMPARE(messages.at(0)->receiver->value(), QString("FR0002"));
    QCOMPARE(messages.at(0)->sendAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 20)));
    QCOMPARE(messages.at(0)->receivedAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 30)));
    QCOMPARE(messages.at(0)->messageType->value(), static_cast<int>(Message::eMessageType::Outgoing));
    QCOMPARE(messages.at(0)->messageStatus->value(), static_cast<int>(Message::eMessageStatus::Read));
    QCOMPARE(messages.at(0)->messageData->value(), QString("Lets Go!"));

    QCOMPARE(messages.at(1)->reference->value(), QString("MS0004"));
    QCOMPARE(messages.at(1)->sender->value(), QString("FR0002"));
    QCOMPARE(messages.at(1)->receiver->value(), QString("USR0001"));
    QCOMPARE(messages.at(1)->sendAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 05)));
    QCOMPARE(messages.at(1)->receivedAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 10)));
    QCOMPARE(messages.at(1)->messageType->value(), static_cast<int>(Message::eMessageType::Incoming));
    QCOMPARE(messages.at(1)->messageStatus->value(), static_cast<int>(Message::eMessageStatus::Delivered));
    QCOMPARE(messages.at(1)->messageData->value(), QString("Go!"));
}

void UserModelTests::verifyDefaultMessages(const QList<Message*>& messages)
{
    QCOMPARE(messages.size(), 0);
}


}
}
