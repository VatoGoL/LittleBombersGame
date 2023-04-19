#include "LevelOne.hpp"

LevelOne::LevelOne(){
    __players = new vector<Player*>;
    __enemies = new vector<Enemy*>;
    __props = new vector<ObjectProp*>;

    __map = new int *[MAP_SIZE];
    for(int i = 0; i < MAP_SIZE; i++){
        __map[i] = new int [MAP_SIZE];
    }
}

void LevelOne::init(){
    //MAP init
    QFile map_file(":/map/Model/GameLevels/LevelOne/map.txt");
    if(!map_file.open(QFile::ReadOnly)){
        throw invalid_argument ("File \"map.txt\" not open");
    }

    QTextStream fin(&map_file);
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            fin >> __map[i][j];
        }
    }

    map_file.close();

    //Static prop Init
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            if(__map[i][j] == CODE_WALL){
                Wall *wall = new Wall(INFINITY_HEALTH, {j,i});
                __props->push_back(wall);
                __props->back()->init();
            }
        }
    }
}
void LevelOne::update(){

}
    
void LevelOne::addObjectOnScene(){

}
void LevelOne::deleteObjectFromScene(){

}

LevelOne::~LevelOne(){
    delete __players;
    delete __enemies;
    delete __props;
    for(int i = 0; i < MAP_SIZE; i++){
        delete[] __map[i];
    }
    delete[] __map;
}
