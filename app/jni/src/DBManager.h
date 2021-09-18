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
//파이어베이스 실시간 데이터베이스에서 데이터를 읽거나 쓸 때 이 구조체를 사용한다.

class DBManager final
{
public:
    DBManager(const DBManager& other) = delete;
    DBManager& operator=(const DBManager& other) = delete;
    virtual ~DBManager();
    void writeToDB(const DBData& data);
    void readFromDB(const firebase::database::DataSnapshot* snapshot);
    void createDBForNewUser();

private:
    DBManager();

public:
    firebase::database::DatabaseReference getDBRef();
    const DBData& getDataReadFromDB();

public:
    static DBManager* getInstance();

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
    DBData readData;
    firebase::database::Database* database = nullptr;
    firebase::database::DatabaseReference dbRef;

private:
    static DBManager* instance;
};