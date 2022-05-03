#pragma once
#include "Main.h"

class polygon {
public:
	polygon() {
		LoadText("Texture/36.jpg"/*"waku.png"*/, 512, 512/*16,16*/, D3DCOLOR_XRGB(255, 0, 0));
		SetPos(0, 0, 0);
		SetRot(0, 0, 0);
		v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
		v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
		v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
		v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);
	};
	~polygon() { };
	// 今回使用する頂点フォーマットの定義
	struct VERTEX
	{
		D3DXVECTOR3 Pos;
		D3DCOLOR Color;
		D3DXVECTOR2 Tex;
	};
	VERTEX v[4];
	D3DXMATRIX mWorld;
	D3DXMATRIX mPos;
	D3DXMATRIX mRot;
	LPDIRECT3DTEXTURE9 lpText;
	float Ang;
	int num = 0;
	int num1 = 0;
	void DrawPolygon();
	void SetPolygon(float x1, float y1, float z1, float x2, float y2, float z2);
	void SetPos(float x, float y, float z) {
		D3DXMatrixTranslation(&mPos, x, y, z);
	}
	void SetRot(float Angx, float Angy, float Angz) {
		D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(Angy), D3DXToRadian(Angx), D3DXToRadian(Angz));
	}
	void LoadText(char fname[], int W, int H, D3DCOLOR Color);
	void SetTex(float x, float y, float n);

};