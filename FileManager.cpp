#include "FileManager.h"
#include <fstream>
#include <iostream>

using std::ofstream;
using std::ifstream;
using std::cout;
using std::string;

// =======================
// LOAD (YUKLEME)
// =======================
void FileManager::loadAll(DirectoryManager& dm, RatingManager& rm) {
    // PERSONELLER
    ifstream fileContacts("contacts.txt");
    if (fileContacts.is_open()) {
        int id;
        string name, email;
        while (fileContacts >> id >> name >> email) {
            dm.addContact(id, name, email);
        }
        fileContacts.close();
    }

    // ETIKETLER
    ifstream fileTags("tags.txt");
    if (fileTags.is_open()) {
        int id;
        string tag;
        while (fileTags >> id >> tag) {
            dm.addTagToContact(id, tag);
        }
        fileTags.close();
    }

    // PUANLAR
    ifstream fileRatings("ratings.txt");
    if (fileRatings.is_open()) {
        string user;
        int id, score;
        while (fileRatings >> user >> id >> score) {
            rm.loadRating(user, id, score, dm);
        }
        fileRatings.close();
    }
}

// =======================
// SAVE (KAYDETME)
// =======================

void FileManager::saveContacts(const DirectoryManager& dm) {
    auto& contacts = const_cast<DirectoryManager&>(dm).getAllContacts();

    ofstream file("contacts.txt");
    if (file.is_open()) {
        for (auto& pair : contacts) {
            file << pair.first << " "
                 << pair.second.name << " "
                 << pair.second.email << "\n";
        }
        file.close();
    }
}

void FileManager::saveTags(const DirectoryManager& dm) {
    auto& contacts = const_cast<DirectoryManager&>(dm).getAllContacts();

    ofstream file("tags.txt");
    if (file.is_open()) {
        for (auto& pair : contacts) {
            for (const string& tag : pair.second.tags) {
                file << pair.first << " " << tag << "\n";
            }
        }
        file.close();
    }
}

// ✅ EN KRITIK YER – ARTIK HEP 5 YAZMIYOR
void FileManager::saveRatings(const RatingManager& rm) {
    const auto& ratings = rm.getRatingScores();

    ofstream file("ratings.txt");
    if (file.is_open()) {
        for (const auto& userPair : ratings) {
            const string& username = userPair.first;
            for (const auto& p : userPair.second) {
                file << username << " "
                     << p.first << " "
                     << p.second << "\n";
            }
        }
        file.close();
    }
}
