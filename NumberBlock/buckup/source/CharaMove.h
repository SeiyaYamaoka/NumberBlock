#pragma once
#include<vector>
#include"Main.h"
#include"polygon.h"
#include"Mesh.h"
#include"DebagDrawText.h"


class CharaMove {
public:
	const float MOVE =		0.5f;		//移動速度
	const float H_ROTATE =	2.0;		//水平方向　回転速度
	const float V_ROTATE =	1.0;		//垂直方向　回転速度
	const float JUMP =		1.0f;		//ジャンプ
	const float GRAVITY =	0.05f;		//重力
	float AngX, AngY;
	D3DXMATRIX mRotY,mRot,mRotX;
	CharaMove();
	~CharaMove();
	void Update(D3DXVECTOR3 *CPos, D3DXVECTOR3 *CLook, D3DXVECTOR3 *CHead) ;
	float Accel;
	int JumpFlg;
	float ksk = 0.5f;
	float kskPlus = 0.0f;
	D3DXVECTOR3 kskVec;
	float kskWASD[4];
	float AngPlus;
	float fPRot;
	float Ang;

	float camz=-10.0f;

	D3DXMATRIX xRot;
	D3DXMATRIX mWorld;
	D3DXMATRIX sTrans, sRot, mIden;
	D3DXMATRIX mScale;

	D3DXMATRIX mWall;


	D3DXMATRIX BallUpdate(D3DXVECTOR3 *CPos, D3DXVECTOR3 *CLook, D3DXVECTOR3 *CHead);

	D3DXMATRIX TPVUpdate(D3DXVECTOR3 *CPos, D3DXVECTOR3 *CLook, D3DXVECTOR3 *CHead);
	std::vector<polygon *> poinfo;
	std::vector<Mesh *> meshinfo;
	void SetMat(std::vector<Mesh *> * mes) {
		meshinfo = *mes;
	}
	static struct CLONEVERTEX {
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 Tex;
	};//クローンと同じ　座標　法線　テクスチャ座標

	void SetPol(std::vector<polygon *> *pol) {
		poinfo = *pol;
	}
	void Setmatrix(D3DXMATRIX trans,  D3DXMATRIX scale) {
		sTrans = trans;
		mScale = scale;
	}
	void init() {
		D3DXMatrixTranslation(&sTrans, 0, 100, 0);
		D3DXMatrixRotationX(&sRot, 0);
		D3DXMatrixRotationX(&xRot, 0);
		D3DXMatrixScaling(&mScale, 1, 1, 1);
	}
};