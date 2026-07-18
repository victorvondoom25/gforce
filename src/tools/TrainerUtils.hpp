#pragma once
#include <string>
#include <filesystem>
#include "../engine/EvaluateUtils.hpp"

inline std::string GetNextNetworkSaveName(const std::string& path) {
    int maxVersion = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path.empty() ? "." : path)) {
        if (entry.path().extension() == ".nnue") {
            std::string filename = entry.path().stem().string();
            if (filename.find("gforce-") == 0) {
                try {
                    int version = std::stoi(filename.substr(7));
                    if (version > maxVersion) maxVersion = version;
                } catch (...) {}
            }
        }
    }
    char buf[32];
    snprintf(buf, sizeof(buf), "gforce-%02d", maxVersion + 1);
    return std::string(buf);
}
