#include"DxLib.h"
#include"block.h"
#include"MapData.h"
#include"Move.h"
#include"Hit.h"
#include "Start.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//�Ղ�Ղ惂�h�L����肽��

	// Windows���[�h�ɂ���
	ChangeWindowMode(TRUE);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(480, 480, 32);
	
	// DX���C�u����������
	if (DxLib_Init() == -1)
	{	//�������Ɏ��s����
		return -1;	       }
	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);	
	BlockInit();
	//------------------------------------------------------
    // ���C�����[�v����
	while (ProcessMessage() == 0)
	{
		bool Main = GetMain();
		if (!Main) 
		{
			while (!Main)//�X�^�[�g���
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
		//����ʂ�����
		ClearDrawScreen();
		//�ړ�����
		Move();
		Spin();
		//���W�擾
		int x1 = GetX();	
		int x2 = GetX2();
		float y1 = GetY();
		float y2 = GetY2();
		int C1 = GetCl1();
		int C2 = GetCl2();
		int Nc1 = GetNext1();
		int Nc2 = GetNext2();
		//�`��
		DrawMap(Nc1,Nc2);
		DarwMove(x1, y1, C1);
		DarwMove(x2, y2, C2);
		//����ʂ�\��ʂ����ւ���
		ScreenFlip();
		if (MAP_HitCheck(x1, y1, false) || MAP_HitCheck(x2, y2, false))
		{
			SearchLoadMap();
			HitSet(x1, y1, C1);
			HitSet(x2, y2, C2);
			DropSearch();
			while (1)
			{
				//����ʂ�����
				ClearDrawScreen();
				//�����Ă�u���b�N�̗�������
				DropMove();
				//�`��
				DrawMap(Nc1, Nc2);
				DrawDrop();
				//����ʂ�\��ʂ����ւ���
				ScreenFlip(); 
				if (!GetDrop())//��������
				{
					while (!GetReMove())
					{
						//����ʂ�����
						ClearDrawScreen();
						//�u���b�N�̏���
						Search();
						while (GetErase())
						{
							//����ʂ�����
							ClearDrawScreen();
							Deadcount();
							//�`��
							DrawMap(Nc1, Nc2);
							//����ʂ�\��ʂ����ւ���
							ScreenFlip();
							if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
						}
						//�`��
						DrawMap(Nc1, Nc2);
						//����ʂ�\��ʂ����ւ���
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
		//ESC�L�[�������ďI��
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	//======================================================
	// DX���C�u�����I���ƃv���O�����I��
	DxLib_End();
	return 0;
}