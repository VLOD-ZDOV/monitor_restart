#include <windows.h>
#include <iostream>

int main() {
    bool isMonitorOn = true;

    while (true) {
        // Проверяем, нажата ли комбинация горячих клавиш (Ctrl + M)
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState('M') & 0x8000) {
            // Меняем состояние монитора
            isMonitorOn = !isMonitorOn;

            // Отправляем команду управления питанием монитора
            if (isMonitorOn) {
                // Включаем монитор
                SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, -1);
                std::cout << "Монитор включен" << std::endl;
            }
            else {
                // Отключаем монитор
                SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
                std::cout << "Монитор выключен" << std::endl;
            }

            // Ждем, пока клавиша отпущена, чтобы избежать множественных нажатий
            while (GetAsyncKeyState(VK_CONTROL) & 0x8000 || GetAsyncKeyState('M') & 0x8000) {
                Sleep(100);
            }
        }

        // Ждем некоторое время перед проверкой снова, чтобы избежать перегрузки процессора
        Sleep(100);
    }

    return 0;
}