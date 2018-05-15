#include "friend-controller-tests.h"

#include <QSignalSpy>

using namespace chat::models;

namespace chat {
namespace controllers { // Instance

static FriendControllerTests instance;

FriendControllerTests::FriendControllerTests()
    : TestSuite( "FriendControllerTests" )
{
}

}

namespace controllers { // Scaffolding

void FriendControllerTests::initTestCase()
{
}

void FriendControllerTests::cleanupTestCase()
{
}

void FriendControllerTests::init()
{
    testUser = new models::UserModel(this, QJsonDocument::fromJson(jsonByteArray).object());
    friendController = new FriendController(this, testUser);
}

void FriendControllerTests::cleanup()
{
    if(friendController != nullptr) {
        friendController->deleteLater();
        friendController = nullptr;
    }

    if(testUser != nullptr) {
        testUser->deleteLater();
        testUser = nullptr;
    }
}
}

namespace controllers { // Tests

void FriendControllerTests::getFriend_setFriendReference_returnsCorrectFriend()
{
    Friend* testFriend = friendController->getFriend("FR0001");
    validateFriend1(testFriend);
}

void FriendControllerTests::getFriend_setInvalidFriendReference_returnsNullptr()
{
    Friend* testFriend = friendController->getFriend("FR0000");
    QVERIFY(testFriend == nullptr);
    Friend* testFriend2 = friendController->getFriend(nullptr);
    QVERIFY(testFriend2 == nullptr);
}

void FriendControllerTests::getFriendByName_setFriendName_retrurnsCorrectFriend()
{
    Friend* testFriend = friendController->getFriendByName("Frienderson");
    validateFriend1(testFriend);
}

void FriendControllerTests::getFriendByName_setInvalidName_returnsNullptr()
{
    Friend* testFriend = friendController->getFriendByName("NotAFriend");
    QVERIFY(testFriend == nullptr);
    Friend* testFriend2 = friendController->getFriendByName(nullptr);
    QVERIFY(testFriend2 == nullptr);
}

void FriendControllerTests::getFriendStatus_setFriendReference_returnsCorrectStatus()
{
    QCOMPARE( friendController->getFriendStatus("FR0002"), models::Friend::eStatus::Offline);
}

void FriendControllerTests::getFriendStatus_setInvalidFriendReference_returnsUnknownStatus()
{
    QCOMPARE( friendController->getFriendStatus("FR0000"), models::Friend::eStatus::Unknown);
}

void FriendControllerTests::getFriendList_returnsCorrectFriendList()
{
    QList<Friend*> friends = friendController->getFriendList();
    QCOMPARE(friends.size(), 2);

    validateFriend1(friends.at(0));
    validateFriend2(friends.at(1));
}

void FriendControllerTests::getFriendListByStatus_setCorrectStatus_returnsCorrectList()
{
    QList<Friend*>* friends = friendController->getFriendListByStatus(models::Friend::eStatus::Offline);
    QCOMPARE(friends->size(), 1);

    validateFriend2(friends->at(0));
}

void FriendControllerTests::getFriendListByStatus_setInvalidStatus_returnsNullSizeList()
{
    QList<Friend*>* friends = friendController->getFriendListByStatus(models::Friend::eStatus::Unknown);
    QCOMPARE(friends->size(), 0);
}

void FriendControllerTests::changeFriendStatus_setFriendReferenceAndValidStatus_setsNewStatus()
{
    QSignalSpy valueChangedSpy(friendController, &FriendController::statusChanged);

    Friend* testFriend = friendController->getFriend("FR0001");
    validateFriend1(testFriend);

    QSignalSpy friendValueChangedSpy(testFriend, &Friend::statusChanged);

    friendController->changeFriendStatus("FR0001", Friend::eStatus::Unknown);
    testFriend = friendController->getFriend("FR0001");

    QCOMPARE(testFriend->reference->value(), QString("FR0001"));
    QCOMPARE(testFriend->friendName->value(), QString("Frienderson"));
    QCOMPARE(testFriend->friendIp->value(), QString("127.01.02.44"));
    QCOMPARE(testFriend->lastVisit->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 0)));
    QCOMPARE(testFriend->status->value(), static_cast<int>(Friend::eStatus::Unknown));

    QCOMPARE(valueChangedSpy.count(), 1);
    QCOMPARE(friendValueChangedSpy.count(), 1);
}

void FriendControllerTests::changeFriendStatus_setFriendReferenceAndInvalidStatus_leavesPreviousValue()
{
    Friend* testFriend = friendController->getFriend("FR0001");
    validateFriend1(testFriend);

    friendController->changeFriendStatus("FR0001", static_cast<Friend::eStatus>(5));
    testFriend = friendController->getFriend("FR0001");
    validateFriend1(testFriend);
}

