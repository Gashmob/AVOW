/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_ALGORITHM_HPP
#define AVOW_ALGORITHM_HPP

#include <string>
#include <json/json.h>
#include "Image.hpp"

/**
 * Abstract class for all algorithms.
 */
class Algorithm {
public:
    /**
     * Main method that take an image as input and return a new image.
     *
     * @param image Image to treat
     * @param config Configuration for the algorithm from the config file
     * @return The Image treated
     */
    virtual Image *run(Image *image, const Json::Value &config) { throw; }

    /**
     * Method that build an instance of algorithm
     *
     * @return An instance of the algorithm ready to run
     */
    static Algorithm *build() { throw; }

    /**
     * Method that return the config of the algorithm.
     * Can use Enquirer to ask user for input.
     *
     * @return
     */
    virtual Json::Value config() { throw; }

protected:
    Algorithm() = default; // Private constructor to prevent instantiation
};


#endif //AVOW_ALGORITHM_HPP
