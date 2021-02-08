//  pybind/lat/compose_lattice_pruned.cc

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


#include "lat/compose-lattice-pruned.h"
#include "compose_lattice_pruned.h"
#include "hmm/transition-model.h"
#include "util/stl-utils.h"
#include "lat/word_align_lattice_pybind.h"
#include "lat/kaldi_lattice_pybind.h"

#include "fst/arc_pybind.h"
#include "fst/fst_pybind.h"
#include "fst/vector_fst_pybind.h"
#include "fstext/lattice-weight.h"
#include "lat/kaldi-lattice.h"
#include "util/kaldi_table_pybind.h"

using namespace kaldi;

void pybind_compose_lattice_pruned(py::module& m) {
  {
    using PyClass = ComposeLatticePrunedOptions;
    py::class_<PyClass>(m, "ComposeLatticePrunedOptions")
      .def(py::init<>());
  }
  m.def("ComposeCompactLatticePruned", &ComposeCompactLatticePruned, py::arg("opts"), py::arg("clat"),py::arg("det_fst"), py::arg("composed_clat"),
    py::return_value_policy::take_ownership);




}