void FriendControllerTests::changeFriendStatus_setInvalidFriendReference_doesNothing()
{
    friendController->changeFriendStatus("FR0000", Friend::eStatus::Unknown);
}

void FriendControllerTests::changeFriendStatus_setFriendAndValidStatus_setsNewStatus()
{
    Friend* testFriend = friendController->getFriend("FR0001");
    validateFriend1(testFriend);

    friendController->changeFriendStatus(testFriend, Friend::eStatus::Unknown);

    QCOMPARE(testFriend->reference->value(), QString("FR0001"));
    QCOMPARE(testFriend->friendName->value(), QString("Frienderson"));
    QCOMPARE(testFriend->friendIp->value(), QString("127.01.02.44"));
    QCOMPARE(testFriend->lastVisit->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 0)));
    QCOMPARE(testFriend->status->value(), static_cast<int>(Friend::eStatus::Unknown));
}

void FriendControllerTests::changeFriendStatus_setInvalidFriend_doesNothing()
{
    friendController->changeFriendStatus(nullptr, Friend::eStatus::Unknown);
}

void FriendControllerTests::changeLastVisit_setFriendReferenceAndValidDateTime_setsNewDateTime()
{
    Friend* testFriend = friendController->getFriend("FR0001");
    validateFriend1(testFriend);
    QDateTime newTime(QDate(2017, 8, 20), QTime(15, 10));
    friendController->changeLastVisit("FR0001", newTime);
    testFriend = friendController->getFriend("FR0001");

    QCOMPARE(testFriend->reference->value(), QString("FR0001"));
    QCOMPARE(testFriend->friendName->value(), QString("Frienderson"));
    QCOMPARE(testFriend->friendIp->value(), QString("127.01.02.44"));
    QCOMPARE(testFriend->lastVisit->value(), QDateTime(QDate(2017, 8, 20), QTime(15, 10)));
    QCOMPARE(testFriend->status->value(), static_cast<int>(Friend::eStatus::Online));
}

void FriendControllerTests::changeLastVisit_setInvalidFriendReference_doesNothing()
{
    QDateTime newTime(QDate(2017, 8, 20), QTime(15, 10));
    friendController->changeLastVisit("FR0000", newTime);
}

void FriendControllerTests::changeLastVisit_setFriendAndValidDateTime_setsNewDateTime()
{
    Friend* testFriend = friendController->getFriend("FR0001");
    validateFriend1(testFriend);

    QDateTime newTime(QDate(2017, 8, 20), QTime(15, 10));
    friendController->changeLastVisit(testFriend, newTime);

    QCOMPARE(testFriend->reference->value(), QString("FR0001"));
    QCOMPARE(testFriend->friendName->value(), QString("Frienderson"));
    QCOMPARE(testFriend->friendIp->value(), QString("127.01.02.44"));
    QCOMPARE(testFriend->lastVisit->value(), QDateTime(QDate(2017, 8, 20), QTime(15, 10)));
    QCOMPARE(testFriend->status->value(), static_cast<int>(Friend::eStatus::Online));
}

void FriendControllerTests::changeLastVisit_setInvalidFriend_doesNothing()
{
    QDateTime newTime(QDate(2017, 8, 20), QTime(15, 10));
    friendController->changeLastVisit(nullptr, newTime);
}

void FriendControllerTests::addFriend_setValidFriend_addsNewFriend()
{
    QSignalSpy valueChangedSpy(friendController, &FriendController::friendAdded);

    QString newReference("FR0003");
    QString newName("FromFriend");
    QString newIp("127.01.02.46");
    Friend::eStatus status = Friend::eStatus::Online;
    QDateTime newTime(QDate(2017, 8, 20), QTime(15, 10));

    Friend* newFriend = new Friend(this, newReference, newName,
                                   newIp, status, newTime);
    friendController->addFriend(newFriend);

    QList<Friend*> friends = friendController->getFriendList();
    QCOMPARE(friends.size(), 3);

    validateFriend1(friends.at(0));
    validateFriend2(friends.at(1));
    validateFriend3(friends.at(2));

    QCOMPARE(valueChangedSpy.count(), 1);
}

