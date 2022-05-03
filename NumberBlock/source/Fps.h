#pragma once
#include <d3dx9.h>
class Fps {
public:
	Fps();
	~Fps();
	DWORD Nowtime, PrevTime;
	int Cnt, fps;
	DWORD NT, PT;
	int CheckFps();
};