#include "Button.h"
#include "GameBasic.h"

//按钮构造方法
Button::Button(int x, int y, int width, int height, string text) :bt_x(x), bt_y(y), bt_width(width), bt_height(height), bt_text(text) {}

//绘制按钮图形
void Button::DrawButton() {

	//设置填充颜色
	setfillcolor(RGB(136, 171, 218));

	//设置线条颜色
	setlinecolor(YELLOW);

	//绘制矩形图形
	fillrectangle(bt_x, bt_y, bt_x + bt_width, bt_y + bt_height);

	//恢复全局线条颜色
	SetLineColor();

	//设置文字颜色
	settextcolor(WHITE);

	//设置文字样式
	settextstyle(20, 10, "黑体");

	//绘制居中文本
	int spaceW = (bt_width - textwidth(bt_text.c_str())) / 2;
	int spaceH = (bt_height - textheight(bt_text.c_str())) / 2;
	outtextxy(bt_x + spaceW, bt_y + spaceH, bt_text.c_str());
}

//检测按钮点击
bool Button::CheckClick(int mouseX, int mouseY) {

	//判断区域有效性
	if (bt_x <= mouseX && mouseX <= bt_x + bt_width && bt_y <= mouseY && mouseY <= bt_y + bt_height) {
		return true;
	}
	else {
		return false;
	}
}

//播放按钮音效
void Button::PlayAudio() {
	PlaySound("asset\\sound\\PutDown.wav", NULL, SND_ASYNC | SND_FILENAME);
}