#include "Load.h"
void Load::LoadMesh(char FName[])
{

	LPD3DXBUFFER lpD3DXBuffer;

	D3DXLoadMeshFromX(FName, D3DXMESH_MANAGED, cdg.lpD3DDevice, NULL, &lpD3DXBuffer, NULL, &(xMesh.NumMaterial), &(xMesh.lpMesh));

	xMesh.Mat = new D3DMATERIAL9[xMesh.NumMaterial];
	xMesh.Tex = new LPDIRECT3DTEXTURE9[xMesh.NumMaterial];

	D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)lpD3DXBuffer->GetBufferPointer();

	DWORD i;
	for (i = 0; i < xMesh.NumMaterial; i++) {
		xMesh.Mat[i] = D3DXMat[i].MatD3D;
		xMesh.Mat[i].Ambient = xMesh.Mat[i].Diffuse;
		if (FAILED(D3DXCreateTextureFromFile(cdg.lpD3DDevice, D3DXMat[i].pTextureFilename, &(xMesh.Tex[i])))) {
			xMesh.Tex[i] = NULL;
		}
	}

	lpD3DXBuffer->Release();
	LPD3DXMESH lpTmpb;						//クローン用
	xMesh.lpMesh->CloneMeshFVF(D3DXMESH_MANAGED | D3DXMESH_NPATCHES, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, cdg.lpD3DDevice, &lpTmpb);
	//座標				法線					テクスチャ座標										クローン
	xMesh.lpMesh->Release();
	xMesh.lpMesh = lpTmpb;
	mp.insert(std::pair<std::string, XFILE>(FName, xMesh));

}
void Load::ReleaseMesh(struct XFILE *XFile)
{
	if (XFile->lpMesh != NULL) {
		DWORD i;

		delete[] XFile->Mat;
		for (i = 0; i < XFile->NumMaterial; i++) {
			if (XFile->Tex[i] != NULL) {
				XFile->Tex[i]->Release();
				XFile->Tex[i] = NULL;
			}
		}
		delete[] XFile->Tex;
		XFile->lpMesh->Release();

		XFile->lpMesh = NULL;
	}
}