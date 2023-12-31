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
#ifndef FMCA_H2MATRIX_H2BACKWARDTRANSFORM_IMPL_H_
#define FMCA_H2MATRIX_H2BACKWARDTRANSFORM_IMPL_H_

namespace FMCA {
namespace internal {
/**
 *  \ingroup H2Matrix
 *  \brief implements the forward transform for the matrix times vector product
 */
template <typename Derived, typename T = Matrix>
void backward_transform_recursion(const TreeBase<Derived> &ct, T *tvec,
                                  std::vector<T> &vec) {
  const Derived &node = ct.derived();
  if (node.nSons()) {
    for (auto i = 0; i < ct.nSons(); ++i) {
      vec[node.sons(i).block_id()] +=
          node.Es()[i].transpose() * vec[node.block_id()];
      backward_transform_recursion(node.sons(i), tvec, vec);
    }
  } else {
    tvec->middleRows(node.indices_begin(), node.V().cols()) +=
        node.V().transpose() * vec[node.block_id()];
  }
}

template <typename Derived, typename T = Matrix>
T backward_transform_impl(const H2MatrixBase<Derived> &mat,
                          std::vector<T> &vec) {
  T retval(mat.rcluster()->indices().size(), vec[0].cols());
  retval.setZero();
  backward_transform_recursion(*(mat.rcluster()), &retval, vec);
  return retval;
};
}  // namespace internal
}  // namespace FMCA
#endif
