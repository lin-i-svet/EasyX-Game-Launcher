#include "GameBasic.h"

//���ر��
static bool BACK = false;

//��ʼ�������
static int X = 180;
static int Y = 40;

//��ǰ�������
static int _X;
static int _Y;

//��һغϿ���
static int Player = 1;

//��Ϸ�վ��ж�
static bool GameContinue = true;

//��Ϸ�����ж�
static int chessSum = 0;

//����ά������
static vector<vector<int>> Board(6, vector<int>(7, 0));

//�������ٶ�λ
static int GetIndexX(int h) { return (h - 90) / 40; }
static int GetIndexY(int w) { return (w - 60) / 40; }

//����������Ч
static void PlayAudio() { PlaySound("asset\\sound\\ThrowChess.wav", NULL, SND_ASYNC | SND_FILENAME); }

//=== ��Ϸ_02 ���ӹ���ʵ�� ===//
static void DropChess(int beginX, int beginY, int endX, int endY, string color);

//=== ��Ϸ_02 ��궨λʵ�� ===//
static void CursorPosition(string color);

//=== ��Ϸ_02 �췽�غ�ʵ�� ===//
static void RedBout();

//=== ��Ϸ_02 �Ʒ��غ�ʵ�� ===//
static void YellowBout();

//=== ��Ϸ_02 �վ��ж�ʵ�� ===//
static bool EndJudgment();

//=== ��Ϸ_02 ����ҳ��ʵ�� ===//
static void Settlement(int winner);

//���ء���Ϸ_02��
GameState LoadGameSecond() {

	//����ͨ�ñ���
	SetBackGround();

	//�������̵װ�
	setfillcolor(RGB(209,209,209));
	fillroundrect(35, 65, 325, 315, 30, 30);

	//�����������
	setfillcolor(RGB(228, 220, 228));
	for (int W = 60; W <= 300; W += 40) {
		for (int H = 90; H <= 290; H += 40) {
			fillcircle(W ,H, 13);
		}
	}

	//����Ԥ�����
	setlinecolor(RGB(195, 195, 195));
	setfillcolor(RGB(195, 195, 195));
	fillcircle(180, 40, 13);
	fillcircle(140, 40, 13);
	fillcircle(100, 40, 13);
	fillcircle(60, 40, 13);
	fillcircle(220, 40, 13);
	fillcircle(260, 40, 13);
	fillcircle(300, 40, 13);
	

	//�ָ�ȫ��������ɫ
	SetLineColor();

	//���Ƽ�λ��ʾ
	settextstyle(20, 0, "����");
	SetTextBlue();
	outtextxy(GUIDEOFFSET, 50, "����  A D ��F");
	SetTextPink();
	outtextxy(GUIDEOFFSET, 80, "�죺�� �� ���س�");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 140, "��Ϸ����");
	outtextxy(GUIDEOFFSET, 170, "   �ᡢ����б��һ��");
	outtextxy(GUIDEOFFSET, 200, "����������������ʤ");
	outtextxy(GUIDEOFFSET, 230, "����˳��Ϊִ������");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 290, "��ǰ�غϣ�");

	//���ƻغ���ʾ
	SetFillBlue();
	fillcircle(505, 300, 15);

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

	//�����¼�����
	return HandleGameSecond();
}

//������Ϸ_02��
GameState HandleGameSecond() {

	//��ƶ���ѭ��
	while (GameContinue) {

		//�췽�غ�ʵ��
		RedBout();
		if (BACK)break;

		//�վּ��
		GameContinue = EndJudgment();
		if (!GameContinue) break;

		//�Ʒ��غ�ʵ��
		YellowBout();
		if (BACK)break;

		//�վּ��
		GameContinue = EndJudgment();
		if (!GameContinue) break;
	}

	//������Ϸ����
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			Board[i][j] = 0;
		}
	}
	GameContinue = true;
	chessSum = 0;
	Player = 1;

	if (BACK == 0) {
		//��Ϸ����
		return END_MENU;
	}
	else {
		//������һ��
		BACK = false;
		return GAME_SELECT;
	}
}

