#include <iostream>
#include "common/array_utils.h"
#include "common/prompt_utils.h"
#include "common/print_utils.h"
#include "01/lab01.h"
#include "02/lab02.h"
#include "03/lab03.h"
#include "04/lab04.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif

int main() {
    std::setlocale(LC_ALL, "Russian");

    #if defined(_WIN32) || defined(_WIN64)
        SetConsoleOutputCP(1251);
        SetConsoleCP(1251);
    #endif

    unsigned short int choice;
    while (true) {
        std::cout << "\nChoices are:\n"
                  << "1: ÒÈÏÛ ÄÀÍÍÛÕ È ÈÕ ÂÍÓÒÐÅÍÍÅÅ ÏÐÅÄÑÒÀÂËÅÍÈÅ Â ÏÀÌßÒÈ\n"
                  << "2: ÎÄÍÎÌÅÐÍÛÅ ÑÒÀÒÈ×ÅÑÊÈÅ ÌÀÑÑÈÂÛ\n"
                  << "3: ÓÊÀÇÀÒÅËÈ\n"
                  << "4: ÒÅÊÑÒÎÂÛÅ ÑÒÐÎÊÈ ÊÀÊ ÌÀÑÑÈÂÛ ÑÈÌÂÎËÎÂ\n";
        choice = prompt_for_number<unsigned short int>("Please choose lab (1, 2, 3, 4)", 1, 4);
        switch (choice) {
            case 1:
                lab01();
                break;
            case 2:
                lab02();
                break;
            case 3:
                lab03();
                break;
            case 4:
                lab04();
                break;
            default:
                std::cout << "Wrong number\n";
                break;
        }
        if (!prompt_for_bool("Choose another lab?")) break;
    }

    system("Pause");

    return 0;
}