#ifndef __ModelShader_h__
#define __ModelShader_h__
#include "Main.h"
#include "Mesh.h"
//�����Ƀv���O����������
class ModelShader {
public:
	//���}�b�s���O
	LPDIRECT3DCUBETEXTURE9 m_texCube;
	void SetRefPower(float power) {
		m_Effect->SetFloat("RefPower", power);
	}

	LPD3DXEFFECT m_Effect;
	//------------------
	//�����ݒ�E���
	//-------------------
	void Init();
	void Release();
	//------------------
	//�p�����[�^�ݒ�n
	//-------------------
	//���[���h�s����Z�b�g
	void SetTransformWorld(D3DXMATRIX* m) {//�|�C���^���g���@�\���̂���64�o�C�g�̃R�s�[�������|�C���^����4�o�C�g�ōς�
		m_Effect->SetMatrix("mW", m);
	}
	//�r���[�s����Z�b�g
	void SetTransformView(D3DXMATRIX* m) {
		m_Effect->SetMatrix("mV", m);
	}
	//�ˉe�s����Z�b�g
	void SetTransformProj(D3DXMATRIX* m) {
		m_Effect->SetMatrix("mP", m);
	}

	//���s�����̃f�[�^���Z�b�g
	void SetDirectionalLight(D3DLIGHT9* light) {
		m_Effect->SetVector("LightDir", (D3DXVECTOR4*)&light->Direction);
		m_Effect->SetVector("LightColor", (D3DXVECTOR4*)&light->Diffuse);
		m_Effect->SetVector("LightAmbient", (D3DXVECTOR4*)&light->Ambient);
		m_Effect->SetVector("LightSpecular", (D3DXVECTOR4*)&light->Specular);
	}

	void SetCamPos(D3DXVECTOR3* camPos) {
		m_Effect->SetVector("CamPos", (D3DXVECTOR4*)camPos);
	}

	void DrawMesh(Mesh* pMesh);


	//�֊s�`��
	void DrawMesh_Outline(	Mesh* pMesh,
							float size,		//����
							D3DXVECTOR4* color);//�F
};
#endif // ! __ModelShader_h__
