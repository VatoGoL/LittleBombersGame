#pragma once
#include "../Engine/Object.hpp"

class ObjectLevel: public Object{
public:
    virtual void init() override;
    virtual void update() override;
    
    virtual void addObjectOnScene();
    virtual void deleteObjectFromScene();

    virtual ~ObjectLevel();
};