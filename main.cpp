#include "Menu.h"
#include "DirectoryManager.h"
#include "RatingManager.h"
#include "FileManager.h"
#include <iostream>

int main() {
    DirectoryManager dm;
    RatingManager rm;

    std::cout << "Veriler yukleniyor...\n";
    FileManager::loadAll(dm, rm); //
    std::cout << "Sistem hazir.\n";

    // Menü çalışır... Kullanıcı çıkış diyene kadar buradadır.
    Menu::mainMenu(dm, rm);

    // --- GÜNCELLEME: ÇIKIŞTA KAYDETME ---
    std::cout << "Veriler kaydediliyor...\n";
    FileManager::saveContacts(dm); //
    FileManager::saveTags(dm);     //
    FileManager::saveRatings(rm);  //
    // ------------------------------------

    return 0;
}