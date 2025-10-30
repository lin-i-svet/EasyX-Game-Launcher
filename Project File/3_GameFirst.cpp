#include "GameBasic.h"

//返回标记
static bool BACK = false;

//初始光标坐标
static int _01X = 185;
static int _01Y = 185;
static int _02X = 185;
static int _02Y = 185;

//玩家回合控制
static int Player = 1;

//游戏终局判断
static bool GameContinue = true;

//游戏和棋判断
static int chessSum = 0;

//棋盘维护数组
static vector<vector<int>> Board(15, vector<int>(15, 0));

//索引快速定位
static int GetIndexX(int x) { return (x - 45) / 20; }
static int GetIndexY(int y) { return (y - 45) / 20; }

//播放落子音效
static void PlayAudio() { PlaySound("asset\\sound\\PutChess.wav", NULL, SND_ASYNC | SND_FILENAME); }

//=== 游戏_01 落子功能实现 ===//
static void DropChess(int dropX, int dropY, string color);

//=== 游戏_01 光标定位实现 ===//
static void CursorPosition(int cursorX, int cursorY, string color);

//=== 游戏_01 黑子回合实现 ===//
static void BlackBout();

//=== 游戏_01 白子回合实现 ===//
static void WhiteBout();

//=== 游戏_01 终局判断实现 ===//
static bool EndJudgment();

//=== 游戏_01 结算页面实现 ===//
static void Settlement(int winner);

//加载“游戏_01”
GameState LoadGameFirst() {

	//设置通用背景
	SetBackGround();

	//绘制棋盘底板
	setfillcolor(RGB(209, 209, 209));
	fillroundrect(30, 30, 340, 340, 10, 10);

	//绘制棋盘棋孔
	setfillcolor(RGB(228, 220, 228));
	for (int H = 45; H <= 325; H += 20) {
		for (int W = 45; W <= 325; W += 20) {
			fillcircle(H, W, 5);
		}
	}

	//绘制键位提示
	settextstyle(20, 0, "黑体");
	SetTextBlue();
	outtextxy(GUIDEOFFSET, 50, "蓝：  W A S D ，F");
	SetTextPink();
	outtextxy(GUIDEOFFSET, 80, "红：↑←↓→ ，回车");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 140, "游戏规则：");
	outtextxy(GUIDEOFFSET, 170, "   横、竖、斜任一方");
	outtextxy(GUIDEOFFSET, 200, "向存在五子连棋则获胜");
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

	//调用事件检测
	return HandleGameFirst();
}

//处理“游戏_01”
GameState HandleGameFirst() {

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
		//游戏结束
		return END_MENU;
	}
	else {
		//返回上一级
		BACK = false;
		return GAME_SELECT;
	}
}

//=== 游戏_01 落子功能实现 ===//
void DropChess(int dropX, int dropY, string color) {

	//设置落子颜色
	if (color == "BLACK") {
		SetFillBlue();
		SetLineBlue();
	}
	if (color == "WHITE") {
		SetFillPink();
		SetLinePink();
	}

	//绘制落子
	fillcircle(dropX, dropY, 7);

	//恢复全局线条颜色
	SetLineColor();

	//播放落子音效
	PlayAudio();
	Sleep(100);
}

//=== 游戏_01 光标定位实现 ===//
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

