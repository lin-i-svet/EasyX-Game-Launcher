#pragma once
#include <easyx.h>
#include <string>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

//按钮结构声明
class Button {
public:

	//按钮构造方法
	Button(int x, int y, int width, int height, string text);

	//绘制按钮图形
	void DrawButton();

	//检测按钮点击
	bool CheckClick(int mouseX, int mouseY);

	//播放按钮音效
	void PlayAudio();

private:

	//按钮x坐标
	int bt_x;

	//按钮y坐标
	int bt_y;

	//按钮宽度
	int bt_width;

	//按钮高度
	int bt_height;

	//按钮文本
	string bt_text;
};