//=== ��Ϸ_02 ���ӹ���ʵ�� ===//
void DropChess(int beginX, int beginY, int endX, int endY, string color ) {

	//����������Ч
	PlayAudio();

	//�������䶯��ѭ��
	while (true) {

		//����֡��
		Sleep(1);

		//����
		cleardevice();

		//����ͨ�ñ���
		SetBackGround();

		//�ػ����̵װ�
		setfillcolor(RGB(209, 209, 209));
		fillroundrect(35, 65, 325, 315, 30, 30);

		//�ػ��������
		for (int W = 60; W <= 300; W += 40) {
			for (int H = 90; H <= 290; H += 40) {
				
				//�������ȷ��������ɫ
				if (Board[GetIndexX(H)][GetIndexY(W)] == 0) {
					setfillcolor(RGB(228, 220, 228));
				}
				if (Board[GetIndexX(H)][GetIndexY(W)] == 1) {
					SetFillBlue();
				}
				if (Board[GetIndexX(H)][GetIndexY(W)] == 2) {
					SetFillPink();
				}
				fillcircle(W, H, 13);
			}
		}

		//����Ԥ�����
		setlinecolor(RGB(195, 195, 195));
		setfillcolor(RGB(195, 195, 195));
		fillcircle(180, 40, 13);
		fillcircle(140, 40, 13);
		fillcircle(100, 40, 13);
		fillcircle(60, 40, 13);
		fillcircle(220, 40, 13);
		fillcircle(260, 40, 13);
		fillcircle(300, 40, 13);


		//�ָ�ȫ��������ɫ
		SetLineColor();

		//���Ƽ�λ��ʾ
		settextstyle(20, 0, "����");
		SetTextBlue();
		outtextxy(GUIDEOFFSET, 50, "����  A D ��F");
		SetTextPink();
		outtextxy(GUIDEOFFSET, 80, "�죺�� �� ���س�");
		settextcolor(BLACK);
		outtextxy(GUIDEOFFSET, 140, "��Ϸ����");
		outtextxy(GUIDEOFFSET, 170, "   �ᡢ����б��һ��");
		outtextxy(GUIDEOFFSET, 200, "����������������ʤ");
		outtextxy(GUIDEOFFSET, 230, "����˳��Ϊִ������");
		settextcolor(BLACK);
		outtextxy(GUIDEOFFSET, 290, "��ǰ�غϣ�");

		//���ƻغ���ʾ
		if (color == "RED") {
			SetFillPink();
		}
		if (color == "YELLOW") {
			SetFillBlue();
		}
		fillcircle(505, 300, 15);

		//������������Ϣ
		settextstyle(20, 0, "����");
		settextcolor(RGB(88, 88, 88));
		outtextxy(5, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, COPYRIGHT.c_str());

		//���Ʒ�����ʾ
		settextstyle(20, 0, "����");
		settextcolor(BLACK);
		outtextxy(520, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, "ESC����");

		//����������ɫ
		if (color == "RED") {
			SetFillBlue();
		}
		if (color == "YELLOW") {
			SetFillPink();
		}

		//���������ٶ�
		beginY += 5;
		fillcircle(beginX, beginY, 13);

		//���������
		FlushBatchDraw();

		//�䵽Ŀ�ĵ�ֹͣ
		if (beginY == endY) {

			//������������״̬
			if (color == "RED") {
				Board[GetIndexX(endY)][GetIndexY(endX)] = 1;
			}
			if (color == "YELLOW") {
				Board[GetIndexX(endY)][GetIndexY(endX)] = 2;
			}
			
			//�˳�ѭ������
			break;
		}
	}
}

//=== ��Ϸ_02 ��궨λʵ�� ===//
void CursorPosition(string color) {
	
	//���ù����ɫ
	if (color == "RED") {
		SetFillBlue();
	}
	if (color == "YELLOW") {
		SetFillPink();
	}
	if (color == "GREY") {
		setlinecolor(RGB(195, 195, 195));
		setfillcolor(RGB(195, 195, 195));
	}

	//���ƹ��
	fillcircle(_X, _Y, 13);

	//�ָ�ȫ��������ɫ
	SetLineColor();
}

