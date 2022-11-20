/**
 *      === AVOW ===
 * Created by Kevin Traini
 *      Under GPL-3.0
 * -----------------------
 */
#ifndef AVOW_DATA_HPP
#define AVOW_DATA_HPP

/**
 * All data structures used in the project
 */
namespace data {
    /**
     * A simple vector in 2 dimensions.
     *
     * @tparam N type of the vector
     */
    template<typename N>
    struct vec2 {
        N x, y;
    };
}

#endif //AVOW_DATA_HPP
