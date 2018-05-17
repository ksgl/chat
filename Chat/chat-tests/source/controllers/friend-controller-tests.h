#ifndef FRIENDCONTROLLERTESTS_H
#define FRIENDCONTROLLERTESTS_H

#include <QTest>

#include <controllers/friend-controller.h>
#include <models/user-model.h>

#include <test-suite.h>

namespace chat {
namespace controllers {

class FriendControllerTests : public TestSuite
{
    Q_OBJECT

public:
   FriendControllerTests();

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

   void getFriend_setFriendReference_returnsCorrectFriend();
   void getFriend_setInvalidFriendReference_returnsNullptr();
   void getFriendByName_setFriendName_retrurnsCorrectFriend();
   void getFriendByName_setInvalidName_returnsNullptr();
   void getFriendStatus_setFriendReference_returnsCorrectStatus();
   void getFriendStatus_setInvalidFriendReference_returnsUnknownStatus();
   void getFriendList_returnsCorrectFriendList();
   void getFriendListByStatus_setCorrectStatus_returnsCorrectList();
   void getFriendListByStatus_setInvalidStatus_returnsNullSizeList();

   void changeFriendStatus_setFriendReferenceAndValidStatus_setsNewStatus();
   void changeFriendStatus_setFriendReferenceAndInvalidStatus_leavesPreviousValue();
   void changeFriendStatus_setInvalidFriendReference_doesNothing();
   void changeFriendStatus_setFriendAndValidStatus_setsNewStatus();
   void changeFriendStatus_setInvalidFriend_doesNothing();
   void changeLastVisit_setFriendReferenceAndValidDateTime_setsNewDateTime();
   void changeLastVisit_setInvalidFriendReference_doesNothing();
   void changeLastVisit_setFriendAndValidDateTime_setsNewDateTime();
   void changeLastVisit_setInvalidFriend_doesNothing();

   void addFriend_setValidFriend_addsNewFriend();
   void addFriend_setNullptr_doesNothing();
   void addFriend_setNameIpLastVisitStatus_addsNewFriend();

   void MultitaskTesting();

private:

   void validateFriend1(const models::Friend* testFriend1);
   void validateFriend2(const models::Friend* testFriend2);
   void validateFriend3(const models::Friend* testFriend3);

   FriendController* friendController{nullptr};
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


#endif // FRIENDCONTROLLERTESTS_H
