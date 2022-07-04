#include <iostream>
#include <Windows.h>
#include "ScreenBuffer.h" 
using namespace std;

ScreenBuffer::ScreenBuffer()
{
	system("cls");
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			front_buffer[y][x] = 0; 
			back_buffer[y][x] = 0; 
		} 
	}
}

void ScreenBuffer::render()
{
	for (int y = 0; y < FIELD_HEIGHT; y++)
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			if (back_buffer[y][x] != front_buffer[y][x])
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)x, (short)y }); 
				if (back_buffer[y][x] == 0)
					cout << ' ';
				else 
					cout << back_buffer[y][x];
			}
		}
	for (int y = 0; y < FIELD_HEIGHT; y++)
		for (int x = 0; x < FIELD_WIDTH; x++)
		{ 
			front_buffer[y][x] = back_buffer[y][x];
			back_buffer[y][x] = 0; 
		}
}

void ScreenBuffer::drawToBackBuffer(const int x, const int y, const char image)
{
	back_buffer[y][x] = image;
}

void ScreenBuffer::drawToBackBuffer(const int x, const int y, const char* image)
{
	for (int index = 0; image[index] != 0; index++)
		back_buffer[y][x + index] = image[index];
}