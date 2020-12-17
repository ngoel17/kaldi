// pybind/fstext/deterministic_fst_pybind.cc

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

#include "pybind/kaldi_pybind.h"


#include "fstext/deterministic-fst.h"
//#include "fstext/deterministic-fst-inl.h"
#include "fstext/deterministic_fst_pybind.h"

#include "fst/arc_pybind.h"
#include "fst/fst_pybind.h"
#include "fst/vector_fst_pybind.h"
#include "fstext/lattice-weight.h"
#include "lat/kaldi-lattice.h"
#include "util/kaldi_table_pybind.h"

void pybind_deterministic_on_demand_fst(py::module& m) {
  
  /*
  py::class_<DeterministicOnDemandFst<fst::StdArc>>(m, "DeterministicOnDemandFst")
    .def("Start", &DeterministicOnDemandFst<fst::StdArc>::Start)
    .def("Final", &DeterministicOnDemandFst<fst::StdArc>::Final)
    .def("GetArc", &DeterministicOnDemandFst<fst::StdArc>::GetArc);
  */
  /*
  py::class_<BackoffDeterministicOnDemandFst<fst::StdArc>,DeterministicOnDemandFst<fst::StdArc>>(m,"BackoffDeterministicOnDemandFst")
    .def(py::init<const Fst<fst::StdArc>&>(),py::arg("fst"));

  */
  py::class_<ScaleDeterministicOnDemandFst,DeterministicOnDemandFst<fst::StdArc>>(m,"ScaleDeterministicOnDemandFst")
    .def(py::init<float,DeterministicOnDemandFst<fst::StdArc>>(),py::arg("scale"),py::arg("det_fst"));
}






















/*
void pybind_scale_deterministic_on_demand_fst(py::module& m){
  {
    using PyClass = ScaleDeterministicOnDemandFst;
    py::class_<PyClass,DeterministicOnDemandFst<fst::StdArc>>(m,"ScaleDeterministicOnDemandFst")
    .def(py::init<float,DeterministicOnDemandFst<fst::StdArc>>(),py::arg("scale"),py::arg("det_fst"), py::return_value_policy::reference);
  }
  }
*/
