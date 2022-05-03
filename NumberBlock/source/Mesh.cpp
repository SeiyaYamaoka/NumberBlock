#include "Mesh.h"
#include "Load.h"
Mesh::Mesh() { }
Mesh::~Mesh(){ ReleaseMesh(); }
void Mesh::Init() {
	
	SetPos(0, 0, 0);
	SetRot(0,0,0);
	SetScale(1.0, 1.0, 1.0);//Meshlength = 2 * scalesize
	
	load();
	//xMesh.lpMesh = lad.xMesh.lpMesh;
	//xMesh.Mat = lad.xMesh.Mat;
	//xMesh.NumMaterial = lad.xMesh.NumMaterial;
	//xMesh.Tex = lad.xMesh.Tex;
	//LoadMesh("Mesh/block02.x");
	//LPD3DXMESH lpTmpb;						//クローン用
	//xMesh.lpMesh->CloneMeshFVF(D3DXMESH_MANAGED | D3DXMESH_NPATCHES, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, cdg.lpD3DDevice, &lpTmpb);
	////座標				法線					テクスチャ座標										クローン
	//xMesh.lpMesh->Release();
	//xMesh.lpMesh = lpTmpb;
}
void Mesh::load() {
	xMesh.lpMesh = lad.mp["Mesh/" + mname].lpMesh;
	xMesh.Mat = lad.mp["Mesh/" + mname].Mat;
	xMesh.NumMaterial = lad.mp["Mesh/" + mname].NumMaterial;
	xMesh.Tex = lad.mp["Mesh/" + mname].Tex;
}
void Mesh::Update() {
mWorld = mScale*mRot*mPos;
}
void Mesh::Render() {
	
	cdg.lpD3DDevice->SetTransform(D3DTS_WORLD, &mWorld);
	DrawMesh();
	
}
void Mesh::SetPos(float x,float y,float z) {
	D3DXMatrixTranslation(&mPos, x, y, z);
}
void Mesh::SetPos(D3DXMATRIX *d) {
	D3DXMatrixTranslation(&mPos, d->_41, d->_42, d->_43);
}
void Mesh::SetPos(D3DXVECTOR3 d) {
	D3DXMatrixTranslation(&mPos, d.x, d.y, d.z);
}
void Mesh::SetRot(float x,float y,float z) {
	//D3DXMatrixRotationX(&mRot, Ang);

	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(y), D3DXToRadian(x), D3DXToRadian(z));
}
void Mesh::SetScale(float x, float y, float z) {
	D3DXMatrixScaling(&mScale, x, y, z);
}
void Mesh::DrawMesh() {
	for (DWORD i = 0; i < xMesh.NumMaterial; i++) {
		cdg.lpD3DDevice->SetMaterial(&xMesh.Mat[i]);
		cdg.lpD3DDevice->SetTexture(0, xMesh.Tex[i]);
		xMesh.lpMesh->DrawSubset(i);//i番目のグループを表示
	}
}

void Mesh::ReleaseMesh()
{
	//if (xMesh.lpMesh != NULL) {
	//	DWORD i;

	//	delete[] xMesh.Mat;
	//	for (i = 0; i<xMesh.NumMaterial; i++) {
	//		if (xMesh.Tex[i] != NULL) {
	//			xMesh.Tex[i]->Release();
	//			xMesh.Tex[i] = NULL;
	//		}
	//	}
	//	delete[] xMesh.Tex;
	//	xMesh.lpMesh->Release();

	//	xMesh.lpMesh = NULL;
	//}
}
//void Mesh::LoadMesh(char FName[])
//{
//
//	LPD3DXBUFFER lpD3DXBuffer;
//
//	D3DXLoadMeshFromX(FName, D3DXMESH_MANAGED, cdg.lpD3DDevice, NULL, &lpD3DXBuffer, NULL, &(xMesh.NumMaterial), &(xMesh.lpMesh));
//
//	xMesh.Mat = new D3DMATERIAL9[xMesh.NumMaterial];
//	xMesh.Tex = new LPDIRECT3DTEXTURE9[xMesh.NumMaterial];
//
//	D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)lpD3DXBuffer->GetBufferPointer();
//
//	DWORD i;
//	for (i = 0; i<xMesh.NumMaterial; i++) {
//		xMesh.Mat[i] = D3DXMat[i].MatD3D;
//		xMesh.Mat[i].Ambient = xMesh.Mat[i].Diffuse;
//		if (FAILED(D3DXCreateTextureFromFile(cdg.lpD3DDevice, D3DXMat[i].pTextureFilename, &(xMesh.Tex[i])))) {
//			xMesh.Tex[i] = NULL;
//		}
//	}
//
//	lpD3DXBuffer->Release();
//
//}