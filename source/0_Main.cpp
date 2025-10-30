#include "GameBasic.h"

//����ȫ��������ɫ
void SetLineColor() {
	setlinecolor(RGB(147, 143, 139));
}

//����ͨ�ñ���
IMAGE img_background;

//����ͨ�ñ���
void SetBackGround() {
	putimage(0, 0, &img_background);
}

//��Ŀ������
int main() {

	//����ͨ�ñ���
	loadimage(&img_background, "asset\\image\\BackGround.jpg");

	//��ʼ��ͼ�δ���
	initgraph(BK_WIDTH, BK_HEIGHT, EX_NOMINIMIZE | EX_DBLCLKS | EX_NOCLOSE);

	// ���浱ǰ���뷨
	SaveInputMethod();

	// ǿ��Ӣ�����뷨
	ForceInputMethod();

	//���ô��ڱ�����ɫ
	setbkcolor(RGB(195, 195, 195));

	//�����ı�����ģʽ
	setbkmode(TRANSPARENT);

	//˫������ʼ
	BeginBatchDraw();

	//====================== ��ͼ���� =====================//

	bool Running = true;
	GameState currentState = BEGIN_MENU;

	//����״̬ѭ��
	while (Running) {
		
		//��ʼʱ��
		int startTime = clock();

		//����ȫ��������ɫ
		SetLineColor();

		//���������
		cleardevice();

		//����״̬���������
		if (currentState == PROGRAM_OVER) {
			Running = false;
		}

		//����״̬����ʼ�˵�
		else if (currentState == BEGIN_MENU) {
			currentState = LoadBeginMenu();
		}

		//����״̬����Ϸѡ��
		else if (currentState == GAME_SELECT) {
			currentState = LoadGameSelect();
		}

		//����״̬����Ϸ_01
		else if (currentState == GAME_FIRST) {
			currentState = LoadGameFirst();
		}

		//����״̬����Ϸ_02
		else if (currentState == GAME_SECOND) {
			currentState = LoadGameSecond();
		}

		//����״̬����Ϸ_03
		else if (currentState == GAME_THIRD) {
			currentState = LoadGameThird();
		}

		//����״̬�������˵�
		else if (currentState == END_MENU) {
			currentState = LoadEndMenu();
		}

		//��ֹʱ��
		int freamTime = clock() - startTime;

		//��Ϸ֡�ʿ���
		if (freamTime < FPS) Sleep(FPS - freamTime);
	}

	//====================== ��ͼ���� =====================//

	//˫������ֹ
	EndBatchDraw();

	// �ָ�ԭʼ���뷨
	RestoreInputMethod();

	//�رմ���
	closegraph();

	//�������
	return 0;
}
