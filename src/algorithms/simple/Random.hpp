/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_RANDOM_HPP
#define AVOW_RANDOM_HPP

#include <iostream>

#include "Algorithm.hpp"
#include "tools.hpp"

using namespace tools;

class Random : public Algorithm {
public:
    Random() {
        _opt = "r,random";
        _hasArgs = true;
        _description = "Generate a random image, args = width,height,channels,seed";
    }

    Image *run(Image *image, const std::vector<std::string> &args) override {
        if (args.size() < 4) {
            std::cout << bold << red << "Invalid number of arguments for blank algorithm, "
                      << args.size() << " given" << reset << std::endl;
            return image;
        }

        delete image; // Delete previous image

        int width = std::stoi(args[0]);
        int height = std::stoi(args[1]);
        int channels = std::stoi(args[2]);
        int seed = std::stoi(args[3]);

        srand(seed);

        return new Image(width, height, channels, [](int x, int y, int c) {
            auto *result = new uint8_t[c];
            for (int i = 0; i < c; i++)
                result[i] = rand() % 256;

            // Set alpha to 255
            if (c == 2)
                result[1] = 255;
            else if (c == 4)
                result[3] = 255;

            return result;
        });
    }
};


#endif //AVOW_RANDOM_HPP
