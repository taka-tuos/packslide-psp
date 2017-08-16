#include "libpuyo.h"

// �S�u���b�N�̓��F�ŗאڂ��Ă�������`�F�b�N����
int Check(struct FIELD* pField)
{
	int nX = 0;
	int nY = 0;
	int nReturn = 0;
	struct FIELD stDummy;

	for (nX = 0; nX < WIDTH; ++nX)
	{
		for (nY = 0; nY < HEIGHT; ++nY)
		{
			// �󔒁��O�Ƃ��Ă���̂ŁA�O�̏ꍇ�͉������Ȃ�
			if(pField->stBlock[nX][nY].nColor == 0)
			{
				continue;
			}

			// �����t���O���N���A���Ă���
			pField->stBlock[nX][nY].nVanish = 0;

			// �t�B�[���h�\���̂��R�s�[���āA�����p�̍\���̗̈���쐬����
			memcpy(&stDummy, pField, sizeof(struct FIELD));

			// ���F�ŗאڂ��Ă�������J�E���g����
			Count(&stDummy, nX, nY, &pField->stBlock[nX][nY].nVanish);

			// ���F�ŗאڂ��Ă������VANISH�萔�𒴂��Ă�����A�߂�l���P�ɂ���
			nReturn |=(pField->stBlock[nX][nY].nVanish >= VANISH);
		}
	}

	// �P�ӏ��ł����������ӏ�������΂P�A�Ȃ���΂O���Ԃ�
	return nReturn;
}

// VANISH�萔��肽�����񓯐F�ŗאڂ��Ă������������
int Vanish(struct FIELD* pField)
{
	int nX = 0;
	int nY = 0;
	
	int en = 0;

	for (nX = 0; nX < WIDTH; ++nX)
	{
		for (nY = 0; nY < HEIGHT; ++nY)
		{
			// ���F�ł̗אڐ���VANISH�萔�ȏォ�H
			if(pField->stBlock[nX][nY].nVanish >= VANISH)
			{
				// �u���b�N�����N���A����
				memset(&pField->stBlock[nX][nY], 0, sizeof(struct BLOCK));
				en++;
			}
		}
	}
	
	return en;
}

// ��������ċ󂢂����Ԃ��P�i�����l�߂�
int Slide(struct FIELD* pField)
{
	int nX = 0;
	int nY = 0;
	int nReturn = 0;

	for (nY = HEIGHT - 1; nY >= 1; --nY)
	{
		for (nX = 0; nX < WIDTH; ++nX)
		{
			// �����ӏ����󔒂ŁA�P�オ�󔒂ł͂Ȃ��ꍇ
			if(pField->stBlock[nX][nY].nColor == 0 &&
				pField->stBlock[nX][nY - 1].nColor != 0)
			{
				// �����ӏ��ւP��̃u���b�N�����R�s�[����
				memcpy(&pField->stBlock[nX][nY], &pField->stBlock[nX][nY - 1], sizeof(struct BLOCK));

				// �P��̃u���b�N�����N���A����
				memset(&pField->stBlock[nX][nY - 1], 0, sizeof(struct BLOCK));

				// �������ӏ����������̂ŁA�߂�l���P�ɂ���
				nReturn	 = 1;
			}
		}
	}

	// �������ӏ����������ꍇ�͂P�A�����łȂ��ꍇ�͂O���Ԃ�
	return nReturn;
}

// ���F�ŗאڂ��Ă�����𐔂���i�ċA�֐��j
void Count(struct FIELD* pField, int nX, int nY, int* pCount)
{
	// �����ӏ��̐F��ێ�����
	int nColor = pField->stBlock[nX][nY].nColor;

	// �_�u���Č������Ȃ��悤�ɁA���������ӏ��̃u���b�N�����N���A���Ă���
	memset(&pField->stBlock[nX][nY], 0, sizeof(struct BLOCK));

	// �J�E���^���C���N�������g����
	++(*pCount);

	// �P��̃u���b�N������
	if(nY - 1 >= 0 && nColor == pField->stBlock[nX][nY - 1].nColor)
	{
		Count(pField, nX, nY - 1, pCount);
	}

	// �P���̃u���b�N������
	if(nY + 1 < HEIGHT && nColor == pField->stBlock[nX][nY + 1].nColor)
	{
		Count(pField, nX, nY + 1, pCount);
	}

	// �P���̃u���b�N������
	if(nX - 1 >= 0 && nColor == pField->stBlock[nX - 1][nY].nColor)
	{
		Count(pField, nX - 1, nY, pCount);
	}

	// �P�E�̃u���b�N������
	if(nX + 1 < WIDTH && nColor == pField->stBlock[nX + 1][nY].nColor)
	{
		Count(pField, nX + 1, nY, pCount);
	}
}