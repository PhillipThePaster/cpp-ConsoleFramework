#include <iostream>
#include <conio.h>
#include <windows.h>
#include <unordered_map>

void setConsoleColor(int color) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }

void Cursor(const std::unordered_map<int, std::string>& tabList, int currentTab) {
    system("cls");
    for (auto it = tabList.begin(); it != tabList.end(); ++it) {
        setConsoleColor(it->first == currentTab ? 14 : 7);
        std::cout << (it->first == currentTab ? "> " : "") << it->second << "\n";
    }
    setConsoleColor(7);
}

void Tabs(int currentTab) {
    system("cls");
    std::cout << "Tab " << currentTab << ".\n";
}

int main() {
    std::unordered_map<int, std::string> tabList = {
        {1, "Tab 1"},
        {2, "Tab 2"},
        {3, "Tab 3"}
    };
    int currentTab = 1;
    bool inTextMode = false;
    Cursor(tabList, currentTab);

    while (true) {
        char key = _getch();
        if (!inTextMode) {
            switch (key) {
            case 72: currentTab = (currentTab - 2 + tabList.size()) % tabList.size() + 1; break;
            case 80: currentTab = (currentTab % tabList.size()) + 1; break;
            case 77: inTextMode = true; Tabs(currentTab); break;
            }
        }
        else {
            switch (key) {
            case 75: inTextMode = false; Cursor(tabList, currentTab); break;
            }
        }
        if (!inTextMode) Cursor(tabList, currentTab);
    }

    return 0;
}
