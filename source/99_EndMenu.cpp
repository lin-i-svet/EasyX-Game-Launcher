#include "GameBasic.h"

//���ء������˵���
GameState LoadEndMenu() {

	//�����������
	IMAGE img_EndPhoto;

	//���ؽ�������
	loadimage(&img_EndPhoto, "asset\\image\\BackGround.jpg");

	//�����������
	putimage(0, 0, &img_EndPhoto);

	//������в���
	int spaceW = (BK_WIDTH - BT_WIDTH) / 2;
	int spaceH = (BK_HEIGHT - BT_HEIGHT) / 2;
	int spaceS = BK_HEIGHT / 4;
	int spaceE = BK_HEIGHT / 4 + BT_HEIGHT + 5;

	//���Ʒ��ذ�ť
	Button back(spaceW, spaceH + spaceE, BT_WIDTH, BT_HEIGHT, "������ҳ");
	back.DrawButton();

	//������������Ϣ
	settextstyle(20, 0, "����");
	settextcolor(RGB(88, 88, 88));
	outtextxy(5, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, COPYRIGHT.c_str());

	//���������
	FlushBatchDraw();

	//�����¼����
	return HandleEndMenu(back);
}

//���������˵���
GameState HandleEndMenu(Button back) {

	//�����¼���Ϣ����
	ExMessage msg = { 0 };

	//��ȡ�����Ϣ
	while (true) {
		if (peekmessage(&msg, EX_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				if (back.CheckClick(msg.x, msg.y)) {
					cerr << "������ҳ" << endl;
					back.PlayAudio();
					Sleep(250);
					return BEGIN_MENU;
				}
			}
		}
		Sleep(10);
	}

	//���뱣��
	return END_MENU;
}