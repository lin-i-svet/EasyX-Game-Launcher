#include "GameBasic.h"

//���ر��
static bool BACK = false;

//�������̲���
const int radius = 12;
const int space = radius * sqrt(3.0) / 2;

//��ʼ�������
static int _01I = 5;
static int _01J = 5;
static int _02I = 5;
static int _02J = 5;

//��һغϿ���
static int Player = 1;

//��Ϸ�վ��ж�
static bool GameContinue = true;

//����ά������
static vector<vector<int>> Board(11, vector<int>(11, 0));

//�������ٶ�λ
static int GetIndexW(int i, int j) { return (35 + 2 * j * space + i * space); }
static int GetIndexH(int i, int j) { return (75 + 2 * i * space); }

//����������Ч
static void PlayAudio() { PlaySound("asset\\sound\\PutChess.wav", NULL, SND_ASYNC | SND_FILENAME); }

//=== ��Ϸ_03 ���ӹ���ʵ�� ===//
static void DropChess(int dropX, int dropY, string color);

//=== ��Ϸ_03 ��궨λʵ�� ===//
static void CursorPosition(int cursorX, int cursorY, string color);

//=== ��Ϸ_03 ���ӻغ�ʵ�� ===//
static void BlackBout();

//=== ��Ϸ_03 ���ӻغ�ʵ�� ===//
static void WhiteBout();

//=== ��Ϸ_03 ���¶�̬�滮 ===//
static bool UpDownDP();

//=== ��Ϸ_03 ���Ҷ�̬�滮 ===//
static bool LeftRightDP();

//=== ��Ϸ_03 �վ��ж�ʵ�� ===//
static bool EndJudgment();

//=== ��Ϸ_03 ����ҳ��ʵ�� ===//
static void Settlement(int winner);

//���ء���Ϸ_03��
GameState LoadGameThird() {

	//����ͨ�ñ���
	SetBackGround();

	//�������̵װ�
	int temp = 15;
	setfillcolor(RGB(209, 209, 209));
	POINT arr[] = { {35 - temp - 10,75 - temp},{35 + 20 * space + temp,75 - temp},{35 + 30 * space + temp + 10,75 + 20 * space + temp},{35 + 10 * space - temp,75 + 20 * space + temp} };
	fillpolygon(arr, 4);

	//������ɫָ��
	setlinestyle(PS_SOLID, 3);
	SetLineBlue();
	POINT black1[] = { {35 - temp - 10,75 - temp},{35 + 20 * space + temp,75 - temp} };
	POINT black2[] = { {35 + 30 * space + temp + 10,75 + 20 * space + temp},{35 + 10 * space - temp,75 + 20 * space + temp} };
	polygon(black1, 2);
	polygon(black2, 2);
	SetLinePink();
	POINT white1[] = { {35 + 20 * space + temp,75 - temp},{35 + 30 * space + temp + 10,75 + 20 * space + temp} };
	POINT white2[] = { {35 - temp - 10,75 - temp},{35 + 10 * space - temp,75 + 20 * space + temp} };
	polygon(white1, 2);
	polygon(white2, 2);

	//�ָ�ȫ��������ɫ
	SetLineColor();

	//�ָ��������
	setlinestyle(PS_SOLID, 1);

	//�����������
	setfillcolor(RGB(228, 220, 228));
	int Space = 35;
	for (int j = 0, H = 75; j < 11; j++, H += 2 * space) {
		for (int i = 0, W = Space; i < 11; i++, W += 2 * space) {
			fillcircle(W, H, 7);
		}
		Space += space;
	}

	//���Ƽ�λ��ʾ
	settextstyle(20, 0, "����");
	SetTextBlue();
	outtextxy(GUIDEOFFSET, 50, "����  W A S D ��F");
	SetTextPink();
	outtextxy(GUIDEOFFSET, 80, "�죺�������� ���س�");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 140, "��Ϸ����");
	outtextxy(GUIDEOFFSET, 170, "   ͬɫ�������߱���");
	outtextxy(GUIDEOFFSET, 200, "Ӧ��ɫ������ͨ���ʤ");
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

	//�����¼�����
	return HandleGameThird();
}

//������Ϸ_03��
GameState HandleGameThird() {

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
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			Board[i][j] = 0;
		}
	}
	GameContinue = true;
	Player = 1;
	_01I = 5;
	_01J = 5;
	_02I = 5;
	_02J = 5;

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

//=== ��Ϸ_03 ���ӹ���ʵ�� ===//
void DropChess(int dropX, int dropY, string color) {

	//����������ɫ
	if (color == "BLACK") {
		SetLineBlue();
		SetFillBlue();
	}
	if (color == "WHITE") {
		SetLinePink();
		SetFillPink();
	}

	//��������
	fillcircle(dropX, dropY, 7);

	//�ָ�ȫ��������ɫ
	SetLineColor();

	//����������Ч
	PlayAudio();
	Sleep(100);
}

//=== ��Ϸ_03 ��궨λʵ�� ===//
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

