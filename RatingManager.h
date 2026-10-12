#ifndef RATING_MANAGER_H
#define RATING_MANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class DirectoryManager; // Forward declaration

class RatingManager {
private:
    // kullanıcı -> (puan verdiği personel ID'leri)
    std::unordered_map<std::string, std::unordered_set<int>> userRatings;

    // ✅ EKLENDİ:
    // kullanıcı -> (personelId -> verilen GERÇEK puan)
    std::unordered_map<std::string,
        std::unordered_map<int, int>> userRatingScores;

public:
    bool ratePersonnel(const std::string& username,
                       int personnelId,
                       int score,
                       DirectoryManager& dm);

    bool hasUserRated(const std::string& username,
                      int personnelId) const;

    // DOSYADAN YUKLEME ICIN
    void loadRating(const std::string& username,
                    int personnelId,
                    int score,
                    DirectoryManager& dm);

    // Eski tanim (uyumluluk icin kalsin)
    void restoreRating(const std::string& username,
                       int personnelId);

    const std::unordered_map<std::string,
          std::unordered_set<int>>& getAllRatings() const;

    // ✅ EKLENDİ:
    // FileManager gerçek puanı buradan okuyacak
    const std::unordered_map<std::string,
        std::unordered_map<int, int>>& getRatingScores() const;
};

#endif
