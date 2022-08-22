#include "Hit.h"
#include "MapData.h"

int CheckHit(float Mx, float My, float SIZE, float PLx, float PLy)
{
	float L1 = Mx;      // Map左
	float R1 = Mx + SIZE;  // Map右(左+横幅)
	float L2 = PLx;       // PL左
	float R2 = PLx + SIZE; // PL右(左+横幅)

	if (R1 <= L2) return 0; //< 線上も当たらないことにする
	if (R2 <= L1) return 0; //< 線上も当たらないことにする

	float U1 = My;      // Map上
	float D1 = My + SIZE;  // Map下(上+縦幅)
	float U2 = PLy;       // PL上
	float D2 = PLy + SIZE; // PL下(上+縦幅)

	if (D1 <= U2) return 0; //< 線上も当たらないことにする
	if (D2 <= U1) return 0; //< 線上も当たらないことにする

	// それ以外の場合は当たっている
	return 1;
}
//============================================================
// 地形の当たり判定の処理
bool MAP_HitCheck(int x, float& y, bool Move)
{
	bool on_ground = false;
	// ブロックの当たり判定
	for (int j = 0; j <= MAP_Y; j++)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			int no = Map_GetData(j * MAP_X + i);
			//背景じゃないかチェック
			if (no != 9)
			{
				// 当たり判定処理
				if (CheckHit((i + 1) * CHIPSIZE, (j + 1) * CHIPSIZE, CHIPSIZE, x, y))
				{
					//左右の移動中か
					if (Move) { on_ground = true; }
					// 上から当たっているかチェック
					else if ((j + 1) * CHIPSIZE >= y)
					{
						if (j != 0)
						{
							on_ground = true;
						}
					}
				}
			}
		}
	}
	return on_ground;
}