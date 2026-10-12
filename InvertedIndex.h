#pragma once
#include <unordered_map>
#include <set>
#include <string>

class InvertedIndex {
private:
    std::unordered_map<std::string, std::set<int>> index;

public:
    void add(const std::string& tag, int id);
    void remove(const std::string& tag, int id);

    std::set<int> get(const std::string& tag);

    // 🔥 DirectoryManager için gerekli
    const std::unordered_map<std::string, std::set<int>>& getAll() const;
};