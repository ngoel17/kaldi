// pybind/lm/const_arpa_lm_pybind.cc

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


#include "lm/const_arpa_lm_pybind.h"
#include "lm/const-arpa-lm.h"
using namespace kaldi;

void pybind_const_arpa_lm(py::module& m) {
    {
      using PyClass = ConstArpaLm;
      py::class_<PyClass>(m, "ConstArpaLm")
	.def(py::init<>())
	.def("Read", &PyClass::Read, py::arg("is"), py::arg("binary"));
      
    }
    {
      using PyClass = ConstArpaLmDeterministicFst;
      py::class_<PyClass>(m, "ConstArpaLmDeterministicFst")
        .def(py::init<const ConstArpaLm&>(), py::arg("lm"));

    }

}
