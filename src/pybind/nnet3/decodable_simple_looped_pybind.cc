//  pybind/nnet3/decodable_simple_looped_pybind.cc

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
#include "nnet3/decodable_simple_looped_pybind.h"

#include "nnet3/decodable-simple-looped.h"


using namespace kaldi;
using namespace nnet3;

void pybind_decodable_simple_looped(py::module& m) {

  {
    using PyClass = NnetSimpleLoopedComputationOptions;
    py::class_<PyClass>(m, "NnetSimpleLoopedComputationOptions")
      .def(py::init<>())
      .def_readwrite("frame_subsampling_factor", &PyClass::frame_subsampling_factor)
      .def_readwrite("acoustic_scale", &PyClass::acoustic_scale);
  }
  {
    using PyClass = DecodableNnetSimpleLoopedInfo;
    py::class_<PyClass>(m, "DecodableNnetSimpleLoopedInfo")
      .def(py::init<const NnetSimpleLoopedComputationOptions &,Nnet *>(),py::arg("opts"),py::arg("nnet"))
      .def(py::init<const NnetSimpleLoopedComputationOptions &,AmNnetSimple *>(),py::arg("opts"),py::arg("nnet"));
      
  }
}
  
