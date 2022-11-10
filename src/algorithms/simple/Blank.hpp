/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_BLANK_HPP
#define AVOW_BLANK_HPP

#include "Algorithm.hpp"

using namespace tools;

/**
 * Generate a blank image
 */
class Blank : public Algorithm {
public:
    Blank() {
        _opt = "b,blank";
        _hasArgs = true;
        _description = "Generate a blank image, args = width,height,channels";
    }

    Image *run(Image *image, const std::vector<std::string> &args) override {
        if (args.size() < 3) {
            std::cout << bold << red << "Invalid number of arguments for blank algorithm, "
                      << args.size() << " given" << reset << std::endl;
            return image;
        }

        delete image; // Delete previous image

        int width = std::stoi(args[0]);
        int height = std::stoi(args[1]);
        int channels = std::stoi(args[2]);

        return new Image(width, height, channels, [](int x, int y, int c) {
            auto *result = new uint8_t[c];
            for (int i = 0; i < c; i++)
                result[i] = 0;

            return result;
        });
    }
};


#endif //AVOW_BLANK_HPP