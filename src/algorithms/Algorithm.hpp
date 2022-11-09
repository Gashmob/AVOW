/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_ALGORITHM_HPP
#define AVOW_ALGORITHM_HPP

#include <string>
#include "cxxopts.hpp"

/**
 * Abstract class for all algorithms.
 */
class Algorithm {
public:
    /**
     * Main method that take an image as input and return a new image.
     * @param args Arguments passed by command line, they will be interpreted has a comma separated list.
     */
    virtual void run(std::string args[]) { throw; } // FIXME : choose args and return type

    virtual void getOption(cxxopts::OptionAdder *adder) const final {
        if (_hasArgs)
            (*adder)(this->_opt, this->_description, cxxopts::value<std::vector<std::string>>());
        else
            (*adder)(this->_opt, this->_description);
    }

protected:
    /**
     * Arg to pass to the command line to use this algorithm.
     * Format : o,opt for -o --opt
     */
    const std::string _opt = "<opt>";
    /**
     * If the algorithm need arguments, they are passed in the command line.
     * Arguments
     */
    const bool _hasArgs = false;
    /**
     * Description of the algorithm.
     */
    const std::string _description = "<algorithm description>";

private:
    Algorithm() = default; // Private constructor to prevent instantiation
};


#endif //AVOW_ALGORITHM_HPP