void FriendControllerTests::addFriend_setNameIpLastVisitStatus_addsNewFriend()
{
    QString newReference("FR0003");
    QString newName("FromFriend");
    QString newIp("127.01.02.46");
    Friend::eStatus status = Friend::eStatus::Online;
    QDateTime newTime(QDate(2017, 8, 20), QTime(15, 10));

    friendController->addFriend(newReference, newName,
                                newIp, status, newTime);

    QList<Friend*> friends = friendController->getFriendList();
    QCOMPARE(friends.size(), 3);

    validateFriend1(friends.at(0));
    validateFriend2(friends.at(1));
    validateFriend3(friends.at(2));
}

void FriendControllerTests::addFriend_setNullptr_doesNothing()
{
    friendController->addFriend(nullptr);

    QList<Friend*> friends = friendController->getFriendList();
    QCOMPARE(friends.size(), 2);
}

void FriendControllerTests::MultitaskTesting()
{
    QString newReference("FR0003");
    QString newName("FromFriend");
    QString newIp("127.01.02.46");
    Friend::eStatus status = Friend::eStatus::Online;
    QDateTime newTime(QDate(2017, 8, 20), QTime(15, 10));

    friendController->addFriend(newReference, newName,
                                newIp, status, newTime);

    QList<Friend*> friends = friendController->getFriendList();
    QCOMPARE(friends.size(), 3);

    friendController->changeFriendStatus(friends.at(1), Friend::eStatus::Unknown);
    QList<Friend*>* friendOnline = friendController->getFriendListByStatus(Friend::eStatus::Online);
    QCOMPARE(friendOnline->size(), 2);

    QList<Friend*>* friendOffline = friendController->getFriendListByStatus(Friend::eStatus::Offline);
    QCOMPARE(friendOffline->size(), 0);

    friendController->changeFriendStatus(friendOnline->at(0), Friend::eStatus::Offline);
    QCOMPARE( friendController->getFriendStatus("FR0001"), models::Friend::eStatus::Offline);

    QString _newReference("FR0004");
    QString _newName("FarFarAwayFriend");
    QString _newIp("127.01.02.47");
    Friend::eStatus _status = Friend::eStatus::Online;
    QDateTime _newTime(QDate(2017, 8, 20), QTime(16, 30));

    Friend* _newFriend = new Friend(this, _newReference, _newName,
                                   _newIp, _status, _newTime);
    friendController->addFriend(_newFriend);

    friends = friendController->getFriendList();
    QCOMPARE(friends.size(), 4);

    friendController->changeLastVisit(friends.at(3), QDateTime(QDate(2017, 8, 20), QTime(13, 0)));
    Friend* lastAddedFriend = friendController->getFriend("FR0004");

    QCOMPARE(lastAddedFriend->reference->value(), QString("FR0004"));
    QCOMPARE(lastAddedFriend->friendName->value(), QString("FarFarAwayFriend"));
    QCOMPARE(lastAddedFriend->friendIp->value(), QString("127.01.02.47"));
    QCOMPARE(lastAddedFriend->lastVisit->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 0)));
    QCOMPARE(lastAddedFriend->status->value(), static_cast<int>(Friend::eStatus::Online));

}

void FriendControllerTests::validateFriend1(Friend *testFriend1)
{
    QCOMPARE(testFriend1->reference->value(), QString("FR0001"));
    QCOMPARE(testFriend1->friendName->value(), QString("Frienderson"));
    QCOMPARE(testFriend1->friendIp->value(), QString("127.01.02.44"));
    QCOMPARE(testFriend1->lastVisit->value(), QDateTime(QDate(2017, 8, 20), QTime(13, 0)));
    QCOMPARE(testFriend1->status->value(), static_cast<int>(Friend::eStatus::Online));
}

void FriendControllerTests::validateFriend2(Friend *testFriend2)
{
    QCOMPARE(testFriend2->reference->value(), QString("FR0002"));
    QCOMPARE(testFriend2->friendName->value(), QString("Friend Friend"));
    QCOMPARE(testFriend2->friendIp->value(), QString("127.01.02.45"));
    QCOMPARE(testFriend2->lastVisit->value(), QDateTime(QDate(2017, 8, 21), QTime(10, 30)));
    QCOMPARE(testFriend2->status->value(), static_cast<int>(Friend::eStatus::Offline));
}

void FriendControllerTests::validateFriend3(Friend* testFriend3)
{
    QCOMPARE(testFriend3->reference->value(), QString("FR0003"));
    QCOMPARE(testFriend3->friendName->value(), QString("FromFriend"));
    QCOMPARE(testFriend3->friendIp->value(), QString("127.01.02.46"));
    QCOMPARE(testFriend3->lastVisit->value(), QDateTime(QDate(2017, 8, 20), QTime(15, 10)));
    QCOMPARE(testFriend3->status->value(), static_cast<int>(Friend::eStatus::Online));
}


}
}

