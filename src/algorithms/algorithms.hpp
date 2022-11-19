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

/**
 * List of all available algorithms
 * key   : name of Algorithm
 * value : pointer to build function
 */
static std::map<std::string, std::function<Algorithm *()>> algorithms = {};

#endif //AVOW_ALGORITHMS_HPP
