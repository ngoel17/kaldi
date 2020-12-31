// pybind/online2/online2_pybind.cc

// Copyright 2020 GoVivace Inc. (Author: Shivani Saini)

// See ../../../COPYING for clarification regarding multiple authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
// WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache 2 License for the specific language governing permissions and
// limitations under the License.

#include "online2/online2_pybind.h"
#include "online2/online_nnet2_feature_pipeline_pybind.h"

void pybind_online2(py::module& m) {
  pybind_online_nnet2_feature_pipeline(m);
}
