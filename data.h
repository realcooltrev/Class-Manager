#pragma once
#include <string>
#include <vector>

#include "models.h"

namespace Data {
    std::vector<Models::person_t> roster = {
        {"Diana", "dnixon4@ivytech.edu"},
        {"Andy", "andy@ivytech.edu"},
        {"Beth", "beth@ivytech.edu"},
        {"Henry", "henry@ivytech.edu"},
        {"Lily", "lili@ivytech.edu"},
        {"Trevor", "tpierce42@ivytech.edu"},
    };

    std::vector<Models::user_data_t> user_data = {
        {"dnixon4", "nice!", Models::Permissions::faculty},
        {"tpierce42", "corndog", Models::Permissions::student, {
            {"Test1", 84},
            {"Test2", 94},
            {"Test3", 73},
            {"Test4", 87},
            {"Test5", 89},
        }},
    };
}
