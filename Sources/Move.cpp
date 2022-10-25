#include "DxLib.h"
#include "MapData.h"
#include "Hit.h"
#include "Move.h"
#include "Start.h"
bool move = false, spin = false, Inversion = false, drop = false,S = true;
int MoveMap[MapMax], R[4];
int ScondX = 0, ScondY = CHIPSIZE;
int DownTime = 0, X1 = CHIPSIZE * 2,X2 = X1; 
float Y1 = 0, G = 0.5f,Y2 = Y1 + ScondY;

int GetX(){	return X1;}
float GetY(){ return Y1;}
int GetX2(){ return X2;}
float GetY2(){ return Y2;}
int GetCl1() { return R[0];}
int GetCl2() { return R[1];}
int GetNext1() { return R[2];}
int GetNext2() { return R[3];}
//ブロック生成
void RandomBlock()
{	
	if (S) { R[2] = GetRand(4); R[3] = GetRand(4); S = false; }//スタート時はブロックを予告していないため
	//位置等のリセット
	ScondX = 0, ScondY = -CHIPSIZE;
	X1 = CHIPSIZE * 5, X2 = X1;
	Y1 = CHIPSIZE, Y2 = Y1 + ScondY;
	drop = false; Inversion = false;
	//予告していたブロックを落下させる
	R[0] = R[2];  R[1] = R[3];
	//ランダムなブロックを予告
	R[2] = GetRand(4); R[3] = GetRand(4);
	if (MoveMap[4] != 9) { Over(); S = true; }//出現する位置にブロックがあるならゲームオーバー
}
void MoveLoadMap()
{
	for (int i = 0; i < MapMax; i++)
	{	MoveMap[i] = Map_GetData(i);}
}
//ブロックの移動処理
void Move()
{
	int drop = false;
	DownTime++;
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
	{
		if (!move)
		{
			move = true; //長押しで反応しない
			int x = X1 + 1,x2 = X2 + 1;
			//壁やほかのぷよが進行方向にあるなら移動しない
			if (!MAP_HitCheck(x, Y1, true) && !MAP_HitCheck(x2, Y2, true))
			{	
				if (X1 < MAP_X * CHIPSIZE) { X1 += CHIPSIZE;	X2 = X1 + ScondX; }//範囲外に移動しない
			}
		}
	}
	else if (CheckHitKey(KEY_INPUT_LEFT) != 0)
	{
		if (!move)
		{
			move = true; //長押しで反応しない
			int x = X1 - 1, x2 = X2 - 1;
			if (!MAP_HitCheck(x,Y1,true) && !MAP_HitCheck(x2, Y2, true))	//壁やほかのぷよが進行方向にあるなら移動しない
			{
				if (X1 - CHIPSIZE > 0) { X1 -= CHIPSIZE; X2 = X1 + ScondX; }//範囲外に移動しない
			}
		}	
	}
	else
	{	move = false;	}
	if(CheckHitKey(KEY_INPUT_DOWN)){ Y1 += G; }
	Y1 += G; //落下させる
	Y2 = Y1 + ScondY;
}
void Spin()
{
	if (CheckHitKey(KEY_INPUT_SPACE) == 0)
	{	spin = true;	}
	else
	{
		if (spin)
		{
			spin = false;
			int y = ScondY, x = ScondX;
			//時計回りに90度回転
			if (Inversion) { ScondX = y; ScondY = x; }
			else { ScondX = -y; ScondY = -x; }
			X2 = X1 + ScondX; Y2 = Y1 + ScondY;
			//回転した結果重なった
			if (MAP_HitCheck(X2, Y2, true))
			{
				if (!Inversion)//隣のブロックや壁に重なる場合
				{
					//90度回転では無く上下を反転する
					ScondX = x; ScondY = -y;
					X1 = X1 + ScondX; Y1 = Y1 - ScondY;
					X2 = X1 + ScondX; Y2 = Y1 + ScondY;
				}
			}
			//重ならなかった
			else 
			{  Inversion = !Inversion; }//横true　縦false
		}
	}
}