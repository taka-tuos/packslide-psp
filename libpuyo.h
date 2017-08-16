#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef __ERASE__
#define __ERASE__

#define WIDTH	12		// �t�B�[���h��
#define HEIGHT	12		// �t�B�[���h��
#define VANISH	4		// �����ɕK�v�Ȍ�
#define COLOR	5		// �F��

// �u���b�N�Ǘ��p�\����
struct BLOCK
{
	int nColor;		   // �F
	int nVanish;	// �����t���O
};

// �t�B�[���h�Ǘ��p�\����
struct FIELD
{
	struct BLOCK stBlock[WIDTH][HEIGHT];	// �u���b�N�\���̔z��
};


int Check(struct FIELD* pField);
int Vanish(struct FIELD* pField);
int Slide(struct FIELD* pField);
void Count(struct FIELD* pField, int nX, int nY, int* pCount);

#endif
