#include "Level.h"
#include "GameBasic.h"

//�ؿ����췽��
Level::Level(int x, int y, int width, int height, string name, int difficulty) :lv_x(x), lv_y(y), lv_width(width), lv_height(height), lv_name(name), lv_difficulty(difficulty) {}

//���ƹؿ�ͼ��
void Level::DrawLevel() {

	//���������ɫ
	setfillcolor(RGB(136, 171, 218));

	//����������ɫ
	setlinecolor(YELLOW);

	//����Բ�Ǿ���ͼ��
	fillroundrect(lv_x, lv_y, lv_x + lv_width, lv_y + lv_height, 10, 10);

	//�ָ�ȫ��������ɫ
	SetLineColor();

	//����������ɫ
	settextcolor(RGB(109, 106, 117));
	settextcolor(WHITE);

	//����������ʽ
	settextstyle(20, 10, "����");

	//���ƾ����ı�
	int spaceW = (lv_width - textwidth(lv_name.c_str())) / 2;
	int spaceH = (lv_height - textheight(lv_name.c_str())) / 2;
	outtextxy(lv_x + spaceW, lv_y + spaceH - 20, lv_name.c_str());

	//���ƹؿ��Ѷ�
	int starX = lv_x + (lv_width - textwidth("ռλ��")) / 2;
	int starY = lv_y + spaceH + 20;
	for (int i = 0; i < 5; i++, starX += 15) {
		if (i < lv_difficulty) {	
			setfillcolor(RGB(255, 217, 0));
		}
		else {
			setfillcolor(WHITE);
		}
		fillcircle(starX, starY, 5);
	}
}

//���ؿ����
bool Level::CheckClick(int mouseX, int mouseY) {

	//�ж�������Ч��
	if (lv_x <= mouseX && mouseX <= lv_x + lv_width && lv_y <= mouseY && mouseY <= lv_y + lv_height) {
		return true;
	}
	else {
		return false;
	}
}

//���Źؿ���Ч
void Level::PlayAudio() {
	PlaySound("asset\\sound\\PutDown.wav", NULL, SND_ASYNC | SND_FILENAME);
}