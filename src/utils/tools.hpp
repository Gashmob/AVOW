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

namespace tools {
    bool fileExists(const std::string &path) {
        std::ifstream f(path.c_str());
        bool res = f.good();
        if (res)
            f.close();

        return res;
    }
}

#endif //AVOW_TOOLS_HPP
