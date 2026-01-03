#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

extern int get_total(void);
extern int get_saving(void);
extern void add_saving(int);
extern void load_from_file(int, int);

HWND hTotal, hSaving, hEdit, hButton;

// Helper to update the labels
void refresh_labels(void)
{
    char buf[64];

    wsprintfA(buf, "Total number: %d", get_total());
    SetWindowTextA(hTotal, buf);

    wsprintfA(buf, "Saving number: %d", get_saving());
    SetWindowTextA(hSaving, buf);
}

// C handles File I/O, passes data to ASM
void load_file(void)
{
    FILE *f = fopen("data.txt", "r");
    if (!f)
        return;

    int t = 0, s = 0;
    // Ensure we read two integers.
    // If data.txt only has "250", it might fail if looking for 2 inputs.
    if (fscanf(f, "%d %d", &t, &s) == 2)
    {
        load_from_file(t, s);
    }

    fclose(f);
}

void save_file(void)
{
    FILE *f = fopen("data.txt", "w");
    if (!f)
        return;

    fprintf(f, "%d %d\n", get_total(), get_saving());
    fclose(f);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM w, LPARAM l)
{
    switch (msg)
    {
    case WM_CREATE:
        // 1. Total Label
        hTotal = CreateWindowA("STATIC", "Total: 0",
                               WS_CHILD | WS_VISIBLE | SS_LEFT,
                               20, 20, 200, 20, hWnd, 0, 0, 0);

        // 2. Saving Label
        hSaving = CreateWindowA("STATIC", "Saving: 0",
                                WS_CHILD | WS_VISIBLE | SS_LEFT,
                                20, 50, 200, 20, hWnd, 0, 0, 0);

        // 3. Input Edit Box
        hEdit = CreateWindowA("EDIT", "0",
                              WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                              20, 80, 80, 25, hWnd, 0, 0, 0);

        // 4. ADD BUTTON (New!)
        hButton = CreateWindowA("BUTTON", "Add",
                                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                110, 80, 80, 25, hWnd, (HMENU)1, 0, 0);

        load_file();
        refresh_labels();
        break;

    case WM_COMMAND:
        // Check if the Button (ID 1) was clicked
        if (LOWORD(w) == 1)
        {
            char buf[32];
            GetWindowTextA(hEdit, buf, sizeof(buf));

            int value = atoi(buf);

            // Only add if value is not 0
            if (value != 0)
            {
                add_saving(value);

                // Reset input and refresh
                SetWindowTextA(hEdit, "0");
                refresh_labels();
            }
        }
        break;

    case WM_DESTROY:
        save_file();
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcA(hWnd, msg, w, l);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE hPrev, LPSTR lpCmd, int n)
{
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = h;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // White background
    wc.lpszClassName = "NASM_GUI";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassA(&wc))
        return 1;

    HWND w = CreateWindowA(
        "NASM_GUI", "NASM GUI Saver",
        WS_OVERLAPPEDWINDOW,
        100, 100, 320, 200,
        0, 0, h, 0);

    ShowWindow(w, n);

    MSG msg;
    while (GetMessageA(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return 0;
}