#pragma once
#include <easyx.h>
#include <string>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

//关卡结构声明
class Level {
public:

	//关卡构造方法
	Level(int x, int y, int width, int  height, string name, int difficulty);

	//绘制关卡图标
	void DrawLevel();

	//检测关卡点击
	bool CheckClick(int mouseX, int mouseY);

	//播放关卡音效
	void PlayAudio();

private:

	//关卡x坐标
	int lv_x;

	//关卡y坐标
	int lv_y;

	//关卡宽度
	int lv_width;

	//关卡高度
	int lv_height;

	//关卡名称
	string lv_name;

	//关卡难度
	int lv_difficulty;

};
