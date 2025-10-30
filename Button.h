#pragma once
#include <easyx.h>
#include <string>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

//��ť�ṹ����
class Button {
public:

	//��ť���췽��
	Button(int x, int y, int width, int height, string text);

	//���ư�ťͼ��
	void DrawButton();

	//��ⰴť���
	bool CheckClick(int mouseX, int mouseY);

	//���Ű�ť��Ч
	void PlayAudio();

private:

	//��ťx����
	int bt_x;

	//��ťy����
	int bt_y;

	//��ť���
	int bt_width;

	//��ť�߶�
	int bt_height;

	//��ť�ı�
	string bt_text;
};