#include"DxLib.h"
#include"block.h"
#include"MapData.h"
#include"Move.h"
#include"Hit.h"
#include "Start.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//ぷよぷよモドキを作りたい

	// Windowsモードにする
	ChangeWindowMode(TRUE);
	// 画面サイズの設定
	SetGraphMode(480, 480, 32);
	
	// DXライブラリ初期化
	if (DxLib_Init() == -1)
	{	//初期化に失敗した
		return -1;	       }
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);	
	BlockInit();
	//------------------------------------------------------
    // メインループ部分
	while (ProcessMessage() == 0)
	{
		bool Main = GetMain();
		if (!Main) 
		{
			while (!Main)//スタート画面
			{
				Start();
				Main = GetMain();
				if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
			}		
			ResetMap();
			MoveLoadMap();
			SearchLoadMap();
			RandomBlock();
		}
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
		int Nc1 = GetNext1();
		int Nc2 = GetNext2();
		//描画
		DrawMap(Nc1,Nc2);
		DarwMove(x1, y1, C1);
		DarwMove(x2, y2, C2);
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
				DrawMap(Nc1, Nc2);
				DrawDrop();
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
						while (GetErase())
						{
							//裏画面を消す
							ClearDrawScreen();
							Deadcount();
							//描画
							DrawMap(Nc1, Nc2);
							//裏画面を表画面を入れ替える
							ScreenFlip();
							if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
						}
						//描画
						DrawMap(Nc1, Nc2);
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
			MoveLoadMap();
			RandomBlock();
		}
		//ESCキーを押して終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	//======================================================
	// DXライブラリ終了とプログラム終了
	DxLib_End();
	return 0;
}