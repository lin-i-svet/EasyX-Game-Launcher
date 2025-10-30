#include "GameBasic.h"

//返回标记
static bool BACK = false;

//初始光标坐标
static int X = 180;
static int Y = 40;

//当前光标坐标
static int _X;
static int _Y;

//玩家回合控制
static int Player = 1;

//游戏终局判断
static bool GameContinue = true;

//游戏和棋判断
static int chessSum = 0;

//棋盘维护数组
static vector<vector<int>> Board(6, vector<int>(7, 0));

//索引快速定位
static int GetIndexX(int h) { return (h - 90) / 40; }
static int GetIndexY(int w) { return (w - 60) / 40; }

//播放落子音效
static void PlayAudio() { PlaySound("asset\\sound\\ThrowChess.wav", NULL, SND_ASYNC | SND_FILENAME); }

//=== 游戏_02 落子功能实现 ===//
static void DropChess(int beginX, int beginY, int endX, int endY, string color);

//=== 游戏_02 光标定位实现 ===//
static void CursorPosition(string color);

//=== 游戏_02 红方回合实现 ===//
static void RedBout();

//=== 游戏_02 黄方回合实现 ===//
static void YellowBout();

//=== 游戏_02 终局判断实现 ===//
static bool EndJudgment();

//=== 游戏_02 结算页面实现 ===//
static void Settlement(int winner);

//加载“游戏_02”
GameState LoadGameSecond() {

	//设置通用背景
	SetBackGround();

	//绘制棋盘底板
	setfillcolor(RGB(209,209,209));
	fillroundrect(35, 65, 325, 315, 30, 30);

	//绘制棋盘棋孔
	setfillcolor(RGB(228, 220, 228));
	for (int W = 60; W <= 300; W += 40) {
		for (int H = 90; H <= 290; H += 40) {
			fillcircle(W ,H, 13);
		}
	}

	//绘制预备棋孔
	setlinecolor(RGB(195, 195, 195));
	setfillcolor(RGB(195, 195, 195));
	fillcircle(180, 40, 13);
	fillcircle(140, 40, 13);
	fillcircle(100, 40, 13);
	fillcircle(60, 40, 13);
	fillcircle(220, 40, 13);
	fillcircle(260, 40, 13);
	fillcircle(300, 40, 13);
	

	//恢复全局线条颜色
	SetLineColor();

	//绘制键位提示
	settextstyle(20, 0, "黑体");
	SetTextBlue();
	outtextxy(GUIDEOFFSET, 50, "蓝：  A D ，F");
	SetTextPink();
	outtextxy(GUIDEOFFSET, 80, "红：← → ，回车");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 140, "游戏规则：");
	outtextxy(GUIDEOFFSET, 170, "   横、竖、斜任一方");
	outtextxy(GUIDEOFFSET, 200, "向存在四子连棋则获胜");
	outtextxy(GUIDEOFFSET, 230, "先手顺序为执蓝优先");
	settextcolor(BLACK);
	outtextxy(GUIDEOFFSET, 290, "当前回合：");

	//绘制回合提示
	SetFillBlue();
	fillcircle(505, 300, 15);

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
	return HandleGameSecond();
}

//处理“游戏_02”
GameState HandleGameSecond() {

	//红黄对弈循环
	while (GameContinue) {

		//红方回合实现
		RedBout();
		if (BACK)break;

		//终局检测
		GameContinue = EndJudgment();
		if (!GameContinue) break;

		//黄方回合实现
		YellowBout();
		if (BACK)break;

		//终局检测
		GameContinue = EndJudgment();
		if (!GameContinue) break;
	}

	//重置游戏数据
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			Board[i][j] = 0;
		}
	}
	GameContinue = true;
	chessSum = 0;
	Player = 1;

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

