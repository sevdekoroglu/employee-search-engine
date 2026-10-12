#pragma once
#include "Contact.h"
#include <unordered_map>
#include <unordered_set> // Set kutuphanesi
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

// Trie Dugumu
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord; // harfler anlamlı bir isim oluşturuyorsa true olur.
    std::vector<int> contactIds; 
    TrieNode() : isEndOfWord(false) {}
};

class DirectoryManager { // yönetici sınıf
private:
    std::unordered_map<int, Contact> contacts;  // ana veri tabanı ( ID-kişi) 
    TrieNode* root; 
    std::unordered_map<std::string, std::vector<int>> tagIndex;  // etiket filtresi
    
    // YENI: Benzersiz E-posta Listesi (SET Veri Yapisi)
    std::unordered_set<std::string> uniqueEmails;

    // --- Trie Yardimci Fonksiyonlari --- // ismi parçalayıp ağaca ekler.
    void insertTrie(const std::string& name, int id) {
        TrieNode* curr = root;

        for (char c : name) {
            char lowerC = tolower(c); // büyük küçük harf duyarlılığı

            // harf için düğüm yoksa 
            if (curr->children.find(lowerC) == curr->children.end()) {
                curr->children[lowerC] = new TrieNode(); // yeni düğüm oluşturuyor
            }
            curr = curr->children[lowerC]; // pointerı düğüme kaydırıyorum yani o  harfe ilerliyo
        }
        curr->isEndOfWord = true;// isim bittiğinde buraya kelime sonu bayrağı koyuyorum
        curr->contactIds.push_back(id);// o isme ait personelin ID' sini son düğüme ekliyorum
    }// trie yapımda çakışma olmaması için vektöre ekliyoruz.
    
    void removeFromTrie(const std::string& name, int id) {
        TrieNode* curr = root;
        for (char c : name) {
            char lowerC = tolower(c);
            if (curr->children.find(lowerC) == curr->children.end()) return;
            curr = curr->children[lowerC];
        }
        auto& ids = curr->contactIds;
        ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());
    }
    
    void collectAllIds(TrieNode* node, std::vector<int>& results) {// DFS(derinlikli öncelikli arama)
        if (!node) return;
        if (node->isEndOfWord) {
            for (int id : node->contactIds) results.push_back(id);
        }// ismin bitişiyse tüm ID'leri topla

        // altındaki tüm harflere git ve aynı işlemi yap.
        for (auto& pair : node->children) {
            collectAllIds(pair.second, results);
        }
    }

public:
    DirectoryManager() {
        root = new TrieNode();
    }

    // YENI CREATE: E-posta kontrolü ile ekleme
    // Donus Kodlari: [Pozitif: ID], [-1: ID Hatasi], [-2: Email Cakismasi]
    int addContact(int id, const std::string& name, const std::string& email) {
        // 1. ID Kontrolü
        if (contacts.find(id) != contacts.end()) { // map ile
            return -1;  // hata kodu ID çakışması
        }

        // 2. Email Kontrolü (SET Kullanimi)
        if (uniqueEmails.find(email) != uniqueEmails.end()) {
            return -2; // Bu mail zaten var!
        }
// kayıt
        Contact c;
        c.id = id;
        c.name = name;
        c.email = email; 
        
        contacts[id] = c;
        uniqueEmails.insert(email); // Maili sete ekle
        insertTrie(name, id);// İSMİ ARAMA AĞACINA EKLE

        return id;
    }

    // DELETE
    bool removeContact(int id) {
        if (contacts.find(id) == contacts.end()) return false;// KİŞİ YOKSA ÇIK

        Contact c = contacts[id];
        // TRİE DEN İSMİNİ BOŞA ÇIKAR(ID 'Yİ LİSTEDEN SİL)
        removeFromTrie(c.name, id);

// 2. ETİKET LİSTELERİNDEN (GARSON AŞÇI VB.) ID ' Yİ SİL
        for (const auto& tag : c.tags) {
            auto& ids = tagIndex[tag];
            // VEKTÖRDEN SİLME İŞLEMİ
            ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());
        }

        // Silinen kisinin mailini de boşa çikar
        uniqueEmails.erase(c.email);

        contacts.erase(id); // ANA KAYDI SİL
        return true;
    }

    // LISTELEME VE ARAMA
    std::vector<Contact> listOrdered() {
        std::vector<Contact> list;
        for (auto& pair : contacts) {
            list.push_back(pair.second);
        }
        // ID'ye gore sirala
        std::sort(list.begin(), list.end(), [](const Contact& a, const Contact& b){
            return a.id < b.id;
        });
        return list;
    }

    void addTagToContact(int id, const std::string& tag) {
        if (contacts.find(id) != contacts.end()) {
            contacts[id].tags.push_back(tag);
            tagIndex[tag].push_back(id);
        }
    }

    void removeTagFromContact(int id, const std::string& tag) {
        if (contacts.find(id) != contacts.end()) {
            auto& t = contacts[id].tags;
            t.erase(std::remove(t.begin(), t.end(), tag), t.end());
            auto& ids = tagIndex[tag];
            ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());
        }
    }
    
    void updateName(int id, const std::string& newName) {
        if (contacts.find(id) != contacts.end()) {
            std::string oldName = contacts[id].name;
            removeFromTrie(oldName, id); 
            contacts[id].name = newName; 
            insertTrie(newName, id);     
        }
    }
    
    Contact* getContactById(int id) {
        if (contacts.find(id) != contacts.end()) return &contacts[id];
        return nullptr;
    }
    
    std::vector<Contact> getTop3Personnel() {
        std::vector<Contact> list = listOrdered();

        std::sort(list.begin(), list.end(), [](const Contact& a, const Contact& b){
            return a.average() > b.average();
        });
        
        if (list.size() > 3) list.resize(3);
        return list;
    }
// kullanıcın yazdığı harflere göre trie de gezinir
    std::vector<Contact> searchByPrefix(const std::string& prefix) {
        std::vector<Contact> results;
        TrieNode* curr = root;
      //  1. kullanıcın girdiği harfler 
        for (char c : prefix) {
            char lowerC = tolower(c);
            if (curr->children.find(lowerC) == curr->children.end()) return results;
            curr = curr->children[lowerC];
        }// girdiği harfler yoksa boş dönüyor böyle bir isim yok çünkü
        std::vector<int> foundIds;
        // recursion (özyineleme) kullandık
        collectAllIds(curr, foundIds); // h harfine prefixin sonuna geldikten sonra o noktadan aşağıya sarkan tüm isimleri çağırmak için yardımccı fonksiyonu kullanıyo
        for (int id : foundIds) {
             if(contacts.find(id) != contacts.end())
                results.push_back(contacts[id]);
        }
        return results;
    }

    std::vector<Contact> searchByTag(const std::string& tag) {
        std::vector<Contact> results;
        if (tagIndex.find(tag) != tagIndex.end()) {
            for (int id : tagIndex[tag]) {
                if(contacts.find(id) != contacts.end()) // ID kontrollü map
                    results.push_back(contacts[id]);
            }
        }
        return results;
    }
    
    std::unordered_map<int, Contact>& getAllContacts() { return contacts; }
};
