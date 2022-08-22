#include"DxLib.h"
#include"block.h"
#include"MapData.h"
#include"Move.h"
#include"Hit.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//ぷよぷよモドキを作りたい

	// Windowsモードにする
	ChangeWindowMode(TRUE);
	// 画面サイズの設定
	SetGraphMode(640, 480, 32);
	
	// DXライブラリ初期化
	if (DxLib_Init() == -1)
	{	//初期化に失敗した
		return -1;	       }
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	ResetMap();
	BlockInit();
	RandomBlock();
	//------------------------------------------------------
    // メインループ部分
	while (ProcessMessage() == 0)
	{
		//裏画面を消す
		ClearDrawScreen();
		//移動処理
		Move();
		Spin();
		//座標取得
		int x1 = GetX();	
		int x2 = GetX2();
		float y1 = GetY();
		float y2 = GetY2();
		int C1 = GetCl1();
		int C2 = GetCl2();
		//描画
		DrawBlock(x1, x2, y1, y2,C1,C2);
		//裏画面を表画面を入れ替える
		ScreenFlip();
		if (MAP_HitCheck(x1, y1, false) || MAP_HitCheck(x2, y2, false))
		{
			SearchLoadMap();
			HitSet(x1, y1, C1);
			HitSet(x2, y2, C2);
			DropSearch();
			while (1)
			{
				//裏画面を消す
				ClearDrawScreen();
				//浮いてるブロックの落下処理
				DropMove();
				//描画
				DrawBlock(0, 0, 0, 0, 0, 0);
				//裏画面を表画面を入れ替える
				ScreenFlip(); 
				if (!GetDrop())//落下完了
				{
					while (!GetReMove())
					{
						//裏画面を消す
						ClearDrawScreen();
						//ブロックの消去
						Search();
						//描画
						DrawBlock(0, 0, 0, 0, 0, 0);
						//裏画面を表画面を入れ替える
						ScreenFlip();
						if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
					}
					while (GetReMove()) 
					{
						MoveLoadMap();
						DropSearch();
					}
				}
				if (!GetDrop())break;
				if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
			}
			Search_chengeMap();
			RandomBlock();
		}
		//ESCキーを押して終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		if (CheckHitKey(KEY_INPUT_Z)) WaitKey();
	}
	//======================================================
	// DXライブラリ終了とプログラム終了
	DxLib_End();
	return 0;
}