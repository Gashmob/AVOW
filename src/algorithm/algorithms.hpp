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
#include <functional>

#include "Algorithm.hpp"

#include "Blank.hpp"
#include "Random.hpp"

/**
 * List of all available algorithms
 * key   : name of Algorithm
 * value : pointer to build function
 *
 * Please sort alphabetically
 */
static std::map<std::string, std::function<Algorithm *()>> algorithms = {
        {"Blank", Blank::build},
        {"Random", Random::build},
};

#endif //AVOW_ALGORITHMS_HPP
