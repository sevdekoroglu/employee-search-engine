#include "NameTrie.h"
#include <algorithm>

NameTrie::NameTrie() {
    root = new Node();
}

NameTrie::~NameTrie() {
    // Basit temizlik (derin delete gerekmez bu projede)
}

void NameTrie::insert(const std::string& name, int id) {
    Node* curr = root;
    for (char c : name) {
        if (!curr->children[c])
            curr->children[c] = new Node();
        curr = curr->children[c];
        curr->ids.push_back(id);
    }
    curr->isEnd = true;
}

void NameTrie::remove(const std::string& name, int id) {
    Node* curr = root;
    for (char c : name) {
        if (!curr->children[c]) return;
        curr = curr->children[c];
        curr->ids.erase(
            std::remove(curr->ids.begin(), curr->ids.end(), id),
            curr->ids.end()
        );
    }
}

void NameTrie::collect(Node* node, std::vector<int>& result) {
    if (!node) return;

    for (int id : node->ids)
        result.push_back(id);

    for (auto& p : node->children)
        collect(p.second, result);
}

std::vector<int> NameTrie::search(const std::string& prefix) {
    Node* curr = root;
    for (char c : prefix) {
        if (!curr->children[c])
            return {};
        curr = curr->children[c];
    }

    std::vector<int> result;
    collect(curr, result);
    return result;
}
