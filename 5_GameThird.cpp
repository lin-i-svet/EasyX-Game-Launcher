#include "GameBasic.h"

//返回标记
static bool BACK = false;

//设置棋盘参数
const int radius = 12;
const int space = radius * sqrt(3.0) / 2;

//初始光标坐标
static int _01I = 5;
static int _01J = 5;
static int _02I = 5;
static int _02J = 5;

//玩家回合控制
static int Player = 1;

//游戏终局判断
static bool GameContinue = true;

//棋盘维护数组
static vector<vector<int>> Board(11, vector<int>(11, 0));

//索引快速定位
static int GetIndexW(int i, int j) { return (35 + 2 * j * space + i * space); }
static int GetIndexH(int i, int j) { return (75 + 2 * i * space); }

//播放落子音效
static void PlayAudio() { PlaySound("asset\\sound\\PutChess.wav", NULL, SND_ASYNC | SND_FILENAME); }

//=== 游戏_03 落子功能实现 ===//
static void DropChess(int dropX, int dropY, string color);

//=== 游戏_03 光标定位实现 ===//
static void CursorPosition(int cursorX, int cursorY, string color);

//=== 游戏_03 黑子回合实现 ===//
static void BlackBout();

//=== 游戏_03 白子回合实现 ===//
static void WhiteBout();

//=== 游戏_03 上下动态规划 ===//
static bool UpDownDP();

//=== 游戏_03 左右动态规划 ===//
static bool LeftRightDP();

//=== 游戏_03 终局判断实现 ===//
static bool EndJudgment();

//=== 游戏_03 结算页面实现 ===//
static void Settlement(int winner);

//加载“游戏_03”
GameState LoadGameThird() {

	//设置通用背景
	SetBackGround();

	//绘制棋盘底板
	int temp = 15;
	setfillcolor(RGB(209, 209, 209));
	POINT arr[] = { {35 - temp - 10,75 - temp},{35 + 20 * space + temp,75 - temp},{35 + 30 * space + temp + 10,75 + 20 * space + temp},{35 + 10 * space - temp,75 + 20 * space + temp} };
	fillpolygon(arr, 4);

	//绘制颜色指引
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

	//恢复全局线条颜色
	SetLineColor();

	//恢复线条宽度
	setlinestyle(PS_SOLID, 1);

	//绘制棋盘棋孔
	setfillcolor(RGB(228, 220, 228));
	int Space = 35;
	for (int j = 0, H = 75; j < 11; j++, H += 2 * space) {
		for (int i = 0, W = Space; i < 11; i++, W += 2 * space) {
			fillcircle(W, H, 7);
		}
		Space += space;
	}

	//绘制键位提示
	settextstyle(20, 0, "黑体");
	SetTextBlue();
	outtextxy(GUIDEOFFSET, 50, "蓝：  W A S D ，F");
	SetTextPink();
	outtextxy(GUIDEOFFSET, 80, "红：↑←↓→ ，回车");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 140, "游戏规则：");
	outtextxy(GUIDEOFFSET, 170, "   同色的两条边被对");
	outtextxy(GUIDEOFFSET, 200, "应颜色的棋连通则获胜");
	outtextxy(GUIDEOFFSET, 230, "先手顺序为执蓝优先");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 290, "当前回合：");

	//绘制制作人信息
	settextstyle(20, 0, "宋体");
	settextcolor(RGB(88, 88, 88));
	outtextxy(5, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, COPYRIGHT.c_str());

	//绘制返回提示
	settextstyle(20, 0, "黑体");
	settextcolor(BLACK);
	outtextxy(520, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, "ESC返回");

	//输出缓冲区
	FlushBatchDraw();

	//调用事件处理
	return HandleGameThird();
}

//处理“游戏_03”
GameState HandleGameThird() {

	//黑白对弈循环
	while (GameContinue) {

		//黑子回合实现
		BlackBout();
		if (BACK)break;

		//终局检测
		GameContinue = EndJudgment();
		if (!GameContinue) break;

		//白子回合实现
		WhiteBout();
		if (BACK)break;

		//终局检测
		GameContinue = EndJudgment();
		if (!GameContinue) break;
	}

	//重置游戏数据
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
		//游戏结束
		return END_MENU;
	}
	else {
		//返回上一级
		BACK = false;
		return GAME_SELECT;
	}
}

//=== 游戏_03 落子功能实现 ===//
void DropChess(int dropX, int dropY, string color) {

	//设置落子颜色
	if (color == "BLACK") {
		SetLineBlue();
		SetFillBlue();
	}
	if (color == "WHITE") {
		SetLinePink();
		SetFillPink();
	}

	//绘制落子
	fillcircle(dropX, dropY, 7);

	//恢复全局线条颜色
	SetLineColor();

	//播放落子音效
	PlayAudio();
	Sleep(100);
}

//=== 游戏_03 光标定位实现 ===//
void CursorPosition(int cursorX, int cursorY, string color) {

	//设置光标颜色
	if (color == "BLACK") {
		SetLineBlue();
	}
	if (color == "WHITE") {
		SetLinePink();
	}
	if (color == "Grey") {
		setlinecolor(RGB(209, 209, 209));
	}

	//绘制光标
	circle(cursorX, cursorY, 9);

	//恢复全局线条颜色
	SetLineColor();
}

