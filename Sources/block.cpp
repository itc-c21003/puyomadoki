#include "block.h"
#include "DxLib.h"
#include "MapData.h"
#include "Hit.h"
int Frame[3],Colours[6];//��0�A��1�A���F2�A��3�A��4�A�D�F5
int Search_MapData[MapMax];
float Time = 0; int DropCount;
int drops[MAP_Y][MAP_X];int count;
bool Drop,ReMove, Erase[MapMax], Erases;

bool GetDrop()  { return Drop; }
bool GetErase()  { return Erases; }
bool GetReMove() { return ReMove; }
void BlockInit()
{
    LoadDivGraph("�摜�f�[�^/Frame.png", 3, 3, 1, CHIPSIZE, CHIPSIZE, Frame);
    LoadDivGraph("�摜�f�[�^/Block.png", 6, 3, 2, CHIPSIZE, CHIPSIZE, Colours);
}
void SearchLoadMap()
{
	for (int i = 0; i < MapMax; i++)
	{
		Search_MapData[i] = Map_GetData(i);	
	}
}

void Search_chengeMap()
{
	for (int i = 0; i < MapMax; i++)
	{
		int c = Search_MapData[i];
		Chenge_MapData(i,c);
	}
}
//�`�揈��
void DrawMap(int c1,int c2)
{
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			int A = y * MAP_X + x;
			int no = Search_MapData[A];
			int xx = (x + 1) * CHIPSIZE;
			int yy = (y + 1) * CHIPSIZE;
			if (no != 8) DrawGraph((x + 1) * CHIPSIZE, (y + 1) * CHIPSIZE, Frame[0], FALSE);
			if (no != 9)
			{
				if (no == 8) { DrawGraph(xx, yy, Frame[1], FALSE); }
				else
				{ 
					if(!Erase[A]) DrawGraph(xx, yy, Colours[no], TRUE);
					else
					{
						int T = (Time / 10);
						if(T%2 == 0)
						{
							DrawGraph(xx, yy, Colours[no], TRUE);
						}
					}
				}
			}	
		}
	}
	int Nx = 10 * CHIPSIZE;
	int Ny =  2 * CHIPSIZE;
	int Ny1 = 3 * CHIPSIZE;
	int Ny2 = 4 * CHIPSIZE;
	DrawFormatString(Nx, Ny, GetColor(255, 255, 255), "Next");
	DrawGraph(Nx, Ny1, Colours[c2], TRUE); DrawGraph(Nx, Ny2, Colours[c1], TRUE);
}
void DarwMove(int x, float y,int c)
{
	DrawGraph(x, y, Colours[c], TRUE);
}
void DrawDrop()
{
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			float Dx = (x + 1) * CHIPSIZE;
			float Dy = (y + 1) * CHIPSIZE + Time;
			int D = drops[y][x] - 1;
			if (D < 6 && D >= 0) { DrawGraph(Dx, Dy, Colours[D], TRUE); }
		}
	}
}
//�u���b�N��z����ɉ�����
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
			DropSet(x, y);	//����������u���b�N�̔���
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
				DropSet(x, y - 1); //��ɂ���u���b�N��S�ė���������
				DropCount++;//���𐔂���
			}		
		}
	}
}
void DropMove()//��������
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
				if(MAP_HitCheck(Dx, Dy, false))//�u���b�N���������I������
				{
					DropCount--;
					HitSet(Dx, Dy, Dc);//�u���b�N��z����ɉ����Ȃ���									  
					drops[y][x] = 0;
					Search_chengeMap();//�z��̕ύX��MapDate�ɋ��L
				}
			}
		}
	}
	if (DropCount == 0) { Drop = false; Time = 0; }//�S���������I������~�߂�
}
void Search()
{
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			count = 1;
			Count(x, y);
		}
	}
	ReMove = true;
}
// �����ɗאڂ��Ă��铯�F�̐��𒲂ׂ�
// x�F���݂�x���W , y�F���݂�y���W , n�F��
void Count(int x, int y)
{
	int A = y * MAP_X + x;
	int c = Search_MapData[A];     //�����̐F���L��
	if (Erase[A])//�����I����Ă���Ȃ琔���Ȃ�
	{
		if (c < 8)
		{
			Search_MapData[A] = 9; //��U�F�������Ĕ������Ȃ��悤�ɂ���
			if (Search_MapData[A + 1] == c && x + 1 < MAP_X - 1) { count++; Count(x + 1, y); }
			if (Search_MapData[A + MAP_X] == c && y + 1 < MAP_Y - 1) { count++; Count(x, y + 1); }
			if (Search_MapData[A - 1] == c && x - 1 > 0) { count++; Count(x - 1, y); }
			if (Search_MapData[A - MAP_X] == c && y - 1 > 0) { count++; Count(x, y - 1); }
			Search_MapData[A] = c; //���ɖ߂�
		}
		if (count >= 4)
		{
			Erase[A] = true;
			if (!Erases)Erases = true;
		}
	}
}
// �����ɗאڂ��Ă��铯�F������
void Des()
{
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			int a = y * MAP_X + x;
			if (Erase[a])//4�ȏ�אڂ��Ă���
			{
				Search_MapData[a] = 9;	
				Erase[a] = false;
				if (!Drop)Drop = true;//����
			}
		}
	}
	Erases = false;
	Time = 0;
}
void Deadcount()
{
	Time++;
	if (Time > 90)Des();
}

