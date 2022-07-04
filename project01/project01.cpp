#include <iostream>
#include<Windows.h>
#include<conio.h>

using namespace std;

void pan(string a[20][40], const int maxnumW, const int maxnumH);
void PlanePosition(COORD image_pos, const int maxnumW, const int maxnumH);

int main() {

	const int maxnumH = 20;
	const int maxnumW = 40;
	string a[maxnumH][maxnumW];


	const char* image = ">-0-<";
	COORD image_pos = { 10,10 };
	COORD gun_pos[5] = { {0,0},{0,0},{0,0},{0,0},{0,0}};
	const char* gun = "!";

	bool shot[5] = { false };

	
	while (true) {
		pan(a, maxnumW, maxnumH);
		
		if (GetAsyncKeyState(VK_LEFT) & (1 << 15))
		{
			if (image_pos.X > 2)
				image_pos.X--;
		}
		if (GetAsyncKeyState(VK_RIGHT) & (1 << 15))
		{
			if (image_pos.X < maxnumW - 6)
				image_pos.X++;
		}
		if (GetAsyncKeyState(VK_UP) & (1 << 15))
		{
			if (image_pos.Y > 1)
				image_pos.Y--;
		}
		if (GetAsyncKeyState(VK_DOWN) & (1 << 15))
		{
			if (image_pos.Y < maxnumH - 2)
				image_pos.Y++;
		}

		if (GetAsyncKeyState(VK_SPACE) & (1 << 15))
	    	{
			for (int x = 0; x < 5; x++) {
				if (shot[x] == false) {
					gun_pos[x].X = image_pos.X + 2;
					gun_pos[x].Y = image_pos.Y;
					shot[x] = true;
					break;
				}
			}
		}
	
		CONSOLE_CURSOR_INFO cur_info; //커서 정보를 담는 구조체
		cur_info.dwSize = 1; //커서 세로 크기
		cur_info.bVisible = false; // 커서를 보이게 할지 여부
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info); // 커서 상태를 해당 구조체 상태로 설정
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), image_pos); // pos 위치로 커서를 옮기는 함수
		cout << image;
		
		for (int x = 0; x < 5; x++) {
			if (shot[x] == true) {
				gun_pos[x].Y--;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), gun_pos[x]);
				cout << gun;
				if (gun_pos[x].Y == 1) {
					shot[x] = false;
				}
			}
		}
		Sleep(20);
		system("cls");
	}

}

void pan(string a[20][40], const int maxnumW, const int maxnumH) {
	a[0][0] = "l";
	a[0][maxnumW - 1] = "l";
	a[maxnumH - 1][0] = "l";
	a[maxnumH - 1][maxnumW - 1] = "l";

	for (int x = 1; x < maxnumW - 1; x++) {
		a[0][x] = "-";
		a[maxnumH - 1][x] = "-";
	}
	for (int x = 1; x < maxnumH - 1; x++) {
		a[x][0] = "l";
		a[x][maxnumW - 1] = "l";
		for (int y = 1; y < maxnumW - 1; y++) {
			a[x][y] = " ";
		}
	}
	for (int x = 0; x < maxnumH; x++) {
		for (int y = 0; y < maxnumW; y++) {
			cout << a[x][y];
		}
		cout << endl;
	}
}

