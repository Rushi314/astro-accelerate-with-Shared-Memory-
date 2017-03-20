#ifndef ASTROACCELERATE_CUDA_DMTIME_H
#define ASTROACCELERATE_CUDA_DMTIME_H

#include "DedispersionStrategy.h"
#include <vector>
#include <assert.h>

namespace astroaccelerate {

/**
 * @brief
 *    Class to encapsulate DmTime
 *    Credit goes to Chris Williams
 * @details
 *
 */

template<typename ValueType>
class DmTime
{
    public:
        DmTime(DedispersionStrategy const&);
        ~DmTime();
        std::size_t number_of_dm_ranges() const;
        std::size_t output_size() const;
        float** operator[](std::size_t dm_range) { return _data[dm_range]; };

    private:
        std::size_t _ouput_size;
        std::vector<std::size_t> _ndms;
        std::size_t _range;
        ValueType*** _data; // contiguous memory block
};

}

#include "detail/DmTime.cpp"
#endif // ASTROACCELERATE_CUDA_DMTIME_H