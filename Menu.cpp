#include "Menu.h"
#include "DirectoryManager.h"
#include "RatingManager.h"
#include "DecisionManager.h"
#include "FileManager.h"
#include <iostream>
#include <limits> 

using std::cin;
using std::cout;
using std::string;
using std::numeric_limits;
using std::streamsize;

void clearInputBuffer() {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

// ANA MENU (Degismedi)
void Menu::mainMenu(DirectoryManager& dm, RatingManager& rm) {
    int secim;
    do {
        cout << "\n=== PERSONEL ARAMA SISTEMI ===\n"
             << "1- Yonetici Menusu\n"
             << "2- Kullanici Menusu\n"
             << "0- Cikis\nSecim: ";
        
        if (!(cin >> secim)) {
            cout << "Hatali giris! Lutfen bir sayi giriniz.\n";
            clearInputBuffer();
            secim = -1; 
            continue;
        }

        if (secim == 1) adminMenu(dm);
        else if (secim == 2) userMenu(dm, rm);

    } while (secim != 0);
}

// YONETICI MENU (Degismedi)
void Menu::adminMenu(DirectoryManager& dm) {
    int s;
    do {
        cout << "\n--- YONETICI MENUSU (CRUD) ---\n"
             << "1- Personel Ekle (CREATE)\n"
             << "2- Personel Listele (READ)\n"
             << "3- Personel Guncelle (UPDATE)\n"
             << "4- Personel Sil (DELETE)\n"
             << "0- Geri Don\nSecim: ";
        
        if (!(cin >> s)) {
            cout << "Hatali giris! Lutfen bir sayi giriniz.\n";
            clearInputBuffer();
            s = -1; 
            continue;
        }

        if (s == 1) adminCreate(dm);
        else if (s == 2) adminRead(dm);
        else if (s == 3) adminUpdate(dm);
        else if (s == 4) adminDelete(dm);

    } while (s != 0);
}

// =======================
// CREATE (GUNCELLENDI: MAIL EKLENDI)
// =======================
void Menu::adminCreate(DirectoryManager& dm) {
    int id;
    string name, email, tag;

    cout << "Personel ID: ";
    while(!(cin >> id)) { 
        cout << "Gecersiz ID! Tekrar giriniz: ";
        clearInputBuffer();
    }

    cout << "Isim: ";
    cin >> name;

    cout << "Kurumsal E-Posta: ";
    cin >> email;

    // Mail ve ID kontrolü yaparak ekleme
    int result = dm.addContact(id, name, email);

    if (result == -1) {
        cout << "HATA: Bu ID zaten mevcut!\n";
        return;
    } else if (result == -2) {
        cout << "HATA: Bu E-Posta adresi zaten kullanimda! (Benzersizlik İhlali)\n";
        return;
    }

    cout << "Etiket gir (0 ile bitir): ";
    while (true) {
        cin >> tag;
        if (tag == "0") break;
        dm.addTagToContact(id, tag);
    }

    // 🔒 KALICILIK
    FileManager::saveContacts(dm);
    FileManager::saveTags(dm);

    cout << "CREATE tamamlandi ve kaydedildi.\n";
}

// READ (GUNCELLENDI: MAIL GOSTERILIYOR)
void Menu::adminRead(DirectoryManager& dm) {
    cout << "\n--- PERSONEL LISTESI ---\n";

    auto list = dm.listOrdered();
    if (list.empty()) {
        cout << "Listelenecek personel yok.\n";
        return;
    }

    for (auto& c : list) {
        cout << "ID: " << c.id 
             << " | " << c.name
             << " | " << c.email
             << " | Ort: " << c.average() << "\n";
    }
}

// UPDATE (Degismedi)
void Menu::adminUpdate(DirectoryManager& dm) {
    int id, s;
    string value;

    cout << "Guncellenecek Personel ID: ";
    while(!(cin >> id)) {
        cout << "Gecersiz ID! Tekrar giriniz: ";
        clearInputBuffer();
    }

    if (!dm.getContactById(id)) {
        cout << "Personel bulunamadi.\n";
        return;
    }

    cout << "\n1- Isim Degistir\n"
         << "2- Etiket Ekle\n"
         << "3- Etiket Sil\nSecim: ";
    
    if (!(cin >> s)) {
        cout << "Hatali secim!\n";
        clearInputBuffer();
        return;
    }

    if (s == 1) {
        cout << "Yeni isim: ";
        cin >> value;
        dm.updateName(id, value);
    }
    else if (s == 2) {
        cout << "Eklenecek etiket: ";
        cin >> value;
        dm.addTagToContact(id, value);
    }
    else if (s == 3) {
        cout << "Silinecek etiket: ";
        cin >> value;
        dm.removeTagFromContact(id, value);
    }

    FileManager::saveContacts(dm);
    FileManager::saveTags(dm);
    cout << "UPDATE tamamlandi ve kaydedildi.\n";
}

// DELETE (Degismedi)
void Menu::adminDelete(DirectoryManager& dm) {
    int id;
    cout << "Silinecek Personel ID: ";
    while(!(cin >> id)) {
        cout << "Gecersiz ID! Tekrar giriniz: ";
        clearInputBuffer();
    }

    if (dm.removeContact(id)) {
        FileManager::saveContacts(dm);
        FileManager::saveTags(dm);
        cout << "DELETE tamamlandi ve kaydedildi.\n";
    } else {
        cout << "Personel bulunamadi.\n";
    }
}

// KULLANICI MENU (GUNCELLENDI: MAIL GOSTERILIYOR)
void Menu::userMenu(DirectoryManager& dm, RatingManager& rm) {
    string username, q;
    int s;

    cout << "Kullanici adi: ";
    cin >> username;

    DecisionManager decision;

    do {
        cout << "\n--- KULLANICI MENUSU (" << username << ") ---\n"
             << "1- Isme Gore Ara (Trie)\n"
             << "2- Etikete Gore Ara (Inverted Index)\n"
             << "3- Personel Puanla\n"
             << "4- Ayin En Iyi 3 Personeli\n"
             << "5- Hibrit ML Onerisi\n"
             << "0- Geri Don\nSecim: ";
        
        if (!(cin >> s)) {
            cout << "Hatali giris! Lutfen bir sayi giriniz.\n";
            clearInputBuffer();
            s = -1;
            continue;
        }

        if (s == 1) {
            cout << "Prefix: ";
            cin >> q;
            auto res = dm.searchByPrefix(q);

            if (res.empty())
                cout << "Sonuc bulunamadi.\n";

            for (auto& c : res)
                cout << c.id << " " << c.name << " (" << c.email << ")"
                     << " | Ort: " << c.average() << "\n";
        }
        else if (s == 2) {
            cout << "Etiket: ";
            cin >> q;
            auto res = dm.searchByTag(q);

            if (res.empty())
                cout << "Sonuc bulunamadi.\n";

            for (auto& c : res)
                cout << c.id << " " << c.name << " (" << c.email << ")"
                     << " | Ort: " << c.average() << "\n";
        }
        else if (s == 3) {
            int id, p;
            cout << "Personel ID: ";
            while(!(cin >> id)) {
                cout << "Gecersiz ID! Tekrar giriniz: ";
                clearInputBuffer();
            }

            cout << "Puan (1-5): ";
            while(!(cin >> p) || p < 1 || p > 5) {
                cout << "Gecersiz puan (1-5 arasi girin): ";
                clearInputBuffer();
            }

            if (rm.ratePersonnel(username, id, p, dm)) {
                FileManager::saveContacts(dm);
                FileManager::saveRatings(rm);
                cout << "Puan kaydedildi ve diske yazildi.\n";
            } else {
                cout << "Daha once puanlanmis veya hatali giris.\n";
            }
        }
        else if (s == 4) {
            auto top = dm.getTop3Personnel();

            if (top.empty()) {
                cout << "Henuz yeterli veri yok.\n";
            } else {
                for (int i = 0; i < (int)top.size(); i++)
                    cout << i + 1 << ". "
                         << top[i].name << " (" << top[i].email << ")"
                         << " | Ort: "
                         << top[i].average() << "\n";
            }
        }
        else if (s == 5) {
            string tag;
            cout << "ML icin etiket gir: ";
            cin >> tag;

            Contact* rec =
                decision.recommendHybridML(dm, username, tag);

            if (rec) {
                cout << "ML Onerisi: "
                     << rec->name << " (" << rec->email << ")"
                     << " | Ort: "
                     << rec->average()
                     << " | Puan Sayisi: "
                     << rec->ratingCount << "\n";
            } else {
                cout << "Uygun personel bulunamadi.\n";
            }
        }

    } while (s != 0);
}