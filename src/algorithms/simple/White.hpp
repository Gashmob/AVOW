/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_WHITE_HPP
#define AVOW_WHITE_HPP

#include <iostream>

#include "Algorithm.hpp"
#include "tools.hpp"

using namespace tools;

class White : public Algorithm {
public:
    White() {
        _opt = "w,white";
        _hasArgs = true;
        _description = "Generate a white image, args = width,height,channels";
    }

    Image *run(Image *image, const std::vector<std::string> &args) override {
        if (args.size() < 3) {
            std::cout << bold << red << "Invalid number of arguments for white algorithm, "
                      << args.size() << " given" << reset << std::endl;
            return image;
        }

        delete image; // Delete previous image

        int width = std::stoi(args[0]);
        int height = std::stoi(args[1]);
        int channels = std::stoi(args[2]);

        return new Image(width, height, channels);
    }
};


#endif //AVOW_WHITE_HPP
