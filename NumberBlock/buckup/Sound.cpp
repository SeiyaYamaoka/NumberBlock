#include "Sound.h"

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