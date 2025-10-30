#pragma once
#include <easyx.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <imm.h>
#pragma comment(lib,"imm32.lib")
#include "Button.h"
#include "Level.h"

//游戏状态枚举
enum GameState {

	//程序结束
	PROGRAM_OVER,

	//开始菜单
	BEGIN_MENU,

	//游戏选择
	GAME_SELECT,

	//游戏_01
	GAME_FIRST,

	//游戏_02
	GAME_SECOND,

	//游戏_03
	GAME_THIRD,

	//结束菜单
	END_MENU
};

//版权信息
const string COPYRIGHT = "制作者：林和光，ID：lin-i-svet，版本：v1.7";

//窗口尺寸信息
const int BK_WIDTH = 600;
const int BK_HEIGHT = 600;

//开始标题尺寸
const int BTOPIC_WIDTH = 480;
const int BTOPIC_HEIGHT = 289;

//结束标题尺寸
const int ETOPIC_WIDTH = 450;
const int ETOPIC_HEIGHT = 450;

//按钮尺寸信息
const int BT_WIDTH = 150;
const int BT_HEIGHT = 45;

//关卡尺寸信息
const int LV_WIDTH = 100;
const int LV_HEIGHT = 100;

//指引宽度偏移
const int GUIDEOFFSET = 375;

//游戏帧率限制
const int FPS = 60;

// 保存当前输入法
void SaveInputMethod();

// 强制英文输入法
void ForceInputMethod();

// 恢复原始输入法
void RestoreInputMethod();

//设置通用背景
void SetBackGround();

//设置全局线条颜色
void SetLineColor();

//设置蓝方填充颜色
void SetFillBlue();

//设置蓝方线条颜色
void SetLineBlue();

//设置蓝方文本颜色
void SetTextBlue();

//设置粉方填充颜色
void SetFillPink();

//设置粉方线条颜色
void SetLinePink();

//设置粉方文本颜色
void SetTextPink();

//加载“开始菜单”
GameState LoadBeginMenu();

//处理“开始菜单”
GameState HandleBeginMenu(Button begin, Button end);

//加载“游戏选择”
GameState LoadGameSelect();

//处理“游戏选择”
GameState HandleGameSelect(vector<Level> gameArray);

//加载“游戏_01”
GameState LoadGameFirst();

//处理“游戏_01”
GameState HandleGameFirst();

//加载“游戏_02”
GameState LoadGameSecond();

//处理“游戏_02”
GameState HandleGameSecond();

//加载“游戏_03”
GameState LoadGameThird();

//处理“游戏_04”
GameState HandleGameThird();

//加载“结束菜单”
GameState LoadEndMenu();

//处理“结束菜单”
GameState HandleEndMenu(Button back);