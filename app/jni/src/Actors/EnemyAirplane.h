#pragma once
#include "Airplane.h"
#include "Bullet.h"

class SplineComponent;

enum class ENEMY_SHIP_SHAPE
{
    SHIP1,
    SHIP2,
    SHIP3,
    SHIP4,
    BOSS1,
    BOSS2
};

enum class ENEMY_BULLET_PATTERN
{
    BULLET_3,
    BULLET_5,
    BULLET_7,
    TARGETED,
    BOSS_CIRCLE,
    BOSS_STAR,
    BOSS_FLOWER
};

class EnemyAirplane :public Airplane
{
public:
    EnemyAirplane() = delete;
    EnemyAirplane(BULLET_COLOR color, ENEMY_SHIP_SHAPE shape, int hp);
    virtual ~EnemyAirplane();
    virtual void render() override;
    virtual void update(float deltaTime) override;
    virtual void handleEvent(SDL_Event& e) override;
    void resetEnemyAirplaneToInitialState();

public:
    void getDamage(int damage);
    void setPath(SplineComponent* path);
    void setCanDamaged(bool canDamaged);
    bool getCanDamaged();
    void setBulletPattern(ENEMY_BULLET_PATTERN pattern);
    void setMaxHP(int maxHP);

private:
    void firePattern1();
    void firePattern2();
    void firePattern3();
    void firePattern4();
    void firePattern5();
    void firePattern6();
    void firePattern7();
    void spawnBullet(float deltaTime);
    static void initStaticData();
    static void initBossCirclePattern();
    static void initBossStarPattern();
    static void initBossHeartPattern();

private:
    ImageComponent* hpBar = nullptr;
    SplineComponent* path = nullptr;
    BULLET_COLOR bulletColor = BULLET_COLOR::RED;
    ENEMY_BULLET_PATTERN bulletPattern = ENEMY_BULLET_PATTERN::TARGETED;
    ENEMY_SHIP_SHAPE shipShape = ENEMY_SHIP_SHAPE::BOSS1;
    int curHp = 0;
    int maxHP = 0;
    float t = 0.0f;
    const int hpBarRowSize = 100;
    const int hpBarColSize = 10;
    std::pair<int, int> befPos;
    Vector2D realDirVec;
    int cnt = 0;
    float degreeGap = 0.0f;
    bool canDamaged = false;
    bool isArrived = false;
    const int rotateRate = 150;
    const float moveRate = 0.5f;
    static const float normalBulletSpeed;
    static Vector2D bullet3DirVec[3];
    static Vector2D bullet5DirVec[5];
    static Vector2D bullet7DirVec[7];
    static Vector2D bossCirclePattern[30];
    static Vector2D bossStarPattern[51];
    static Vector2D bossStarPatternStartPos[51];
    static Vector2D bossFlowerPattern[40];
    static Vector2D bossFlowerPatternStartPos[40];
    static bool isInitStaticData;
};

