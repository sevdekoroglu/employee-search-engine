#pragma once
#include "DirectoryManager.h"
#include <string>

class DecisionManager {
public:
    // Basit bir kural tabanli öneri sistemi (Rule-Based / Hybrid)
    // Belirtilen etikete sahip, puani en yüksek ve en çok oy almis personeli önerir.
    Contact* recommendHybridML(DirectoryManager& dm, 
                               const std::string& username, 
                               const std::string& tag);
};