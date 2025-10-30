#include "GameBasic.h"

//���ء���ʼ�˵���
GameState LoadBeginMenu() {

	//����ר������
	IMAGE img_BeginPhoto;

	//����ר������
	loadimage(&img_BeginPhoto, "asset\\image\\BeginPhoto.jpg");

	//����ר������
	putimage(0, 0, &img_BeginPhoto);

	//������в���
	int spaceW = (BK_WIDTH - BT_WIDTH) / 2;
	int spaceH = (BK_HEIGHT - BT_HEIGHT) / 2;
	int spaceS = BK_HEIGHT / 4;
	int spaceE = BK_HEIGHT / 4 + BT_HEIGHT + 5;

	//���ƿ�ʼ��ť
	Button begin(spaceW, spaceH + spaceS - 5, BT_WIDTH, BT_HEIGHT, "��ʼ��Ϸ");
	begin.DrawButton();

	//���ƽ�����ť
	Button end(spaceW, spaceH + spaceE, BT_WIDTH, BT_HEIGHT, "�˳���Ϸ");
	end.DrawButton();

	//������������Ϣ
	settextstyle(20, 0, "����");
	settextcolor(RGB(88, 88, 88));
	outtextxy(5, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, COPYRIGHT.c_str());

	//���������
	FlushBatchDraw();

	//�����¼����
	return HandleBeginMenu(begin, end);
}

//������ʼ�˵���
GameState HandleBeginMenu(Button begin, Button end) {

	//�����¼���Ϣ����
	ExMessage msg = { 0 };

	//��ȡ�����Ϣ
	while (true) {
		if (peekmessage(&msg, EX_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				if (begin.CheckClick(msg.x, msg.y)) {
					cerr << "��ʼ��Ϸ" << endl;
					begin.PlayAudio();
					Sleep(250);
					return GAME_SELECT;
				}
				if (end.CheckClick(msg.x, msg.y)) {
					cerr << "�˳���Ϸ" << endl;
					end.PlayAudio();
					Sleep(350);
					return PROGRAM_OVER;
				}
			}
		}
		Sleep(10);
	}

	//���뱣��
	return BEGIN_MENU;
}