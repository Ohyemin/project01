#include <iostream>
#include<windows.h>
#include "GameObject.h"
using namespace std;


void GameObject::move() 
{
    pos.X -= (GetAsyncKeyState(VK_LEFT) & (1 << 15) && pos.X > 1) ? 1 : 0;
    pos.X += (GetAsyncKeyState(VK_RIGHT) & (1 << 15) && pos.X < FIELD_WIDTH - 6) ? 1 : 0;
    pos.Y -= (GetAsyncKeyState(VK_UP) & (1 << 15) && pos.Y > 3) ? 1 : 0;
    pos.Y += (GetAsyncKeyState(VK_DOWN) & (1 << 15) && pos.Y < FIELD_HEIGHT - 2) ? 1 : 0;
}


void GameObject::movingEnemy() {
    if (pos.X == X)
        pos.Y++;
    else if (pos.X == X + 4)
        enemyMove = -1;
    else if (pos.X == X - 4)
        enemyMove = 1;
    pos.X += enemyMove;
}

void GameObject::Gun(COORD Player_pos) {
    if (shot == false) {
        pos.X = Player_pos.X + 2;
        pos.Y = Player_pos.Y;
        shot = true;
    }
}

bool GameObject::HitEnemy(GameObject enemy) {
    if (pos.Y == enemy.pos.Y) {
        for (int y = 0; y < 5; y++) {
            if (pos.X == enemy.pos.X + y) {
                shot = false;
                return true;
            }
        }
    }
    if (pos.Y == 1) {
        shot = false;
    }
    return false;
}

void GameObject::Gun_move() {
    if (shot == true) {
        pos.Y--; 
    }
}

