#include "GameBasic.h"

//���ر��
static bool BACK = false;

//��ʼ�������
static int _01X = 185;
static int _01Y = 185;
static int _02X = 185;
static int _02Y = 185;

//��һغϿ���
static int Player = 1;

//��Ϸ�վ��ж�
static bool GameContinue = true;

//��Ϸ�����ж�
static int chessSum = 0;

//����ά������
static vector<vector<int>> Board(15, vector<int>(15, 0));

//�������ٶ�λ
static int GetIndexX(int x) { return (x - 45) / 20; }
static int GetIndexY(int y) { return (y - 45) / 20; }

//����������Ч
static void PlayAudio() { PlaySound("asset\\sound\\PutChess.wav", NULL, SND_ASYNC | SND_FILENAME); }

//=== ��Ϸ_01 ���ӹ���ʵ�� ===//
static void DropChess(int dropX, int dropY, string color);

//=== ��Ϸ_01 ��궨λʵ�� ===//
static void CursorPosition(int cursorX, int cursorY, string color);

//=== ��Ϸ_01 ���ӻغ�ʵ�� ===//
static void BlackBout();

//=== ��Ϸ_01 ���ӻغ�ʵ�� ===//
static void WhiteBout();

//=== ��Ϸ_01 �վ��ж�ʵ�� ===//
static bool EndJudgment();

//=== ��Ϸ_01 ����ҳ��ʵ�� ===//
static void Settlement(int winner);

//���ء���Ϸ_01��
GameState LoadGameFirst() {

	//����ͨ�ñ���
	SetBackGround();

	//�������̵װ�
	setfillcolor(RGB(209, 209, 209));
	fillroundrect(30, 30, 340, 340, 10, 10);

	//�����������
	setfillcolor(RGB(228, 220, 228));
	for (int H = 45; H <= 325; H += 20) {
		for (int W = 45; W <= 325; W += 20) {
			fillcircle(H, W, 5);
		}
	}

	//���Ƽ�λ��ʾ
	settextstyle(20, 0, "����");
	SetTextBlue();
	outtextxy(GUIDEOFFSET, 50, "����  W A S D ��F");
	SetTextPink();
	outtextxy(GUIDEOFFSET, 80, "�죺�������� ���س�");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 140, "��Ϸ����");
	outtextxy(GUIDEOFFSET, 170, "   �ᡢ����б��һ��");
	outtextxy(GUIDEOFFSET, 200, "����������������ʤ");
	outtextxy(GUIDEOFFSET, 230, "����˳��Ϊִ������");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 290, "��ǰ�غϣ�");

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
	return HandleGameFirst();
}

//������Ϸ_01��
GameState HandleGameFirst() {

	//�ڰ׶���ѭ��
	while (GameContinue) {

		//���ӻغ�ʵ��
		BlackBout();
		if (BACK)break;

		//�վּ��
		GameContinue = EndJudgment();
		if (!GameContinue) break;

		//���ӻغ�ʵ��
		WhiteBout();
		if (BACK)break;

		//�վּ��
		GameContinue = EndJudgment();
		if (!GameContinue) break;
	}

	//������Ϸ����
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			Board[i][j] = 0;
		}
	}
	GameContinue = true;
	chessSum = 0;
	Player = 1;
	_01X = 185;
	_01Y = 185;
	_02X = 185;
	_02Y = 185;

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

//=== ��Ϸ_01 ���ӹ���ʵ�� ===//
void DropChess(int dropX, int dropY, string color) {

	//����������ɫ
	if (color == "BLACK") {
		SetFillBlue();
		SetLineBlue();
	}
	if (color == "WHITE") {
		SetFillPink();
		SetLinePink();
	}

	//��������
	fillcircle(dropX, dropY, 7);

	//�ָ�ȫ��������ɫ
	SetLineColor();

	//����������Ч
	PlayAudio();
	Sleep(100);
}

//=== ��Ϸ_01 ��궨λʵ�� ===//
void CursorPosition(int cursorX, int cursorY, string color) {

	//���ù����ɫ
	if (color == "BLACK") {
		SetLineBlue();
	}
	if (color == "WHITE") {
		SetLinePink();
	}
	if (color == "Grey") {
		setlinecolor(RGB(209, 209, 209));
	}

	//���ƹ��
	circle(cursorX, cursorY, 9);

	//�ָ�ȫ��������ɫ
	SetLineColor();
}

