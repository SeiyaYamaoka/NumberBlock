#pragma once

#pragma comment(lib, "dsound.lib")
#include "source/Main.h"
#include<dsound.h>
#include "source/wavread.h"
class Sound {
public:

#define SOUNDNUM 5
#define mug common::getInstance()
	Sound() {//初期化-------------------------------------------------------------
	//---------------------DirectSound関連-----------------------
		DirectSoundCreate8(NULL, &lpDSound, NULL);

		//協調レベルを設定
		lpDSound->SetCooperativeLevel(cdg.hwnd, DSSCL_PRIORITY);

		// プライマリ・バッファの作成
		// DSBUFFERDESC構造体を設定
		DSBUFFERDESC dsbdesc;
		ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
		dsbdesc.dwSize = sizeof(DSBUFFERDESC);
		// プライマリ・バッファを指定
		dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
		dsbdesc.dwBufferBytes = 0;
		dsbdesc.lpwfxFormat = NULL;

		// バッファを作る
		lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL);

		// プライマリ・バッファのWaveフォーマットを設定
		// 　　　優先協調レベル以上の協調レベルが設定されている必要があります．
		WAVEFORMATEX pcmwf;
		ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX));
		pcmwf.wFormatTag = WAVE_FORMAT_PCM;
		pcmwf.nChannels = 2;		// ２チャンネル（ステレオ）
		pcmwf.nSamplesPerSec = 44100;	// サンプリング・レート　44.1kHz
		pcmwf.nBlockAlign = 4;
		pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
		pcmwf.wBitsPerSample = 16;		// 16ビット
		lpSPrimary->SetFormat(&pcmwf);

		CoInitialize(NULL);
		LoadWAVE3D(lpSBGM, lpS3DBGM, "Sound/tw052.mp3");
		lpS3DBGM->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);//３Dじゃないモード
		lpSBGM->Play(0, 0, DSBPLAY_LOOPING);//再生　ループー＞第三引数:DSBPLAY_LOOPING


											//LoadWAVE3D(lpSSE, lpS3DSE, "Test.WAV");
											//lpS3DSE->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);//
											//lpS3DSE->SetPosition(x, y, z, DS3D_IMMEDIATE);//音源の位置
		LoadWAVE3D(lpSSE[0], lpS3DSE[0], "Sound/se_maoudamashii_system31.wav");
		lpS3DSE[0]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
		lpS3DSE[0]->SetPosition(x, y, z, DS3D_IMMEDIATE);//音源の位置
		LPDIRECTSOUNDBUFFER lpSTmp;
		for (int i = 0; i < SOUNDNUM; i++) {
			lpDSound->DuplicateSoundBuffer(lpSSE[0], &lpSTmp);
			lpSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID *)&lpSSE[i]);
			lpSSE[i]->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID *)&lpS3DSE[i]);
			lpS3DSE[i]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
			lpSTmp->Release();
		}

		lpSBGM->GetFrequency(&Hz);//周波数取得

		lpSPrimary->QueryInterface(IID_IDirectSound3DListener8, (LPVOID *)&lpSListener);//リスナーの生成
		lpSListener->SetRolloffFactor(0.3f, DS3D_IMMEDIATE);//聞こえ具合
	};
	~Sound() {
		lpSBGM->Release();
		lpS3DBGM->Release();//lpDSoundより先に書く
		for (int i = 0; i < SOUNDNUM; i++) {
			lpSSE[i]->Release();
			lpS3DSE[i]->Release();
		}
		CoUninitialize();

		lpSListener->Release();

		//解放---------------------------------------------------------------
		lpSPrimary->Release();
		lpDSound->Release();
	};
	static common &getInstance() {
		static common Instance;
		return Instance;
	}
	LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト
	LPDIRECTSOUNDBUFFER lpSPrimary;

	LPDIRECTSOUNDBUFFER8 lpSBGM;//セカンダリバッファ
	LPDIRECTSOUND3DBUFFER lpS3DBGM;//設定用
	DWORD Hz;

	LPDIRECTSOUNDBUFFER8 lpSSE[SOUNDNUM];//test.wav用
	LPDIRECTSOUND3DBUFFER lpS3DSE[SOUNDNUM];//
	LPDIRECTSOUND3DLISTENER8 lpSListener;


	float x = 0, y = 10, z = 100;

	void LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, char *fname);
	void SoundProc(D3DXVECTOR3 CPos, D3DXVECTOR3 CLook, D3DXVECTOR3 CHead);
};