#include "CharaMove.h"

CharaMove::CharaMove() {

};
CharaMove::~CharaMove() {};
void CharaMove::Update(D3DXVECTOR3 *CPos, D3DXVECTOR3 *CLook, D3DXVECTOR3 *CHead) {
	if (GetAsyncKeyState('W') & 0x8000) {
		D3DXVECTOR3 Vec;
		Vec = D3DXVECTOR3(0.0f, 0.0f, MOVE);
		D3DXVec3TransformCoord(&Vec, &Vec, &mRotY);
		*CPos += Vec;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		D3DXVECTOR3 Vec;
		Vec = D3DXVECTOR3(0.0f, 0.0f, -MOVE);
		D3DXVec3TransformCoord(&Vec, &Vec, &mRotY);
		*CPos += Vec;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		D3DXVECTOR3 Vec;
		Vec = D3DXVECTOR3(-MOVE, 0.0f, 0.0f);
		D3DXVec3TransformCoord(&Vec, &Vec, &mRotY);
		*CPos += Vec;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		D3DXVECTOR3 Vec;
		Vec = D3DXVECTOR3(MOVE, 0.0f, 0.0f);
		D3DXVec3TransformCoord(&Vec, &Vec, &mRotY);
		*CPos += Vec;
	}
	if (GetAsyncKeyState('Q') & 0x8000) {
		D3DXVECTOR3 Vec;
		Vec = D3DXVECTOR3(0.0f, -MOVE, 0.0f);
		D3DXVec3TransformCoord(&Vec, &Vec, &mRotY);
		*CPos += Vec;
	}
	if (GetAsyncKeyState('E') & 0x8000) {
		D3DXVECTOR3 Vec;
		Vec = D3DXVECTOR3(0.0f, MOVE, 0.0f);
		D3DXVec3TransformCoord(&Vec, &Vec, &mRotY);
		*CPos += Vec;
	}

	//カメラ回転
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		AngY -= H_ROTATE;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		AngY += H_ROTATE;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (AngX > -80) {
			AngX -= V_ROTATE;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (AngX < 80) {
			AngX += V_ROTATE;
		}
	}

	D3DXMatrixRotationY(&mRotY, D3DXToRadian(AngY));

	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(AngY), D3DXToRadian(AngX), 0);

	D3DXVec3TransformNormal(CLook, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &mRot);	//向いている方向
	D3DXVec3TransformNormal(CHead, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &mRot);	//頭上方向
	*CLook = *CPos + *CLook;	//カメラの現在位置から前（Z）方向に１の場所
	
};
D3DXMATRIX CharaMove::BallUpdate(D3DXVECTOR3 *CPos, D3DXVECTOR3 *CLook, D3DXVECTOR3 *CHead) {

	if (GetAsyncKeyState('3') & 0x8000) {
		D3DXMatrixTranslation(&sTrans, 0, 10, 0);
		Accel = 0;
	}
	//カメラ回転

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (AngX > -60) {
			AngX -= H_ROTATE;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (AngX < 60) {
			AngX += H_ROTATE;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		AngY -= H_ROTATE;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		AngY += H_ROTATE;
	}
	D3DXMatrixRotationY(&mRotY, D3DXToRadian(AngY));

	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(AngY), D3DXToRadian(AngX), 0);
	int keyflg = 0;
	D3DXVECTOR3 ToVec(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 tmpVec(0.0f, 0.0f, 0.0f);
	kskVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (GetAsyncKeyState('W') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &mRotY);
		ToVec += tmpVec;
		kskWASD[0] += 0.1f;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, -1.0f), &mRotY);
		ToVec += tmpVec;
		kskWASD[2] += 0.1f;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &mRotY);
		ToVec += tmpVec;
		kskWASD[1] += 0.1f;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &mRotY);
		ToVec += tmpVec;
		kskWASD[3] += 0.1f;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (JumpFlg < 1) {
			Accel = JUMP;
			JumpFlg++;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (kskWASD[i] > 0.5f) {
			kskWASD[i] = 0.5f;
		}
		kskWASD[i] -= 0.05;
		if (kskWASD[i] < 0) {
			kskWASD[i] = 0;
		}
	}
	D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, kskWASD[0]), &mRotY);
	kskVec += tmpVec;
	D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, -kskWASD[2]), &mRotY);
	kskVec += tmpVec;
	D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(-kskWASD[1], 0.0f, 0.0f), &mRotY);
	kskVec += tmpVec;
	D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(kskWASD[3], 0.0f, 0.0f), &mRotY);
	kskVec += tmpVec;


	//落下
	sTrans._42 += Accel;
	Accel -= GRAVITY;
	if (Accel < -1.0f)Accel = -1.0f;
	ddt.SetChar("Accel %.2f\n", Accel);
	//板ポリ下当たり判定ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	float Dis;
	for (int i = 0; i < poinfo.size(); i++) {
		if (D3DXIntersectTri(&poinfo[i]->v[0].Pos, &poinfo[i]->v[1].Pos, &poinfo[i]->v[2].Pos, &D3DXVECTOR3(sTrans._41, sTrans._42, sTrans._43), &D3DXVECTOR3(0, -1, 0), NULL, NULL, &Dis)
			|| D3DXIntersectTri(&poinfo[i]->v[0].Pos, &poinfo[i]->v[2].Pos, &poinfo[i]->v[3].Pos, &D3DXVECTOR3(sTrans._41, sTrans._42, sTrans._43), &D3DXVECTOR3(0, -1, 0), NULL, NULL, &Dis)) {
			if (Dis <= 1) {
				sTrans._42 += (1 - Dis);
				Accel = -Accel*0.5f;
				if (Accel < 0.1f) { Accel = 0; }//
				JumpFlg = 0;

			}
		}
	}
	//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	//Mesh下当たり判定--------------------------------------------------------------------
	for (int i = 1; i < meshinfo.size(); i++) {
		D3DXMATRIX mInv;
		D3DXMatrixInverse(&mInv, NULL, &meshinfo[i]->mWorld);
		D3DXVECTOR3 LocalPos, LocalVec;
		D3DXVec3TransformCoord(&LocalPos, &D3DXVECTOR3(sTrans._41, sTrans._42, sTrans._43), &mInv);
		D3DXVec3TransformNormal(&LocalVec, &D3DXVECTOR3(0, -1, 0), &mInv);
		BOOL Hit;
		float WallDis = -1;
		D3DXIntersect(meshinfo[i]->xMesh.lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &WallDis, NULL, NULL);
		if (Hit) {
			if (WallDis <=1.2) {
				sTrans._42 += (1.2 - WallDis);
				Accel = -Accel*0.5f;
				if (Accel < 0.2f) { Accel = 0; }//
				JumpFlg = 0;
			}
		}
	}//-----------------------------------------------------------------------------







	D3DXVECTOR3 FrontVec;
	if (keyflg == 1) {
		D3DXVec3Normalize(&ToVec, &ToVec);	//斜め移動時の高速化防止

		//回転 
	
		D3DXVec3TransformNormal(&FrontVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &sRot);	//プレイヤーの向いている方向

		float tmpRot;
		tmpRot = D3DXVec3Dot(&ToVec, &FrontVec);	//内積を求める
		tmpRot = D3DXToDegree(acos(tmpRot));		//角度に直す（マイナス無し）
		D3DXVECTOR3 RotAxis;
		D3DXVec3Cross(&RotAxis, &FrontVec, &ToVec);	//外積を求める

		if (tmpRot >= 0.1f) {
			if (tmpRot >= 15.0f) {
				tmpRot = 15.0f;
			}
		}
		if (RotAxis.y > 0) {	//左回転の場合はYがマイナスになる
			fPRot += tmpRot;
		}
		else if (RotAxis.y < 0) {
			fPRot -= tmpRot;
		}
		else {
			fPRot += tmpRot;
		}
		fPRot = float((int)fPRot % 360);
		D3DXMatrixRotationY(&sRot, D3DXToRadian(fPRot));
		AngPlus += 1.0f;
		if (AngPlus > 20)AngPlus = 20;

	}

	for (int i = 1; i < meshinfo.size(); i++) {
		//逆行列の計算
	D3DXMATRIX mInv;
	D3DXMatrixInverse(&mInv, NULL, &meshinfo[i]->mWorld);

	D3DXVECTOR3 LocalPos, LocalVec;
	//3次元ベクトルに４ｘ４の行列を掛け算する関数//	指定された行列によりベクトルをトランスフォームし、その結果を w = 1 に射影する
	D3DXVec3TransformCoord(&LocalPos, &D3DXVECTOR3(meshinfo[0]->mWorld._41, meshinfo[0]->mWorld._42, meshinfo[0]->mWorld._43), &mInv);
	//指定された行列によりベクトル法線をトランスフォームする
	D3DXVec3TransformNormal(&LocalVec, &FrontVec, &mInv);
	DWORD PolyNo;
	BOOL Hit;
	float WallDis = -1;

	D3DXIntersect(meshinfo[i]->xMesh.lpMesh, &LocalPos, &LocalVec, &Hit, &PolyNo, NULL, NULL, &WallDis, NULL, NULL);
	if (Hit) {

		//例が当たったところのポリゴンの頂点番号を取得する
		WORD *pI;
		meshinfo[i]->xMesh.lpMesh->LockIndexBuffer(0, (LPVOID*)&pI);

		WORD VNo[3];
		VNo[0] = *(pI + PolyNo * 3 + 0);
		VNo[1] = *(pI + PolyNo * 3 + 1);
		VNo[2] = *(pI + PolyNo * 3 + 2);
		meshinfo[i]->xMesh.lpMesh->UnlockIndexBuffer();
		//取得した頂点の座標を取得	
		CLONEVERTEX *pV;
		meshinfo[i]->xMesh.lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);

		D3DXVECTOR3 vPos[3];
		vPos[0] = (pV + VNo[0])->Pos;
		vPos[1] = (pV + VNo[1])->Pos;
		vPos[2] = (pV + VNo[2])->Pos;
		meshinfo[i]->xMesh.lpMesh->UnlockVertexBuffer();
		//三つの座標からポリゴンの淵を表すベクトルを取得
		D3DXVECTOR3 Vec1, Vec2;
		Vec1 = vPos[1] - vPos[0];
		Vec2 = vPos[2] - vPos[0];
		//外積で法線ベクトルを取得
		D3DXVECTOR3 WallVec;
		D3DXVec3Cross(&WallVec, &Vec1, &Vec2);

		D3DXVec3TransformNormal(&WallVec, &WallVec, &meshinfo[i]->mWorld);

		D3DXVec3Normalize(&WallVec, &WallVec);
		float Dot;
		Dot = D3DXVec3Dot(&WallVec, &-FrontVec);
		float Limit;
		Limit = 1.1 / Dot;
		if (Limit < 0)Limit *= -1;
		if (WallDis < Limit) {
	
			kskVec += WallVec*((Limit - WallDis)*Dot);
			//D3DXVECTOR3(meshinfo[0]->mWorld._41, meshinfo[0]->mWorld._42, meshinfo[0]->mWorld._43) += WallVec*((Limit - WallDis)*Dot);
			//D3DXVECTOR3(sTrans._41, sTrans._42, sTrans._43) += WallVec*((Limit - WallDis)*Dot);
		}
		//ddt.SetChar("HIT");
	}
	}
		////ddt.SetChar("strans(%.2f,%.2f,%.2f)\n",sTrans.)
		//if (Hit == 1) { ddt.SetChar("Hit:TRUE"); }else{ ddt.SetChar("Hit:FALSE"); }
		//ddt.SetChar("mWorld4(%.2f,%.2f,%.2f)\n", D3DXVECTOR3(mWorld._41, mWorld._42, mWorld._43));

		ddt.SetChar("mWorld1(%.2f,%.2f,%.2f,%.2f)\n", &D3DXVECTOR4(mWorld._11, mWorld._12, mWorld._13, mWorld._14));
		ddt.SetChar("mWorld2(%.2f,%.2f,%.2f,%.2f)\n", &D3DXVECTOR4(mWorld._21, mWorld._22, mWorld._23, mWorld._24));
		ddt.SetChar("mWorld3(%.2f,%.2f,%.2f,%.2f)\n", &D3DXVECTOR4(mWorld._31, mWorld._32, mWorld._33, mWorld._34));
		ddt.SetChar("mWorld4(%.2f,%.2f,%.2f,%.2f)\n", &D3DXVECTOR4(mWorld._41, mWorld._42, mWorld._43,mWorld._44));
		//ddt.SetChar("meshinfo[0](%.2f,%.2f,%.2f)\n", D3DXVECTOR3(meshinfo[0]->mWorld._41, meshinfo[0]->mWorld._42, meshinfo[0]->mWorld._43));
		//ddt.SetChar("Walldis %.2f\n", WallDis);	
		//ddt.SetChar("Limit %.2f\n", Limit);
		//ddt.SetChar("Dot %.2f\n", Dot);
		//ddt.SetChar("polyno %ld\n", PolyNo);
		//ddt.SetChar("WallVec(%2.f,%.2f,%.2f)\n", WallVec);
		//ddt.SetChar("LocalPos(%2.f,%.2f,%.2f)\n", LocalPos);
		//ddt.SetChar("Localvec(%2.f,%.2f,%.2f)\n", LocalVec);

	//}

	AngPlus -= 0.5f;
	if (AngPlus < 0)AngPlus = 0;
	Ang += AngPlus;
	if (Ang > 360)Ang = 0;
	D3DXMatrixRotationX(&xRot, D3DXToRadian(Ang));

	D3DXMATRIX mTmp;

	//ToVec += kskVec;
	ddt.SetChar("kskvec(%.2f,%.2f,%.2f)\n", kskVec);
	//D3DXVec3Normalize(&kskVec, &kskVec);	//斜め移動時の高速化防止
	ddt.SetChar("Tovec(%.2f,%.2f,%.2f)\n", ToVec);
	D3DXMatrixTranslation(&mTmp, kskVec.x, kskVec.y, kskVec.z);
	sTrans = mTmp * sTrans;



	if (GetAsyncKeyState('R') & 0x8000) {
		camz += 0.5f;
		if (camz > -8.0f) {
			camz = -8.0f;
		}
	}
	if (GetAsyncKeyState('F') & 0x8000) {
		camz -= 0.5f;
		if (camz < -50.0f) {
			camz = -50.0f;
		}
	}
	D3DXVec3TransformCoord(CLook, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &sTrans);
	D3DXVec3TransformCoord(CPos, &D3DXVECTOR3(0.0f, 3.0f, camz), &mRot);
	*CPos = *CLook + *CPos;	

	mWorld = mScale*xRot*sRot*sTrans;
	return mWorld;
}
D3DXMATRIX CharaMove::TPVUpdate(D3DXVECTOR3 *CPos, D3DXVECTOR3 *CLook, D3DXVECTOR3 *CHead) {
	if (GetAsyncKeyState('3') & 0x8000) {
		D3DXMatrixTranslation(&sTrans, 0, 10, 0);
	}
	//カメラ回転

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (AngX > -60) {
			AngX -= H_ROTATE;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (AngX < 60) {
			AngX += H_ROTATE;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		AngY -= H_ROTATE;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		AngY += H_ROTATE;
	}
	D3DXMatrixRotationY(&mRotY, D3DXToRadian(AngY));
	D3DXMatrixRotationYawPitchRoll(&mRot, D3DXToRadian(AngY), D3DXToRadian(AngX), 0);
	int keyflg = 0;
	D3DXVECTOR3 ToVec(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 tmpVec(0.0f, 0.0f, 0.0f);
	if (GetAsyncKeyState('W') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &mRotY);
		ToVec += tmpVec;
		
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, -1.0f), &mRotY);
		ToVec += tmpVec;
		
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &mRotY);
		ToVec += tmpVec;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &mRotY);
		ToVec += tmpVec;
		
	}
	if (GetAsyncKeyState('E') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &mRotY);
		ToVec += tmpVec;
	}
	if (GetAsyncKeyState('Q') & 0x8000) {
		keyflg = 1;
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &mRotY);
		ToVec += tmpVec;

	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
	}

	if (keyflg == 1) {
		D3DXVec3Normalize(&ToVec, &ToVec);	//斜め移動時の高速化防止
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &mRotY);
		D3DXMATRIX mTmp;
		D3DXMatrixTranslation(&mTmp,ToVec.x, ToVec.y, ToVec.z);
		sTrans = mTmp * sTrans;
	}
	if (GetAsyncKeyState('R') & 0x8000) {
		camz += 0.5f;
		if (camz > -5.0f) {
			camz = -5.0f;
		}
	}
	if (GetAsyncKeyState('F') & 0x8000) {
		camz -= 0.5f;
		if (camz < -50.0f) {
			camz = -50.0f;
		}
	}
	D3DXVec3TransformCoord(CLook, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &sTrans);
	D3DXVec3TransformCoord(CPos, &D3DXVECTOR3(0.0f, 3.0f, camz), &mRot);
	*CPos = *CLook + *CPos;

	mWorld = mScale*sTrans;
	return mWorld;
}




