#include "MapData.h"
#include "DxLib.h"

int Data[MapMax]
{
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 9, 9, 9, 9, 9, 9, 8,
8, 8, 8, 8, 8, 8, 8, 8,
};
int MapData[MapMax];
void ResetMap()
{
	for (int i = 0; i < MapMax; i++)
	{	MapData[i] = Data[i];}
}
int Map_GetData(int i)
{
	// �}�b�v�͈̔͊O���m�F
	if (i < 0 || i >= MapMax)	return 0;

	int no = MapData[i];
	return no;
}
void Chenge_MapData(int i,int c)
{	MapData[i] = c;}