//=== 游戏_02 落子功能实现 ===//
void DropChess(int beginX, int beginY, int endX, int endY, string color ) {

	//播放落子音效
	PlayAudio();

	//棋子下落动画循环
	while (true) {

		//控制帧率
		Sleep(1);

		//清屏
		cleardevice();

		//设置通用背景
		SetBackGround();

		//重绘棋盘底板
		setfillcolor(RGB(209, 209, 209));
		fillroundrect(35, 65, 325, 315, 30, 30);

		//重绘棋盘棋孔
		for (int W = 60; W <= 300; W += 40) {
			for (int H = 90; H <= 290; H += 40) {
				
				//根据棋孔确定绘制颜色
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

		//绘制预备棋孔
		setlinecolor(RGB(195, 195, 195));
		setfillcolor(RGB(195, 195, 195));
		fillcircle(180, 40, 13);
		fillcircle(140, 40, 13);
		fillcircle(100, 40, 13);
		fillcircle(60, 40, 13);
		fillcircle(220, 40, 13);
		fillcircle(260, 40, 13);
		fillcircle(300, 40, 13);


		//恢复全局线条颜色
		SetLineColor();

		//绘制键位提示
		settextstyle(20, 0, "黑体");
		SetTextBlue();
		outtextxy(GUIDEOFFSET, 50, "蓝：  A D ，F");
		SetTextPink();
		outtextxy(GUIDEOFFSET, 80, "红：← → ，回车");
		settextcolor(BLACK);
		outtextxy(GUIDEOFFSET, 140, "游戏规则：");
		outtextxy(GUIDEOFFSET, 170, "   横、竖、斜任一方");
		outtextxy(GUIDEOFFSET, 200, "向存在四子连棋则获胜");
		outtextxy(GUIDEOFFSET, 230, "先手顺序为执蓝优先");
		settextcolor(BLACK);
		outtextxy(GUIDEOFFSET, 290, "当前回合：");

		//绘制回合提示
		if (color == "RED") {
			SetFillPink();
		}
		if (color == "YELLOW") {
			SetFillBlue();
		}
		fillcircle(505, 300, 15);

		//绘制制作人信息
		settextstyle(20, 0, "宋体");
		settextcolor(RGB(88, 88, 88));
		outtextxy(5, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, COPYRIGHT.c_str());

		//绘制返回提示
		settextstyle(20, 0, "黑体");
		settextcolor(BLACK);
		outtextxy(520, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, "ESC返回");

		//设置落子颜色
		if (color == "RED") {
			SetFillBlue();
		}
		if (color == "YELLOW") {
			SetFillPink();
		}

		//控制下落速度
		beginY += 5;
		fillcircle(beginX, beginY, 13);

		//输出缓冲区
		FlushBatchDraw();

		//落到目的地停止
		if (beginY == endY) {

			//更新棋盘数组状态
			if (color == "RED") {
				Board[GetIndexX(endY)][GetIndexY(endX)] = 1;
			}
			if (color == "YELLOW") {
				Board[GetIndexX(endY)][GetIndexY(endX)] = 2;
			}
			
			//退出循环动画
			break;
		}
	}
}

//=== 游戏_02 光标定位实现 ===//
void CursorPosition(string color) {
	
	//设置光标颜色
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

	//绘制光标
	fillcircle(_X, _Y, 13);

	//恢复全局线条颜色
	SetLineColor();
}

//=== 游戏_02 红方回合实现 ===//
void RedBout() {

	//恢复初始光标
	_X = X;
	_Y = Y;

	//绘制初始光标
	CursorPosition("RED");

	//定义事件消息变量
	ExMessage msg = { 0 };

	//获取左键盘信息
	while (Player == 1) {
		if (peekmessage(&msg, EX_KEY)) {
			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {

					//A键按下
				case 'A':
					if (_X - 40 >= 60) {
						CursorPosition("GREY");
						_X -= 40;
						CursorPosition("RED");
					}
					cout << "A DOWN" << endl;
					break;

					//D键按下
				case 'D':
					if (_X + 40 <= 300) {
						CursorPosition("GREY");
						_X += 40;
						CursorPosition("RED");
					}
					cout << "D DOWN" << endl;
					break;

					//F键按下
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

//=== 游戏_02 黄方回合实现 ===//
void YellowBout() {

	//恢复初始光标
	_X = X;
	_Y = Y;

	//绘制初始光标
	CursorPosition("YELLOW");

	//定义事件消息变量
	ExMessage msg = { 0 };

	//获取右键盘信息
	while (Player == 2) {
		if (peekmessage(&msg, EX_KEY)) {
			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {

					//左键按下
				case VK_LEFT:
					if (_X - 40 >= 60) {
						CursorPosition("GREY");
						_X -= 40;
						CursorPosition("YELLOW");
					}
					cout << "LEFT DOWN" << endl;
					break;

					//右键按下
				case VK_RIGHT:
					if (_X + 40 <= 300) {
						CursorPosition("GREY");
						_X += 40;
						CursorPosition("YELLOW");
					}
					cout << "RIGHT DOWN" << endl;
					break;

					//回车键按下
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

	while (right <= 6 && Board[X][right] == Board[X][Y]) {
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

	while (down <= 5 && Board[down][Y] == Board[X][Y]) {
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
	while (x <= 5 && y <= 6 && Board[x][y] == Board[X][Y]) {
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
	while (x <= 5 && y >= 0 && Board[x][y] == Board[X][Y]) {
		count++;
		x++;
		y--;
	}

	//向右对角线下探测
	x = X;
	y = Y;
	while (x >= 0 && y <= 6 && Board[x][y] == Board[X][Y]) {
		count++;
		x--;
		y++;
	}

	//返回右对角线连子
	return count;
}

//=== 游戏_02 终局判断实现 ===//
bool EndJudgment() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (Board[i][j] != 0) {
				if (Tool1(i, j) >= 4 || Tool2(i, j) >= 4 || Tool3(i, j) >= 4 || Tool4(i, j) >= 4) {
					Settlement(Board[i][j]);
					cerr << "正在返回棋盘循环" << endl;
					return false;
				}
				if (chessSum == 42) {
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

//=== 游戏_02 结算页面实现 ===//
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