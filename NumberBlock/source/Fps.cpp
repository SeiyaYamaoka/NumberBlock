#include "Fps.h"
Fps::Fps(){}
Fps::~Fps(){}
int Fps::CheckFps() {

	NT = timeGetTime();
	if ((NT - PT) < 0)return -fps;//���t���[���Ɉ��񂷂�
	PT = NT;
	Nowtime = timeGetTime();
	Cnt++;
	if ((Nowtime - PrevTime) >= 1000) {//��b�Ԍv����Fps�ɏo��
		PrevTime = Nowtime;
		fps = Cnt;
		Cnt = 0;
	}
	return fps;
}