#pragma once
#include"Main.h"
#include "Sound.h"
#include<stdio.h>
#include "FileOperation.h"
class Title {
public:
	Title() {};
	~Title() {};
	Sound s;
	// 最初に1回実行
	void Init();
	// 最後に一回実行
	void Release();

	// [毎回実行]処理を書く
	void Update();
	// [毎回実行]描画を書く
	void Draw();

	void DrawFrame();
	D3DXVECTOR3 CPos = D3DXVECTOR3(0.0f, 5.0f, -10.0f),
		CLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		CHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	LPDIRECT3DTEXTURE9 lpTimehair;
	LPD3DXSPRITE lpTime;
	D3DXMATRIX mTimeWorld;
	D3DXMATRIX mTTWorld;
	D3DXMATRIX mTimeTrans;
	RECT rcNum[10] = { { 0,0,38,64 },
	{ 39,0,76,64 },
	{ 77,0,114,64 },
	{ 115,0,152,64 },
	{ 153,0,190,64 },
	{ 191,0,228,64 },
	{ 229,0,266,64 },
	{ 267,0,304,64 },
	{ 306,0,342,64 },
	{ 343,0,380,64 } };
	LPDIRECT3DTEXTURE9 lpTimetext;
	LPD3DXSPRITE lpTimetextsp;
	D3DXMATRIX mScoreWorld;
	//テクスチャ
	int highscore = 0;
	LPDIRECT3DTEXTURE9 lpCrosshair;
	LPD3DXSPRITE lpCross;
	D3DXMATRIX mCrossWorld;
	LPDIRECT3DTEXTURE9 lpText;
	void LoadText(char fname[], int W, int H, D3DCOLOR Color, LPDIRECT3DTEXTURE9 *lp)
	{
		if (W == 0)W = D3DX_DEFAULT;
		if (H == 0)H = D3DX_DEFAULT;
		D3DXCreateTextureFromFileEx(cdg.lpD3DDevice, fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lp);
	}

};