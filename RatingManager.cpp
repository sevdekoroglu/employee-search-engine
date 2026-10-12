#include "RatingManager.h"
#include "DirectoryManager.h"

// Kullanicinin bir personele puan vermesi
bool RatingManager::ratePersonnel(const std::string& username,
                                  int personnelId,
                                  int score,
                                  DirectoryManager& dm) {
    if (score < 1 || score > 5) return false;

    if (hasUserRated(username, personnelId)) {
        return false;
    }

    Contact* c = dm.getContactById(personnelId);
    if (c == nullptr) return false;

    c->totalScore += score;
    c->ratingCount++;

    // mevcut yapı (bozulmadı)
    userRatings[username].insert(personnelId);

    // ✅ EKLENDİ: GERÇEK PUANI SAKLA
    userRatingScores[username][personnelId] = score;

    return true;
}

bool RatingManager::hasUserRated(const std::string& username,
                                 int personnelId) const {
    auto it = userRatings.find(username);
    if (it != userRatings.end()) {
        if (it->second.find(personnelId) != it->second.end()) {
            return true;
        }
    }
    return false;
}

void RatingManager::restoreRating(const std::string& username,
                                  int personnelId) {
    userRatings[username].insert(personnelId);
}

void RatingManager::loadRating(const std::string& username,
                               int personnelId,
                               int score,
                               DirectoryManager& dm) {
    userRatings[username].insert(personnelId);
    userRatingScores[username][personnelId] = score;

    Contact* c = dm.getContactById(personnelId);
    if (c) {
        c->totalScore += score;
        c->ratingCount++;
    }
}

const std::unordered_map<std::string,
      std::unordered_set<int>>& RatingManager::getAllRatings() const {
    return userRatings;
}

// ✅ EKLENDİ
const std::unordered_map<std::string,
    std::unordered_map<int, int>>&
RatingManager::getRatingScores() const {
    return userRatingScores;
}