//=== 游戏_01 黑子回合实现 ===//
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
					if (_01Y - 20 >= 45) {
						CursorPosition(_01X, _01Y, "Grey");
						_01Y -= 20;
						CursorPosition(_01X, _01Y, "BLACK");
					}
					cout << "W DOWN" << endl;
					break;

					//S键按下
				case 'S':
					if (_01Y + 20 <= 325) {
						CursorPosition(_01X, _01Y, "Grey");
						_01Y += 20;
						CursorPosition(_01X, _01Y, "BLACK");
					}
					cout << "S DOWN" << endl;
					break;

					//A键按下
				case 'A':
					if (_01X - 20 >= 45) {
						CursorPosition(_01X, _01Y, "Grey");
						_01X -= 20;
						CursorPosition(_01X, _01Y, "BLACK");
					}
					cout << "A DOWN" << endl;
					break;

					//D键按下
				case 'D':
					if (_01X + 20 <= 325) {
						CursorPosition(_01X, _01Y, "Grey");
						_01X += 20;
						CursorPosition(_01X, _01Y, "BLACK");
					}
					cout << "D DOWN" << endl;
					break;

					//F键按下
				case 'F':
					if (Board[GetIndexX(_01X)][GetIndexY(_01Y)] == 0) {
						DropChess(_01X, _01Y, "BLACK");
						Player = 2;
						Board[GetIndexX(_01X)][GetIndexY(_01Y)] = 1;
						chessSum++;
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

//=== 游戏_01 白子回合实现 ===//
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
					if (_02Y - 20 >= 45) {
						CursorPosition(_02X, _02Y, "Grey");
						_02Y -= 20;
						CursorPosition(_02X, _02Y, "WHITE");
					}
					cout << "UP DOWN" << endl;
					break;

					//下键按下
				case VK_DOWN:
					if (_02Y + 20 <= 325) {
						CursorPosition(_02X, _02Y, "Grey");
						_02Y += 20;
						CursorPosition(_02X, _02Y, "WHITE");
					}
					cout << "DOWN DOWN" << endl;
					break;

					//左键按下
				case VK_LEFT:
					if (_02X - 20 >= 45) {
						CursorPosition(_02X, _02Y, "Grey");
						_02X -= 20;
						CursorPosition(_02X, _02Y, "WHITE");
					}
					cout << "LEFT DOWN" << endl;
					break;

					//右键按下
				case VK_RIGHT:
					if (_02X + 20 <= 325) {
						CursorPosition(_02X, _02Y, "Grey");
						_02X += 20;
						CursorPosition(_02X, _02Y, "WHITE");
					}
					cout << "RIGHT DOWN" << endl;
					break;

					//回车键按下
				case VK_RETURN:
					if (Board[GetIndexX(_02X)][GetIndexY(_02Y)] == 0) {
						DropChess(_02X, _02Y, "WHITE");
						Player = 1;
						Board[GetIndexX(_02X)][GetIndexY(_02Y)] = 2;
						chessSum++;
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

//工具函数1
static int Tool1(int X, int Y) {

	//原地棋子
	int count = 1;

	//向左/右探测
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

	//返回水平连子
	return count;
}

//工具函数2
static int Tool2(int X, int Y) {

	//原地棋子
	int count = 1;

	//向上/下探测
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

	//返回垂直连子
	return count;
}

//工具函数3
static int Tool3(int X, int Y) {

	//原地棋子
	int count = -1;

	//向左对角线上探测
	int x = X;
	int y = Y;
	while (x >= 0 && y >= 0 && Board[x][y] == Board[X][Y]) {
		count++;
		x--;
		y--;
	}

	//向左对角线下探测
	x = X;
	y = Y;
	while (x <= 14 && y <= 14 && Board[x][y] == Board[X][Y]) {
		count++;
		x++;
		y++;
	}

	//返回左对角线连子
	return count;
}

//工具函数4
static int Tool4(int X, int Y) {

	//原地棋子
	int count = -1;

	//向右对角线上探测
	int x = X;
	int y = Y;
	while (x <= 14 && y >= 0 && Board[x][y] == Board[X][Y]) {
		count++;
		x++;
		y--;
	}

	//向右对角线下探测
	x = X;
	y = Y;
	while (x >= 0 && y <= 14 && Board[x][y] == Board[X][Y]) {
		count++;
		x--;
		y++;
	}

	//返回右对角线连子
	return count;
}

//=== 游戏_01 终局判断实现 ===//
bool EndJudgment() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Board[i][j] != 0) {
				if (Tool1(i, j) >= 5 || Tool2(i, j) >= 5 || Tool3(i, j) >= 5 || Tool4(i, j) >= 5) {
					Settlement(Board[i][j]);
					cerr << "正在返回棋盘循环" << endl;
					return false;
				}
				if (chessSum == 225) {
					Settlement(3);
					cerr << "触发和棋" << endl;
					return false;
				}
			}
			//棋盘测试：cout << Board[i][j] << " ";
		}
		//棋盘测试：cout << endl;
	}
	return true;
}

//=== 游戏_01 结算页面实现 ===//
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
	if (winner == 3) {
		settextcolor(YELLOW);
		outtextxy(70, 380, "双方和棋！");
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