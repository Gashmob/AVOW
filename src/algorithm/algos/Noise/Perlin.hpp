/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_PERLIN_HPP
#define AVOW_PERLIN_HPP

#include <cstdint>
#include "data.hpp"

class Perlin {
public:
    Perlin(int width, int height, int density) : _width(width), _height(height), _density(density) {
        int dw = width / density;
        int dh = height / density;
        _gradients = new data::vec2<float>[dw * dh];

        for (int i = 0; i < dw * dh; i++) {
            float angle = (float) rand() / RAND_MAX * 2 * M_PI;
            _gradients[i] = {cos(angle), sin(angle)};
        }
    }

    ~Perlin() {
        delete[] _gradients;
    }

    uint8_t get(int x, int y) {
        // TODO : Get 4 corners, dot product then interpolate
        return 0;
    }

private:
    int _width;
    int _height;
    int _density;

    data::vec2<float> *_gradients;
};


#endif //AVOW_PERLIN_HPP
