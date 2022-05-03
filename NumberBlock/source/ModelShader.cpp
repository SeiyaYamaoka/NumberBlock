#include"ModelShader.h"

void ModelShader::Init() {
	//�V�F�[�_�ǂݍ���&�R���p�C��
	LPD3DXBUFFER pErr = nullptr;	//�R���p�C���G���[�ꗗ������
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(
		cdg.GetDev(), "source/ModelShader.fx",
		0, 0, 0, 0, &m_Effect, &pErr);

	if (hr != D3D_OK) {
		MessageBox(nullptr, (LPCSTR)pErr->GetBufferPointer(), "�V�F�[�_�R���p�C���G���[", MB_OK);
		return;
	}
}
void ModelShader::DrawMesh(Mesh* pMesh) {
	//CGame�N���X��Draw()�ŏ������V�F�[�_�`��̂Ƃ�����R�s�[����
	m_Effect->SetTechnique("Tech");
	m_Effect->Begin(0, 0);
	m_Effect->BeginPass(0);
	for (int i = 0; i < pMesh->xMesh.NumMaterial; i++) {
		//--------------------------------------------------------------------------------------------------------
		//�}�e���A���̃Z�b�g
		//-----------------------------------------------------------------------------------------------------
		D3DMATERIAL9* pMate = &pMesh->xMesh.Mat[i];
		//�e�N�X�`��
		LPDIRECT3DTEXTURE9 pTex = pMesh->xMesh.Tex[i];
		m_Effect->SetTexture("MateDiffuseTex", pTex);
		//�}�e���A���F(Diffuse)
		m_Effect->SetVector("MateDiffuse", (D3DXVECTOR4*)&pMate->Diffuse);
		m_Effect->SetVector("MateSpecular", (D3DXVECTOR4*)&pMate->Specular);
		m_Effect->SetFloat("MateSpecular", pMate->Power);
		//�O���[�o���փZ�b�g�����f�[�^��K�p����
		m_Effect->CommitChanges();
		pMesh->xMesh.lpMesh->DrawSubset(i);//	����

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

