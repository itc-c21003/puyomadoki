#include "DxLib.h"
#include "Start.h"
bool Main = false; int StringCount = 0;
const int Size = 32;
//�X�^�[�g��ʂ̏���
void Start()
{
	ClearDrawScreen();
	if (CheckHitKey(KEY_INPUT_SPACE) != 0)Main = true;
	StringCount++; if (StringCount > 240)StringCount = 0;
	if (StringCount < 120)DrawString(64, Size * 4, "�X�y�[�X�L�[�������ăX�^�[�g", GetColor(255, 255, 255));
	DrawString(64, Size * 6, "����", GetColor(255, 255, 255));
	DrawString(64, Size * 7, "�\���L�[���ňړ�", GetColor(255, 255, 255));
	DrawString(64, Size * 8, "�\���L�[���ŉ���", GetColor(255, 255, 255));
	DrawString(64, Size * 9, "�X�y�[�X�L�[�ŉ�]", GetColor(255, 255, 255));
	DrawString(64, Size *10, "�G�X�P�[�v�L�[�����ďI��", GetColor(255, 255, 255));
	ScreenFlip();
}
//�X�^�[�g��ʂɖ߂�
void Over()
{
	Main = false;
}
//�V�[���̏�Ԃ��擾
bool GetMain()
{
	return Main;
}