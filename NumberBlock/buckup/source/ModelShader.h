#ifndef __ModelShader_h__
#define __ModelShader_h__
#include "Main.h"
#include "Mesh.h"
//ここにプログラムを書く
class ModelShader {
public:
	//環境マッピング
	LPDIRECT3DCUBETEXTURE9 m_texCube;
	void SetRefPower(float power) {
		m_Effect->SetFloat("RefPower", power);
	}

	LPD3DXEFFECT m_Effect;
	//------------------
	//初期設定・解放
	//-------------------
	void Init();
	void Release();
	//------------------
	//パラメータ設定系
	//-------------------
	//ワールド行列をセット
	void SetTransformWorld(D3DXMATRIX* m) {//ポインタを使う　構造体だと64バイトのコピーが発生ポインタだと4バイトで済む
		m_Effect->SetMatrix("mW", m);
	}
	//ビュー行列をセット
	void SetTransformView(D3DXMATRIX* m) {
		m_Effect->SetMatrix("mV", m);
	}
	//射影行列をセット
	void SetTransformProj(D3DXMATRIX* m) {
		m_Effect->SetMatrix("mP", m);
	}

	//平行光源のデータをセット
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


	//輪郭描画
	void DrawMesh_Outline(	Mesh* pMesh,
							float size,		//太さ
							D3DXVECTOR4* color);//色
};
#endif // ! __ModelShader_h__
