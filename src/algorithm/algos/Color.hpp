/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_COLOR_HPP
#define AVOW_COLOR_HPP

#include "Algorithm.hpp"
#include "enquirer.hpp"

class Color : public Algorithm {
public:
    static Color *build() {
        return new Color();
    }

    Image *run(Image *image, const Json::Value &config) override {
        delete image;

        uint8_t red = config["red"].asUInt();
        uint8_t green = config["green"].asUInt();
        uint8_t blue = config["blue"].asUInt();

        return new Image(config["width"].asInt(), config["height"].asInt(), 3, [=](int x, int y, int c) {
            auto *result = new uint8_t[c];
            result[0] = red;
            result[1] = green;
            result[2] = blue;

            return result;
        });
    }

    Json::Value config() override {
        Json::Value config;

        int width = enquirer::number<int>("Width of the image");
        int height = enquirer::number<int>("Height of the image");
        auto red = enquirer::number<uint8_t>("Red value");
        auto green = enquirer::number<uint8_t>("Green value");
        auto blue = enquirer::number<uint8_t>("Blue value");

        config["width"] = width;
        config["height"] = height;
        config["red"] = red;
        config["green"] = green;
        config["blue"] = blue;

        return config;
    }

    void describe() override {
        std::cout << "Generates an image with a single color." << std::endl
                  << "The configuration needs the width and height of the image and the color (rgb)." << std::endl
                  << "The color is a 3-tuple of unsigned 8-bit integers. There is no alpha channel." << std::endl;
    }
};


#endif //AVOW_COLOR_HPP
