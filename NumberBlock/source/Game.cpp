#include "Game.h"

void Game::Init() {
	sou.Init();
	sou.lpSGBGM->Play(0, 0, DSBPLAY_LOOPING);
	count = 0;
	start = timeGetTime();
	baniframe = 0;
	baniflg = 0;
	keyaniflg = 0;
	blaniflg = 0;
	time0 = 0;
	startflg = 1;
	resultflg = 0;
	tcount = 0;
	m_MS.Init();
	saiinit();
	
	meshinf = fop.ReadFile(meshinf);

	//CM.SetPol(&polyinf);
	//CM.SetMat(&meshinf);
	//CM.init();
	filenum = meshinf.size();
	num = 0;
	blockmax = 10;
	Score = 0;
	for (int i = 0; i < smax; i++) {
		for (int j = 0; j < smax; j++) {
			for (int k = 0; k < smax; k++) {
				if (j == smax - 1) { s[i][j][k].display = 1; }
				else { s[i][j][k].display = 0; }
				s[i][j][k].xyz = D3DXVECTOR3(-2 * i + (smax - 1), -2 * j + (smax - 1), -2 * k + (smax - 1));
			}
		}
	}

	num = meshinf.size();
	for (int i = 0; i < smax; i++) {
		for (int j = 0; j < smax; j++) {
			for (int k = 0; k < smax; k++) {

				if (s[i][j][k].display == 1) {
					s[i][j][k].meshnum = num;
					num++;
					Mesh *lpm = new Mesh();
					//if (num % 2 == 0) {
					lpm->mname = "kuroro.x";
					//}
					//else { lpm->mname = "siroro.x"; }
					lpm->Init();
					lpm->SetPos(s[i][j][k].xyz);
					lpm->Update();
					meshinf.push_back(lpm);
				}
				else {
					s[i][j][k].meshnum = -999;
				}
			}
		}
	}
	c.x = smax / 2;
	c.y = smax - 2;
	c.z = smax / 2;
	c.meshnum = num;
	//D3DXMatrixIdentity(&meshinf[c.meshnum]->mWorld);
	s[c.x][c.y][c.z].meshnum = c.meshnum;
	s[c.x][c.y][c.z].display = 1;
	Mesh *lpm = new Mesh();
	lpm->mname = "saikoro135.x";
	lpm->Init();
	lpm->SetPos(s[c.x][c.y][c.z].xyz);
	lpm->Update();
	meshinf.push_back(lpm);



	//スプライト
	//タイムの数字
	LoadText("Texture/number.png", 380, 64, D3DCOLOR_XRGB(255, 0, 255), &lpTimehair);
	D3DXCreateSprite(cdg.lpD3DDevice, &lpTime);
	lpTime->OnResetDevice();
	LoadText("Texture/timescore.png", 380, 256, D3DCOLOR_XRGB(255, 0, 255), &lpTimetext);
	D3DXCreateSprite(cdg.lpD3DDevice, &lpTimetextsp);
	lpTimetextsp->OnResetDevice();

	keyanirotx = keyaniroty = keyanirotz = 0;
	D3DXMatrixIdentity(&miden);
	CPos = D3DXVECTOR3(3.0f, 5.0f, -13.0f);
	CLook = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	CHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixTranslation(&mTimeTrans, -38.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mScoreTrans, -38.0f, 0.0f, 0.0f);
	
	cdg.scean = 4;
}
void Game::Draw() {

	//cdg.lpD3DDevice->SetTransform(D3DTS_WORLD, &miden);

	//m_MS.SetTransformWorld(&meshinf[c.meshnum]->mWorld);
	//m_MS.(meshinf[c.meshnum],0.1,&D3DXVECTOR4(1,0,0,1));
	cdg.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//cdg.lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	for (int i = 0; i < filenum; i++) {
		meshinf[i]->Render();
	}
	for (int i = 0; i < smax; i++) {
		for (int j = 0; j < smax; j++) {
			for (int k = 0; k < smax; k++) {
				if (s[i][j][k].display == 1) {

					meshinf[s[i][j][k].meshnum]->Render();
				}
			}
		}
	}
	//meshinf[c.meshnum]->Render();
	cdg.lpD3DDevice->SetFVF(FVF_VERTEX);

	//cdg.lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	cdg.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
