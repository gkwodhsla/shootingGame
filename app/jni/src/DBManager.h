#pragma once

#include "firebase/app.h"
#include "firebase/util.h"
#include "firebase/database.h"

struct DBData
{
    int attackUpgrade = 0;
    int bulletUpgrade = 0;
    int curAirplaneUpgrade = 0;
    int thunderNum = 0;
    int shieldNum = 0;
    int money = 0;
    int maxStage = 0;
    int curAttack = 0;
    int curBullet = 0;
};

class DBManager
{
public:
    DBManager();
    virtual ~DBManager();
    void writeToDB(const DBData& data);
    DBData readFromDB();
    void createDBForNewUser();
private:
    const std::string attackUpgradeKey = "attackUpgrade";
    const std::string bulletUpgradeKey = "bulletUpgrade";
    const std::string curAirplaneUpgradeKey = "curAirplane";
    const std::string thunderNumKey = "thunderNum";
    const std::string shieldNumKey = "shieldNum";
    const std::string moneyKey = "money";
    const std::string maxStageKey = "maxStage";
    const std::string curAttackKey = "curAttack";
    const std::string curBulletKey = "curBullet";
    static firebase::database::Database *database;
    static firebase::database::DatabaseReference dbRef;
};