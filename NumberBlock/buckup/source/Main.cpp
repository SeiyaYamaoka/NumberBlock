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

//#define	FULLSCREEN	0		// �t���X�N���[������ 1 �ɂ���

//#define	SCRW		800	// Width	16:9
//#define	SCRH		600	// Height

LPDIRECT3D9				lpD3D;		// Direct3D�C���^�[�t�F�C�X

									//LPDIRECT3DDEVICE9		cdg.lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X


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
	if (MessageBox(cdg.hwnd, "�t���X�N���[���ɂ��܂����H", "�m�F", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
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

	//---------------------DirectX Graphics�֘A-----------------------

	// Direct3D �I�u�W�F�N�g���쐬
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		// �I�u�W�F�N�g�쐬���s
		MessageBox(NULL, "Direct3D �̍쐬�Ɏ��s���܂����B", "ERROR", MB_OK | MB_ICONSTOP);
		// �I������
		return 0;
	}
	// �g�p����A�_�v�^�ԍ�
	adapter = 0;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D �������p�����[�^�̐ݒ�
	if (bFullScreen)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
		//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		D3DDISPLAYMODE disp;
		// ���݂̉�ʃ��[�h���擾
		lpD3D->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// �\���̈�T�C�Y�̐ݒ�
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!bFullScreen)
	{
		// �E�C���h�E���[�h
		d3dpp.Windowed = 1;
	}

	// Z �o�b�t�@�̎����쐬
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//�ޯ��ޯ̧��ۯ��\�ɂ���(GetDC���\�ɂȂ�)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// �f�o�C�X�̍쐬 - T&L HAL
	//if (FAILED(m_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE, &m_d3dpp, &m_lpD3DDev)))
	if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, cdg.hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &cdg.lpD3DDevice)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, cdg.hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &cdg.lpD3DDevice)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, cdg.hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &cdg.lpD3DDevice)))
			{
				// ���ǎ��s����
				MessageBox(NULL, "DirectX9���������ł��܂���B\n���Ή��̃p�\�R���Ǝv���܂��B", "ERROR", MB_OK | MB_ICONSTOP);
				lpD3D->Release();
				// �I������
				return 0;
			}
		}
	}

	// �����_�����O�E�X�e�[�g��ݒ�
	// Z �o�b�t�@�L����->�O��֌W�̌v�Z�𐳊m�ɂ��Ă����
	cdg.lpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	cdg.lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�u�����f�B���O�L����
	cdg.lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// �A���t�@�u�����f�B���O���@��ݒ�
	cdg.lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	cdg.lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�
	cdg.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// �e�N�X�`���̐F���g�p
	cdg.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// ���_�̐F���g�p
	cdg.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// �����_�����O���̐F�̌v�Z���@�̐ݒ�
	cdg.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//���ʃJ�����O
	cdg.lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �t�B���^�ݒ�
	cdg.lpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	cdg.lpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	cdg.lpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// ���C�g
	cdg.lpD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	
	//cdg.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);//���邳�v�Z���邩���Ȃ���
	//D3DLIGHT9 Light;
	//ZeroMemory(&Light, sizeof(Light));
	//Light.Type = D3DLIGHT_DIRECTIONAL;//�f�B���N�V���i�����C�g
	//Light.Diffuse.r = 1.0f;//}
	//Light.Diffuse.g = 1.0f;//}���C�g�̐F
	//Light.Diffuse.b = 1.0f;//}
	//Light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	//cdg.lpD3DDevice->SetLight(0, &Light);
	//cdg.lpD3DDevice->LightEnable(0, TRUE);

	cdg.lpD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	cdg.lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &lpBackbuffer);

	// ���_�t�H�[�}�b�g�̐ݒ�
	cdg.lpD3DDevice->SetFVF(FVF_VERTEX);

	timeBeginPeriod(1);


	// ������
	Title title;
	
	Game game;
	//game.Init();


	// �Q�[�����[�v //
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


	// �I������
	//title.Release();
	//game.Release();

	lpBackbuffer->Release();

	// Direct3D �I�u�W�F�N�g�����
	cdg.lpD3DDevice->Release();
	lpD3D->Release();

	return (int)msg.wParam;
}