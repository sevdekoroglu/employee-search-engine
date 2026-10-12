#pragma once
#include "DirectoryManager.h"
#include "RatingManager.h"

class Menu {
public:
    // Fonksiyonlari static yaptik ki Menu m; demeden Menu::mainMenu() diyebilelim.
    static void mainMenu(DirectoryManager& dm, RatingManager& rm);
    
    static void adminMenu(DirectoryManager& dm);
    static void adminCreate(DirectoryManager& dm);
    static void adminRead(DirectoryManager& dm);
    static void adminUpdate(DirectoryManager& dm);
    static void adminDelete(DirectoryManager& dm);

    static void userMenu(DirectoryManager& dm, RatingManager& rm);
};