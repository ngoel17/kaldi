//  pybind/lat/word_align_lattice_pybind.cc

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


#include "lat/word-align-lattice.h"
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

void pybind_word_align_lattice(py::module& m) {
  
  //m.def("WordAlignLattice", &WriteLattice);
  {
    using PyClass = WordBoundaryInfoOpts;
    py::class_<PyClass>(m, "WordBoundaryInfoOpts")
      .def(py::init<>());
  }
  {
    using PyClass = WordBoundaryInfoNewOpts;
    py::class_<PyClass>(m, "WordBoundaryInfoNewOpts")
      .def(py::init<>());
  }
  {
    using PyClass = WordBoundaryInfo;
    py::class_<PyClass>(m, "WordBoundaryInfo")
      .def(py::init<const WordBoundaryInfoNewOpts &>(),py::arg("opts"))
      .def(py::init<const WordBoundaryInfoNewOpts & , std::string >(),py::arg("opts"),py::arg("word_boundary_file"));
  }
  m.def("WordAlignLattice", &WordAlignLattice, py::arg("lat"), py::arg("tmodel"),py::arg("info"), py::arg("max_states"), py::arg("lat_out"),
    py::return_value_policy::take_ownership);



}
