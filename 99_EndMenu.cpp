#include "GameBasic.h"

//加载“结束菜单”
GameState LoadEndMenu() {

	//定义结束背景
	IMAGE img_EndPhoto;

	//加载结束背景
	loadimage(&img_EndPhoto, "asset\\image\\BackGround.jpg");

	//输出结束背景
	putimage(0, 0, &img_EndPhoto);

	//计算居中参数
	int spaceW = (BK_WIDTH - BT_WIDTH) / 2;
	int spaceH = (BK_HEIGHT - BT_HEIGHT) / 2;
	int spaceS = BK_HEIGHT / 4;
	int spaceE = BK_HEIGHT / 4 + BT_HEIGHT + 5;

	//绘制返回按钮
	Button back(spaceW, spaceH + spaceE, BT_WIDTH, BT_HEIGHT, "返回首页");
	back.DrawButton();

	//绘制制作人信息
	settextstyle(20, 0, "宋体");
	settextcolor(RGB(88, 88, 88));
	outtextxy(5, BK_HEIGHT - textheight(COPYRIGHT.c_str()) - 5, COPYRIGHT.c_str());

	//输出缓冲区
	FlushBatchDraw();

	//调用事件检测
	return HandleEndMenu(back);
}

//处理“结束菜单”
GameState HandleEndMenu(Button back) {

	//定义事件消息变量
	ExMessage msg = { 0 };

	//获取鼠标信息
	while (true) {
		if (peekmessage(&msg, EX_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				if (back.CheckClick(msg.x, msg.y)) {
					cerr << "返回首页" << endl;
					back.PlayAudio();
					Sleep(250);
					return BEGIN_MENU;
				}
			}
		}
		Sleep(10);
	}

	//编译保护
	return END_MENU;
}