void Game::Update() {
	//key
	static int mmin;
	float Dis = -1;
	std::vector<int > hitlist;
	std::vector<float > Dislist;
	std::vector<float > mDislist;

	if (debagflg == 0) {
		ddt.SetChar("CPos(%.2f,%.2f,%.2f)\n", CPos);
		ddt.SetChar("CLook(%.2f,%.2f,%.2f)\n", CLook);
		ddt.SetChar("CHead(%.2f,%.2f,%.2f)\n", CHead);
		static int keyflg = 0;
		static D3DXMATRIX bmStart, bmEnd, bmNow;
		static float frame;

		if (GetAsyncKeyState('X') & 0x8000) {
		}

		if (GetAsyncKeyState('Z') & 0x8000) {
			ddt.SetChar("Zpress");
			if (keyflg == 0) {
				frame = 0;

				D3DXMatrixTranslation(&bmStart, s[c.x][c.y + 1][c.z].xyz.x, s[c.x][c.y + 1][c.z].xyz.y, s[c.x][c.y + 1][c.z].xyz.z);
				bmNow = bmStart;
				D3DXMatrixTranslation(&bmEnd, s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
				keyflg = 1;
			}
		}
		ddt.SetChar("keyflg :%d\n", keyflg);
		if (keyflg == 1) {
			frame += 0.01;
			if (frame > 1) {
				frame = 1;
				keyflg = 0;

			}
			bmNow = AnimeProc(&bmStart, &bmEnd, &bmNow, frame);
			meshinf[c.meshnum]->SetPos(bmNow._41, bmNow._42, bmNow._43);
			meshinf[c.meshnum]->Update();
		}
		ddt.SetChar("frame %.2f", frame);
		//if (GetAsyncKeyState('I')) {
		//	for (int i = 0; i < meshinf.size(); i++) {
		//		delete meshinf[i];
		//	}
		//	meshinf.clear();

		//	meshinf = fop.ReadFile(meshinf);
		//	CM.SetPol(&polyinf);
		//	CM.SetMat(&meshinf);
		//	CM.init();
		//}
		CM.Update(&CPos, &CLook, &CHead);

		ddt.SetChar("meshinf.size%d\n", meshinf.size());

		CLook = CLook - CPos;
		//Meshの当たり判定
		for (int i = 0; i < meshinf.size(); i++) {
			D3DXMATRIX mInv;
			D3DXMatrixInverse(&mInv, NULL, &meshinf[i]->mWorld);
			D3DXVECTOR3 LocalPos, LocalVec;
			D3DXVec3TransformCoord(&LocalPos, &CPos, &mInv);
			D3DXVec3TransformNormal(&LocalVec, &CLook, &mInv);
			BOOL Hit;
			float WallDis = -1;
			D3DXIntersect(meshinf[i]->xMesh.lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &WallDis, NULL, NULL);
			if (Hit) {

			}
			else {

			}
			mDislist.push_back(WallDis);
		}

		CLook = CPos + CLook;
		mmin = minDis(mDislist, mDislist.size());
		ddt.SetChar("mmin %d", mmin);
		ddt.SetChar("mDislist.size %u\n", mDislist.size());

		if (mmin != -1) {
			ddt.SetChar("x:%.2f", meshinf[mmin]->mWorld._41);
			ddt.SetChar("y:%.2f", meshinf[mmin]->mWorld._42);
			ddt.SetChar("z:%.2f\n", meshinf[mmin]->mWorld._43);
			ddt.SetChar("name:%s", &meshinf[mmin]->mname);
		}
	}
	//if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
	//	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { Release(); Init(); }
	//	if (GetAsyncKeyState('1') & 0x8000) {
	//		CPos = D3DXVECTOR3(3.0f, 5.0f, -13.0f);
	//		CLook = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	//		CHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//		debagflg = 1;
	//		
	//	}
	//	if (GetAsyncKeyState('0') & 0x8000) {
	//		debagflg = 0;
	//	}
	//	if (GetAsyncKeyState('2') & 0x8000) {
	//		CPos = D3DXVECTOR3(.0f, 5.0f, -13.0f);
	//		CLook = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	//		CHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//		debagflg = 2;
	//	}
	//}
	if (debagflg == 1) {
		if (resultflg == 0&&startflg==0) {
			baniflg = 0;
			static D3DXMATRIX bmStart, bmEnd, bmNow;
			//if (GetAsyncKeyState('B') & 0x8000) {
			//DWORD time = (end - start)/1000;
			//if (time % 5 == 0) {
			//if (baniflg == 0) {
			//	if (blaniflg == 0) {
			//		baniflg = 1;
			//	}
			//}
			//}

			if (Score >= 50)blockmax = 15;
			if (Score >= 100)blockmax = 20;
			if (Score >= 150)blockmax = 25;
			if (Score >= 200)blockmax = 30;
			if (Score >= 300)blockmax = 35;
			if (Score >= 400)blockmax = 40;

			if (blockinf.size() <= blockmax) {
				if (baniflg == 0) {
					if (blaniflg == 0) {
						baniflg = 1;
					}
				}
			}
			if (baniflg == 1) {
				std::mt19937 mt(srnd());
				std::uniform_int_distribution<int> rands(0, 6);

				std::mt19937 mtd(brnd());
				std::uniform_int_distribution<int> randb(1, 6);


				int randomnumx, randomnumz;
				randomnumx = rands(mt);
				randomnumz = rands(mt);
				if (s[randomnumx][5][randomnumz].meshnum == -999) {
					block *b = new block;
					b->blocknum = randb(mtd);

					b->x = randomnumx;
					b->y = 5;
					b->z = randomnumz;
					num++;
					b->meshnum = num;

					blockinf.push_back(b);

					s[b->x][b->y][b->z].meshnum = b->meshnum;
					s[b->x][b->y][b->z].display = 1;
					s[b->x][b->y][b->z].blockinfnum = blockinf.size() - 1;
					//if (s[b->x][b->y][b->z].blockinfnum < 0)s[b->x][b->y][b->z].blockinfnum = 0;

					Mesh *lpmb = new Mesh();
					if (b->blocknum == 1) { lpmb->mname = /*"saikoro135.x"*/"b1.x"; }
					else if (b->blocknum == 2) { lpmb->mname = "b2.x"; }
					else if (b->blocknum == 3) { lpmb->mname = "b3.x"; }
					else if (b->blocknum == 4) { lpmb->mname = "b4.x"; }
					else if (b->blocknum == 5) { lpmb->mname = "b5.x"; }
					else if (b->blocknum == 6) { lpmb->mname = "b6.x"; }

					lpmb->Init();
					lpmb->SetPos(s[b->x][b->y][b->z].xyz);
					lpmb->Update();
					meshinf.push_back(lpmb);

					baniframe = 0;
					D3DXMatrixTranslation(&bmStart, s[b->x][b->y + 1][b->z].xyz.x, s[b->x][b->y + 1][b->z].xyz.y, s[b->x][b->y + 1][b->z].xyz.z);
					bmNow = bmStart;
					D3DXMatrixTranslation(&bmEnd, s[b->x][b->y][b->z].xyz.x, s[b->x][b->y][b->z].xyz.y, s[b->x][b->y][b->z].xyz.z);
					blaniflg = 1;
					sou.SE->Play(0, 0, 0);
				}
			}
			if (blaniflg == 1) {
				baniframe += 0.1;
				if (baniframe > 1) {
					baniframe = 1;
					blaniflg = 0;

				}

				bmNow = AnimeProc(&bmStart, &bmEnd, &bmNow, baniframe);
				meshinf[num]->SetPos(bmNow._41, bmNow._42, bmNow._43);
				meshinf[num]->Update();
			}
			//}


			if (s[c.x][c.y + 1][c.z].deathflg == 1) {
				//ddt.SetChar("当たり\n");
				D3DXMATRIX start, end;
				D3DXMatrixTranslation(&start, s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
				D3DXMatrixTranslation(&end, s[c.x][c.y + 1][c.z].xyz.x, s[c.x][c.y + 1][c.z].xyz.y, s[c.x][c.y + 1][c.z].xyz.z);

				meshinf[c.meshnum]->mWorld = AnimeProc(&start, &end, &meshinf[c.meshnum]->mWorld, blockinf[s[c.x][c.y + 1][c.z].blockinfnum]->frame);
				c.frame = blockinf[s[c.x][c.y + 1][c.z].blockinfnum]->frame;
				/*		c.frame += 0.01;
						if (c.frame > 1) {
							c.frame = 1;
						}*/
			}
			if (s[c.x][c.y + 1][c.z].meshnum == -999) {
				D3DXMATRIX start, end;
				D3DXMatrixTranslation(&start, s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
				D3DXMatrixTranslation(&end, s[c.x][c.y + 1][c.z].xyz.x, s[c.x][c.y + 1][c.z].xyz.y, s[c.x][c.y + 1][c.z].xyz.z);
				meshinf[c.meshnum]->mWorld = AnimeProc(&start, &end, &meshinf[c.meshnum]->mWorld, c.frame);
				c.frame += 0.1;
				if (c.frame > 1) {
					c.frame = 1;
				}
			}
			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				if (keyaniflg == 0) {
					if (c.z > 0) {
						if (s[c.x][c.y][c.z - 1].meshnum == -999) {
							int num = tatesai[0];
							tatesai[0] = tatesai[1];
							tatesai[1] = tatesai[2];
							tatesai[2] = tatesai[3];
							tatesai[3] = num;

							yokosai[0] = tatesai[0];
							yokosai[2] = tatesai[2];


							s[c.x][c.y][c.z].display = 0;
							s[c.x][c.y][c.z].meshnum = -999;

							c.z -= 1;
							if (s[c.x][c.y + 1][c.z].meshnum == -999) { c.y += 1; }
							s[c.x][c.y][c.z].display = 1;
							s[c.x][c.y][c.z].meshnum = c.meshnum;

							D3DXQUATERNION q(0, 0, 0, 1); // 単位クォータニオン'q'を生成
							D3DXMATRIX TurnMat; // 回転行列
							keyanirotx += 90;
							D3DXMatrixIdentity(&TurnMat);
							D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(keyaniroty), D3DXToRadian(keyanirotx), D3DXToRadian(keyanirotz));
							//クォータニオンをマトリックスに変換
							D3DXMatrixRotationQuaternion(&TurnMat, &q);
							mStart = meshinf[c.meshnum]->mWorld;
							meshinf[c.meshnum]->SetPos(s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
							meshinf[c.meshnum]->Update();
							mEnd = TurnMat*meshinf[c.meshnum]->mWorld;
							mNow = mStart;
							AnimeFrame = 0;
							keyaniflg = 1;
						}
						else if (s[c.x][c.y][c.z - 1].meshnum != -999 && s[c.x][c.y - 1][c.z - 1].meshnum == -999 /*&& s[c.x][c.y][c.z - 1].deathflg == 0*/) {
							int num = tatesai[0];
							tatesai[0] = tatesai[1];
							tatesai[1] = tatesai[2];
							tatesai[2] = tatesai[3];
							tatesai[3] = num;

							yokosai[0] = tatesai[0];
							yokosai[2] = tatesai[2];


							s[c.x][c.y][c.z].display = 0;
							s[c.x][c.y][c.z].meshnum = -999;

							c.z -= 1;
							//if (s[c.x][c.y][c.z].deathflg == 0) {
							c.y -= 1;
							//}
							s[c.x][c.y][c.z].display = 1;
							s[c.x][c.y][c.z].meshnum = c.meshnum;

							D3DXQUATERNION q(0, 0, 0, 1); // 単位クォータニオン'q'を生成
							D3DXMATRIX TurnMat; // 回転行列
							keyanirotx += 90;
							D3DXMatrixIdentity(&TurnMat);
							D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(keyaniroty), D3DXToRadian(keyanirotx), D3DXToRadian(keyanirotz));
							//クォータニオンをマトリックスに変換
							D3DXMatrixRotationQuaternion(&TurnMat, &q);
							mStart = meshinf[c.meshnum]->mWorld;
							meshinf[c.meshnum]->SetPos(s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
							meshinf[c.meshnum]->Update();
							mEnd = TurnMat*meshinf[c.meshnum]->mWorld;
							mNow = mStart;
							AnimeFrame = 0;
							keyaniflg = 1;
						}
					}
				}
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
				if (keyaniflg == 0) {
					if (c.z < smax - 1) {
						if (s[c.x][c.y][c.z + 1].meshnum == -999) {
							int num = tatesai[0];
							tatesai[0] = tatesai[3];
							tatesai[3] = tatesai[2];
							tatesai[2] = tatesai[1];
							tatesai[1] = num;

							yokosai[0] = tatesai[0];
							yokosai[2] = tatesai[2];


							s[c.x][c.y][c.z].display = 0;
							s[c.x][c.y][c.z].meshnum = -999;

							c.z += 1;
							if (s[c.x][c.y + 1][c.z].meshnum == -999) { c.y += 1; }
							s[c.x][c.y][c.z].display = 1;
							s[c.x][c.y][c.z].meshnum = c.meshnum;

							D3DXQUATERNION q(0, 0, 0, 1); // 単位クォータニオン'q'を生成
							D3DXMATRIX TurnMat; // 回転行列
							keyanirotx -= 90;
							D3DXMatrixIdentity(&TurnMat);
							D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(keyaniroty), D3DXToRadian(keyanirotx), D3DXToRadian(keyanirotz));
							//クォータニオンをマトリックスに変換
							D3DXMatrixRotationQuaternion(&TurnMat, &q);
							mStart = meshinf[c.meshnum]->mWorld;
							meshinf[c.meshnum]->SetPos(s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
							meshinf[c.meshnum]->Update();
							mEnd = TurnMat*meshinf[c.meshnum]->mWorld;
							mNow = mStart;
							AnimeFrame = 0;
							keyaniflg = 1;
						}
						else if (s[c.x][c.y][c.z + 1].meshnum != -999 && s[c.x][c.y - 1][c.z + 1].meshnum == -999 /*&& s[c.x][c.y][c.z + 1].deathflg == 0*/) {
							int num = tatesai[0];
							tatesai[0] = tatesai[3];
							tatesai[3] = tatesai[2];
							tatesai[2] = tatesai[1];
							tatesai[1] = num;

							yokosai[0] = tatesai[0];
							yokosai[2] = tatesai[2];

							s[c.x][c.y][c.z].display = 0;
							s[c.x][c.y][c.z].meshnum = -999;

							c.z += 1;
							//if (s[c.x][c.y][c.z].deathflg == 0) {
							c.y -= 1;
							//}
							s[c.x][c.y][c.z].display = 1;
							s[c.x][c.y][c.z].meshnum = c.meshnum;

							D3DXQUATERNION q(0, 0, 0, 1); // 単位クォータニオン'q'を生成
							D3DXMATRIX TurnMat; // 回転行列
							keyanirotx -= 90;
							D3DXMatrixIdentity(&TurnMat);
							D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(keyaniroty), D3DXToRadian(keyanirotx), D3DXToRadian(keyanirotz));
							//クォータニオンをマトリックスに変換
							D3DXMatrixRotationQuaternion(&TurnMat, &q);
							mStart = meshinf[c.meshnum]->mWorld;
							meshinf[c.meshnum]->SetPos(s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
							meshinf[c.meshnum]->Update();
							mEnd = TurnMat*meshinf[c.meshnum]->mWorld;
							mNow = mStart;
							AnimeFrame = 0;
							keyaniflg = 1;
						}
					}
				}
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
				if (keyaniflg == 0) {
					if (c.x > 0) {
						if (s[c.x - 1][c.y][c.z].meshnum == -999) {
							int num = yokosai[0];
							yokosai[0] = yokosai[3];
							yokosai[3] = yokosai[2];
							yokosai[2] = yokosai[1];
							yokosai[1] = num;

							tatesai[0] = yokosai[0];
							tatesai[2] = yokosai[2];

							s[c.x][c.y][c.z].display = 0;
							s[c.x][c.y][c.z].meshnum = -999;

							c.x -= 1;
							if (s[c.x][c.y + 1][c.z].meshnum == -999) { c.y += 1; }
							s[c.x][c.y][c.z].display = 1;
							s[c.x][c.y][c.z].meshnum = c.meshnum;

							D3DXQUATERNION q(0, 0, 0, 1); // 単位クォータニオン'q'を生成
							D3DXMATRIX TurnMat; // 回転行列


							keyanirotz -= 90;
							D3DXMatrixIdentity(&TurnMat);
							D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(keyaniroty), D3DXToRadian(keyanirotx), D3DXToRadian(keyanirotz));
							//クォータニオンをマトリックスに変換
							D3DXMatrixRotationQuaternion(&TurnMat, &q);
							mStart = meshinf[c.meshnum]->mWorld;
							meshinf[c.meshnum]->SetPos(s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
							meshinf[c.meshnum]->Update();
							mEnd = TurnMat*meshinf[c.meshnum]->mWorld;
							mNow = mStart;
							AnimeFrame = 0;
							keyaniflg = 1;
						}
						else if (s[c.x - 1][c.y][c.z].meshnum != -999 && s[c.x - 1][c.y - 1][c.z].meshnum == -999) {
							int num = yokosai[0];
							yokosai[0] = yokosai[3];
							yokosai[3] = yokosai[2];
							yokosai[2] = yokosai[1];
							yokosai[1] = num;

							tatesai[0] = yokosai[0];
							tatesai[2] = yokosai[2];


							s[c.x][c.y][c.z].display = 0;
							s[c.x][c.y][c.z].meshnum = -999;

							c.x -= 1;
							/*						if (s[c.x][c.y][c.z].deathflg == 1) {

														s[c.x][c.y][c.z].blockinfnum;
														s[c.x][c.y][c.z].meshnum = -999;
														s[c.x][c.y][c.z].display = 0;
														s[c.x][c.y][c.z].deathflg = 0;
														blockinf.erase(blockinf.begin() + s[c.x][c.y][c.z].blockinfnum);
														s[c.x][c.y][c.z].blockinfnum = -1;

													}c*/
													//if (s[c.x][c.y][c.z].deathflg == 0) {
							c.y -= 1;
							//}
							s[c.x][c.y][c.z].display = 1;
							s[c.x][c.y][c.z].meshnum = c.meshnum;

							D3DXQUATERNION q(0, 0, 0, 1); // 単位クォータニオン'q'を生成
							D3DXMATRIX TurnMat; // 回転行列
							keyanirotz -= 90;
							D3DXMatrixIdentity(&TurnMat);
							D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(keyaniroty), D3DXToRadian(keyanirotx), D3DXToRadian(keyanirotz));
							//クォータニオンをマトリックスに変換
							D3DXMatrixRotationQuaternion(&TurnMat, &q);
							mStart = meshinf[c.meshnum]->mWorld;
							meshinf[c.meshnum]->SetPos(s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
							meshinf[c.meshnum]->Update();
							mEnd = TurnMat*meshinf[c.meshnum]->mWorld;
							mNow = mStart;
							AnimeFrame = 0;
							keyaniflg = 1;
						}
					}
				}
			}

			if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
				if (keyaniflg == 0) {
					if (c.x < smax - 1) {
						if (s[c.x + 1][c.y][c.z].meshnum == -999) {
							int num = yokosai[0];
							yokosai[0] = yokosai[1];
							yokosai[1] = yokosai[2];
							yokosai[2] = yokosai[3];
							yokosai[3] = num;
							tatesai[0] = yokosai[0];
							tatesai[2] = yokosai[2];

							s[c.x][c.y][c.z].display = 0;
							s[c.x][c.y][c.z].meshnum = -999;
							c.x += 1;
							if (s[c.x][c.y + 1][c.z].meshnum == -999) { c.y += 1; }
							s[c.x][c.y][c.z].display = 1;
							s[c.x][c.y][c.z].meshnum = c.meshnum;

							D3DXQUATERNION q(0, 0, 0, 1); // 単位クォータニオン'q'を生成
							D3DXMATRIX TurnMat; // 回転行列

							keyanirotz += 90;
							D3DXMatrixIdentity(&TurnMat);
							D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(keyaniroty), D3DXToRadian(keyanirotx), D3DXToRadian(keyanirotz));
							//クォータニオンをマトリックスに変換
							D3DXMatrixRotationQuaternion(&TurnMat, &q);
							mStart = meshinf[c.meshnum]->mWorld;
							meshinf[c.meshnum]->SetPos(s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
							meshinf[c.meshnum]->Update();
							mEnd = TurnMat*meshinf[c.meshnum]->mWorld;
							mNow = mStart;
							AnimeFrame = 0;
							keyaniflg = 1;
						}
						else if (s[c.x + 1][c.y][c.z].meshnum != -999 && s[c.x + 1][c.y - 1][c.z].meshnum == -999/* && s[c.x+1][c.y][c.z].deathflg == 0*/) {
							int num = yokosai[0];
							yokosai[0] = yokosai[1];
							yokosai[1] = yokosai[2];
							yokosai[2] = yokosai[3];
							yokosai[3] = num;
							tatesai[0] = yokosai[0];
							tatesai[2] = yokosai[2];


							s[c.x][c.y][c.z].display = 0;
							s[c.x][c.y][c.z].meshnum = -999;

							c.x += 1;
							//if (s[c.x][c.y][c.z].deathflg == 0) {
							c.y -= 1;
							//}
							s[c.x][c.y][c.z].display = 1;
							s[c.x][c.y][c.z].meshnum = c.meshnum;

							D3DXQUATERNION q(0, 0, 0, 1); // 単位クォータニオン'q'を生成
							D3DXMATRIX TurnMat; // 回転行列
							keyanirotz += 90;
							D3DXMatrixIdentity(&TurnMat);
							D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(keyaniroty), D3DXToRadian(keyanirotx), D3DXToRadian(keyanirotz));
							//クォータニオンをマトリックスに変換
							D3DXMatrixRotationQuaternion(&TurnMat, &q);
							mStart = meshinf[c.meshnum]->mWorld;
							meshinf[c.meshnum]->SetPos(s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
							meshinf[c.meshnum]->Update();
							mEnd = TurnMat*meshinf[c.meshnum]->mWorld;
							mNow = mStart;
							//D3DXMATRIX start, end, now;

							//D3DXMatrixTranslation(&start, s[c.x][c.y][c.z].xyz.x, s[c.x][c.y][c.z].xyz.y, s[c.x][c.y][c.z].xyz.z);
							//D3DXMatrixTranslation(&end, s[c.x][c.y + 1][c.z].xyz.x, s[c.x][c.y + 1][c.z].xyz.y, s[c.x][c.y + 1][c.z].xyz.z);
							//meshinf[c.meshnum]->mWorld = AnimeProc(&start, &end, &meshinf[c.meshnum]->mWorld, c.frame);
							AnimeFrame = 0;
							keyaniflg = 1;
						}
					}
				}
			}

			if (keyaniflg == 1) {
				AnimeFrame += 0.1f;
				AnimeProc();
				meshinf[c.meshnum]->mWorld = mNow;
				if (AnimeFrame > 1) {
					sou.SE2->Play(0, 0, 0);
					c.frame = 0;
					AnimeFrame = 1;
					keyaniflg = 0;
					setsai(tatesai, yokosai);
					if (sai[0] == 1) {
						if (sai[1] == 2) {
							if (sai[4] == 4) {//パスの変更はコピペでおｋ
								meshinf[c.meshnum]->mname = "saikoro135.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}

					if (sai[0] == 2) {
						if (sai[1] == 6) {
							if (sai[4] == 4) {
								meshinf[c.meshnum]->mname = "saikoro365.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 6) {
						if (sai[1] == 5) {
							if (sai[4] == 4) {
								meshinf[c.meshnum]->mname = "saikoro645.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 5) {
						if (sai[1] == 1) {
							if (sai[4] == 4) {
								meshinf[c.meshnum]->mname = "saikoro415.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 2) {
						if (sai[1] == 4) {
							if (sai[4] == 1) {
								meshinf[c.meshnum]->mname = "saikoro351.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 5) {
						if (sai[1] == 3) {
							if (sai[4] == 1) {
								meshinf[c.meshnum]->mname = "saikoro421.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 3) {
						if (sai[1] == 2) {
							if (sai[4] == 1) {
								meshinf[c.meshnum]->mname = "saikoro231.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 6) {
						if (sai[1] == 2) {
							if (sai[4] == 3) {
								meshinf[c.meshnum]->mname = "saikoro632.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 4) {
						if (sai[1] == 2) {
							if (sai[4] == 6) {
								meshinf[c.meshnum]->mname = "saikoro536.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 3) {
						if (sai[1] == 6) {
							if (sai[4] == 2) {
								meshinf[c.meshnum]->mname = "saikoro263.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 1) {
						if (sai[1] == 5) {
							if (sai[4] == 3) {
								meshinf[c.meshnum]->mname = "saikoro142.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 5) {
						if (sai[1] == 4) {
							if (sai[4] == 6) {
								meshinf[c.meshnum]->mname = "saikoro456.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 3) {
						if (sai[1] == 1) {
							if (sai[4] == 5) {
								meshinf[c.meshnum]->mname = "saikoro214.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 2) {
						if (sai[1] == 3) {
							if (sai[4] == 6) {
								meshinf[c.meshnum]->mname = "saikoro326.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}

					if (sai[0] == 4) {
						if (sai[1] == 6) {
							if (sai[4] == 5) {
								meshinf[c.meshnum]->mname = "saikoro564.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 4) {
						if (sai[1] == 1) {
							if (sai[4] == 2) {
								meshinf[c.meshnum]->mname = "saikoro513.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 6) {
						if (sai[1] == 4) {
							if (sai[4] == 2) {
								meshinf[c.meshnum]->mname = "saikoro653.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}

					if (sai[0] == 5) {
						if (sai[1] == 6) {
							if (sai[4] == 3) {
								meshinf[c.meshnum]->mname = "saikoro462.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 6) {
						if (sai[1] == 3) {
							if (sai[4] == 5) {
								meshinf[c.meshnum]->mname = "saikoro624.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 1) {
						if (sai[1] == 4) {
							if (sai[4] == 5) {
								meshinf[c.meshnum]->mname = "saikoro154.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 2) {
						if (sai[1] == 1) {
							if (sai[4] == 3) {
								meshinf[c.meshnum]->mname = "saikoro312.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 3) {
						if (sai[1] == 5) {
							if (sai[4] == 6) {
								meshinf[c.meshnum]->mname = "saikoro246.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 1) {
						if (sai[1] == 3) {
							if (sai[4] == 2) {
								meshinf[c.meshnum]->mname = "saikoro123.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					if (sai[0] == 4) {
						if (sai[1] == 5) {
							if (sai[4] == 1) {
								meshinf[c.meshnum]->mname = "saikoro541.x";
								meshinf[c.meshnum]->load();
								meshinf[c.meshnum]->SetRot(0, 0, 0);
								meshinf[c.meshnum]->Update();
								keyanirotx = keyaniroty = keyanirotz = 0;
							}
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int i = 0; i < blockinf.size(); i++) {
							if (((c.x + 1 == blockinf[i]->x || c.x - 1 == blockinf[i]->x) && c.y == blockinf[i]->y && c.z == blockinf[i]->z) || ((c.z + 1 == blockinf[i]->z || c.z - 1 == blockinf[i]->z) && c.y == blockinf[i]->y && c.x == blockinf[i]->x)) {
								if (blockinf[i]->blocknum == sai[0]) {
									blockinf[i]->braniflg = 1;
									s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].deathflg = 1;
									////meshinf.erase(meshinf.begin() + s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].meshnum);
									//s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].meshnum = -999;
									//s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].display = 0;
									//blockinf.erase(blockinf.begin() + i);
								}
							}
							//else if (c.z + 1 == blockinf[i]->z || c.z - 1 == blockinf[i]->z && c.y == blockinf[i]->y && c.x == blockinf[i]->x) {
							//	meshinf.erase(meshinf.begin() + blockinf[i]->meshnum);
							//	s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].meshnum = -999;
							//	s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].display = 0;
							//	blockinf.erase(blockinf.begin() + i);
							//}
						}
					}
				}

			}

			for (int i = 0; i < blockinf.size(); i++) {

				if (blockinf[i]->braniflg == 1) {
					blockinf[i]->frame += 0.1;


					D3DXMATRIX start, end, now;
					D3DXMatrixTranslation(&start, s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].xyz.x, s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].xyz.y, s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].xyz.z);
					D3DXMatrixTranslation(&end, s[blockinf[i]->x][blockinf[i]->y + 1][blockinf[i]->z].xyz.x, s[blockinf[i]->x][blockinf[i]->y + 1][blockinf[i]->z].xyz.y, s[blockinf[i]->x][blockinf[i]->y + 1][blockinf[i]->z].xyz.z);

					meshinf[blockinf[i]->meshnum]->mWorld = AnimeProc(&start, &end, &meshinf[blockinf[i]->meshnum]->mWorld, blockinf[i]->frame);

					if (blockinf[i]->frame > 1) {
						sou.SE1->Play(0, 0, 0);
						Score += blockinf[i]->blocknum;
						s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].meshnum = -999;
						s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].display = 0;
						s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].deathflg = 0;
						s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].blockinfnum = -1;
						blockinf.erase(blockinf.begin() + i);

					}
				}
			}
			for (int i = 0; i < blockinf.size(); i++) {
				s[blockinf[i]->x][blockinf[i]->y][blockinf[i]->z].blockinfnum = i;
			}
			//for (int j = 0; j < smax; j++) {
			//	for (int k = 0; k < smax; k++) {
			//		ddt.SetChar("%d ", s[j][5][k].blockinfnum);
			//		
			//	}
			//	ddt.SetChar("\n");
			//}

		/*	for (int i = 0; i < 6; i++) {
				if (i == 0 || i == 1 || i == 4) {
					ddt.SetChar("sai[%d]", i);
					ddt.SetChar(":%d\n", sai[i]);
				}
			}
			*/
			//ddt.SetChar("b.x:%d\n", b.x);
			//ddt.SetChar("b.y:%d\n", b.y);
			//ddt.SetChar("b.z:%d\n", b.z);
			/*ddt.SetChar("c.x:%d\n", c.x);
			ddt.SetChar("c.y:%d\n", c.y);
			ddt.SetChar("c.z:%d\n", c.z);
			for (int i = 0; i < blockinf.size(); i++){
				if (i % 10==0)ddt.SetChar("\n");
				ddt.SetChar("%d ", blockinf[i]->meshnum);
				ddt.SetChar("%d ", blockinf[i]->x);
				ddt.SetChar("%d ", blockinf[i]->y);
				ddt.SetChar("%d ", blockinf[i]->z);
				ddt.SetChar("%d ", blockinf[i]->blocknum);
			}
			ddt.SetChar("\nmeshinf.size %d\n", meshinf.size());*/
		}
	}
	if (debagflg == 2) {


	}
	end = timeGetTime();

	//ddt.SetChar("\ntime %d\n", (end - start) / 1000);
	//ddt.SetChar("blockinf.size %d\n",blockinf.size());
	//ddt.SetChar("num %d", num);
}

void Game::Release() {
	int high = 0;
	high = fop.ReadScore();
	if (high < Score) {
		fop.WriteScore(Score);
	}
	m_MS.Release();
	lpTimehair->Release();
	lpTimetext->Release();
	for (int i = 0; i < polyinf.size(); i++) {
		delete polyinf[i];
	}
	polyinf.clear();
	for (int i = 0; i < meshinf.size(); i++) {
		delete meshinf[i];
	}
	meshinf.clear();

	blockinf.clear();
	sou.Release();
	cdg.scean = 0;
}

void Game::DrawFrame() {

	if (fps.CheckFps() <= 0) {
		return;
	}

	//if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
	//	if (cdg.SpaceFlg == 0) {
	//		//Release();
	//		cdg.scean = 5;
	//		cdg.SpaceFlg = 1;
	//		return;
	//	}

	//}
	//else { cdg.SpaceFlg = 0; }
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		if (cdg.EscapeFlg == 0) {
			//Release();
			cdg.scean = 5;
			cdg.EscapeFlg = 1;
			return;
		}

	}
	else { cdg.EscapeFlg = 0; }


	//ddt.SetChar("FPS:%d\n", fps.fps);
	//レイを向いている方向に発射、スプライトで目標＋表示、レイが当たったポリゴンの情報をデバックで表示

	// 更新処理
	Game::Update();

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

	m_MS.SetTransformView(&mView);
	m_MS.SetTransformProj(&mProj);
	m_MS.SetDirectionalLight(&light);
	m_MS.SetCamPos((D3DXVECTOR3*)&mCam._41);
	// 描画処理

	Game::Draw();
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RECT rc = { 0,0,380 ,64 };
	RECT rcs = { 0,64,380 ,128 };
	D3DXMatrixTranslation(&mTTWorld, SCRW - 140, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mSWorld, 0.0f, -10.0f, 0.0f);

	//RECT rcss = { 0,128,380 ,192 };
	//D3DXMatrixTranslation(&mStartWorld, SCRW/2, 0.0f, 0.0f);

	lpTimetextsp->Begin(D3DXSPRITE_ALPHABLEND);

	//lpTimetextsp->SetTransform(&mStartWorld);
	//lpTimetextsp->Draw(lpTimetext, &rcss, &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));


	lpTimetextsp->SetTransform(&mTTWorld);
	lpTimetextsp->Draw(lpTimetext, &rc, &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	lpTimetextsp->SetTransform(&mSWorld);
	lpTimetextsp->Draw(lpTimetext, &rcs, &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	lpTimetextsp->End();
	static int nu1 = 0;
	//ddt.SetChar("resultflg %d", resultflg);
	
	if (startflg == 0) {
		nu1 = 90 - ((end - start) / 1000);
		if (nu1 < 0)nu1 = 0;
		time0 = nu1;
		if (nu1 == 0) { resultflg = 1; }
	}
	if (nu1 > 88 && startflg == 0) {
		RECT rcss = { 0,128,380 ,192 };
		lpTimetextsp->Begin(D3DXSPRITE_ALPHABLEND);

		lpTimetextsp->SetTransform(&mStartWorld);
		lpTimetextsp->Draw(lpTimetext, &rcss, &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		lpTimetextsp->End();
		D3DXMatrixTranslation(&mStartWorld, SCRW / 2, 0.0f, 0.0f);
	}
	char cScore[12];
	sprintf_s(cScore, sizeof(cScore), "%d", nu1);

	int i, j;

	for (i = 0; cScore[i] != '\0'; i++);

	D3DXMatrixTranslation(&mTimeWorld, SCRW, 50.0f, 0.0f);

	D3DXMatrixTranslation(&mScoreWorld, SCRW / 6, 50.0f, 0.0f);
	lpTime->Begin(D3DXSPRITE_ALPHABLEND);
	for (; i >= 0; i--) {
		mTimeWorld *= mTimeTrans;
		lpTime->SetTransform(&mTimeWorld);
		lpTime->Draw(lpTimehair, &rcNum[cScore[i] - '0'], &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		//ddt.SetChar("%c ", cScore[i]);
	}

	for (; i >= 0; i--) {
		mScoreWorld *= mScoreTrans;
		lpTime->SetTransform(&mScoreWorld);
		lpTime->Draw(lpTimehair, &rcNum[cScore[i] - '0'], &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		//ddt.SetChar("%c ", cScore[i]);
	}
	lpTime->End();

	char cScore1[12];
	sprintf_s(cScore1, sizeof(cScore1), "%d", Score);

	i = 0; j = 0;

	for (i = 0; cScore1[i] != '\0'; i++);
	lpTime->Begin(D3DXSPRITE_ALPHABLEND);
	for (; i >= 0; i--) {
		mScoreWorld *= mScoreTrans;
		lpTime->SetTransform(&mScoreWorld);
		lpTime->Draw(lpTimehair, &rcNum[cScore1[i] - '0'], &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		//ddt.SetChar("%c ", cScore[i]);
	}
	lpTime->End();

	ddt.Draw();
	ddt.Bufferreset();
	//RECT rcss = { 0,128,380 ,192 };
	//lpTimetextsp->Begin(D3DXSPRITE_ALPHABLEND);

	//lpTimetextsp->SetTransform(&mStartWorld);
	//lpTimetextsp->Draw(lpTimetext, &rcss, &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//lpTimetextsp->End();
	//D3DXMatrixTranslation(&mStartWorld, SCRW / 2, 0.0f, 0.0f);

	if (startflg == 1) {
		starttime = 3 - ((end - start) / 1000);

		D3DXMatrixTranslation(&mStarttimeWorld, SCRW / 2, 0.0f, 0.0f);

		char cScore2[12];
		sprintf_s(cScore2, sizeof(cScore2), "%d",starttime);

		i = 0; j = 0;

		for (i = 0; cScore2[i] != '\0'; i++);
		lpTime->Begin(D3DXSPRITE_ALPHABLEND);
		for (; i >= 0; i--) {
			
			lpTime->SetTransform(&mStarttimeWorld);
			lpTime->Draw(lpTimehair, &rcNum[cScore2[i] - '0'], &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			//ddt.SetChar("%c ", cScore[i]);
		}
		lpTime->End();

		if (starttime < 0) { start = timeGetTime(); startflg = 0; }
	}
	if (resultflg == 1) { 
		RECT rcst = { 0,192,380 ,256 };
		D3DXMatrixTranslation(&mTimeupWorld, SCRW - 300, 100, 0.0f);
		lpTimetextsp->Begin(D3DXSPRITE_ALPHABLEND);
		lpTimetextsp->SetTransform(&mTimeupWorld);
		lpTimetextsp->Draw(lpTimetext, &rcst, &vec, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		lpTimetextsp->End();
		if (tcount > 100) {
			cdg.scean = 5;
		}
		tcount++;
	
	}

	// 描画終了
	cdg.lpD3DDevice->EndScene();

	// バックバッファをプライマリバッファにコピー
	cdg.lpD3DDevice->Present(NULL, NULL, NULL, NULL);

}