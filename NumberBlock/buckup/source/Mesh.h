#pragma once
#include"Main.h"
#include<string>
class Mesh
{
public:
	Mesh();
	~Mesh();

	static struct XFILE {
		LPD3DXMESH lpMesh;//メッシュの形のデータ
		DWORD NumMaterial;//マテリアルの個数
		D3DMATERIAL9 *Mat;//マテリアルのデータ
		LPDIRECT3DTEXTURE9 *Tex;//テクスチャのデータ
	};
	static struct CLONEVERTEX {
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 Tex;
	};//クローンと同じ　座標　法線　テクスチャ座標


	XFILE xMesh;
	void DrawMesh();
	//void LoadMesh( char FName[]);
	void ReleaseMesh();

	void Init() ;
	void load();
	void Update();
	void Render();
	void SetPos(float x,float y,float z);
	void SetPos(D3DXVECTOR3 d);
	void SetPos(D3DXMATRIX *d);
	void SetRot(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetMatrix(D3DXMATRIX w) {
		mWorld = w;
	}

	std::string mname = "";
	D3DXMATRIX mPos, mRot, mScale, mWorld;
private:

	


};


