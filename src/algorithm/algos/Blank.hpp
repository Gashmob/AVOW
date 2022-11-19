/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_BLANK_HPP
#define AVOW_BLANK_HPP

#include "Algorithm.hpp"
#include "enquirer.hpp"

class Blank : public Algorithm {
public:
    static Blank *build() {
        return new Blank();
    }

    Image *run(Image *image, const Json::Value &config) override {
        delete image;

        return new Image(config["width"].asInt(), config["height"].asInt(), 2, [](int x, int y, int c) {
            auto *result = new uint8_t[c];
            for (int i = 0; i < c; i++)
                result[i] = 0;

            return result;
        });
    }

    Json::Value config() override {
        Json::Value config;

        int width = enquirer::number<int>("Width of the image");
        int height = enquirer::number<int>("Height of the image");

        config["width"] = width;
        config["height"] = height;

        return config;
    }
};

#endif //AVOW_BLANK_HPP
