/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_NOISE_HPP
#define AVOW_NOISE_HPP

#include "Algorithm.hpp"
#include "enquirer.hpp"
#include "Noise/Perlin.hpp"

class Noise : public Algorithm {
public:
    static Noise *build() {
        return new Noise();
    }

    Image *run(Image *image, const Json::Value &config) override {
        delete image;

        int width = config["width"].asInt();
        int height = config["height"].asInt();
        int density = config["density"].asInt();

        Perlin perlin(width, height, density);

        return new Image(width, height, 2, [&](int x, int y, int c) {
            auto *result = new uint8_t[c];
            result[0] = perlin.get(x, y);
            result[1] = 255;

            return result;
        });
    }

    Json::Value config() override {
        Json::Value config;

        int width = enquirer::number<int>("Width of the image");
        int height = enquirer::number<int>("Height of the image");
        int density = enquirer::number<int>("Density of the noise (number of pixels per case)");
        bool grayscale = enquirer::toggle("Noise applied on ?", "Grayscale", "Transparency");

        config["width"] = width;
        config["height"] = height;
        config["density"] = density;
        config["grayscale"] = grayscale;

        return config;
    }

    void describe() override {
        std::cout << "Use Perlin noise to generate a new image." << std::endl
                  << "The configuration needs the width and height of the image, "
                     "the density of the grid used for the noise and if the noise "
                     "is applied on grayscale or transparency." << std::endl
                  << "Warning : if the noise is applied on transparency, the image need to be saved in a format that supports transparency."
                  << std::endl;
    }
};


#endif //AVOW_NOISE_HPP
