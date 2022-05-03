#pragma once
#include"Main.h"
#include<map>
class Load {
public :
	// �ȒP�ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃}�N��
#define lad Load::getInstance()
	static struct XFILE {
		LPD3DXMESH lpMesh;//���b�V���̌`�̃f�[�^
		DWORD NumMaterial;//�}�e���A���̌�
		D3DMATERIAL9 *Mat;//�}�e���A���̃f�[�^
		LPDIRECT3DTEXTURE9 *Tex;//�e�N�X�`���̃f�[�^
	};
	static struct CLONEVERTEX {
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 Tex;
	};//�N���[���Ɠ����@���W�@�@���@�e�N�X�`�����W
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