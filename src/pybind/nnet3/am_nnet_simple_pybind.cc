//  pybind/nnet3/am_nnet_simple_pybind.cc

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
#include "nnet3/am_nnet_simple_pybind.h"

#include "nnet3/am-nnet-simple.h"

#include "base/kaldi-common.h"
#include "matrix/matrix-lib.h"
#include "nnet3/nnet-nnet.h"


using namespace kaldi;
using namespace nnet3;

void pybind_am_nnet_simple(py::module& m) {

  {
    using PyClass = AmNnetSimple;
    py::class_<PyClass>(m, "AmNnetSimple")
      .def(py::init<>())
      .def("Read",&PyClass::Read,py::arg("is"),py::arg("binary"))
      .def("GetNnet",overload_cast_<>()(&PyClass::GetNnet));
    
  }
}

