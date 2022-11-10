/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_ALGORITHMS_HPP
#define AVOW_ALGORITHMS_HPP

#include <map>
#include <string>

#include "Algorithm.hpp"

#include "simple/Blank.hpp"
#include "simple/White.hpp"

/**
 * List of all available algorithms
 * key   : _opt member of Algorithm
 * value : instance of Algorithm
 */
static std::map<std::string, Algorithm *> algorithms = {
        std::make_pair("blank", new Blank()),
        std::make_pair("white", new White()),
};

#endif //AVOW_ALGORITHMS_HPP
