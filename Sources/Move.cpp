#include "DxLib.h"
#include "MapData.h"
#include "Hit.h"
#include "Move.h"

bool move, spin = false, Inversion = false, drop = false;;
int MoveMap[MapMax], R[2];
int ScondX = 0, ScondY = CHIPSIZE;
int DownTime = 0, X1 = CHIPSIZE * 2,X2 = X1; 
float Y1 = 0, G = 0.5f,Y2 = Y1 + ScondY;

int GetX(){	return X1;}
float GetY(){ return Y1;}
int GetX2(){ return X2;}
float GetY2(){ return Y2;}
int GetCl1() { return R[0];}
int GetCl2() { return R[1];}
//ブロック生成
void RandomBlock()
{
	ScondX = 0, ScondY = CHIPSIZE;
	X1 = CHIPSIZE * 2, X2 = X1;
	Y1 = 0, Y2 = Y1 + ScondY;
	drop = false; R[0] = GetRand(4); R[1] = GetRand(4);
	MoveLoadMap();
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
				if (X1 < MAP_X * CHIPSIZE) { X1 += CHIPSIZE;	X2 = X1 + ScondX; }
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
				if (X1 - CHIPSIZE > 0) { X1 -= CHIPSIZE; X2 = X1 + ScondX; }
			}
		}	
	}
	else
	{	move = false;	}
	Y1 += G;
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
			if (Inversion) { ScondX = y; ScondY = x; }
			else { ScondX = -y; ScondY = -x; }

			 X2 = X1 + ScondX; Y2 = Y1 + ScondY;
			 if (MAP_HitCheck(X2, Y2, true))
			 {
				int Rx = X1 + CHIPSIZE; int Lx = X1 - CHIPSIZE;
				if (!MAP_HitCheck(Rx, Y1, true)&& ScondX < 0)
				{
					X1 = Rx;
					X2 = X1 + ScondX;
					Y2 = Y1 + ScondY;
					Inversion = !Inversion;
				}
				else if (!MAP_HitCheck(Lx, Y1, true)&& ScondX > 0)
			    {
					X1 = Lx;
					X2 = X1 + ScondX;
					Y2 = Y1 + ScondY;
					Inversion = !Inversion;
				}
				else
				{
					ScondX = x; ScondY = y;
					X2 = X1 + ScondX; Y2 = Y1 + ScondY;
				}
			 }
			else 
			{  	Inversion = !Inversion; }
		}
	}
}