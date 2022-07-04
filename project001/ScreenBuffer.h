#pragma once
# define FIELD_WIDTH  50
# define FIELD_HEIGHT 25
class ScreenBuffer {
private:
	char front_buffer[FIELD_HEIGHT][FIELD_WIDTH];
	char back_buffer[FIELD_HEIGHT][FIELD_WIDTH];

public:
	ScreenBuffer();
	void render();
	void drawToBackBuffer(const int x, const int y, const char image);
	void drawToBackBuffer(const int x, const int y, const char* image);
};