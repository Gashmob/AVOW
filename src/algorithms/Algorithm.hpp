/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_ALGORITHM_HPP
#define AVOW_ALGORITHM_HPP

#include <string>

/**
 * Abstract class for all algorithms.
 */
class Algorithm {
public:
    /**
     * Main method that take an image as input and return a new image.
     * @param args Arguments passed by command line of the form : a,b,c,d,... split around ,
     */
    virtual void run(std::string args[]) = 0; // FIXME : choose args and return type

    /**
     * Arg to pass to the command line to use this algorithm.
     * Format : o,opt for -o --opt
     * Allow arguments of the form : a,b,c,d,...
     */
    const std::string _opt = "<opt>";
    /**
     * Name of the algorithm.
     */
    const std::string _name = "<algorithm name>";
    /**
     * Description of the algorithm.
     */
    const std::string _description = "<algorithm description>";

private:
    Algorithm() = default; // Private constructor to prevent instantiation
};


#endif //AVOW_ALGORITHM_HPP
