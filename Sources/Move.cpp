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
//�u���b�N����
void RandomBlock()
{	
	if (S) { R[2] = GetRand(4); R[3] = GetRand(4); S = false; }//�X�^�[�g���̓u���b�N��\�����Ă��Ȃ�����
	//�ʒu���̃��Z�b�g
	ScondX = 0, ScondY = -CHIPSIZE;
	X1 = CHIPSIZE * 5, X2 = X1;
	Y1 = CHIPSIZE, Y2 = Y1 + ScondY;
	drop = false; Inversion = false;
	//�\�����Ă����u���b�N�𗎉�������
	R[0] = R[2];  R[1] = R[3];
	//�����_���ȃu���b�N��\��
	R[2] = GetRand(4); R[3] = GetRand(4);
	if (MoveMap[4] != 9) { Over(); S = true; }//�o������ʒu�Ƀu���b�N������Ȃ�Q�[���I�[�o�[
}
void MoveLoadMap()
{
	for (int i = 0; i < MapMax; i++)
	{	MoveMap[i] = Map_GetData(i);}
}
//�u���b�N�̈ړ�����
void Move()
{
	int drop = false;
	DownTime++;
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
	{
		if (!move)
		{
			move = true; //�������Ŕ������Ȃ�
			int x = X1 + 1,x2 = X2 + 1;
			//�ǂ�ق��̂Ղ悪�i�s�����ɂ���Ȃ�ړ����Ȃ�
			if (!MAP_HitCheck(x, Y1, true) && !MAP_HitCheck(x2, Y2, true))
			{	
				if (X1 < MAP_X * CHIPSIZE) { X1 += CHIPSIZE;	X2 = X1 + ScondX; }//�͈͊O�Ɉړ����Ȃ�
			}
		}
	}
	else if (CheckHitKey(KEY_INPUT_LEFT) != 0)
	{
		if (!move)
		{
			move = true; //�������Ŕ������Ȃ�
			int x = X1 - 1, x2 = X2 - 1;
			if (!MAP_HitCheck(x,Y1,true) && !MAP_HitCheck(x2, Y2, true))	//�ǂ�ق��̂Ղ悪�i�s�����ɂ���Ȃ�ړ����Ȃ�
			{
				if (X1 - CHIPSIZE > 0) { X1 -= CHIPSIZE; X2 = X1 + ScondX; }//�͈͊O�Ɉړ����Ȃ�
			}
		}	
	}
	else
	{	move = false;	}
	if(CheckHitKey(KEY_INPUT_DOWN)){ Y1 += G; }
	Y1 += G; //����������
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
			//���v����90�x��]
			if (Inversion) { ScondX = y; ScondY = x; }
			else { ScondX = -y; ScondY = -x; }
			X2 = X1 + ScondX; Y2 = Y1 + ScondY;
			//��]�������ʏd�Ȃ���
			if (MAP_HitCheck(X2, Y2, true))
			{
				if (!Inversion)//�ׂ̃u���b�N��ǂɏd�Ȃ�ꍇ
				{
					//90�x��]�ł͖����㉺�𔽓]����
					ScondX = x; ScondY = -y;
					X1 = X1 + ScondX; Y1 = Y1 - ScondY;
					X2 = X1 + ScondX; Y2 = Y1 + ScondY;
				}
			}
			//�d�Ȃ�Ȃ�����
			else 
			{  Inversion = !Inversion; }//��true�@�cfalse
		}
	}
}