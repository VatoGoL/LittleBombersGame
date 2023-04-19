#pragma once

#define INFINITY_HEALTH -1

typedef struct vector2d{
    long x = 0;
    long y = 0;
} vector2d_t;

class Object{
public:
    virtual void init() = 0;
    virtual void update() = 0;
    //virtual ~Object();
};
