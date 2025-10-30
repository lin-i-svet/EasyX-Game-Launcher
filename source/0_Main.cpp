#include "GameBasic.h"

//设置全局线条颜色
void SetLineColor() {
	setlinecolor(RGB(147, 143, 139));
}

//定义通用背景
IMAGE img_background;

//设置通用背景
void SetBackGround() {
	putimage(0, 0, &img_background);
}

//项目主函数
int main() {

	//加载通用背景
	loadimage(&img_background, "asset\\image\\BackGround.jpg");

	//初始化图形窗口
	initgraph(BK_WIDTH, BK_HEIGHT, EX_NOMINIMIZE | EX_DBLCLKS | EX_NOCLOSE);

	// 保存当前输入法
	SaveInputMethod();

	// 强制英文输入法
	ForceInputMethod();

	//设置窗口背景颜色
	setbkcolor(RGB(195, 195, 195));

	//设置文本背景模式
	setbkmode(TRANSPARENT);

	//双缓冲起始
	BeginBatchDraw();

	//====================== 绘图部分 =====================//

	bool Running = true;
	GameState currentState = BEGIN_MENU;

	//窗口状态循环
	while (Running) {
		
		//起始时间
		int startTime = clock();

		//设置全局线条颜色
		SetLineColor();

		//清除缓冲区
		cleardevice();

		//窗口状态：程序结束
		if (currentState == PROGRAM_OVER) {
			Running = false;
		}

		//窗口状态：开始菜单
		else if (currentState == BEGIN_MENU) {
			currentState = LoadBeginMenu();
		}

		//窗口状态：游戏选择
		else if (currentState == GAME_SELECT) {
			currentState = LoadGameSelect();
		}

		//窗口状态：游戏_01
		else if (currentState == GAME_FIRST) {
			currentState = LoadGameFirst();
		}

		//窗口状态：游戏_02
		else if (currentState == GAME_SECOND) {
			currentState = LoadGameSecond();
		}

		//窗口状态：游戏_03
		else if (currentState == GAME_THIRD) {
			currentState = LoadGameThird();
		}

		//窗口状态：结束菜单
		else if (currentState == END_MENU) {
			currentState = LoadEndMenu();
		}

		//终止时间
		int freamTime = clock() - startTime;

		//游戏帧率控制
		if (freamTime < FPS) Sleep(FPS - freamTime);
	}

	//====================== 绘图部分 =====================//

	//双缓冲终止
	EndBatchDraw();

	// 恢复原始输入法
	RestoreInputMethod();

	//关闭窗口
	closegraph();

	//程序结束
	return 0;
}
