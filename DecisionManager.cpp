#include "DecisionManager.h"
#include <vector>
#include <algorithm>

Contact* DecisionManager::recommendHybridML(DirectoryManager& dm, 
                                            const std::string& username, 
                                            const std::string& tag) {
    // 1. İlgili etikete sahip tüm personelleri getir
    std::vector<Contact> candidates = dm.searchByTag(tag);

    if (candidates.empty()) return nullptr;

    // 2. Hibrit Siralama Puani (Weighted Score)
    // Formül: (Ortalama Puan * 0.7) + (Oy Sayisi Agirligi * 0.3)
    // Bu sayede sadece 1 kisinin 5 verdigi personel degil, 
    // 100 kisinin 4.8 verdigi personel öne çikar.
    
    Contact* bestCandidate = nullptr;
    double maxScore = -1.0;

    for (auto& candidate : candidates) {
        // Contact nesnesinin kopyasi üzerinde islem yapiyoruz, 
        // asil veriye erismek için pointer lazim.
        Contact* realPtr = dm.getContactById(candidate.id); 
        
        if (!realPtr) continue;

        double avg = realPtr->average();
        // Oy sayisini normalize etmek için basit bir logaritmik yaklasim veya sinir kullanabiliriz
        // Basitlik adina: Oy sayisi 10'u geçerse tam puan alsin.
        double popularity = (realPtr->ratingCount > 10) ? 5.0 : (realPtr->ratingCount / 2.0);

        double hybridScore = (avg * 0.7) + (popularity * 0.3);

        if (hybridScore > maxScore) {
            maxScore = hybridScore;
            bestCandidate = realPtr;
        }
    }

    return bestCandidate;
}