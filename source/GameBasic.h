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

//��Ϸ״̬ö��
enum GameState {

	//�������
	PROGRAM_OVER,

	//��ʼ�˵�
	BEGIN_MENU,

	//��Ϸѡ��
	GAME_SELECT,

	//��Ϸ_01
	GAME_FIRST,

	//��Ϸ_02
	GAME_SECOND,

	//��Ϸ_03
	GAME_THIRD,

	//�����˵�
	END_MENU
};

//��Ȩ��Ϣ
const string COPYRIGHT = "�����ߣ��ֺ͹⣬ID��lin-i-svet���汾��v1.7";

//���ڳߴ���Ϣ
const int BK_WIDTH = 600;
const int BK_HEIGHT = 600;

//��ʼ����ߴ�
const int BTOPIC_WIDTH = 480;
const int BTOPIC_HEIGHT = 289;

//��������ߴ�
const int ETOPIC_WIDTH = 450;
const int ETOPIC_HEIGHT = 450;

//��ť�ߴ���Ϣ
const int BT_WIDTH = 150;
const int BT_HEIGHT = 45;

//�ؿ��ߴ���Ϣ
const int LV_WIDTH = 100;
const int LV_HEIGHT = 100;

//ָ�����ƫ��
const int GUIDEOFFSET = 375;

//��Ϸ֡������
const int FPS = 60;

// ���浱ǰ���뷨
void SaveInputMethod();

// ǿ��Ӣ�����뷨
void ForceInputMethod();

// �ָ�ԭʼ���뷨
void RestoreInputMethod();

//����ͨ�ñ���
void SetBackGround();

//����ȫ��������ɫ
void SetLineColor();

//�������������ɫ
void SetFillBlue();

//��������������ɫ
void SetLineBlue();

//���������ı���ɫ
void SetTextBlue();

//���÷۷������ɫ
void SetFillPink();

//���÷۷�������ɫ
void SetLinePink();

//���÷۷��ı���ɫ
void SetTextPink();

//���ء���ʼ�˵���
GameState LoadBeginMenu();

//������ʼ�˵���
GameState HandleBeginMenu(Button begin, Button end);

//���ء���Ϸѡ��
GameState LoadGameSelect();

//������Ϸѡ��
GameState HandleGameSelect(vector<Level> gameArray);

//���ء���Ϸ_01��
GameState LoadGameFirst();

//������Ϸ_01��
GameState HandleGameFirst();

//���ء���Ϸ_02��
GameState LoadGameSecond();

//������Ϸ_02��
GameState HandleGameSecond();

//���ء���Ϸ_03��
GameState LoadGameThird();

//������Ϸ_04��
GameState HandleGameThird();

//���ء������˵���
GameState LoadEndMenu();

//���������˵���
GameState HandleEndMenu(Button back);