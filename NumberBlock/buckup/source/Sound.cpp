#include "Sound.h"
void Sound::LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND8 lpDSound, char *fname)
{
	HRESULT hr;

	// WAVE�t�@�C�����J��
	CWaveSoundRead WaveFile;
	WaveFile.Open(fname);

	// �Z�J���_���E�o�b�t�@���쐬����
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	// �o�b�t�@�����
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSData);
	pDSTmp->Release();

	// �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
	LPVOID lpvPtr1;		// �ŏ��̃u���b�N�̃|�C���^
	DWORD dwBytes1;		// �ŏ��̃u���b�N�̃T�C�Y
	LPVOID lpvPtr2;		// �Q�Ԗڂ̃u���b�N�̃|�C���^
	DWORD dwBytes2;		// �Q�Ԗڂ̃u���b�N�̃T�C�Y

	hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
	if (DSERR_BUFFERLOST == hr)
	{
		pDSData->Restore();
		hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ���b�N����

		// �����ŁC�o�b�t�@�ɏ�������
		// �o�b�t�@�Ƀf�[�^���R�s�[����
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// �������݂��I������炷����Unlock����D
		hr = pDSData->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}
}
void Sound::LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, char *fname)
{
	HRESULT hr;

	// WAVE�t�@�C�����J��
	CWaveSoundRead WaveFile;
	WaveFile.Open(fname);

	// �Z�J���_���E�o�b�t�@���쐬����
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	//(DSBCAPS_CTRL3D=�R�c�T�E���h���g�p)
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRL3D |
		DSBCAPS_CTRLVOLUME | /*DSBCAPS_CTRLPAN |*/ DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	//3D�T�E���h��HEL�A���S���Y����I��
	dsbdesc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
	//	dsbdesc.guid3DAlgorithm=DS3DALG_DEFAULT;

	// �o�b�t�@�����
	LPDIRECTSOUNDBUFFER pDSTmp;
	//lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSData);
	pDSTmp->Release();

	// �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
	LPVOID lpvPtr1;		// �ŏ��̃u���b�N�̃|�C���^
	DWORD dwBytes1;		// �ŏ��̃u���b�N�̃T�C�Y
	LPVOID lpvPtr2;		// �Q�Ԗڂ̃u���b�N�̃|�C���^
	DWORD dwBytes2;		// �Q�Ԗڂ̃u���b�N�̃T�C�Y

	hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
	if (DSERR_BUFFERLOST == hr)
	{
		pDSData->Restore();
		hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ���b�N����

		// �����ŁC�o�b�t�@�ɏ�������
		// �o�b�t�@�Ƀf�[�^���R�s�[����
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// �������݂��I������炷����Unlock����D
		hr = pDSData->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}

	//3D�̃Z�J���_���o�b�t�@�����
	pDSData->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&pDSData3D);
}
void Sound::SoundProc(D3DXVECTOR3 CPos, D3DXVECTOR3 CLook, D3DXVECTOR3 CHead) {
	lpSListener->SetPosition(CPos.x, CPos.y, CPos.z, DS3D_IMMEDIATE);//�J���������X�i�[

																	 //D3DXMATRIX mRotY, mRotX,mRot;

																	 //D3DXMatrixRotationY(&mRotY, D3DXToRadian(CamAngY));
																	 //D3DXMatrixRotationY(&mRotX, D3DXToRadian(CamAngX));
																	 //mRot = mRotX*mRotY;
																	 //D3DXVec3TransformNormal(&CLook, &D3DXVECTOR3(0, 0, 1), &mRot);
																	 //D3DXVec3TransformNormal(&CHead, &D3DXVECTOR3(0, 1, 0), &mRot);


	lpSListener->SetOrientation(CLook.x, CLook.y, CLook.z,//���X�i�[�����Ă������
		CHead.x, CHead.y, CHead.z,//���X�i�[�̓��̕���
		DS3D_IMMEDIATE);


}
void Sound::Init() {
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
	LoadWAVE(lpSBGM, lpDSound, "Sound/vigilante.WAV");
	LoadWAVE(lpSGBGM, lpDSound, "Sound/tw052 (online-audio-converter.com).WAV");
//	lpS3DBGM->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);//�RD����Ȃ����[�h
	//lpSBGM->Play(0, 0, DSBPLAY_LOOPING);//�Đ��@���[�v�[����O����:DSBPLAY_LOOPING


										//LoadWAVE3D(lpSSE, lpS3DSE, "Test.WAV");
										//lpS3DSE->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);//
										//lpS3DSE->SetPosition(x, y, z, DS3D_IMMEDIATE);//�����̈ʒu
	LoadWAVE(SE, lpDSound, "Sound/se_maoudamashii_system31.wav");
	LoadWAVE(SE1, lpDSound, "Sound/se_maoudamashii_system32.wav");
	LoadWAVE(SE2, lpDSound, "Sound/putting_a_frying_pan.wav");
	//lpS3DSE[0]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
	//lpS3DSE[0]->SetPosition(x, y, z, DS3D_IMMEDIATE);//�����̈ʒu
	//LPDIRECTSOUNDBUFFER lpSTmp;
	//for (int i = 0; i < SOUNDNUM; i++) {
	//	lpDSound->DuplicateSoundBuffer(lpSSE[0], &lpSTmp);
	//	lpSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID *)&lpSSE[i]);
	//	lpSSE[i]->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID *)&lpS3DSE[i]);
	//	lpS3DSE[i]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
	//	lpSTmp->Release();
	//}

	lpSBGM->GetFrequency(&Hz);//���g���擾

	lpSPrimary->QueryInterface(IID_IDirectSound3DListener8, (LPVOID *)&lpSListener);//���X�i�[�̐���
	lpSListener->SetRolloffFactor(0.3f, DS3D_IMMEDIATE);//�������
}
void Sound::Release() {
	// �I������
	lpSBGM->Release();
	lpSGBGM->Release();
	//lpS3DBGM->Release();//lpDSound����ɏ���
	//for (int i = 0; i < SOUNDNUM; i++) {
		SE->Release();
		SE1->Release();
		SE2->Release();
	//	lpS3DSE[i]->Release();
	//}

	CoUninitialize();

	lpSListener->Release();

	//���---------------------------------------------------------------
	lpSPrimary->Release();
	lpDSound->Release();
}