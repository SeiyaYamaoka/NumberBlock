#pragma once
#include<d3dx9.h>
class common {
public:	
	// 簡単にアクセスできるようにするためのマクロ
#define cdg common::getInstance()
#define	SCRW		1280	// Width	16:9
#define	SCRH		720	// Height

	BOOL EnterFlg = FALSE;
	BOOL EscapeFlg = FALSE;
	BOOL SpaceFlg = FALSE;
	int scean = 0;

	LPDIRECT3DDEVICE9		GetDev() { return lpD3DDevice; }			// D3Dデバイス取得
	IDirect3DDevice9*			lpD3DDevice;			// D3Dデバイス
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