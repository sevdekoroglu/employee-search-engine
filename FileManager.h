#pragma once
#include "DirectoryManager.h"
#include "RatingManager.h"

class FileManager {
public:
    static void loadAll(DirectoryManager& dm, RatingManager& rm);

    static void saveContacts(const DirectoryManager& dm);
    static void saveTags(const DirectoryManager& dm);
    static void saveRatings(const RatingManager& rm);
};