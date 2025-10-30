#include "Level.h"
#include "GameBasic.h"

//关卡构造方法
Level::Level(int x, int y, int width, int height, string name, int difficulty) :lv_x(x), lv_y(y), lv_width(width), lv_height(height), lv_name(name), lv_difficulty(difficulty) {}

//绘制关卡图标
void Level::DrawLevel() {

	//设置填充颜色
	setfillcolor(RGB(136, 171, 218));

	//设置线条颜色
	setlinecolor(YELLOW);

	//绘制圆角矩形图形
	fillroundrect(lv_x, lv_y, lv_x + lv_width, lv_y + lv_height, 10, 10);

	//恢复全局线条颜色
	SetLineColor();

	//设置文字颜色
	settextcolor(RGB(109, 106, 117));
	settextcolor(WHITE);

	//设置文字样式
	settextstyle(20, 10, "黑体");

	//绘制居中文本
	int spaceW = (lv_width - textwidth(lv_name.c_str())) / 2;
	int spaceH = (lv_height - textheight(lv_name.c_str())) / 2;
	outtextxy(lv_x + spaceW, lv_y + spaceH - 20, lv_name.c_str());

	//绘制关卡难度
	int starX = lv_x + (lv_width - textwidth("占位符")) / 2;
	int starY = lv_y + spaceH + 20;
	for (int i = 0; i < 5; i++, starX += 15) {
		if (i < lv_difficulty) {	
			setfillcolor(RGB(255, 217, 0));
		}
		else {
			setfillcolor(WHITE);
		}
		fillcircle(starX, starY, 5);
	}
}

//检测关卡点击
bool Level::CheckClick(int mouseX, int mouseY) {

	//判断区域有效性
	if (lv_x <= mouseX && mouseX <= lv_x + lv_width && lv_y <= mouseY && mouseY <= lv_y + lv_height) {
		return true;
	}
	else {
		return false;
	}
}

//播放关卡音效
void Level::PlayAudio() {
	PlaySound("asset\\sound\\PutDown.wav", NULL, SND_ASYNC | SND_FILENAME);
}