//  pybind/lat/sausages_pybind.cc

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


#include "lat/sausages.h"
#include "hmm/transition-model.h"
#include "util/stl-utils.h"
#include "lat/sausages_pybind.h"
#include "lat/kaldi_lattice_pybind.h"

#include "fst/arc_pybind.h"
#include "fst/fst_pybind.h"
#include "fst/vector_fst_pybind.h"
#include "fstext/lattice-weight.h"
#include "lat/kaldi-lattice.h"
#include "util/kaldi_table_pybind.h"
using namespace kaldi;

void pybind_sausages(py::module& m) {
  {
    using PyClass = MinimumBayesRiskOptions;
    py::class_<PyClass>(m, "MinimumBayesRiskOptions")
      .def(py::init<>());
  }
  {
    using PyClass = MinimumBayesRisk;
    py::class_<PyClass>(m, "MinimumBayesRisk")
      .def(py::init<const CompactLattice & , MinimumBayesRiskOptions>(),py::arg("clat"),py::arg("opts"))
      .def("GetOneBest",&PyClass::GetOneBest)
      .def("GetTimes",&PyClass::GetTimes)
      .def("GetSausageTimes",&PyClass::GetSausageTimes)
      .def("GetOneBestTimes",&PyClass::GetOneBestTimes)
      .def("GetOneBestConfidences",&PyClass::GetOneBestConfidences)
      .def("GetBayesRisk",&PyClass::GetBayesRisk);
  }

}
