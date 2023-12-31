// This file is part of FMCA, the Fast Multiresolution Covariance Analysis
// package.
//
// Copyright (c) 2022, Michael Multerer
//
// All rights reserved.
//
// This source code is subject to the GNU Affero General Public License v3.0
// license and without any warranty, see <https://github.com/muchip/FMCA>
// for further information.
//
#ifndef FMCA_UTIL_TICTOC__
#define FMCA_UTIL_TICTOC__

#include <iostream>
#include <string>
#include <sys/time.h>

#include "Macros.h"

namespace FMCA {
class Tictoc {
public:
  void tic(void) { gettimeofday(&start, NULL); }
  Scalar toc(void) {
    gettimeofday(&stop, NULL);
    Scalar dtime =
        stop.tv_sec - start.tv_sec + 1e-6 * (stop.tv_usec - start.tv_usec);
    return dtime;
  }
  Scalar toc(const std::string &message) {
    gettimeofday(&stop, NULL);
    Scalar dtime =
        stop.tv_sec - start.tv_sec + 1e-6 * (stop.tv_usec - start.tv_usec);
    std::cout << message << " " << dtime << "sec.\n";
    return dtime;
  }

private:
  struct timeval start; /* variables for timing */
  struct timeval stop;
};
} // namespace FMCA
#endif