//=== 游戏_03 黑子回合实现 ===//
void BlackBout() {

	//绘制回合提示
	SetFillBlue();
	fillcircle(505, 300, 15);

	//定义事件消息变量
	ExMessage msg = { 0 };

	//获取左键盘信息
	while (Player == 1) {
		if (peekmessage(&msg, EX_KEY)) {
			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {

					//W键按下
				case 'W':
					if (_01I - 1 >= 0) {
						CursorPosition(GetIndexW(_01I,_01J), GetIndexH(_01I,_01J), "Grey");
						_01I -= 1;
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "BLACK");
					}
					cout << "W DOWN" << endl;
					break;

					//S键按下
				case 'S':
					if (_01I + 1 <= 10) {
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "Grey");
						_01I += 1;
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "BLACK");
					}
					cout << "S DOWN" << endl;
					break;

					//A键按下
				case 'A':
					if (_01J - 1 >= 0) {
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "Grey");
						_01J -= 1;
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "BLACK");
					}
					cout << "A DOWN" << endl;
					break;

					//D键按下
				case 'D':
					if (_01J + 1 <= 10) {
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "Grey");
						_01J += 1;
						CursorPosition(GetIndexW(_01I, _01J), GetIndexH(_01I, _01J), "BLACK");
					}
					cout << "D DOWN" << endl;
					break;

					//F键按下
				case 'F':
					if (Board[_01I][_01J] == 0) {
						DropChess(GetIndexW(_01I,_01J), GetIndexH(_01I,_01J), "BLACK");
						Player = 2;
						Board[_01I][_01J] = 1;
					}
					cout << "F DOWN" << endl;
					break;

					//ESC按下
				case VK_ESCAPE:
					BACK = true;
					Player = 3;
					break;
				}
			}
		}

		//输出缓冲区
		FlushBatchDraw();

		//设置延迟保护
		Sleep(10);
	}
}

//=== 游戏_03 白子回合实现 ===//
void WhiteBout() {

	//绘制回合提示
	SetFillPink();
	fillcircle(505, 300, 15);

	//定义事件消息变量
	ExMessage msg = { 0 };

	//获取右键盘信息
	while (Player == 2) {
		if (peekmessage(&msg, EX_KEY)) {
			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {

					//上键按下
				case VK_UP:
					if (_02I - 1 >= 0) {
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "Grey");
						_02I -= 1;
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
					}
					cout << "UP DOWN" << endl;
					break;

					//下键按下
				case VK_DOWN:
					if (_02I + 1 <= 10) {
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "Grey");
						_02I += 1;
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
					}
					cout << "DOWN DOWN" << endl;
					break;

					//左键按下
				case VK_LEFT:
					if (_02J - 1 >= 0) {
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "Grey");
						_02J -= 1;
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
					}
					cout << "LEFT DOWN" << endl;
					break;

					//右键按下
				case VK_RIGHT:
					if (_02J + 1 <= 10) {
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "Grey");
						_02J += 1;
						CursorPosition(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
					}
					cout << "RIGHT DOWN" << endl;
					break;

					//回车键按下
				case VK_RETURN:
					if (Board[_02I][_02J] == 0) {
						DropChess(GetIndexW(_02I, _02J), GetIndexH(_02I, _02J), "WHITE");
						Player = 1;
						Board[_02I][_02J] = 2;
					}
					cout << "ENTER DOWN" << endl;
					break;

					//ESC按下
				case VK_ESCAPE:
					BACK = true;
					Player = 3;
					break;
				}
			}
		}
		//输出缓冲区
		FlushBatchDraw();

		//设置延迟保护
		Sleep(10);
	}
}

//=== 游戏_03 上下动态规划 ===//
static bool UpDownDP() {

	//初始化DP
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
		
		//状态转移 - 两个来源
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

		//双向逼近 - 查漏补缺
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

	//计算终点是否有效
	for (int j = 0; j < 11; j++) {
		if (dp[10][j] == 1) {
			return true;
		}
	}
	return false;
}

//=== 游戏_03 左右动态规划 ===//
static bool LeftRightDP() {

	//初始化DP
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

		//状态转移 - 两个来源
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

		//双向逼近 - 查漏补缺
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

	//计算终点是否有效
	for (int i = 0; i < 11; i++) {
		if (dp[i][10] == 1) {
			return true;
		}
	}
	return false;
}

//=== 游戏_03 终局判断实现 ===//
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

//=== 游戏_03 结算页面实现 ===//
void Settlement(int winner) {

	//设置结算字体
	settextstyle(40, 20, "黑体");

	//绘制结算提示
	if (winner == 1) {
		SetTextBlue();
		outtextxy(70, 380, "蓝方胜利！");
	}
	if (winner == 2) {
		SetTextPink();
		outtextxy(70, 380, "红方胜利！");
	}
	settextcolor(GREEN);
	outtextxy(70, 460, "按“V”键完成结算");
	FlushBatchDraw();

	//播放结算音效
	PlaySound("asset\\sound\\GameOver.wav", NULL, SND_ASYNC | SND_FILENAME);

	//按“V”键完成结算
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