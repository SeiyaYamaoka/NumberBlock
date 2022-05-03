#include"polygon.h"
void polygon::DrawPolygon() {

	D3DXMatrixMultiply(&mWorld, &mPos, &mRot);
	cdg.lpD3DDevice->SetTexture(0, lpText);
	cdg.lpD3DDevice->SetTransform(D3DTS_WORLD, &mWorld);//回転行列をセット
	cdg.lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));
}
void polygon::SetPolygon(float x1,float y1,float z1,float x2,float y2,float z2) {
	//板ポリの設定
	v[0].Pos = D3DXVECTOR3(x1,y1 , z1);
	v[1].Pos = D3DXVECTOR3(x2,y1 ,z1 );
	v[2].Pos = D3DXVECTOR3(x2, y2, z2);
	v[3].Pos = D3DXVECTOR3(x1, y2, z2);

	v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255); 
	v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	
}
void polygon::SetTex(float x,float y,float n) {
	//板ポリの設定

	v[0].Tex = D3DXVECTOR2(x/n,y/n);
	v[1].Tex = D3DXVECTOR2((x+1)/n, y/n);
	v[2].Tex = D3DXVECTOR2((x+1)/n, (y+1)/n);
	v[3].Tex = D3DXVECTOR2(x/n, (y+1)/n);
}

void polygon::LoadText(char fname[], int W, int H, D3DCOLOR Color)
{
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(cdg.lpD3DDevice, fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, &lpText);
}