#pragma once
#include "Main.h"
#include<dsound.h>
#include "wavread.h"
#pragma comment(lib, "dsound.lib")
class Sound {
public:

#define SOUNDNUM 5
#define mug Sound::getInstance()
	Sound() { /*Init();*/ };
	~Sound() {/* Release();*/ };

	LPDIRECTSOUND8 lpDSound;	//DirectSound�I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER lpSPrimary;

	LPDIRECTSOUNDBUFFER8 lpSBGM;//�Z�J���_���o�b�t�@
	LPDIRECTSOUND3DBUFFER lpS3DBGM;//�ݒ�p
	DWORD Hz;

	LPDIRECTSOUND8 lpDGSound;	//DirectSound�I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER8 lpSGBGM;//�Z�J���_���o�b�t�@

	LPDIRECTSOUNDBUFFER8 lpSSE[SOUNDNUM];//test.wav�p
	LPDIRECTSOUND3DBUFFER lpS3DSE[SOUNDNUM];//
	LPDIRECTSOUNDBUFFER8 SE;
	LPDIRECTSOUNDBUFFER8 SE1;
	LPDIRECTSOUNDBUFFER8 SE2;
	//robot-footstep2.mp3

	LPDIRECTSOUND3DLISTENER8 lpSListener;

	float x = 0, y = 10, z = 100;

	void Init();
	void Release();

	void LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, char *fname);
	void SoundProc(D3DXVECTOR3 CPos, D3DXVECTOR3 CLook, D3DXVECTOR3 CHead);
	void LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND8 lpDSound, char *fname);


	static Sound &getInstance() {
		static  Sound Instance;
		return Instance;
	}

};