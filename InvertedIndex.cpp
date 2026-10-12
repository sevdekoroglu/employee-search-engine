#include "InvertedIndex.h"

void InvertedIndex::add(const std::string& tag, int id) {
    index[tag].insert(id);
}

void InvertedIndex::remove(const std::string& tag, int id) {
    if (!index.count(tag)) return;

    index[tag].erase(id);
    if (index[tag].empty())
        index.erase(tag);
}

std::set<int> InvertedIndex::get(const std::string& tag) {
    if (!index.count(tag)) return {};
    return index[tag];
}

const std::unordered_map<std::string, std::set<int>>&
InvertedIndex::getAll() const {
    return index;
}