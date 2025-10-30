#include "GameBasic.h"

// ������̬��������ԭʼ���뷨״̬
static HKL g_hklOriginal = NULL;
static DWORD g_dwOriginalThread = 0;

// ���浱ǰ���뷨
void SaveInputMethod() {
    // ��ȡǰ̨���ڵ��߳�ID
    HWND hwndFore = GetForegroundWindow();
    if (hwndFore) {
        g_dwOriginalThread = GetWindowThreadProcessId(hwndFore, NULL);
        // ��ȡ��ǰ���뷨����
        g_hklOriginal = GetKeyboardLayout(g_dwOriginalThread);
    }
}

// ǿ��Ӣ�����뷨
void ForceInputMethod() {

    // ��ȡӢ�����뷨�ļ��̲��ֱ�ʶ��
    HKL hklEnglish = LoadKeyboardLayoutA("00000409", KLF_ACTIVATE);

    if (hklEnglish) {
        // ����Ӣ�ļ��̲���
        ActivateKeyboardLayout(hklEnglish, KLF_SETFORPROCESS);

        // ֪ͨ��ǰ�����л����뷨
        HWND hwnd = GetForegroundWindow();
        PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)hklEnglish);
    }
}

// �ָ�ԭʼ���뷨
void RestoreInputMethod() {

    if (g_hklOriginal) {
        // ����ԭʼ���̲���
        HKL hklRestored = ActivateKeyboardLayout(g_hklOriginal, KLF_SETFORPROCESS);

        if (hklRestored) {
            // ֪ͨ���ڻָ����뷨
            HWND hwndFore = GetForegroundWindow();
            if (hwndFore) {
                PostMessage(hwndFore, WM_INPUTLANGCHANGEREQUEST,
                    0, (LPARAM)g_hklOriginal);
            }
        }
    }
}