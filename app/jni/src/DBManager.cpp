#include "DBManager.h"
#include "Framework.h"
#include "GlobalFunction.h"
#include <android/log.h>
#include <firebase/variant.h>

DBManager::DBManager()
{
    database = firebase::database::Database::GetInstance(Framework::app);

    if(!database)
    {
        __android_log_print(ANDROID_LOG_INFO, "SDL_Error",
                            "Create android real time database failed...");
    }
    else
    {
        dbRef = database->GetReference();
    }


}

DBManager::~DBManager()
{

}

void DBManager::writeToDB(const DBData& data)
{
    dbRef.Child("users").Child(Framework::UID).Child(attackUpgradeKey).SetValue(data.attackUpgrade);
    dbRef.Child("users").Child(Framework::UID).Child(bulletUpgradeKey).SetValue(data.bulletUpgrade);
    dbRef.Child("users").Child(Framework::UID).Child(curAirplaneUpgradeKey).SetValue(data.curAirplaneUpgrade);
    dbRef.Child("users").Child(Framework::UID).Child(thunderNumKey).SetValue(data.thunderNum);
    dbRef.Child("users").Child(Framework::UID).Child(shieldNumKey).SetValue(data.shieldNum);
    dbRef.Child("users").Child(Framework::UID).Child(moneyKey).SetValue(data.money);
    dbRef.Child("users").Child(Framework::UID).Child(maxStageKey).SetValue(data.maxStage);
    dbRef.Child("users").Child(Framework::UID).Child(curAttackKey).SetValue(data.curAttack);
    dbRef.Child("users").Child(Framework::UID).Child(curBulletKey).SetValue(data.curBullet);
}

void DBManager::readFromDB(const firebase::database::DataSnapshot* snapshot)
{
    readData.attackUpgrade = snapshot->Child(attackUpgradeKey).value().AsInt64().int64_value();
    readData.bulletUpgrade = snapshot->Child(bulletUpgradeKey).value().AsInt64().int64_value();
    readData.curAirplaneUpgrade = snapshot->Child(curAirplaneUpgradeKey).value().AsInt64().int64_value();
    readData.shieldNum = snapshot->Child(shieldNumKey).value().AsInt64().int64_value();
    readData.thunderNum = snapshot->Child(thunderNumKey).value().AsInt64().int64_value();
    readData.money = snapshot->Child(moneyKey).value().AsInt64().int64_value();
    readData.maxStage = snapshot->Child(maxStageKey).value().AsInt64().int64_value();
    readData.curAttack = snapshot->Child(curAttackKey).value().AsInt64().int64_value();
    readData.curBullet = snapshot->Child(curBulletKey).value().AsInt64().int64_value();
}

void DBManager::createDBForNewUser()
{
    dbRef.Child("users").Child(Framework::UID).Child(attackUpgradeKey).SetValue(0);
    dbRef.Child("users").Child(Framework::UID).Child(bulletUpgradeKey).SetValue(0);
    dbRef.Child("users").Child(Framework::UID).Child(curAirplaneUpgradeKey).SetValue(1);
    dbRef.Child("users").Child(Framework::UID).Child(thunderNumKey).SetValue(0);
    dbRef.Child("users").Child(Framework::UID).Child(shieldNumKey).SetValue(0);
    dbRef.Child("users").Child(Framework::UID).Child(moneyKey).SetValue(0);
    dbRef.Child("users").Child(Framework::UID).Child(maxStageKey).SetValue(1);
    dbRef.Child("users").Child(Framework::UID).Child(curAttackKey).SetValue(25);
    dbRef.Child("users").Child(Framework::UID).Child(curBulletKey).SetValue(1);
}

firebase::database::DatabaseReference DBManager::getDBRef()
{
    return dbRef;
}

DBData DBManager::getDataReadFromDB()
{
    return readData;
}