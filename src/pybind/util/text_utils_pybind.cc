// pybind/lat/word_align_lattice_pybind.cc

// Copyright 2020 GoVivace Inc. (Author: Shivani Saini)

// See ../../COPYING for clarification regarding multiple authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
// WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache 2 License for the specific language governing permissions and
// limitations under the License.

#include "util/stl-utils.h"
#include "util/text-utils.h"
#include "util/text_utils_pybind.h"

using namespace kaldi;

void pybind_text_utils(py::module& m) {
  m.def("SplitStringToVector", &SplitStringToVector, py::arg("full"), py::arg("delim"),py::arg("omit_empty_strings"), py::arg("out"),
    py::return_value_policy::take_ownership);
}
