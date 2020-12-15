// pybind/fstext/deterministic_fst_inl_pybind.h
// created by Shivani Saini,Govivace Inc.

// Copyright 2011-2012  Microsoft Corporation  Johns Hopkins University (Author: Daniel Povey)

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

#ifndef KALDI_PYBIND_FSTEXT_DETERMINISTIC_FST_PYBIND_H_
#define KALDI_PYBIND_FSTEXT_DETERMINISTIC_FST_PYBIND_H_

#include "pybind/kaldi_pybind.h"


#include "fstext/deterministic-fst.h"
//#include "fstext/deterministic-fst-inl.h"
//#include "fstext/deterministic_fst_pybind.h"

#include "lat/word_align_lattice_pybind.h"
#include "lat/kaldi_lattice_pybind.h"

#include "fst/arc_pybind.h"
#include "fst/fst_pybind.h"
#include "fst/vector_fst_pybind.h"
#include "fstext/lattice-weight.h"
#include "lat/kaldi-lattice.h"
#include "util/kaldi_table_pybind.h"


namespace fst {
template <class Arc>
void pybind_deterministic_on_demand_fst(py::module& m, const std::string& class_name,
                                const std::string& class_help_doc = "") {
  using PyClass = fst::DeterministicOnDemandFst<Arc>;
  py::class_<PyClass>(m, class_name.c_str(), class_help_doc.c_str())
      .def(py::init<>());
 }
template<class Arc>
void pybind_backoff_deterministic_on_demand_fst(py::module& m, const std::string& class_name,
                                const std::string& class_help_doc = "") {
  using PyClass = fst::BackoffDeterministicOnDemandFst<Arc>;
  py::class_<PyClass,fst::DeterministicOnDemandFst<Arc>>(m, class_name.c_str(), class_help_doc.c_str())
    .def(py::init<const Fst<Arc>&>(),py::arg("fst"));
}

void pybind_scale_deterministic_on_demand_fst(py::module& m) {
  {
    using PyClass = fst::ScaleDeterministicOnDemandFst;
    py::class_<PyClass,fst::DeterministicOnDemandFst<fst::StdArc>>(m,"fst::ScaleDeterministicOnDemandFst")
    .def(py::init<float,DeterministicOnDemandFst<fst::StdArc>>(),py::arg("scale"),py::arg("det_fst"), py::return_value_policy::reference);
  }
}


} // end namespace fst

#endif  // KALDI_PYBIND_FSTEXT_DETERMINISTIC_FST_INL_PYBIND_H_

