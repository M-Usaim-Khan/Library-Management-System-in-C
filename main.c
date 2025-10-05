#include <windows.h>
// Usaim
#define IDC_USERNAME 101
#define IDC_PASSWORD 102
#define IDC_LOGIN    103

// Window procedure (handles events)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDC_LOGIN) {
                char username[100], password[100];
                GetWindowText(GetDlgItem(hwnd, IDC_USERNAME), username, 100);
                GetWindowText(GetDlgItem(hwnd, IDC_PASSWORD), password, 100);

                if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
                    MessageBox(hwnd, "Login Successful!", "Success", MB_OK | MB_ICONINFORMATION);
                } else {
                    MessageBox(hwnd, "Invalid username or password", "Error", MB_OK | MB_ICONERROR);
                }
            }
        } break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// Entry point
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int nCmdShow) {
    // Register window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = "LoginWin32";
    RegisterClass(&wc);

    // Create main window
    HWND hwnd = CreateWindow("LoginWin32", "Login Page (Win32)",
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             100, 100, 350, 220,
                             NULL, NULL, hInst, NULL);

    // Username label + textbox
    CreateWindow("STATIC", "Username:", WS_VISIBLE | WS_CHILD,
                 20, 20, 80, 25, hwnd, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                 120, 20, 180, 25, hwnd, (HMENU)IDC_USERNAME, NULL, NULL);

    // Password label + textbox
    CreateWindow("STATIC", "Password:", WS_VISIBLE | WS_CHILD,
                 20, 60, 80, 25, hwnd, NULL, NULL, NULL);
    CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD,
                 120, 60, 180, 25, hwnd, (HMENU)IDC_PASSWORD, NULL, NULL);

    // Login button
    CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_CHILD,
                 120, 100, 100, 30, hwnd, (HMENU)IDC_LOGIN, NULL, NULL);

    // Message loop
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