//=== ��Ϸ_02 �췽�غ�ʵ�� ===//
void RedBout() {

	//�ָ���ʼ���
	_X = X;
	_Y = Y;

	//���Ƴ�ʼ���
	CursorPosition("RED");

	//�����¼���Ϣ����
	ExMessage msg = { 0 };

	//��ȡ�������Ϣ
	while (Player == 1) {
		if (peekmessage(&msg, EX_KEY)) {
			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {

					//A������
				case 'A':
					if (_X - 40 >= 60) {
						CursorPosition("GREY");
						_X -= 40;
						CursorPosition("RED");
					}
					cout << "A DOWN" << endl;
					break;

					//D������
				case 'D':
					if (_X + 40 <= 300) {
						CursorPosition("GREY");
						_X += 40;
						CursorPosition("RED");
					}
					cout << "D DOWN" << endl;
					break;

					//F������
				case 'F':
					if (Board[5][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 290,"RED");
						Board[5][GetIndexY(_X)] == 1;
						Player = 2;
						chessSum++;
					}
					else if (Board[4][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 250, "RED");
						Board[4][GetIndexY(_X)] == 1;
						Player = 2;
						chessSum++;
					}
					else if (Board[3][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 210, "RED");
						Board[3][GetIndexY(_X)] == 1;
						Player = 2;
						chessSum++;
					}
					else if (Board[2][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 170, "RED");
						Board[2][GetIndexY(_X)] == 1;
						Player = 2;
						chessSum++;
					}
					else if (Board[1][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 130, "RED");
						Board[1][GetIndexY(_X)] == 1;
						Player = 2;
						chessSum++;
					}
					else if (Board[0][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 90, "RED");
						Board[0][GetIndexY(_X)] == 1;
						Player = 2;
						chessSum++;
					}
					cout << "F DOWN" << endl;
					break;

					//ESC����
				case VK_ESCAPE:
					BACK = true;
					Player = 3;
					break;
				}
			}
		}

		//���������
		FlushBatchDraw();

		//�����ӳٱ���
		Sleep(10);
	}
}

//=== ��Ϸ_02 �Ʒ��غ�ʵ�� ===//
void YellowBout() {

	//�ָ���ʼ���
	_X = X;
	_Y = Y;

	//���Ƴ�ʼ���
	CursorPosition("YELLOW");

	//�����¼���Ϣ����
	ExMessage msg = { 0 };

	//��ȡ�Ҽ�����Ϣ
	while (Player == 2) {
		if (peekmessage(&msg, EX_KEY)) {
			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {

					//�������
				case VK_LEFT:
					if (_X - 40 >= 60) {
						CursorPosition("GREY");
						_X -= 40;
						CursorPosition("YELLOW");
					}
					cout << "LEFT DOWN" << endl;
					break;

					//�Ҽ�����
				case VK_RIGHT:
					if (_X + 40 <= 300) {
						CursorPosition("GREY");
						_X += 40;
						CursorPosition("YELLOW");
					}
					cout << "RIGHT DOWN" << endl;
					break;

					//�س�������
				case VK_RETURN:
					if (Board[5][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 290, "YELLOW");
						Board[5][GetIndexY(_X)] == 2;
						Player = 1;
						chessSum++;
					}
					else if (Board[4][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 250, "YELLOW");
						Board[4][GetIndexY(_X)] == 2;
						Player = 1;
						chessSum++;
					}
					else if (Board[3][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 210, "YELLOW");
						Board[3][GetIndexY(_X)] == 2;
						Player = 1;
						chessSum++;
					}
					else if (Board[2][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 170, "YELLOW");
						Board[2][GetIndexY(_X)] == 2;
						Player = 1;
						chessSum++;
					}
					else if (Board[1][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 130, "YELLOW");
						Board[1][GetIndexY(_X)] == 2;
						Player = 1;
						chessSum++;
					}
					else if (Board[0][GetIndexY(_X)] == 0) {
						DropChess(_X, _Y, _X, 90, "YELLOW");
						Board[0][GetIndexY(_X)] == 2;
						Player = 1;
						chessSum++;
					}
					cout << "ENTER DOWN" << endl;
					break;

					//ESC����
				case VK_ESCAPE:
					BACK = true;
					Player = 3;
					break;
				}
			}
		}

		//���������
		FlushBatchDraw();

		//�����ӳٱ���
		Sleep(10);
	}
}