//=== ��Ϸ_03 ���ӻغ�ʵ�� ===//
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
					if (_01I - 1 >= 0) {
						CursorPosition(GetIndexW(_01I,_01J), GetIndexH(_01I,_01J), "Grey");
						_01I -= 1;
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "BLACK");
					}
					cout << "W DOWN" << endl;
					break;

					//S������
				case 'S':
					if (_01I + 1 <= 10) {
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "Grey");
						_01I += 1;
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "BLACK");
					}
					cout << "S DOWN" << endl;
					break;

					//A������
				case 'A':
					if (_01J - 1 >= 0) {
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "Grey");
						_01J -= 1;
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "BLACK");
					}
					cout << "A DOWN" << endl;
					break;

					//D������
				case 'D':
					if (_01J + 1 <= 10) {
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "Grey");
						_01J += 1;
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "BLACK");
					}
					cout << "D DOWN" << endl;
					break;

					//F������
				case 'F':
					if (Board[_01I][_01J] == 0) {
						DropChess(GetIndexW(_01I,_01J), GetIndexH(_01I,_01J), "BLACK");
						Player = 2;
						Board[_01I][_01J] = 1;
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

//=== ��Ϸ_03 ���ӻغ�ʵ�� ===//
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
					if (_02I - 1 >= 0) {
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "Grey");
						_02I -= 1;
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
					}
					cout << "UP DOWN" << endl;
					break;

					//�¼�����
				case VK_DOWN:
					if (_02I + 1 <= 10) {
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "Grey");
						_02I += 1;
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
					}
					cout << "DOWN DOWN" << endl;
					break;

					//�������
				case VK_LEFT:
					if (_02J - 1 >= 0) {
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "Grey");
						_02J -= 1;
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
					}
					cout << "LEFT DOWN" << endl;
					break;

					//�Ҽ�����
				case VK_RIGHT:
					if (_02J + 1 <= 10) {
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "Grey");
						_02J += 1;
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
					}
					cout << "RIGHT DOWN" << endl;
					break;

					//�س�������
				case VK_RETURN:
					if (Board[_02I][_02J] == 0) {
						DropChess(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
						Player = 1;
						Board[_02I][_02J] = 2;
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

//=== ��Ϸ_03 ���¶�̬�滮 ===//
static bool UpDownDP() {

	//��ʼ��DP
	vector<vector<int>> dp(11, vector<int>(11, INT_MAX));
	for (int j = 0; j < 11; j++) {
		if (Board[0][j] == 1) {
			dp[0][j] = 1;
		}
		else {
			dp[0][j] = 0;
		}
	}
	for (int i = 0; i < 11; i++) {
		
		//״̬ת�� - ������Դ
		for (int j = 0; j < 11; j++) {
			if (dp[i][j] == INT_MAX) {
				if (Board[i][j] == 1) {
					if (j + 1 <= 10) {
						dp[i][j] = dp[i - 1][j] >= dp[i - 1][j + 1] ? dp[i - 1][j] : dp[i - 1][j + 1];
					}
					else {
						dp[i][j] = dp[i - 1][j];
					}
				}
				else {
					dp[i][j] = 0;
				}
			}
		}

		//˫��ƽ� - ��©��ȱ
		int pos = 0;
		while (pos<=10) {
			if (dp[i][pos] == 1) {
				int index = pos;
				while (index - 1 >= 0 && dp[i][index - 1] == 0 && Board[i][index - 1] == 1) {
					index--;
					dp[i][index] = 1;
				}
				index = pos;
				while (index + 1 <= 10 && dp[i][index + 1] == 0 && Board[i][index + 1] == 1) {
					index++;
					dp[i][index] = 1;
				}
			}
			pos++;
		}
	}

	//�����յ��Ƿ���Ч
	for (int j = 0; j < 11; j++) {
		if (dp[10][j] == 1) {
			return true;
		}
	}
	return false;
}

//=== ��Ϸ_03 ���Ҷ�̬�滮 ===//
static bool LeftRightDP() {

	//��ʼ��DP
	vector<vector<int>> dp(11, vector<int>(11, INT_MAX));
	for (int i = 0; i < 11; i++) {
		if (Board[i][0] == 2) {
			dp[i][0] = 1;
		}
		else {
			dp[i][0] = 0;
		}
	}
	for (int j = 0; j < 11; j++) {

		//״̬ת�� - ������Դ
		for (int i = 0; i < 11; i++) {
			if (dp[i][j] == INT_MAX) {
				if (Board[i][j] == 2) {
					if (i + 1 <= 10) {
						dp[i][j] = dp[i][j - 1] >= dp[i + 1][j - 1] ? dp[i][j - 1] : dp[i + 1][j - 1];
					}
					else {
						dp[i][j] = dp[i][j - 1];
					}
				}
				else {
					dp[i][j] = 0;
				}
			}
		}

		//˫��ƽ� - ��©��ȱ
		int pos = 0;
		while (pos <= 10) {
			if (dp[pos][j] == 1) {
				int index = pos;
				while (index - 1 >= 0 && dp[index - 1][j] == 0 && Board[index - 1][j] == 2) {
					index--;
					dp[index][j] = 1;
				}
				index = pos;
				while (index + 1 <= 10 && dp[index + 1][j] == 0 && Board[index + 1][j] == 2) {
					index++;
					dp[index][j] = 1;
				}
			}
			pos++;
		}
	}

	//�����յ��Ƿ���Ч
	for (int i = 0; i < 11; i++) {
		if (dp[i][10] == 1) {
			return true;
		}
	}
	return false;
}

//=== ��Ϸ_03 �վ��ж�ʵ�� ===//
static bool EndJudgment() {
	if (UpDownDP()) {
		Settlement(1);
		return false;
	}
	if (LeftRightDP()) {
		Settlement(2);
		return false;
	}
	return true;
}

//=== ��Ϸ_03 ����ҳ��ʵ�� ===//
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