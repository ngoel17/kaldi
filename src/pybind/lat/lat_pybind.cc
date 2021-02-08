// pybind/lat/lat_pybind.cc

// Copyright 2020   Mobvoi AI Lab, Beijing, China
//                  (author: Fangjun Kuang, Yaguang Hu, Jian Wang)

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

#include "lat/lat_pybind.h"
#include "lat/sausages_pybind.h"
#include "lat/kaldi_lattice_pybind.h"
#include "lat/lattice_functions_pybind.h"
#include "lat/word_align_lattice_pybind.h"
#include "compose_lattice_pruned.h"

void pybind_lat(py::module& m) {
  pybind_kaldi_lattice(m);
  pybind_word_align_lattice(m);
  pybind_lattice_functions(m);
  pybind_sausages(m);
  pybind_compose_lattice_pruned(m);

  // pybind_determinize_lattice_pruned is wrapped in fst/fst_pybind.cc
  // since it is in the `fst` namespace
}
