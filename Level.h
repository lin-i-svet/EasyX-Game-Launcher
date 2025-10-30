#pragma once
#include <easyx.h>
#include <string>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

//�ؿ��ṹ����
class Level {
public:

	//�ؿ����췽��
	Level(int x, int y, int width, int  height, string name, int difficulty);

	//���ƹؿ�ͼ��
	void DrawLevel();

	//���ؿ����
	bool CheckClick(int mouseX, int mouseY);

	//���Źؿ���Ч
	void PlayAudio();

private:

	//�ؿ�x����
	int lv_x;

	//�ؿ�y����
	int lv_y;

	//�ؿ����
	int lv_width;

	//�ؿ��߶�
	int lv_height;

	//�ؿ�����
	string lv_name;

	//�ؿ��Ѷ�
	int lv_difficulty;

};
