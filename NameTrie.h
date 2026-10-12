#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class NameTrie {
private:
    struct Node {
        std::unordered_map<char, Node*> children;
        std::vector<int> ids;
        bool isEnd = false;
    };

    Node* root;

    void collect(Node* node, std::vector<int>& result);

public:
    NameTrie();
    ~NameTrie();

    void insert(const std::string& name, int id);
    void remove(const std::string& name, int id);

    // 🔥 DirectoryManager'in aradığı fonksiyon
    std::vector<int> search(const std::string& prefix);
};
