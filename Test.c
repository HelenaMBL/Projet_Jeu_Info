#include <windows.h>
#include <wchar.h>
#include <stdio.h>

int main() {
    SetConsoleOutputCP(CP_UTF8); // code page UTF-8
    system("chcp 65001");         // alternative

    wprintf(L"Test ♥ ♣ ♦ ♠ ★\n"); // doit s'afficher
    return 0;
}
