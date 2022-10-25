#include "DxLib.h"
#include "Start.h"
bool Main = false; int StringCount = 0;
const int Size = 32;
//スタート画面の処理
void Start()
{
	ClearDrawScreen();
	if (CheckHitKey(KEY_INPUT_SPACE) != 0)Main = true;
	StringCount++; if (StringCount > 240)StringCount = 0;
	if (StringCount < 120)DrawString(64, Size * 4, "スペースキーを押してスタート", GetColor(255, 255, 255));
	DrawString(64, Size * 6, "操作", GetColor(255, 255, 255));
	DrawString(64, Size * 7, "十字キー横で移動", GetColor(255, 255, 255));
	DrawString(64, Size * 8, "十字キー下で加速", GetColor(255, 255, 255));
	DrawString(64, Size * 9, "スペースキーで回転", GetColor(255, 255, 255));
	DrawString(64, Size *10, "エスケープキー押して終了", GetColor(255, 255, 255));
	ScreenFlip();
}
//スタート画面に戻る
void Over()
{
	Main = false;
}
//シーンの状態を取得
bool GetMain()
{
	return Main;
}