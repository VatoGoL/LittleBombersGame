#pragma once
#include "../ObjectLevel.hpp"
#include "../../GameObject/Being/Player/Player.hpp"
#include "../../GameObject/Being/Enemy/Enemy.hpp"
#include "../../GameObject/Props/Wall/Wall.hpp"
#include <QTextStream>
#include <QFile>
#include "vector"

using namespace std;
#define CODE_EMPTY 0
#define CODE_PLAYER 1
#define CODE_ENEMY 2
#define CODE_WALL 3
#define MAP_SIZE 11

class LevelOne: public ObjectLevel{
private:
    int **__map;
    vector<Player*> *__players;
    vector<Enemy*> *__enemies;
    vector<ObjectProp*> *__props;
    
public:
    LevelOne();

    virtual void init() override;
    virtual void update() override;
    
    virtual void addObjectOnScene() override;
    virtual void deleteObjectFromScene() override;

    virtual ~LevelOne();
};