//=== ��Ϸ_01 ���ӻغ�ʵ�� ===//
void BlackBout() {

	//���ƻغ���ʾ
	SetFillBlue();
	fillcircle(505, 300, 15);

	//�����¼���Ϣ����
	ExMessage msg = { 0 };

	//��ȡ�������Ϣ
	while (Player == 1) {
		if (peekmessage(&msg, EX_KEY)) {
			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {

					//W������
				case 'W':
					if (_01Y - 20 >= 45) {
						CursorPosition(_01X, _01Y, "Grey");
						_01Y -= 20;
						CursorPosition(_01X, _01Y, "BLACK");
					}
					cout << "W DOWN" << endl;
					break;

					//S������
				case 'S':
					if (_01Y + 20 <= 325) {
						CursorPosition(_01X, _01Y, "Grey");
						_01Y += 20;
						CursorPosition(_01X, _01Y, "BLACK");
					}
					cout << "S DOWN" << endl;
					break;

					//A������
				case 'A':
					if (_01X - 20 >= 45) {
						CursorPosition(_01X, _01Y, "Grey");
						_01X -= 20;
						CursorPosition(_01X, _01Y, "BLACK");
					}
					cout << "A DOWN" << endl;
					break;

					//D������
				case 'D':
					if (_01X + 20 <= 325) {
						CursorPosition(_01X, _01Y, "Grey");
						_01X += 20;
						CursorPosition(_01X, _01Y, "BLACK");
					}
					cout << "D DOWN" << endl;
					break;

					//F������
				case 'F':
					if (Board[GetIndexX(_01X)][GetIndexY(_01Y)] == 0) {
						DropChess(_01X, _01Y, "BLACK");
						Player = 2;
						Board[GetIndexX(_01X)][GetIndexY(_01Y)] = 1;
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

//=== ��Ϸ_01 ���ӻغ�ʵ�� ===//
void WhiteBout() {

	//���ƻغ���ʾ
	SetFillPink();
	fillcircle(505, 300, 15);

	//�����¼���Ϣ����
	ExMessage msg = { 0 };

	//��ȡ�Ҽ�����Ϣ
	while (Player == 2) {
		if (peekmessage(&msg, EX_KEY)) {
			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {

					//�ϼ�����
				case VK_UP:
					if (_02Y - 20 >= 45) {
						CursorPosition(_02X, _02Y, "Grey");
						_02Y -= 20;
						CursorPosition(_02X, _02Y, "WHITE");
					}
					cout << "UP DOWN" << endl;
					break;

					//�¼�����
				case VK_DOWN:
					if (_02Y + 20 <= 325) {
						CursorPosition(_02X, _02Y, "Grey");
						_02Y += 20;
						CursorPosition(_02X, _02Y, "WHITE");
					}
					cout << "DOWN DOWN" << endl;
					break;

					//�������
				case VK_LEFT:
					if (_02X - 20 >= 45) {
						CursorPosition(_02X, _02Y, "Grey");
						_02X -= 20;
						CursorPosition(_02X, _02Y, "WHITE");
					}
					cout << "LEFT DOWN" << endl;
					break;

					//�Ҽ�����
				case VK_RIGHT:
					if (_02X + 20 <= 325) {
						CursorPosition(_02X, _02Y, "Grey");
						_02X += 20;
						CursorPosition(_02X, _02Y, "WHITE");
					}
					cout << "RIGHT DOWN" << endl;
					break;

					//�س�������
				case VK_RETURN:
					if (Board[GetIndexX(_02X)][GetIndexY(_02Y)] == 0) {
						DropChess(_02X, _02Y, "WHITE");
						Player = 1;
						Board[GetIndexX(_02X)][GetIndexY(_02Y)] = 2;
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

	while (right <= 14 && Board[X][right] == Board[X][Y]) {
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

	while (down <= 14 && Board[down][Y] == Board[X][Y]) {
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
	while (x <= 14 && y <= 14 && Board[x][y] == Board[X][Y]) {
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
	while (x <= 14 && y >= 0 && Board[x][y] == Board[X][Y]) {
		count++;
		x++;
		y--;
	}

	//���ҶԽ�����̽��
	x = X;
	y = Y;
	while (x >= 0 && y <= 14 && Board[x][y] == Board[X][Y]) {
		count++;
		x--;
		y++;
	}

	//�����ҶԽ�������
	return count;
}

//=== ��Ϸ_01 �վ��ж�ʵ�� ===//
bool EndJudgment() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Board[i][j] != 0) {
				if (Tool1(i, j) >= 5 || Tool2(i, j) >= 5 || Tool3(i, j) >= 5 || Tool4(i, j) >= 5) {
					Settlement(Board[i][j]);
					cerr << "���ڷ�������ѭ��" << endl;
					return false;
				}
				if (chessSum == 225) {
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

//=== ��Ϸ_01 ����ҳ��ʵ�� ===//
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