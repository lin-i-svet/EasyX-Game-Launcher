#include "GameBasic.h"

//加载“游戏选择”
GameState LoadGameSelect() {

	//设置游戏队列
	vector<Level> gameArray;
	gameArray.push_back({ 5 + 15 * 1 + LV_WIDTH * 0, 15, 100, 100, "五子棋", 3 });
	gameArray.push_back({ 5 + 15 * 2 + LV_WIDTH * 1,15,100,100,"四子棋",2 });
	gameArray.push_back({ 5 + 15 * 3 + LV_WIDTH * 2,15,100,100,"六贯棋",4 });
	gameArray.push_back({ 5 + 15 * 4 + LV_WIDTH * 3,15,100,100,"敬请期待",0 });
	gameArray.push_back({ 5 + 15 * 5 + LV_WIDTH * 4,15,100,100,"敬请期待",0 });

	//设置通用背景
	SetBackGround();

	//绘制游戏队列
	for (auto x : gameArray) {
		x.DrawLevel();
	}

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
	return HandleGameSelect(gameArray);
}

//处理“游戏选择”
GameState HandleGameSelect(vector<Level> gameArray) {

	//定义事件消息变量
	ExMessage msg = { 0 };

	//获取鼠标和键盘信息
	while (true) {
		if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
			switch (msg.message) {

				//键盘ESC按下
			case WM_KEYDOWN:
				if (msg.vkcode == VK_ESCAPE) {
					return BEGIN_MENU;
				}

				//鼠标左键按下
			case WM_LBUTTONDOWN:
				if (gameArray[0].CheckClick(msg.x, msg.y)) {
					cerr << "游戏_01" << endl;
					gameArray[0].PlayAudio();
					Sleep(250);
					return GAME_FIRST;
				}
				if (gameArray[1].CheckClick(msg.x, msg.y)) {
					cerr << "游戏_02" << endl;
					gameArray[1].PlayAudio();
					Sleep(250);
					return GAME_SECOND;
				}
				if (gameArray[2].CheckClick(msg.x, msg.y)) {
					cerr << "游戏_03" << endl;
					gameArray[2].PlayAudio();
					Sleep(250);
					return GAME_THIRD;
				}
			}
		}

		//设置延迟保护
		Sleep(10);
	}

	//编译保护
	return GAME_SELECT;
}