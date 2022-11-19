/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_TOOLS_HPP
#define AVOW_TOOLS_HPP

#include <string>
#include <fstream>
#include <vector>

namespace tools {
    /**
     * Check if a file exists.
     *
     * @param path Path to the file.
     * @return true if file exists, false otherwise.
     */
    bool fileExists(const std::string &path) {
        std::ifstream f(path.c_str());
        bool res = f.good();
        if (res)
            f.close();

        return res;
    }

    /**
     * Returns the extension of a file : file.png -> png.
     *
     * @param path Path to the file.
     * @return The extension of the file.
     */
    std::string getExtension(const std::string &path) {
        return path.substr(path.find_last_of('.') + 1);
    }

    std::vector<std::string> split(const std::string &src, const char delim = ',') {
        std::vector<std::string> res;

        std::string current;
        for (const auto c: src) {
            if (c == delim) {
                res.push_back(current);
                current = "";
            } else {
                current += c;
            }
        }

        if (!current.empty())
            res.push_back(current);

        return res;
    }
}

#endif //AVOW_TOOLS_HPP
