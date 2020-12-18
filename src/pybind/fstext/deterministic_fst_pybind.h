// pybind/fstext/deterministic_fst_inl_pybind.h

// Copyright 2020 GoVivace Inc. (Author: Shivani Saini)
//                Xiaomi Corporation (Author: Fangjun Kuang)

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

#include "fstext/deterministic-fst.h"
#include "pybind/kaldi_pybind.h"

template <typename Arc>
void pybind_deterministic_on_demand_fst(py::module& m, const char* name) {
  using PyClass = fst::DeterministicOnDemandFst<Arc>;
  py::class_<PyClass, std::unique_ptr<PyClass, py::nodelete>> pyclass(m, name);
  pyclass.def("Start", &PyClass::Start);
  pyclass.def("Weight", &PyClass::Final, py::arg("s"));
  pyclass.def("GetArc", &PyClass::GetArc, py::arg("s"), py::arg("ilabel"),
              py::arg("oarc"));
}

template <typename Arc>
void pybind_backoff_deterministic_on_demand_fst(py::module& m,
                                                const char* name) {
  using PyClass = fst::BackoffDeterministicOnDemandFst<Arc>;
  py::class_<PyClass, fst::DeterministicOnDemandFst<Arc>> pyclass(m, name);
  pyclass.def(py::init<const fst::Fst<Arc>&>(), py::arg("fst"));
}

void pybind_deterministic_fst(py::module& m);

#endif  // KALDI_PYBIND_FSTEXT_DETERMINISTIC_FST_INL_PYBIND_H_
