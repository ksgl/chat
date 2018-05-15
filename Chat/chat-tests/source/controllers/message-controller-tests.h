#ifndef MESSAGECONTROLLERTESTS_H
#define MESSAGECONTROLLERTESTS_H

#include <QTest>

#include <controllers/message-controller.h>
#include <models/user-model.h>

#include <test-suite.h>

namespace chat {
namespace controllers {

class MessageControllerTests : public TestSuite
{
    Q_OBJECT

public:
   MessageControllerTests();

public slots:

   /// @brief Called before the first test function is executed
   void initTestCase();
   /// @brief Called after the last test function was executed.
   void cleanupTestCase();
   /// @brief Called before each test function is executed.
   void init();
   /// @brief Called after every test function.
   void cleanup();

private slots:

   void getChat_setFriendReference_returnsCorrectChat();
   void getChat_setInvalidFriendReference_returnsNullptr();
   void getMessage_setChatAndMessageReference_returnsCorrectMessage();
   void getMessage_setFriendReference_returnsCorrectMessage();
   void getMessage_setMessageReference_returnsCorrectMessage();
   void getMessage_setInvalidMessageReference_returnsNullptr();
   void getMessage_setInvalidChat_returnsNullptr();
   void getMessage_setInvalidFriendReference_returnsNullptr();

   void getMessageStatus_setMessageReference_returnsCorrectStatus();

   void getMessageList_setChat_returnsCorrectList();
   //void getMessageList_setInvalidChat_returnsNullptr();
   void getMessageListByFriend_setFriendReference_returnsCorrectList();
   //void getMessageListByFriend_setInvalidFriendReference_returnsNullptr();
   void getMessageListByStatus_setChatAndStatus_returnsCorrectList();
   void getMessageListByStatus_setInvalidChat_returnsNullptr();
   void getMessageListByStatus_setMessages_returnsCorrectList();

   void changeMessageStatus_setMessageAndStatus_setsNewStatus();
   void changeMessageStatus_setMessageReferenceAndStatus_setsNewStatus();
   void changeMessageStatus_setInvalidMessageReference_doesNothing();

   void addMessage_setChatAndMessage_addsMessage();
   void addMessage_setChatAndParameters_addsMessage();
   void addMessage_setFriendReferenceAndMessage_addsMessage();
   void addMessage_setFriendReferenceAndParameters_addsMessage();
   void addMessage_setInvalidChat_doesNothind();
   void addMessage_setInvalidFriendReference_doesNothing();

   void MultitaskTesting();

private:

   void validateChat1(const models::ChatModel* testChat1);
   void validateMessage1(models::Message* testMessage1);
   void validateMessage2(models::Message* testMessage2);
   void validateMessage3(models::Message* testMessage3);

   MessageController* messageController{nullptr};
   models::UserModel* testUser{nullptr};

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


}
}


#endif // MESSAGECONTROLLERTESTS_H
