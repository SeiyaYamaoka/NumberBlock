#pragma once
#include<d3dx9.h>
class common {
public:	
	// �ȒP�ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃}�N��
#define cdg common::getInstance()
#define	SCRW		1280	// Width	16:9
#define	SCRH		720	// Height

	BOOL EnterFlg = FALSE;
	BOOL EscapeFlg = FALSE;
	BOOL SpaceFlg = FALSE;
	int scean = 0;

	LPDIRECT3DDEVICE9		GetDev() { return lpD3DDevice; }			// D3D�f�o�C�X�擾
	IDirect3DDevice9*			lpD3DDevice;			// D3D�f�o�C�X
	//LPDIRECT3DDEVICE9		lpD3DDevice;
	static common &getInstance() {
		static common Instance;
		return Instance;
	}
	static const int mapmax = 10;
	struct MAP {
		D3DXVECTOR3 Pos;
		int m = 1;
	};
	HWND hwnd;

};