#define _USE_MATH_DEFINES

#include "DxLib.h"
#include "App.h"
#include <windows.h>
#include <math.h>

const int X = 600, Y = 0;
const int x = 0, y = 300, z = -700;
LONGLONG t;
LONGLONG temp_time;
MSG msg;
HWND hWnd;
WNDCLASS myProg;
int ModelHandle, GHandle, Light_Handle, tmp = 0, Space = 0, mouseX, mouseY, mHandle_1, mHandle_2, mHandle_3;
bool Flag = false;
int Ghandle = 0;
float  AnimTotalTime_1, AnimTotalTime_2, AnimTotalTime_3;
float  AnimNowTime;
int    AnimAttachIndex_1, AnimAttachIndex_2, AnimAttachIndex_3;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool Regist_Window(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//SetGraphMode(1920, 1080, 32);
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	SetWindowText(u8"くじ引き");
	Rand rnd;
	SetOutApplicationLogValidFlag(FALSE);
	if (!Regist_Window(hInstance, hPrevInstance, lpCmdLine, nCmdShow))return -1;
	if (!rnd.LoadDate())return -1;

	ChangeWindowMode(true);
	
	

	if (DxLib_Init() < 0)
	{
		
		return -1;
	}
	/*--------本体(抽選箱)---------------------*/
	ModelHandle = MV1LoadModel("model\\Box.mv1");
	//MV1SetRotationXYZ(ModelHandle, VGet(0, M_PI / 4, 0));
	MV1SetPosition(ModelHandle, VGet(0.0f, 0.0f, 0.0f));
	SetLightDirectionHandle(Light_Handle, VGet(0, 0, 0));
	SetCameraPositionAndTarget_UpVecY(VGet(300, 450, -100), VGet(0, 0, 0));
	/*----------------------------------------*/

	SetLightPosition(VGet(0,0,0));

	//GHandle = LoadGraph("image\\Button.png");
	

	/*-------アニメーション関係----------------*/
	mHandle_1 = MV1LoadModel("model\\kuji_top.mv1");
	mHandle_2 = MV1LoadModel("model\\kuji_top_1.mv1");
	mHandle_3 = MV1LoadModel("model\\kuji_bottom.mv1");

	MV1SetScale(mHandle_1, VGet(1.1f, 1.1f, 1.0f));
	MV1SetScale(mHandle_2, VGet(1.1f, 1.1f, 1.0f));
	MV1SetScale(mHandle_3, VGet(1.1f, 1.1f, 1.0f));

	MV1SetPosition(mHandle_1, VGet(x, y, z));
	MV1SetPosition(mHandle_2, VGet(x, y, z));
	MV1SetPosition(mHandle_3, VGet(x, y, z));

	MV1SetRotationXYZ(mHandle_1, VGet(0, M_PI / 2, 0));
	MV1SetRotationXYZ(mHandle_2, VGet(0, M_PI / 2, 0));
	MV1SetRotationXYZ(mHandle_3, VGet(0, M_PI / 2, 0));

	AnimAttachIndex_1 = MV1AttachAnim(mHandle_1, 0);
	AnimAttachIndex_2 = MV1AttachAnim(mHandle_2, 0);
	AnimAttachIndex_3 = MV1AttachAnim(mHandle_3, 0);
	
	AnimTotalTime_1 = MV1GetAttachAnimTotalTime(mHandle_1, AnimAttachIndex_1);
	AnimTotalTime_2 = MV1GetAttachAnimTotalTime(mHandle_2, AnimAttachIndex_2);
	AnimTotalTime_3 = MV1GetAttachAnimTotalTime(mHandle_3, AnimAttachIndex_3);

	AnimNowTime = 0.0f;

	MV1SetAttachAnimTime(mHandle_1, AnimAttachIndex_1, AnimNowTime);
	MV1SetAttachAnimTime(mHandle_2, AnimAttachIndex_1, AnimNowTime);
	MV1SetAttachAnimTime(mHandle_3, AnimAttachIndex_3, AnimNowTime);
	/*----------------------------------------*/

	
	SetDrawScreen(DX_SCREEN_BACK);


   	while(ProcessMessage() != -1) {

		//GetMousePoint(&mouseX, &mouseY);

		if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		

/*-----------------------メインウィンドウの処理------------------------------------------------------*/
	ClearDrawScreen();

	/*-------------------model描画------------------------------*/
	MV1SetPosition(ModelHandle, VGet(0.0f, 0.0f, 0.0f));
	SetCameraPositionAndTarget_UpVecY(VGet(0, 500, -1000), VGet(0, 0, 0));
	MV1DrawModel(ModelHandle);
	/*---------------------------------------------------------*/

	/*--------------ボタン描画---------------------------------*/
		//DrawExtendGraph(X, Y, X + 40, Y + 40, GHandle, TRUE);
	/*---------------------------------------------------------*/

		if ((CheckHitKey(KEY_INPUT_RETURN) != 0) && (CheckHitKey(KEY_INPUT_SPACE) == 0))
		{
			Flag = false;
			Space = 0;
		}


		if ((CheckHitKey(KEY_INPUT_RETURN) == 0) && (CheckHitKey(KEY_INPUT_SPACE) != 0))
		{
			if (Space > 1)
			{
				Space = 2;
				Flag = true;
				AnimNowTime = 0.0f;
			}
			else Space++;				
		}

		if (Space == 1)tmp = rnd.Random();

		if (Flag == true)
		{
			AnimNowTime += 1.0f;
			MV1SetAttachAnimTime(mHandle_1, AnimAttachIndex_1, AnimNowTime);
			MV1SetAttachAnimTime(mHandle_2, AnimAttachIndex_2, AnimNowTime);
			MV1SetAttachAnimTime(mHandle_3, AnimAttachIndex_3, AnimNowTime);
			MV1DrawModel(mHandle_1);
			MV1DrawModel(mHandle_2);
			MV1DrawModel(mHandle_3);

			if (AnimNowTime >= AnimTotalTime_1)
			{
				rnd.DrawImage(tmp);
			}
		}

	SetScreenFlipTargetWindow(NULL);
	ScreenFlip();
/*--------------------------------------------------------------------------------------------------*/

	WaitTimer(2);

/*------------------------サブウィンドウの処理------------------------------------------------------*/
	
		ClearDrawScreen();
		rnd.Count();
		SetScreenFlipTargetWindow(hWnd);
		ScreenFlip();
	

/*--------------------------------------------------------------------------------------------------*/
	}
	if (!rnd.SaveDate())return -1;
	DeleteGraph(GHandle);
	MV1DeleteModel(ModelHandle);
	rnd.ImageDelete();
	DxLib_End();
	
	return 0;
}

//windowプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}


//サブウィンドウの登録
bool Regist_Window(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
	myProg.style = CS_HREDRAW | CS_VREDRAW;
	myProg.lpfnWndProc = WndProc;
	myProg.cbClsExtra = 0;
	myProg.cbWndExtra = 0;
	myProg.hInstance = hInstance;
	myProg.hIcon = NULL;
	myProg.hCursor = LoadCursor(NULL, IDC_ARROW);
	myProg.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	myProg.lpszMenuName = NULL;
	myProg.lpszClassName = "ウィンドウ１クラスネーム";
	if (!RegisterClass(&myProg))
	{
		return false;
	}
	hWnd = CreateWindow(
		"ウィンドウ１クラスネーム",
		"詳細",
		WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500,
		NULL, NULL, hInstance, NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
}
