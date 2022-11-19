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

    /**
     * Returns keys of the map
     *
     * @tparam K Type of the key
     * @tparam V Type of the value
     * @param input Map to get keys
     * @return Keys of the map
     */
    template<typename K, typename V>
    std::vector<K> keys(const std::map<K, V> &input) {
        std::vector<K> keys;
        for (auto &it: input)
            keys.push_back(it.first);

        return keys;
    }
}

#endif //AVOW_TOOLS_HPP
