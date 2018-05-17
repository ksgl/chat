#include "message-controller-tests.h"

#include <QSignalSpy>

using namespace chat::models;

namespace chat {
namespace controllers { // Instance

static MessageControllerTests instance;

MessageControllerTests::MessageControllerTests()
    : TestSuite( "MessageControllerTests" )
{
}

}

namespace controllers { // Scaffolding

void MessageControllerTests::initTestCase()
{
}

void MessageControllerTests::cleanupTestCase()
{
}

void MessageControllerTests::init()
{
    testUser = new models::UserModel(this, QJsonDocument::fromJson(jsonByteArray).object());
    messageController = new MessageController(this, testUser);
}

void MessageControllerTests::cleanup()
{
    if(messageController != nullptr) {
        messageController->deleteLater();
        messageController = nullptr;
    }

    if(testUser != nullptr) {
        testUser->deleteLater();
        testUser = nullptr;
    }
}
}

namespace controllers { // Tests

void MessageControllerTests::getChat_setFriendReference_returnsCorrectChat()
{
    ChatModel* testChat = messageController->getChatByFriend("FR0001");
    validateChat1(testChat);
}

void MessageControllerTests::getChat_setInvalidFriendReference_returnsNullptr()
{
    ChatModel* testChat = messageController->getChatByFriend("FR0000");
    QVERIFY(testChat == nullptr);
    testChat = messageController->getChatByFriend(nullptr);
    QVERIFY(testChat == nullptr);
}

void MessageControllerTests::getMessage_setChatAndMessageReference_returnsCorrectMessage()
{
    ChatModel* testChat = messageController->getChatByFriend("FR0001");
    Message* message = messageController->getMessageByChat(testChat, "MS0001");
    validateMessage1(message);
}

void MessageControllerTests::getMessage_setFriendReference_returnsCorrectMessage()
{
    Message* message = messageController->getMessageByFriend("FR0001", "MS0002");
    validateMessage2(message);
}

void MessageControllerTests::getMessage_setMessageReference_returnsCorrectMessage()
{
    Message* message = messageController->getMessage("MS0003");
    validateMessage3(message);
}

void MessageControllerTests::getMessage_setInvalidMessageReference_returnsNullptr()
{
    Message* message = messageController->getMessage("MS0000");
    QVERIFY(message == nullptr);
}

void MessageControllerTests::getMessage_setInvalidChat_returnsNullptr()
{
    Message* message = messageController->getMessageByChat(nullptr, "MS0001");
    QVERIFY(message == nullptr);
}

void MessageControllerTests::getMessage_setInvalidFriendReference_returnsNullptr()
{
    Message* message = messageController->getMessageByFriend("FR0000", "MS0001");
    QVERIFY(message == nullptr);
}

void MessageControllerTests::getMessageStatus_setMessageReference_returnsCorrectStatus()
{
    QCOMPARE( messageController->getMessageStatus("MS0001"), static_cast<int>(Message::eMessageStatus::Read));
}

void MessageControllerTests::getMessageList_setChat_returnsCorrectList()
{
    ChatModel* testChat = messageController->getChatByFriend("FR0001");
    QList<Message*> messages = messageController->getMessageList(testChat);

    QCOMPARE(messages.size(), 2);

    validateMessage1(messages.at(0));
    validateMessage2(messages.at(1));
}

/*
void MessageControllerTests::getMessageList_setInvalidChat_returnsNullptr()
{
    QList<Message*> messages = messageController->getMessageList(nullptr);
    QVERIFY(messages.isEmpty());
}
*/


void MessageControllerTests::getMessageListByFriend_setFriendReference_returnsCorrectList()
{
    QList<Message*> messages = messageController->getMessageListByFriend("FR0001");

    QCOMPARE(messages.size(), 2);

    validateMessage1(messages.at(0));
    validateMessage2(messages.at(1));
}

/*
void MessageControllerTests::getMessageListByFriend_setInvalidFriendReference_returnsNullptr()
{
    QList<Message*> testMessages = messageController->getMessageListByFriend("FR0000");
    QVERIFY( testMessages.isEmpty());
    testMessages = messageController->getMessageListByFriend(nullptr);
    QVERIFY(testMessages.isEmpty());
}
*/

void MessageControllerTests::getMessageListByStatus_setChatAndStatus_returnsCorrectList()
{
    ChatModel* testChat = messageController->getChatByFriend("FR0001");
    QList<Message*>* messages = messageController->getMessageListByStatus(testChat, Message::eMessageStatus::Read);

    QCOMPARE(messages->size(), 1);

    validateMessage1(messages->at(0));
}

void MessageControllerTests::getMessageListByStatus_setInvalidChat_returnsNullptr()
{
    QList<Message*>* messages = messageController->getMessageListByStatus(nullptr, Message::eMessageStatus::Read);
    QVERIFY( messages == nullptr);
}

void MessageControllerTests::getMessageListByStatus_setMessages_returnsCorrectList()
{
    ChatModel* testChat = messageController->getChatByFriend("FR0001");
    QList<Message*> allMessages = testChat->messages->derivedEntities();
    QList<Message*>* messages = messageController->getMessageListByStatus(allMessages, Message::eMessageStatus::Delivered);

    QCOMPARE(messages->size(), 1);

    validateMessage2(messages->at(0));
}

void MessageControllerTests::changeMessageStatus_setMessageAndStatus_setsNewStatus()
{
    Message* message = messageController->getMessage("MS0003");
    messageController->changeMessageStatus(message, Message::eMessageStatus::Read);
    QCOMPARE( messageController->getMessageStatus("MS0003"), static_cast<int>(Message::eMessageStatus::Read));
}

void MessageControllerTests::changeMessageStatus_setMessageReferenceAndStatus_setsNewStatus()
{
    messageController->changeMessageStatus("MS0003", Message::eMessageStatus::Read);
    QCOMPARE( messageController->getMessageStatus("MS0003"), static_cast<int>(Message::eMessageStatus::Read));
}

void MessageControllerTests::changeMessageStatus_setInvalidMessageReference_doesNothing()
{
    messageController->changeMessageStatus("MS0000", Message::eMessageStatus::Read);
}

void MessageControllerTests::addMessage_setChatAndMessage_addsMessage()
{
    Message* message = messageController->getMessageByFriend("FR0002", "MS0003");
    validateMessage3(message);

    ChatModel* testChat = messageController->getChatByFriend("FR0001");

    messageController->addMessage(testChat, message);

    testChat = messageController->getChatByFriend("FR0001");

    QCOMPARE(testChat->reference->value(), QString("CHT0001"));
    QCOMPARE(testChat->friendInChatReference->value(), QString("FR0001"));
    QList<Message*>& messages = testChat->messages->derivedEntities();
    QCOMPARE(messages.size(), 3);

    validateMessage1(messages.at(0));
    validateMessage2(messages.at(1));
    validateMessage3(messages.at(2));
}

void MessageControllerTests::addMessage_setChatAndParameters_addsMessage()
{
    ChatModel* testChat = messageController->getChatByFriend("FR0001");
    messageController->addMessage(testChat, "MS0005", "Hi!", Message::eMessageType::Incoming,
                                  QDateTime(QDate(2017, 8, 20), QTime(20, 00)));

    testChat = messageController->getChatByFriend("FR0001");
    QList<Message*>& messages = testChat->messages->derivedEntities();
    QCOMPARE(messages.size(), 3);

    QCOMPARE(messages.at(2)->reference->value(), QString("MS0005"));
    QCOMPARE(messages.at(2)->sender->value(), QString("FR0001"));
    QCOMPARE(messages.at(2)->receiver->value(), QString("USR0001"));
    QCOMPARE(messages.at(2)->sendAt->value(), QDateTime(QDate(2017, 8, 20), QTime(20, 00)));
    //QCOMPARE(messages.at(2)->receivedAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 50)));
    QCOMPARE(messages.at(2)->messageType->value(), static_cast<int>(Message::eMessageType::Incoming));
    QCOMPARE(messages.at(2)->messageStatus->value(), static_cast<int>(Message::eMessageStatus::Delivered));
    QCOMPARE(messages.at(2)->messageData->value(), QString("Hi!"));
}

void MessageControllerTests::addMessage_setFriendReferenceAndMessage_addsMessage()
{
    Message* message = messageController->getMessageByFriend("FR0002", "MS0003");
    messageController->addMessage("FR0001", message);
    ChatModel* testChat = messageController->getChatByFriend("FR0001");

    QCOMPARE(testChat->reference->value(), QString("CHT0001"));
    QCOMPARE(testChat->friendInChatReference->value(), QString("FR0001"));
    QList<Message*>& messages = testChat->messages->derivedEntities();
    QCOMPARE(messages.size(), 3);

    validateMessage1(messages.at(0));
    validateMessage2(messages.at(1));
    validateMessage3(messages.at(2));
}

void MessageControllerTests::addMessage_setFriendReferenceAndParameters_addsMessage()
{
    messageController->addMessage("FR0001", "MS0006", "I wanna die!", Message::eMessageType::Outgoing,
                                  QDateTime(QDate(2017, 8, 20), QTime(11, 00)));

    ChatModel* testChat = messageController->getChatByFriend("FR0001");
    QList<Message*>& messages = testChat->messages->derivedEntities();
    QCOMPARE(messages.size(), 3);

    QCOMPARE(messages.at(2)->reference->value(), QString("MS0006"));
    QCOMPARE(messages.at(2)->sender->value(), QString("USR0001"));
    QCOMPARE(messages.at(2)->receiver->value(), QString("FR0001"));
    //QCOMPARE(messages.at(2)->sendAt->value(), QDateTime(QDate(2017, 8, 20), QTime(11, 00)));
    //QCOMPARE(messages.at(2)->receivedAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 50)));
    QCOMPARE(messages.at(2)->messageType->value(), static_cast<int>(Message::eMessageType::Outgoing));
    QCOMPARE(messages.at(2)->messageStatus->value(), static_cast<int>(Message::eMessageStatus::NotDelivered));
    QCOMPARE(messages.at(2)->messageData->value(), QString("I wanna die!"));
}

void MessageControllerTests::addMessage_setInvalidChat_doesNothind()
{
    messageController->addMessage(nullptr, "MS0006", "I wanna die!", Message::eMessageType::Outgoing,
                                  QDateTime(QDate(2017, 8, 20), QTime(11, 00)));
    ChatModel* testChat = messageController->getChatByFriend("FR0001");
    QList<Message*>& messages = testChat->messages->derivedEntities();
    QCOMPARE(messages.size(), 2);
}

void MessageControllerTests::addMessage_setInvalidFriendReference_doesNothing()
{
    messageController->addMessage("FR0000", "MS0006", "I wanna die!", Message::eMessageType::Outgoing,
                                  QDateTime(QDate(2017, 8, 20), QTime(11, 00)));
    ChatModel* testChat = messageController->getChatByFriend("FR0001");
    QList<Message*>& messages = testChat->messages->derivedEntities();
    QCOMPARE(messages.size(), 2);
}

void MessageControllerTests::MultitaskTesting()
{
}

void MessageControllerTests::validateMessage1(models::Message* testMessage1)
{
    QCOMPARE(testMessage1->reference->value(), QString("MS0001"));
    QCOMPARE(testMessage1->sender->value(), QString("FR0001"));
    QCOMPARE(testMessage1->receiver->value(), QString("USR0001"));
    QCOMPARE(testMessage1->sendAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 40)));
    QCOMPARE(testMessage1->receivedAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 50)));
    QCOMPARE(testMessage1->messageType->value(), static_cast<int>(Message::eMessageType::Incoming));
    QCOMPARE(testMessage1->messageStatus->value(), static_cast<int>(Message::eMessageStatus::Read));
    QCOMPARE(testMessage1->messageData->value(), QString("Hello!"));
}
void MessageControllerTests::validateMessage2(models::Message* testMessage2)
{
    QCOMPARE(testMessage2->reference->value(), QString("MS0002"));
    QCOMPARE(testMessage2->sender->value(), QString("USR0001"));
    QCOMPARE(testMessage2->receiver->value(), QString("FR0001"));
    QCOMPARE(testMessage2->sendAt->value(), QDateTime(QDate(2017, 8, 20), QTime(14, 00)));
    QCOMPARE(testMessage2->receivedAt->value(), QDateTime(QDate(2017, 8, 20), QTime(14, 00)));
    QCOMPARE(testMessage2->messageType->value(), static_cast<int>(Message::eMessageType::Outgoing));
    QCOMPARE(testMessage2->messageStatus->value(), static_cast<int>(Message::eMessageStatus::Delivered));
    QCOMPARE(testMessage2->messageData->value(), QString("Hello back!"));
}
void MessageControllerTests::validateMessage3(models::Message* testMessage3)
{
    QCOMPARE(testMessage3->reference->value(), QString("MS0003"));
    QCOMPARE(testMessage3->sender->value(), QString("USR0001"));
    QCOMPARE(testMessage3->receiver->value(), QString("FR0002"));
    QCOMPARE(testMessage3->sendAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 20)));
    QCOMPARE(testMessage3->receivedAt->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 30)));
    QCOMPARE(testMessage3->messageType->value(), static_cast<int>(Message::eMessageType::Outgoing));
    QCOMPARE(testMessage3->messageStatus->value(), static_cast<int>(Message::eMessageStatus::Read));
    QCOMPARE(testMessage3->messageData->value(), QString("Lets Go!"));
}

void MessageControllerTests::validateChat1(const models::ChatModel* testChat1)
{
    QCOMPARE(testChat1->reference->value(), QString("CHT0001"));
    QCOMPARE(testChat1->friendInChatReference->value(), QString("FR0001"));
    QList<Message*>& messages = testChat1->messages->derivedEntities();
    QCOMPARE(messages.size(), 2);

    validateMessage1(messages.at(0));
    validateMessage2(messages.at(1));
}

}
}
