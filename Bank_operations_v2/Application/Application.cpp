#include <iostream>
#include "../Contribution_discriptors/Contribution_descriptors.h"
#include "../Bank_operations/Contribution_table.h";
#include <string>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "App_functions.h"

using namespace Bank_operations;

void (*func_ptrs[])(Contribution_table&) = {
    nullptr,
    Open_account,
    Show_account_status,
    Close_account,
    Work_with_account,
    Get_all_accounts,
};
int Get_solution() {
    std::string menu[] = {
        "0. Exit",
        "1. Open_account",
        "2. Show account status",
        "3. Close account",
        "4. Work with account",
        "5. Get all account",
    };
    int solve = -1;
    do {
        system("cls");
        for (int i = 0; i < 6; i++) {
            std::cout << menu[i] << std::endl;
        }
        std::cout << "Input number of function" << std::endl;
        std::cin >> solve;
        if (!std::cin.good()) {
            std::cout << "Input don't correct";
            std::cin.ignore(10000, '\n');
            std::cin.clear();
            Sleep(3000);
            continue;
        }
    } while ((solve < 0) || (solve > 6));
    return solve;
}
int main()
{
    Contribution_table new_table;
    int solution = 0;
    while (solution = Get_solution()) {
        system("cls");
        func_ptrs[solution](new_table);
        _getch();
        if (!std::cin.good()) {
           std::cin.clear();
           std::cin.ignore(10000, '\n');
            
        }
    }
}