#include "block.h"
#include "DxLib.h"
#include "MapData.h"
#include "Hit.h"
int Frame[3],Colours[6];//緑0、赤1、黄色2、青3、紫4、灰色5
int Search_MapData[MapMax], No[MAP_Y][MAP_X] = {0};
float Time = 0; int DropCount;
int drops[MAP_Y][MAP_X];
bool Drop, Erase, ReMove;

bool GetDrop()  { return Drop; }
bool GetReMove() { return ReMove; }
void BlockInit()
{
    LoadDivGraph("画像データ/Frame.png", 3, 3, 1, CHIPSIZE, CHIPSIZE, Frame);
    LoadDivGraph("画像データ/Block.png", 6, 3, 2, CHIPSIZE, CHIPSIZE, Colours);
	SearchLoadMap();
}
void SearchLoadMap()
{
	for (int i = 0; i < MapMax; i++)
	{
		Search_MapData[i] = Map_GetData(i);	}
}

void Search_chengeMap()
{
	for (int i = 0; i < MapMax; i++)
	{
		int c = Search_MapData[i];
		Chenge_MapData(i,c);
	}
}
//描画処理
void DrawBlock(int x1, int x2, float y1, float y2, int c1, int c2)
{
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			int no = Search_MapData[y * MAP_X + x];
			int Dx = (x + 1) * CHIPSIZE;
			int Dy = (y + 1) * CHIPSIZE;
			if (no != 8) DrawGraph((x + 1) * CHIPSIZE, (y + 1) * CHIPSIZE, Frame[0], FALSE);
			if (no != 9)
			{
				if (no == 8) { DrawGraph(Dx, Dy, Frame[1], FALSE); }
				else { DrawGraph(Dx, Dy, Colours[no], TRUE); }
			}
			DrawFormatString((x + 1) * CHIPSIZE, (y + 1) * CHIPSIZE, GetColor(0, 0, 0), "%d", No[y][x]);			
		}
	}
	if(!Drop)
	{	DrawGraph(x1, y1, Colours[c1], TRUE);	DrawGraph(x2, y2, Colours[c2], TRUE);	}
	else
	{
		for (int x = 0; x < MAP_X; x++)
		{
			for (int y = 0; y < MAP_Y; y++)
			{
				int no = Search_MapData[y * MAP_X + x];
				int Dx = (x + 1) * CHIPSIZE;
				float Dy = (y + 1) * CHIPSIZE + Time;
				int D = drops[y][x] - 1;
				if (D < 6 && D >= 0) DrawGraph(Dx, Dy, Colours[D], TRUE);
			}
		}
	}
}

void HitSet(int x, float y, int c)
{
	int Ix = x / CHIPSIZE -1;	
	int Iy = y / CHIPSIZE -1; 
	Search_MapData[Iy * MAP_X + Ix] = c;
}
void DropSearch()
{
	Time = 0;
	DropCount = 0;
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			DropSet(x, y);	
		}
	}
	if (DropCount != 0)	{Drop = true; }
	if (DropCount == 0)	{Drop = false; }
	ReMove = false;
	Search_chengeMap();
}

void DropSet(int x, int y)
{
	if (y >= 0) 
	{
		int A = y * MAP_X + x;
		int a = Search_MapData[A];
		if (a < 8) 
		{			
			if (Search_MapData[A + MAP_X] == 9)
			{
				Search_MapData[A] = 9;
				drops[y][x] = a + 1;
				DropSet(x, y - 1);
				DropCount++;
			}		
		}
	}
}
void DropMove()
{
	Time += 2;
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			int c = drops[y][x];
			if(c != 0)
			{
				int Dc = c - 1, Dx = (x + 1) * CHIPSIZE;
				float Dy = Time + (y + 1) * CHIPSIZE;
				if(MAP_HitCheck(Dx, Dy, false))
				{
					DropCount--;
					HitSet(Dx, Dy, Dc);
					drops[y][x] = 0;
					Search_chengeMap();
				}
				if (DropCount == 0) { Drop = false; Time = 0;}
			}
		}
	}
}

// 自分に隣接している同色の数を調べる
// x：現在のx座標 , y：現在のy座標 , n：数
void Count(int x, int y, int n)
{
	if (n == 4)Erase = true;

	int A = y * MAP_X + x;
	int c = Search_MapData[A];     //自分の色を記憶
	if (c < 8)
	{
		No[y][x] = n;
		Search_MapData[A] = 9; //一旦色を消して反応しないようにする
		if (Search_MapData[A + 1]  == c && x + 1 < MAP_X - 1) { n++; Count(x + 1, y, n); }
		if (Search_MapData[A + MAP_X] == c && y + 1 < MAP_Y - 1) { n++; Count(x, y + 1, n); }
		if (Search_MapData[A - 1]  == c && x - 1 > 0) { n++; Count(x - 1, y, n); }
		if (Search_MapData[A - MAP_X] == c && y - 1 > 0) { n++; Count(x, y - 1, n); }
		Search_MapData[A] = c; //元に戻す
	}
}
// 自分に隣接している同色を消す
void Des(int x, int y)
{
	int A = y * MAP_X + x;
	int c = Search_MapData[A];

	Search_MapData[A] = 9;
	if (Search_MapData[A + 1] == c && x + 1 < MAP_X) Des(x + 1, y);
	if (Search_MapData[A + MAP_X]== c && y + 1< MAP_Y) Des(x, y + 1);
	if (Search_MapData[A - 1] == c && x > 0) Des(x - 1, y);
	if (Search_MapData[A - MAP_X]== c && y > 0) Des(x, y - 1);
	No[y][x] = 0;
}
void Search()
{
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{			
			int a = No[y][x];
			Count(x, y, 1);
			if (Erase)//4つ以上隣接している
			{	
			Des(x, y);
			Drop = true;//消去
			Erase = false;	
			}
		}
	}
	ReMove = true;
}
