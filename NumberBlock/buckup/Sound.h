#pragma once

#pragma comment(lib, "dsound.lib")
#include "source/Main.h"
#include<dsound.h>
#include "source/wavread.h"
class Sound {
public:

#define SOUNDNUM 5
#define mug common::getInstance()
	Sound() {//������-------------------------------------------------------------
	//---------------------DirectSound�֘A-----------------------
		DirectSoundCreate8(NULL, &lpDSound, NULL);

		//�������x����ݒ�
		lpDSound->SetCooperativeLevel(cdg.hwnd, DSSCL_PRIORITY);

		// �v���C�}���E�o�b�t�@�̍쐬
		// DSBUFFERDESC�\���̂�ݒ�
		DSBUFFERDESC dsbdesc;
		ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
		dsbdesc.dwSize = sizeof(DSBUFFERDESC);
		// �v���C�}���E�o�b�t�@���w��
		dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
		dsbdesc.dwBufferBytes = 0;
		dsbdesc.lpwfxFormat = NULL;

		// �o�b�t�@�����
		lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL);

		// �v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
		// �@�@�@�D�拦�����x���ȏ�̋������x�����ݒ肳��Ă���K�v������܂��D
		WAVEFORMATEX pcmwf;
		ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX));
		pcmwf.wFormatTag = WAVE_FORMAT_PCM;
		pcmwf.nChannels = 2;		// �Q�`�����l���i�X�e���I�j
		pcmwf.nSamplesPerSec = 44100;	// �T���v�����O�E���[�g�@44.1kHz
		pcmwf.nBlockAlign = 4;
		pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
		pcmwf.wBitsPerSample = 16;		// 16�r�b�g
		lpSPrimary->SetFormat(&pcmwf);

		CoInitialize(NULL);
		LoadWAVE3D(lpSBGM, lpS3DBGM, "Sound/tw052.mp3");
		lpS3DBGM->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);//�RD����Ȃ����[�h
		lpSBGM->Play(0, 0, DSBPLAY_LOOPING);//�Đ��@���[�v�[����O����:DSBPLAY_LOOPING


											//LoadWAVE3D(lpSSE, lpS3DSE, "Test.WAV");
											//lpS3DSE->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);//
											//lpS3DSE->SetPosition(x, y, z, DS3D_IMMEDIATE);//�����̈ʒu
		LoadWAVE3D(lpSSE[0], lpS3DSE[0], "Sound/se_maoudamashii_system31.wav");
		lpS3DSE[0]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
		lpS3DSE[0]->SetPosition(x, y, z, DS3D_IMMEDIATE);//�����̈ʒu
		LPDIRECTSOUNDBUFFER lpSTmp;
		for (int i = 0; i < SOUNDNUM; i++) {
			lpDSound->DuplicateSoundBuffer(lpSSE[0], &lpSTmp);
			lpSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID *)&lpSSE[i]);
			lpSSE[i]->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID *)&lpS3DSE[i]);
			lpS3DSE[i]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
			lpSTmp->Release();
		}

		lpSBGM->GetFrequency(&Hz);//���g���擾

		lpSPrimary->QueryInterface(IID_IDirectSound3DListener8, (LPVOID *)&lpSListener);//���X�i�[�̐���
		lpSListener->SetRolloffFactor(0.3f, DS3D_IMMEDIATE);//�������
	};
	~Sound() {
		lpSBGM->Release();
		lpS3DBGM->Release();//lpDSound����ɏ���
		for (int i = 0; i < SOUNDNUM; i++) {
			lpSSE[i]->Release();
			lpS3DSE[i]->Release();
		}
		CoUninitialize();

		lpSListener->Release();

		//���---------------------------------------------------------------
		lpSPrimary->Release();
		lpDSound->Release();
	};
	static common &getInstance() {
		static common Instance;
		return Instance;
	}
	LPDIRECTSOUND8 lpDSound;	//DirectSound�I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER lpSPrimary;

	LPDIRECTSOUNDBUFFER8 lpSBGM;//�Z�J���_���o�b�t�@
	LPDIRECTSOUND3DBUFFER lpS3DBGM;//�ݒ�p
	DWORD Hz;

	LPDIRECTSOUNDBUFFER8 lpSSE[SOUNDNUM];//test.wav�p
	LPDIRECTSOUND3DBUFFER lpS3DSE[SOUNDNUM];//
	LPDIRECTSOUND3DLISTENER8 lpSListener;


	float x = 0, y = 10, z = 100;

	void LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, char *fname);
	void SoundProc(D3DXVECTOR3 CPos, D3DXVECTOR3 CLook, D3DXVECTOR3 CHead);
};