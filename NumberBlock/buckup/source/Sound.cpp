#include "Sound.h"
void Sound::LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND8 lpDSound, char *fname)
{
	HRESULT hr;

	// WAVEファイルを開く
	CWaveSoundRead WaveFile;
	WaveFile.Open(fname);

	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	// バッファを作る
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSData);
	pDSTmp->Release();

	// セカンダリ・バッファにWaveデータを書き込む
	LPVOID lpvPtr1;		// 最初のブロックのポインタ
	DWORD dwBytes1;		// 最初のブロックのサイズ
	LPVOID lpvPtr2;		// ２番目のブロックのポインタ
	DWORD dwBytes2;		// ２番目のブロックのサイズ

	hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if (DSERR_BUFFERLOST == hr)
	{
		pDSData->Restore();
		hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ロック成功

		// ここで，バッファに書き込む
		// バッファにデータをコピーする
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// 書き込みが終わったらすぐにUnlockする．
		hr = pDSData->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}
}
void Sound::LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, char *fname)
{
	HRESULT hr;

	// WAVEファイルを開く
	CWaveSoundRead WaveFile;
	WaveFile.Open(fname);

	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	//(DSBCAPS_CTRL3D=３Ｄサウンドを使用)
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRL3D |
		DSBCAPS_CTRLVOLUME | /*DSBCAPS_CTRLPAN |*/ DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	//3DサウンドのHELアルゴリズムを選択
	dsbdesc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
	//	dsbdesc.guid3DAlgorithm=DS3DALG_DEFAULT;

	// バッファを作る
	LPDIRECTSOUNDBUFFER pDSTmp;
	//lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSData);
	pDSTmp->Release();

	// セカンダリ・バッファにWaveデータを書き込む
	LPVOID lpvPtr1;		// 最初のブロックのポインタ
	DWORD dwBytes1;		// 最初のブロックのサイズ
	LPVOID lpvPtr2;		// ２番目のブロックのポインタ
	DWORD dwBytes2;		// ２番目のブロックのサイズ

	hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if (DSERR_BUFFERLOST == hr)
	{
		pDSData->Restore();
		hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ロック成功

		// ここで，バッファに書き込む
		// バッファにデータをコピーする
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// 書き込みが終わったらすぐにUnlockする．
		hr = pDSData->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}

	//3Dのセカンダリバッファを作る
	pDSData->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&pDSData3D);
}
void Sound::SoundProc(D3DXVECTOR3 CPos, D3DXVECTOR3 CLook, D3DXVECTOR3 CHead) {
	lpSListener->SetPosition(CPos.x, CPos.y, CPos.z, DS3D_IMMEDIATE);//カメラがリスナー

																	 //D3DXMATRIX mRotY, mRotX,mRot;

																	 //D3DXMatrixRotationY(&mRotY, D3DXToRadian(CamAngY));
																	 //D3DXMatrixRotationY(&mRotX, D3DXToRadian(CamAngX));
																	 //mRot = mRotX*mRotY;
																	 //D3DXVec3TransformNormal(&CLook, &D3DXVECTOR3(0, 0, 1), &mRot);
																	 //D3DXVec3TransformNormal(&CHead, &D3DXVECTOR3(0, 1, 0), &mRot);


	lpSListener->SetOrientation(CLook.x, CLook.y, CLook.z,//リスナーが見ている方向
		CHead.x, CHead.y, CHead.z,//リスナーの頭の方向
		DS3D_IMMEDIATE);


}
void Sound::Init() {
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
	LoadWAVE(lpSBGM, lpDSound, "Sound/vigilante.WAV");
	LoadWAVE(lpSGBGM, lpDSound, "Sound/tw052 (online-audio-converter.com).WAV");
//	lpS3DBGM->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);//３Dじゃないモード
	//lpSBGM->Play(0, 0, DSBPLAY_LOOPING);//再生　ループー＞第三引数:DSBPLAY_LOOPING


										//LoadWAVE3D(lpSSE, lpS3DSE, "Test.WAV");
										//lpS3DSE->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);//
										//lpS3DSE->SetPosition(x, y, z, DS3D_IMMEDIATE);//音源の位置
	LoadWAVE(SE, lpDSound, "Sound/se_maoudamashii_system31.wav");
	LoadWAVE(SE1, lpDSound, "Sound/se_maoudamashii_system32.wav");
	LoadWAVE(SE2, lpDSound, "Sound/putting_a_frying_pan.wav");
	//lpS3DSE[0]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
	//lpS3DSE[0]->SetPosition(x, y, z, DS3D_IMMEDIATE);//音源の位置
	//LPDIRECTSOUNDBUFFER lpSTmp;
	//for (int i = 0; i < SOUNDNUM; i++) {
	//	lpDSound->DuplicateSoundBuffer(lpSSE[0], &lpSTmp);
	//	lpSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID *)&lpSSE[i]);
	//	lpSSE[i]->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID *)&lpS3DSE[i]);
	//	lpS3DSE[i]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
	//	lpSTmp->Release();
	//}

	lpSBGM->GetFrequency(&Hz);//周波数取得

	lpSPrimary->QueryInterface(IID_IDirectSound3DListener8, (LPVOID *)&lpSListener);//リスナーの生成
	lpSListener->SetRolloffFactor(0.3f, DS3D_IMMEDIATE);//聞こえ具合
}
void Sound::Release() {
	// 終了処理
	lpSBGM->Release();
	lpSGBGM->Release();
	//lpS3DBGM->Release();//lpDSoundより先に書く
	//for (int i = 0; i < SOUNDNUM; i++) {
		SE->Release();
		SE1->Release();
		SE2->Release();
	//	lpS3DSE[i]->Release();
	//}

	CoUninitialize();

	lpSListener->Release();

	//解放---------------------------------------------------------------
	lpSPrimary->Release();
	lpDSound->Release();
}