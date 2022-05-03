#pragma once
#include"Main.h"
#include<map>
class Load {
public :
	// 簡単にアクセスできるようにするためのマクロ
#define lad Load::getInstance()
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
	
	std::map<std::string, XFILE> mp;

	Load() { 
	LoadMesh("Mesh/saikoro135.x");
	LoadMesh("Mesh/saikoro365.x");
	LoadMesh("Mesh/saikoro645.x");
	LoadMesh("Mesh/saikoro415.x");
	LoadMesh("Mesh/saikoro351.x");
	LoadMesh("Mesh/saikoro421.x");
	LoadMesh("Mesh/saikoro231.x");
	LoadMesh("Mesh/saikoro632.x");
	LoadMesh("Mesh/saikoro536.x");
	LoadMesh("Mesh/saikoro263.x");
	LoadMesh("Mesh/saikoro142.x");
	LoadMesh("Mesh/saikoro456.x");
	LoadMesh("Mesh/saikoro214.x");
	LoadMesh("Mesh/saikoro326.x");
	LoadMesh("Mesh/saikoro564.x");
	LoadMesh("Mesh/saikoro513.x");
	LoadMesh("Mesh/saikoro653.x");
	LoadMesh("Mesh/saikoro462.x");
	LoadMesh("Mesh/saikoro624.x");
	LoadMesh("Mesh/saikoro154.x");
	LoadMesh("Mesh/saikoro312.x");
	LoadMesh("Mesh/saikoro246.x");
	LoadMesh("Mesh/saikoro123.x");
	LoadMesh("Mesh/saikoro541.x");

	LoadMesh("Mesh/b1.x");
	LoadMesh("Mesh/b2.x");
	LoadMesh("Mesh/b3.x");
	LoadMesh("Mesh/b4.x");
	LoadMesh("Mesh/b5.x");
	LoadMesh("Mesh/b6.x");

	LoadMesh("Mesh/rokkakugu.x");
	LoadMesh("Mesh/kuroro.x");
	LoadMesh("Mesh/siroro.x");
	}
	~Load() { ReleaseMesh(&xMesh); }

	void LoadMesh(char FName[]);
	void ReleaseMesh(struct XFILE *XFile);

	static Load &getInstance() {
		static Load Instance;
		return Instance;
	}

};