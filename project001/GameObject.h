#pragma once
#include "ScreenBuffer.h"

class GameObject {
private:
    int X = 0;
    int enemyMove = 1;
public:
    bool shot = false;
    COORD pos;
    const char* image;


    GameObject(const char* image) {
        this->image = image;
    }

    GameObject(COORD pos, const char* image) {
        X = pos.X;
        this->pos = pos;
        this->image = image;
    }

    void move();
    void Gun(COORD);
    void movingEnemy();
    void Gun_move();
    bool HitEnemy(GameObject);
};