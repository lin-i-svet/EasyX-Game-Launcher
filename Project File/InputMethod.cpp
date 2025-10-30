#include "GameBasic.h"

// 声明静态变量保存原始输入法状态
static HKL g_hklOriginal = NULL;
static DWORD g_dwOriginalThread = 0;

// 保存当前输入法
void SaveInputMethod() {
    // 获取前台窗口的线程ID
    HWND hwndFore = GetForegroundWindow();
    if (hwndFore) {
        g_dwOriginalThread = GetWindowThreadProcessId(hwndFore, NULL);
        // 获取当前输入法布局
        g_hklOriginal = GetKeyboardLayout(g_dwOriginalThread);
    }
}

// 强制英文输入法
void ForceInputMethod() {

    // 获取英文输入法的键盘布局标识符
    HKL hklEnglish = LoadKeyboardLayoutA("00000409", KLF_ACTIVATE);

    if (hklEnglish) {
        // 激活英文键盘布局
        ActivateKeyboardLayout(hklEnglish, KLF_SETFORPROCESS);

        // 通知当前窗口切换输入法
        HWND hwnd = GetForegroundWindow();
        PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)hklEnglish);
    }
}

// 恢复原始输入法
void RestoreInputMethod() {

    if (g_hklOriginal) {
        // 激活原始键盘布局
        HKL hklRestored = ActivateKeyboardLayout(g_hklOriginal, KLF_SETFORPROCESS);

        if (hklRestored) {
            // 通知窗口恢复输入法
            HWND hwndFore = GetForegroundWindow();
            if (hwndFore) {
                PostMessage(hwndFore, WM_INPUTLANGCHANGEREQUEST,
                    0, (LPARAM)g_hklOriginal);
            }
        }
    }
}