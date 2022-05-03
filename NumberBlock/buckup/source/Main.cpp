#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<vector>

#include "Main.h"
#include "Title.h"
#include"Game.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

//#define	FULLSCREEN	0		// フルスクリーン時に 1 にする

//#define	SCRW		800	// Width	16:9
//#define	SCRH		600	// Height

LPDIRECT3D9				lpD3D;		// Direct3Dインターフェイス

									//LPDIRECT3DDEVICE9		cdg.lpD3DDevice;	// Direct3DDeviceインターフェイス


LPDIRECT3DSURFACE9 lpBackbuffer;
D3DPRESENT_PARAMETERS d3dpp;

int adapter;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

LRESULT APIENTRY WndFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			//PostQuitMessage(0);
			return 0;
		}
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPSTR lpszCmdParam, int nCmdshow)
{
	MSG msg;


	WNDCLASS wc;
	char szAppName[] = "Generic Game SDK Window";

	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = WndFunc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	RegisterClass(&wc);

	cdg.hwnd = CreateWindowEx(
		//		WS_EX_TOPMOST,
		0,
		szAppName,
		"NumberBlock",
		//		WS_VISIBLE|WS_POPUP,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCRW, SCRH,
		NULL, NULL, hInst,
		NULL);

	if (!cdg.hwnd)return FALSE;

	ShowWindow(cdg.hwnd, nCmdshow);
	UpdateWindow(cdg.hwnd);
	SetFocus(cdg.hwnd);
	bool bFullScreen = false;
	if (MessageBox(cdg.hwnd, "フルスクリーンにしますか？", "確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		bFullScreen = true;
	}
	if (bFullScreen) {
		ShowCursor(FALSE);
	}
	else {
		RECT rc = { 0,0,SCRW,SCRH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(cdg.hwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOZORDER);
	}

	//---------------------DirectX Graphics関連-----------------------

	// Direct3D オブジェクトを作成
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		// オブジェクト作成失敗
		MessageBox(NULL, "Direct3D の作成に失敗しました。", "ERROR", MB_OK | MB_ICONSTOP);
		// 終了する
		return 0;
	}
	// 使用するアダプタ番号
	adapter = 0;

	// ウインドウの作成が完了したので、Direct3D を初期化する
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D 初期化パラメータの設定
	if (bFullScreen)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
		//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		D3DDISPLAYMODE disp;
		// 現在の画面モードを取得
		lpD3D->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// 表示領域サイズの設定
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!bFullScreen)
	{
		// ウインドウモード
		d3dpp.Windowed = 1;
	}

	// Z バッファの自動作成
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//ﾊﾞｯｸﾊﾞｯﾌｧをﾛｯｸ可能にする(GetDCも可能になる)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// デバイスの作成 - T&L HAL
	//if (FAILED(m_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE, &m_d3dpp, &m_lpD3DDev)))
	if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, cdg.hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &cdg.lpD3DDevice)))
	{
		// 失敗したので HAL で試行
		if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, cdg.hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &cdg.lpD3DDevice)))
		{
			// 失敗したので REF で試行
			if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, cdg.hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &cdg.lpD3DDevice)))
			{
				// 結局失敗した
				MessageBox(NULL, "DirectX9が初期化できません。\n未対応のパソコンと思われます。", "ERROR", MB_OK | MB_ICONSTOP);
				lpD3D->Release();
				// 終了する
				return 0;
			}
		}
	}

	// レンダリング・ステートを設定
	// Z バッファ有効化->前後関係の計算を正確にしてくれる
	cdg.lpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	cdg.lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファブレンディング有効化
	cdg.lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// アルファブレンディング方法を設定
	cdg.lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	cdg.lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// レンダリング時のアルファ値の計算方法の設定
	cdg.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// テクスチャの色を使用
	cdg.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// 頂点の色を使用
	cdg.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// レンダリング時の色の計算方法の設定
	cdg.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//裏面カリング
	cdg.lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// フィルタ設定
	cdg.lpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	cdg.lpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	cdg.lpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// ライト
	cdg.lpD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	
	//cdg.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);//明るさ計算するかしないか
	//D3DLIGHT9 Light;
	//ZeroMemory(&Light, sizeof(Light));
	//Light.Type = D3DLIGHT_DIRECTIONAL;//ディレクショナルライト
	//Light.Diffuse.r = 1.0f;//}
	//Light.Diffuse.g = 1.0f;//}ライトの色
	//Light.Diffuse.b = 1.0f;//}
	//Light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	//cdg.lpD3DDevice->SetLight(0, &Light);
	//cdg.lpD3DDevice->LightEnable(0, TRUE);

	cdg.lpD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	cdg.lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &lpBackbuffer);

	// 頂点フォーマットの設定
	cdg.lpD3DDevice->SetFVF(FVF_VERTEX);

	timeBeginPeriod(1);


	// 初期化
	Title title;
	
	Game game;
	//game.Init();


	// ゲームループ //
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			switch (cdg.scean)
			{
			case 0:	title.Init(); break;
			case 1:title.DrawFrame(); break;
			case 2:title.Release(); break;
			case 3:game.Init(); break;
			case 4:game.DrawFrame(); break;
			case 5:game.Release(); break;
			case 6:break;
			default:
				break;
			}
		}
		if (cdg.scean == 6) { break; }
	}

	timeEndPeriod(1);


	// 終了処理
	//title.Release();
	//game.Release();

	lpBackbuffer->Release();

	// Direct3D オブジェクトを解放
	cdg.lpD3DDevice->Release();
	lpD3D->Release();

	return (int)msg.wParam;
}