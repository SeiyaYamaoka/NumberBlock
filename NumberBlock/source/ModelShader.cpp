#include"ModelShader.h"

void ModelShader::Init() {
	//シェーダ読み込み&コンパイル
	LPD3DXBUFFER pErr = nullptr;	//コンパイルエラー一覧が入る
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(
		cdg.GetDev(), "source/ModelShader.fx",
		0, 0, 0, 0, &m_Effect, &pErr);

	if (hr != D3D_OK) {
		MessageBox(nullptr, (LPCSTR)pErr->GetBufferPointer(), "シェーダコンパイルエラー", MB_OK);
		return;
	}
}
void ModelShader::DrawMesh(Mesh* pMesh) {
	//CGameクラスのDraw()で書いたシェーダ描画のところをコピーした
	m_Effect->SetTechnique("Tech");
	m_Effect->Begin(0, 0);
	m_Effect->BeginPass(0);
	for (int i = 0; i < pMesh->xMesh.NumMaterial; i++) {
		//--------------------------------------------------------------------------------------------------------
		//マテリアルのセット
		//-----------------------------------------------------------------------------------------------------
		D3DMATERIAL9* pMate = &pMesh->xMesh.Mat[i];
		//テクスチャ
		LPDIRECT3DTEXTURE9 pTex = pMesh->xMesh.Tex[i];
		m_Effect->SetTexture("MateDiffuseTex", pTex);
		//マテリアル色(Diffuse)
		m_Effect->SetVector("MateDiffuse", (D3DXVECTOR4*)&pMate->Diffuse);
		m_Effect->SetVector("MateSpecular", (D3DXVECTOR4*)&pMate->Specular);
		m_Effect->SetFloat("MateSpecular", pMate->Power);
		//グローバルへセットしたデータを適用する
		m_Effect->CommitChanges();
		pMesh->xMesh.lpMesh->DrawSubset(i);//	書く

	}
	m_Effect->EndPass();
	m_Effect->End();



}
void ModelShader::DrawMesh_Outline(Mesh* pMesh,float size,	D3DXVECTOR4* color) {
	m_Effect->SetFloat("OutlineSize", size);
	m_Effect->SetVector("OutlineColor", color);
	m_Effect->SetTechnique("OutlineTech");
	m_Effect->Begin(0, 0);
	m_Effect->BeginPass(0);
	for (int i = 0; i < pMesh->xMesh.NumMaterial; i++) {
		pMesh->xMesh.lpMesh->DrawSubset(i);
	}
	m_Effect->EndPass();
	m_Effect->End();
}
void ModelShader::Release() {
	if (m_Effect) { m_Effect->Release(); m_Effect = nullptr; }
}

