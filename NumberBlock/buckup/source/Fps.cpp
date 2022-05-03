#include "Fps.h"
Fps::Fps(){}
Fps::~Fps(){}
int Fps::CheckFps() {

	NT = timeGetTime();
	if ((NT - PT) < 0)return -fps;//何フレームに一回回すか
	PT = NT;
	Nowtime = timeGetTime();
	Cnt++;
	if ((Nowtime - PrevTime) >= 1000) {//一秒間計測後Fpsに出力
		PrevTime = Nowtime;
		fps = Cnt;
		Cnt = 0;
	}
	return fps;
}