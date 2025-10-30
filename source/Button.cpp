#include "Button.h"
#include "GameBasic.h"

//��ť���췽��
Button::Button(int x, int y, int width, int height, string text) :bt_x(x), bt_y(y), bt_width(width), bt_height(height), bt_text(text) {}

//���ư�ťͼ��
void Button::DrawButton() {

	//���������ɫ
	setfillcolor(RGB(136, 171, 218));

	//����������ɫ
	setlinecolor(YELLOW);

	//���ƾ���ͼ��
	fillrectangle(bt_x, bt_y, bt_x + bt_width, bt_y + bt_height);

	//�ָ�ȫ��������ɫ
	SetLineColor();

	//����������ɫ
	settextcolor(WHITE);

	//����������ʽ
	settextstyle(20, 10, "����");

	//���ƾ����ı�
	int spaceW = (bt_width - textwidth(bt_text.c_str())) / 2;
	int spaceH = (bt_height - textheight(bt_text.c_str())) / 2;
	outtextxy(bt_x + spaceW, bt_y + spaceH, bt_text.c_str());
}

//��ⰴť���
bool Button::CheckClick(int mouseX, int mouseY) {

	//�ж�������Ч��
	if (bt_x <= mouseX && mouseX <= bt_x + bt_width && bt_y <= mouseY && mouseY <= bt_y + bt_height) {
		return true;
	}
	else {
		return false;
	}
}

//���Ű�ť��Ч
void Button::PlayAudio() {
	PlaySound("asset\\sound\\PutDown.wav", NULL, SND_ASYNC | SND_FILENAME);
}