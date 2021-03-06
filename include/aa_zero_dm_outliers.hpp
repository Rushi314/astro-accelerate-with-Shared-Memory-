#ifndef ASTRO_ACCELERATE_AA_ZERO_DM_OUTLIERS_HPP
#define ASTRO_ACCELERATE_AA_ZERO_DM_OUTLIERS_HPP

#include <stdio.h>
#include <time.h>
#include <vector_types.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include "aa_device_zero_dm_outliers_kernel.hpp"

namespace astroaccelerate {

  /**
   * \brief Function that performs zero_dm with outlier rejection.
   * \details The user should not have to use this function directly.
   */
  void zero_dm_outliers(unsigned short *const d_input, const int nchans, const int nsamp);

} // namespace astroaccelerate
  
#endif // ASTRO_ACCELERATE_AA_ZERO_DM_OUTLIERS_HPP