//���ߺ���1
static int Tool1(int X, int Y) {

	//ԭ������
	int count = 1;

	//����/��̽��
	int left = Y - 1;
	int right = Y + 1;

	while (left >= 0 && Board[X][left] == Board[X][Y]) {
		count++;
		left--;
	}

	while (right <= 6 && Board[X][right] == Board[X][Y]) {
		count++;
		right++;
	}

	//����ˮƽ����
	return count;
}

//���ߺ���2
static int Tool2(int X, int Y) {

	//ԭ������
	int count = 1;

	//����/��̽��
	int up = X - 1;
	int down = X + 1;

	while (up >= 0 && Board[up][Y] == Board[X][Y]) {
		count++;
		up--;
	}

	while (down <= 5 && Board[down][Y] == Board[X][Y]) {
		count++;
		down++;
	}

	//���ش�ֱ����
	return count;
}

//���ߺ���3
static int Tool3(int X, int Y) {

	//ԭ������
	int count = -1;

	//����Խ�����̽��
	int x = X;
	int y = Y;
	while (x >= 0 && y >= 0 && Board[x][y] == Board[X][Y]) {
		count++;
		x--;
		y--;
	}

	//����Խ�����̽��
	x = X;
	y = Y;
	while (x <= 5 && y <= 6 && Board[x][y] == Board[X][Y]) {
		count++;
		x++;
		y++;
	}

	//������Խ�������
	return count;
}

//���ߺ���4
static int Tool4(int X, int Y) {

	//ԭ������
	int count = -1;

	//���ҶԽ�����̽��
	int x = X;
	int y = Y;
	while (x <= 5 && y >= 0 && Board[x][y] == Board[X][Y]) {
		count++;
		x++;
		y--;
	}

	//���ҶԽ�����̽��
	x = X;
	y = Y;
	while (x >= 0 && y <= 6 && Board[x][y] == Board[X][Y]) {
		count++;
		x--;
		y++;
	}

	//�����ҶԽ�������
	return count;
}

//=== ��Ϸ_02 �վ��ж�ʵ�� ===//
bool EndJudgment() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (Board[i][j] != 0) {
				if (Tool1(i, j) >= 4 || Tool2(i, j) >= 4 || Tool3(i, j) >= 4 || Tool4(i, j) >= 4) {
					Settlement(Board[i][j]);
					cerr << "���ڷ�������ѭ��" << endl;
					return false;
				}
				if (chessSum == 42) {
					Settlement(3);
					cerr << "��������" << endl;
					return false;
				}
			}
			//���̲��ԣ�cout << Board[i][j] << " ";
		}
		//���̲��ԣ�cout << endl;
	}
	return true;
}

//=== ��Ϸ_02 ����ҳ��ʵ�� ===//
void Settlement(int winner) {

	//���ý�������
	settextstyle(40, 20, "����");

	//���ƽ�����ʾ
	if (winner == 1) {
		SetTextBlue();
		outtextxy(70, 380, "����ʤ����");
	}
	if (winner == 2) {
		SetTextPink();
		outtextxy(70, 380, "�췽ʤ����");
	}
	if (winner == 3) {
		settextcolor(YELLOW);
		outtextxy(70, 380, "˫�����壡");
	}
	settextcolor(GREEN);
	outtextxy(70, 460, "����V������ɽ���");
	FlushBatchDraw();

	//���Ž�����Ч
	PlaySound("asset\\sound\\GameOver.wav", NULL, SND_ASYNC | SND_FILENAME);

	//����V������ɽ���
	ExMessage msg = { 0 };

	while (1) {
		if (peekmessage(&msg, EX_KEY)) {
			if (msg.message == WM_KEYDOWN) {
				if (msg.vkcode == 'V') {
					cerr << "V DOWN" << endl;
					return;
				}
			}
		}
		Sleep(5);
	}
	return;
}