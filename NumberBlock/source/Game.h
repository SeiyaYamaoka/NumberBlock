#pragma once
#include<vector>
#include"Main.h"
#include"Mesh.h"
#include"CharaMove.h"
#include"DebagDrawText.h"
#include"Fps.h"
#include"polygon.h"
#include"Load.h"
#include"FileOperation.h"
#include <io.h>
#include <Fcntl.h>
#include "ModelShader.h"
#include "random"
#include "Sound.h"

class Game {
public:

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

	// 最初に1回実行
	void Init();
	// 最後に一回実行
	void Release();

	// [毎回実行]処理を書く
	void Update();
	// [毎回実行]描画を書く
	void Draw();

	void DrawFrame();

	int debagflg = 1;

	int time0 = 0;
	int baniflg = 0;

	int resultflg = 0;
	int startflg = 0;
	int starttime = 3;
	int tcount = 0;
	std::random_device srnd;

	std::random_device brnd;
	
	int Score ;

	DWORD start, end;
	int count = 0;

	Fps fps;
	Sound sou;
	
	polygon ground;

	ModelShader m_MS;
	
	//カメラ移動
	CharaMove CM;

	//カメラパラメータ
	D3DXVECTOR3 CPos = D3DXVECTOR3(0.0f, 5.0f, -10.0f),
				CLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				CHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	int blockmax;
	//UI
	LPDIRECT3DTEXTURE9 lpTimehair;
	LPD3DXSPRITE lpTime;
	D3DXMATRIX mTimeWorld;
	D3DXMATRIX mTimeTrans;
	D3DXMATRIX mScoreWorld;
	D3DXMATRIX mScoreTrans;
	D3DXMATRIX mTimeupWorld;
	D3DXMATRIX mStartWorld;
	D3DXMATRIX mStarttimeWorld;
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
	D3DXMATRIX mTTWorld;

	D3DXMATRIX mSWorld;


	common::MAP map[common::mapmax][common::mapmax][common::mapmax];

	static struct stage {
		int meshnum;
		int blockinfnum = -1;
		BOOL display;
		D3DXVECTOR3 xyz;
		int deathflg = 0;
	};

	static struct chara {
		D3DXVECTOR3 xyz;
		int x, y, z;
		int num;
		int meshnum;
		float frame = 0;
	};
	static const int smax = 7;

	stage s[smax][smax][smax];
	chara c;

	int filenum = 0;
	int num = 0;


	//std::vector<D3DXVECTOR3> stage;
	//std::vector<std::string> mn;

	static struct CLONEVERTEX {
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 Tex;
	};//クローンと同じ　座標　法線　テクスチャ座標

	int sai[6];
	int tatesai[4], yokosai[4];
	void saiinit() { //136452   3 -- 2  4--5   
		sai[0] = 1; sai[1] = 2; sai[2] = 6; sai[3] = 5; sai[4] = 4; sai[5] = 3;//サイコロの目の数字上から手前側にぐるっと回って左右の順
		tatesai[0] = sai[0]; tatesai[1] = sai[1]; tatesai[2] = sai[2]; tatesai[3] = sai[3];
		yokosai[0] = sai[0]; yokosai[1] = sai[5]; yokosai[2] = sai[2]; yokosai[3] = sai[4];
	}
	void setsai(int tate[],int yoko[]){
		sai[0] = tatesai[0]; sai[1] = tatesai[1]; sai[2] = tatesai[2]; sai[3] = tatesai[3]; sai[4] = yokosai[3]; sai[5] = yokosai[1];
	}//

	 //キーフレームアニメーション
	D3DXMATRIX mStart, mEnd, mNow;
	float AnimeFrame;

	int keyaniflg = 0;
	float keyaniroty = 0;
	float keyanirotz = 0;
	float keyanirotx = 0;
	D3DXMATRIX miden;
	void AnimeProc(void) {
		D3DXQUATERNION qStart, qEnd, qNow;
		D3DXQuaternionRotationMatrix(&qStart, &mStart);
		D3DXQuaternionRotationMatrix(&qEnd, &mEnd);
		D3DXQuaternionSlerp(&qNow, &qStart, &qEnd, AnimeFrame);
		D3DXMatrixRotationQuaternion(&mNow, &qNow);
		D3DXVECTOR3 StartPos, EndPos, NowPos;
		StartPos = D3DXVECTOR3(mStart._41, mStart._42, mStart._43);
		EndPos = D3DXVECTOR3(mEnd._41, mEnd._42, mEnd._43);
		D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, AnimeFrame);

		//meshinf[c.meshnum]->SetPos(NowPos);
		//meshinf[c.meshnum]->mWorld = mNow;
		//meshinf[c.meshnum]->Update();
		mNow._41 = NowPos.x;
		mNow._42 = NowPos.y;
		mNow._43 = NowPos.z;
	}

	float baniframe;
	int blaniflg = 0;

	D3DXMATRIX AnimeProc(D3DXMATRIX *mStart, D3DXMATRIX *mEnd, D3DXMATRIX *mNow,float frame) {
		D3DXQUATERNION qStart, qEnd, qNow;
		D3DXQuaternionRotationMatrix(&qStart, mStart);
		D3DXQuaternionRotationMatrix(&qEnd, mEnd);
		D3DXQuaternionSlerp(&qNow, &qStart, &qEnd, frame);
		D3DXMatrixRotationQuaternion(mNow, &qNow);
		D3DXVECTOR3 StartPos, EndPos, NowPos;
		StartPos = D3DXVECTOR3(mStart->_41, mStart->_42, mStart->_43);
		EndPos = D3DXVECTOR3(mEnd->_41, mEnd->_42, mEnd->_43);
		D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, frame);

		//meshinf[c.meshnum]->SetPos(NowPos);
		//meshinf[c.meshnum]->mWorld = mNow;
		//meshinf[c.meshnum]->Update();
		mNow->_41 = NowPos.x;
		mNow->_42 = NowPos.y;
		mNow->_43 = NowPos.z;
		
		return *mNow;
	}


	void LoadText(char fname[], int W, int H, D3DCOLOR Color, LPDIRECT3DTEXTURE9 *lp)
	{
		if (W == 0)W = D3DX_DEFAULT;
		if (H == 0)H = D3DX_DEFAULT;
		D3DXCreateTextureFromFileEx(cdg.lpD3DDevice, fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lp);
	}

	//std::vector<D3DXVECTOR3 *> poinf;
	std::vector<polygon *> polyinf;
	std::vector<Mesh *> meshinf;

	static struct block {
		D3DXVECTOR3 xyz;
		int x, y, z;
		int blocknum;
		int meshnum;
		int braniflg = 0;
		float frame = 0;
	};
	std::vector<block *> blockinf;




	int minDis(std::vector<float > Dis, UINT len) {
		float min=FLT_MAX;
		int i = 0, j = 0;
		int k = 0;
		for ( i = 0; i < len; i++) {
			
			if (Dis[i] > 0&&min > Dis[i]) { min = Dis[i]; j = i; }
			else { k++; }
		}
		if (k >= len) {
			return -1;
		}
		else {
			return j;
		}
	}

	

};