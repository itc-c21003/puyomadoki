#include "Hit.h"
#include "MapData.h"

int CheckHit(float Mx, float My, float SIZE, float PLx, float PLy)
{
	float L1 = Mx;      // Map��
	float R1 = Mx + SIZE;  // Map�E(��+����)
	float L2 = PLx;       // PL��
	float R2 = PLx + SIZE; // PL�E(��+����)

	if (R1 <= L2) return 0; //< �����������Ȃ����Ƃɂ���
	if (R2 <= L1) return 0; //< �����������Ȃ����Ƃɂ���

	float U1 = My;      // Map��
	float D1 = My + SIZE;  // Map��(��+�c��)
	float U2 = PLy;       // PL��
	float D2 = PLy + SIZE; // PL��(��+�c��)

	if (D1 <= U2) return 0; //< �����������Ȃ����Ƃɂ���
	if (D2 <= U1) return 0; //< �����������Ȃ����Ƃɂ���

	// ����ȊO�̏ꍇ�͓������Ă���
	return 1;
}
//============================================================
// �n�`�̓����蔻��̏���
bool MAP_HitCheck(int x, float& y, bool Move)
{
	bool on_ground = false;
	// �u���b�N�̓����蔻��
	for (int j = 0; j <= MAP_Y; j++)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			int no = Map_GetData(j * MAP_X + i);
			//�w�i����Ȃ����`�F�b�N
			if (no != 9)
			{
				// �����蔻�菈��
				if (CheckHit((i + 1) * CHIPSIZE, (j + 1) * CHIPSIZE, CHIPSIZE, x, y))
				{
					//���E�̈ړ�����
					if (Move) { on_ground = true; }
					// �ォ�瓖�����Ă��邩�`�F�b�N
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