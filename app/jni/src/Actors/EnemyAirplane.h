#pragma once
#include "AirplaneParent.h"
#include "Bullet.h"
#include "AttackStrategy/AttackStrategy.h"

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

class EnemyAirplane :public AirplaneParent
{
public:
    EnemyAirplane() = delete;
    EnemyAirplane(const EnemyAirplane&) = delete;
    EnemyAirplane& operator=(const EnemyAirplane&) = delete;
    EnemyAirplane(const BULLET_COLOR color, const ENEMY_SHIP_SHAPE shape, int hp);
    virtual ~EnemyAirplane();
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    virtual void handleEvent(const SDL_Event& e) override;
    void resetEnemyAirplaneToInitialState();

public:
    void getDamage(int damage);
    void setPath(SplineComponent* path);
    void setCanDamaged(bool canDamaged);
    bool getCanDamaged();
    void setBulletPattern(const ENEMY_BULLET_PATTERN pattern);
    void setMaxHP(int maxHP);

private:
    void spawnBullet(float deltaTime);
    void hitAnimation(float deltaTime);
    static void initStaticData();

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
    float animAccTime = 0.0f;
    bool canDamaged = false;
    bool isArrived = false;
    bool isHitAnimPlay = false;
    const int rotateRate = 150;
    const float moveRate = 0.5f;
    AttackStrategy* curAttackStrategy = nullptr;

    static AttackStrategy* circlePattern;
    static AttackStrategy* fire3Pattern;
    static AttackStrategy* fire5Pattern;
    static AttackStrategy* fire7Pattern;
    static AttackStrategy* flowerPattern;
    static AttackStrategy* starPattern;
    static AttackStrategy* targetingPattern;

    static const float normalBulletSpeed;
    static bool isInitStaticData;
};

