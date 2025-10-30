#include "GameBasic.h"

//���ء���Ϸѡ��
GameState LoadGameSelect() {

	//������Ϸ����
	vector<Level> gameArray;
	gameArray.push_back({ 5 + 15 * 1 + LV_WIDTH * 0, 15, 100, 100, "������", 3 });
	gameArray.push_back({ 5 + 15 * 2 + LV_WIDTH * 1,15,100,100,"������",2 });
	gameArray.push_back({ 5 + 15 * 3 + LV_WIDTH * 2,15,100,100,"������",4 });
	gameArray.push_back({ 5 + 15 * 4 + LV_WIDTH * 3,15,100,100,"�����ڴ�",0 });
	gameArray.push_back({ 5 + 15 * 5 + LV_WIDTH * 4,15,100,100,"�����ڴ�",0 });

	//����ͨ�ñ���
	SetBackGround();

	//������Ϸ����
	for (auto x : gameArray) {
		x.DrawLevel();
	}

	//������������Ϣ
	settextstyle(20, 0, "����");
	settextcolor(RGB(88, 88, 88));
	outtextxy(5, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, COPYRIGHT.c_str());

	//���Ʒ�����ʾ
	settextstyle(20, 0, "����");
	settextcolor(BLACK);
	outtextxy(520, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, "ESC����");

	//���������
	FlushBatchDraw();

	//�����¼����
	return HandleGameSelect(gameArray);
}

//������Ϸѡ��
GameState HandleGameSelect(vector<Level> gameArray) {

	//�����¼���Ϣ����
	ExMessage msg = { 0 };

	//��ȡ���ͼ�����Ϣ
	while (true) {
		if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
			switch (msg.message) {

				//����ESC����
			case WM_KEYDOWN:
				if (msg.vkcode == VK_ESCAPE) {
					return BEGIN_MENU;
				}

				//����������
			case WM_LBUTTONDOWN:
				if (gameArray[0].CheckClick(msg.x, msg.y)) {
					cerr << "��Ϸ_01" << endl;
					gameArray[0].PlayAudio();
					Sleep(250);
					return GAME_FIRST;
				}
				if (gameArray[1].CheckClick(msg.x, msg.y)) {
					cerr << "��Ϸ_02" << endl;
					gameArray[1].PlayAudio();
					Sleep(250);
					return GAME_SECOND;
				}
				if (gameArray[2].CheckClick(msg.x, msg.y)) {
					cerr << "��Ϸ_03" << endl;
					gameArray[2].PlayAudio();
					Sleep(250);
					return GAME_THIRD;
				}
			}
		}

		//�����ӳٱ���
		Sleep(10);
	}

	//���뱣��
	return GAME_SELECT;
}