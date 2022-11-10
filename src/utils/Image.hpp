/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_IMAGE_HPP
#define AVOW_IMAGE_HPP

#include <string>
#include <cstring>
#include <stdexcept>
#include <functional>

#include "tools.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

/**
 * Class representing an image.
 */
class Image final {
public:
    /**
     * Open an image from a file.
     *
     * @param path Path to the image file.
     * @throws runtime_error if the file cannot be opened or doesn't exists.
     */
    explicit Image(const std::string &path) {
        // Pre-initialize to avoid warning
        _width = _height = 0;
        _channels = 1;

        if (!tools::fileExists(path))
            throw std::runtime_error("File does not exist: " + path);

        if (stbi_info(path.c_str(), &_width, &_height, &_channels) == 0)
            throw std::runtime_error("Cannot open file: " + path);

        _data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
    }

    /**
     * Create an image from a generator
     *
     * @param width Width of image
     * @param height Height of image
     * @param channels Number of channels, 1 = grayscale, 2 = grayscale + alpha, 3 = RGB, 4 = RGBA
     * @param generator Generator function (x, y, channels) -> value, default generator set to white image
     */
    Image(int width, int height, int channels, uint8_t *(*generator)(int, int, int) = _default_generator)
            : _width(width), _height(height), _channels(channels) {
        _data = new uint8_t[_width * _height * _channels];

        map([&generator](int x, int y, int c, uint8_t *value) {
            return generator(x, y, c);
        });
    }

    /**
     * Create a deep copy of other.
     *
     * @param other The image to copy.
     */
    Image(const Image &other) {
        _width = other._width;
        _height = other._height;
        _channels = other._channels;
        _data = new uint8_t[_width * _height * _channels];
        memcpy(_data, other._data, _width * _height * _channels);
    }

    /**
     * Free the image data.
     */
    ~Image() {
        stbi_image_free(_data);
    }

    /**
     * Save the image to a file.
     *
     * @param path Path to the output file.
     * @throws runtime_error if the file format is not supported.
     */
    void save(const std::string &path) {
        std::string ext = tools::getExtension(path);

        if (ext == "png")
            stbi_write_png(path.c_str(), _width, _height, _channels, _data, _width * _channels);
        else if (ext == "jpg" || ext == "jpeg")
            stbi_write_jpg(path.c_str(), _width, _height, _channels, _data, 100);
        else if (ext == "bmp")
            stbi_write_bmp(path.c_str(), _width, _height, _channels, _data);
        else if (ext == "tga")
            stbi_write_tga(path.c_str(), _width, _height, _channels, _data);
        else if (ext == "hdr")
            stbi_write_hdr(path.c_str(), _width, _height, _channels, (float *) _data);
        else
            throw std::runtime_error("Unsupported file format: " + ext);
    }

    /**
     * Number of channels in the image.
     * 1 = grayscale, 2 = grayscale + alpha, 3 = RGB, 4 = RGBA
     *
     * @return Number of channels.
     */
    int channels() const {
        return _channels;
    }

    /**
     * Width of the image.
     *
     * @return Width.
     */
    int width() const {
        return _width;
    }

    /**
     * Height of the image.
     *
     * @return Height.
     */
    int height() const {
        return _height;
    }

    /**
     * Get the data buffer.
     *
     * @return Data buffer.
     */
    uint8_t *data() const {
        return _data;
    }

    /**
     * Get the pixel at the given coordinates.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @return Array of uint8_t of size channels().
     */
    uint8_t *read(int x, int y) const {
        auto *result = new uint8_t[_channels];
        memcpy(result, _data + (y * _width + x) * _channels, _channels);

        return result;
    }

    /**
     * Set the pixel at the given coordinates.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param data uint8_t array of size channels().
     * @return Self instance.
     */
    Image *write(int x, int y, uint8_t *data) {
        memcpy(_data + (y * _width + x) * _channels, data, _channels);

        return this;
    }

    /**
     * Map all the image with func
     *
     * @param func The function to apply to each pixel (x, y, channels, data) -> data
     * @return Self instance
     */
    Image *map(const std::function<uint8_t *(int, int, int, uint8_t *)> &func) {
        for (int x = 0; x < _width; x++) {
            for (int y = 0; y < _height; y++) {
                write(x, y, func(x, y, _channels, read(x, y)));
            }
        }

        return this;
    }

private:
    uint8_t *_data;
    int _width, _height, _channels;

    /**
     * Return a white pixel. Used as default generator.
     *
     * @param x
     * @param y
     * @param channels
     * @return
     */
    static uint8_t *_default_generator(int x, int y, int channels) {
        auto *result = new uint8_t[channels];
        // Set each bit of result to 1 for a white pixel
        for (int i = 0; i < channels; i++)
            result[i] = 255;

        return result;
    }
};


#endif //AVOW_IMAGE_HPP
