/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_RANDOM_HPP
#define AVOW_RANDOM_HPP

#include "Algorithm.hpp"
#include "enquirer.hpp"

class Random : public Algorithm {
public:
    static Random *build() {
        return new Random();
    }

    Image *run(Image *image, const Json::Value &config) override {
        delete image;

        srand(time(nullptr));

        return new Image(config["width"].asInt(), config["height"].asInt(), 3, [](int x, int y, int c) {
            auto *result = new uint8_t[c];
            for (int i = 0; i < c; i++)
                result[i] = rand() % 256;

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

#endif //AVOW_RANDOM_HPP
