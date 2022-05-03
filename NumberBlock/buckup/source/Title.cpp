#include "Title.h"

void Title::Init() {
	LoadText("Texture/NTitle.png", SCRW, SCRH,0, &lpCrosshair);
	//スプライト
	D3DXCreateSprite(cdg.lpD3DDevice, &lpCross);
	lpCross->OnResetDevice();
	//mug.lpSBGM->Play(0, 0, DSBSTATUS_LOOPING);
	LoadText("Texture/number.png", 380, 64, D3DCOLOR_XRGB(255, 0, 255), &lpTimehair);
	D3DXCreateSprite(cdg.lpD3DDevice, &lpTime);
	lpTime->OnResetDevice();

	LoadText("Texture/timescore.png", 380,384, D3DCOLOR_XRGB(255, 0, 255), &lpTimetext);
	D3DXCreateSprite(cdg.lpD3DDevice, &lpTimetextsp);
	lpTimetextsp->OnResetDevice();
	s.Init();
	s.lpSBGM->Play(0, 0, DSBPLAY_LOOPING);
	cdg.scean = 1;
	D3DXMatrixTranslation(&mTimeTrans, -38.0f, 0.0f, 0.0f);
	highscore = fop.ReadScore();
}
void Title::Release() {

	lpCrosshair->Release();
	s.Release();
	cdg.scean = 3;
}
void Title::Draw() {

}
void Title::Update() {

}
void Title::DrawFrame() {

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (cdg.SpaceFlg == 0) {
			//Release();
			cdg.scean = 2;
			cdg.SpaceFlg = 1;
			return;
		}

	}
	else { cdg.SpaceFlg = 0; }
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		if (cdg.EscapeFlg == 0) {
			//Release();
			cdg.scean = 6;
			cdg.EscapeFlg = 1;
			return;
		}

	}
	else { cdg.EscapeFlg = 0; }


	Title::Update();
	// 描画開始
	cdg.lpD3DDevice->BeginScene();

	// バックバッファと Z バッファをクリア
	cdg.lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	D3DXMATRIX mView, mProj;

	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&CPos,
		&CLook,
		&CHead
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 300.0f);

	//行列設定
	cdg.lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	cdg.lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	//shader
	cdg.GetDev()->GetTransform(D3DTS_VIEW, &mView);
	cdg.GetDev()->GetTransform(D3DTS_PROJECTION, &mProj);
	D3DXMATRIX mCam;
	D3DXMatrixInverse(&mCam, nullptr, &mView);

	D3DLIGHT9 light;
	cdg.lpD3DDevice->GetLight(0, &light);

	Title::Draw();
	
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
	
	


	D3DXMatrixTranslation(&mCrossWorld,0,0, 0.0f);
	RECT rc = { 0,0,SCRW,SCRH };
//	D3DXVECTOR3 vec = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	//Beagin
	lpCross->Begin(D3DXSPRITE_ALPHABLEND);
	lpCross->SetTransform(&mCrossWorld);
	lpCross->Draw(lpCrosshair, &rc, &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	lpCross->End();


	char cScore[12];
	sprintf_s(cScore, sizeof(cScore), "%d", highscore);

	int i, j;

	for (i = 0; cScore[i] != '\0'; i++);

	D3DXMatrixTranslation(&mTimeWorld, SCRW, 50.0f, 0.0f);
	RECT rc1 = { 0,256,380 ,384 };
	D3DXMatrixTranslation(&mTTWorld, SCRW /2, 0.0f, 0.0f);
	lpTimetextsp->Begin(D3DXSPRITE_ALPHABLEND);

	lpTimetextsp->SetTransform(&mTTWorld);
	lpTimetextsp->Draw(lpTimetext, &rc1, &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	lpTimetextsp->End();

	lpTime->Begin(D3DXSPRITE_ALPHABLEND);
	for (; i >= 0; i--) {
		mTimeWorld *= mTimeTrans;
		lpTime->SetTransform(&mTimeWorld);
		lpTime->Draw(lpTimehair, &rcNum[cScore[i] - '0'], &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		//ddt.SetChar("%c ", cScore[i]);
	}




	lpTime->End();


	// 描画終了
	cdg.lpD3DDevice->EndScene();

	// バックバッファをプライマリバッファにコピー
	cdg.lpD3DDevice->Present(NULL, NULL, NULL, NULL);
}
