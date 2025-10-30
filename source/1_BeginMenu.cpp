#include "GameBasic.h"

//加载“开始菜单”
GameState LoadBeginMenu() {

	//定义专属背景
	IMAGE img_BeginPhoto;

	//加载专属背景
	loadimage(&img_BeginPhoto, "asset\\image\\BeginPhoto.jpg");

	//设置专属背景
	putimage(0, 0, &img_BeginPhoto);

	//计算居中参数
	int spaceW = (BK_WIDTH - BT_WIDTH) / 2;
	int spaceH = (BK_HEIGHT - BT_HEIGHT) / 2;
	int spaceS = BK_HEIGHT / 4;
	int spaceE = BK_HEIGHT / 4 + BT_HEIGHT + 5;

	//绘制开始按钮
	Button begin(spaceW, spaceH + spaceS - 5, BT_WIDTH, BT_HEIGHT, "开始游戏");
	begin.DrawButton();

	//绘制结束按钮
	Button end(spaceW, spaceH + spaceE, BT_WIDTH, BT_HEIGHT, "退出游戏");
	end.DrawButton();

	//绘制制作人信息
	settextstyle(20, 0, "宋体");
	settextcolor(RGB(88, 88, 88));
	outtextxy(5, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, COPYRIGHT.c_str());

	//输出缓冲区
	FlushBatchDraw();

	//调用事件检测
	return HandleBeginMenu(begin, end);
}

//处理“开始菜单”
GameState HandleBeginMenu(Button begin, Button end) {

	//定义事件消息变量
	ExMessage msg = { 0 };

	//获取鼠标信息
	while (true) {
		if (peekmessage(&msg, EX_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				if (begin.CheckClick(msg.x, msg.y)) {
					cerr << "开始游戏" << endl;
					begin.PlayAudio();
					Sleep(250);
					return GAME_SELECT;
				}
				if (end.CheckClick(msg.x, msg.y)) {
					cerr << "退出游戏" << endl;
					end.PlayAudio();
					Sleep(350);
					return PROGRAM_OVER;
				}
			}
		}
		Sleep(10);
	}

	//编译保护
	return BEGIN_MENU;
}