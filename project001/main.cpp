#include <iostream>
#include<Windows.h>
#include "GameObject.h"
#include "ScreenBuffer.h"
#include <vector>

using namespace std;

void init(ScreenBuffer& screenBuffer,char *field);
void Score_pos(int score);
void Pan(char *field);
void space(bool& discontinuity, vector <GameObject> &bullet, GameObject player);
void GameOverCheck(vector <GameObject>& bullet, vector <GameObject>& enemies,int &score,bool &OVER);
void PlayResult(int score);
void CurSor();

int main() {
    while (true) {
        char* field = nullptr;
        ScreenBuffer screenBuffer;
        CurSor();
        field = new char[FIELD_WIDTH * FIELD_HEIGHT];
        GameObject player({ 10,10 }, ">-0-<");
        vector <GameObject> enemies;
        vector <GameObject> bullet;
        char restart;
        bool discontinuity = false;
        bool OVER = true;
        int score = 0;
        short up = 7;
        short down = 9;

        for (int x = 0; x < 8; x++)
            if (x < 4) {
                enemies.push_back(GameObject{ {up,2},"[XUX]" });
                up += 10;
            }
            else {
                enemies.push_back(GameObject{ {down,4},"[XUX]" });
                down += 10;
            }
        
        Pan(field);


        while (OVER) {
            init(screenBuffer, field);
            player.move();
            screenBuffer.drawToBackBuffer(player.pos.X, player.pos.Y, player.image);
            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].movingEnemy();
                screenBuffer.drawToBackBuffer(enemies[i].pos.X, enemies[i].pos.Y, enemies[i].image);
            }

            space(discontinuity, bullet, player);
            GameOverCheck(bullet, enemies, score, OVER);
            for (auto v : bullet)
                if (v.shot == true)
                    screenBuffer.drawToBackBuffer(v.pos.X, v.pos.Y, v.image);

            Score_pos(score);
            screenBuffer.render();
            Sleep(100);
        }
        PlayResult(score);

        cin >> restart;
        if (restart == 'n' || restart == 'N')
            return 0;
    }
}


void init(ScreenBuffer& screenBuffer, char* field) {
    for (int x = 0; x < FIELD_WIDTH; x++)
    {
        for (int y = 0; y < FIELD_HEIGHT; y++)
        {
            screenBuffer.drawToBackBuffer(x, y, " -|"[field[y * FIELD_WIDTH + x]]);
        }
    }
}

void space(bool& discontinuity, vector <GameObject>& bullet, GameObject player) {
    int shot_Count = 0;
    if (GetAsyncKeyState(VK_SPACE) & (1 << 15))
    {
        if (discontinuity == false) {
            bullet.push_back(GameObject{ "!" });

            for (shot_Count = 0; shot_Count < bullet.size() - 1; shot_Count++) {
                if (bullet[shot_Count].shot == false)
                    break;
            }
            if (bullet[shot_Count].shot == false)
                bullet[shot_Count].Gun(player.pos);
        }
        discontinuity = true;
    }
    else
        discontinuity = false;
}

void GameOverCheck(vector <GameObject>&bullet, vector <GameObject>& enemies, int &score, bool& OVER) {
    bool enemy_break = false;
    for (int i = 0; i < bullet.size(); i++)
    {
        bullet[i].Gun_move();
        for (int j = 0; j < enemies.size(); j++)
        {
            if (enemies[j].pos.Y == FIELD_HEIGHT - 2)
                OVER = false;
            enemy_break = bullet[i].HitEnemy(enemies[j]);
            if (enemy_break == true) {
                enemies.erase(enemies.begin() + j);
                score += 1;
                break;
            }
        }
    }
    if (score == 8)
        OVER = false;
}

void PlayResult(int score) {
    system("cls");
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    if (score == 8)
    {
        cout << endl << "                YOU WIN !!     " << endl;
        cout << endl << "                Score : " << score << endl;
        cout << endl << "                Play Again? (y/n) : ";
    }

    else
    {
        cout << endl << "              YOU LOOSE !!     " << endl;
        cout << endl << "              Score: " << score << endl;
        cout << endl << "              Play Again? (y/n) : ";
    }
}

void Score_pos(int score) {
    COORD score_pos = { 25,0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), score_pos);
    cout << "score: " << score;
}

void Pan(char* field) {
    for (int x = 0; x < FIELD_WIDTH; x++) 
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            field[y * FIELD_WIDTH + x] = (x == 0 || x == FIELD_WIDTH - 1) ? 2 : 0;
            if (y == 1 && (x >0 && x < FIELD_WIDTH - 1)) {
                field[y * FIELD_WIDTH + x] = 1;
            }
            if ( y == FIELD_HEIGHT - 1 && (x > 0 && x < FIELD_WIDTH - 1)) {
                field[y * FIELD_WIDTH + x] = 1;
            }            
        }
}

void CurSor() {
    CONSOLE_CURSOR_INFO cur_info;
    cur_info.dwSize = 1; 
    cur_info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
}

