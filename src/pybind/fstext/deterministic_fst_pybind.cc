// pybind/fstext/deterministic_fst_pybind.cc

// Copyright 2020 GoVivace Inc. (Author: Shivani Saini)
//                Xiaomi Corporation (Author: Fangjun Kuang)

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

#include "fstext/deterministic_fst_pybind.h"
using namespace fst;
static void pybind_scale_deterministic_on_demand_fst(py::module& m) {
  using PyClass = fst::ScaleDeterministicOnDemandFst;
  py::class_<PyClass, fst::DeterministicOnDemandFst<fst::StdArc>> pyclass(
      m, "ScaleDeterministicOnDemandStdFst");
  pyclass.def(py::init<float, fst::DeterministicOnDemandFst<fst::StdArc>*>(),
              py::arg("scale"), py::arg("det_fst"));
}

void pybind_deterministic_fst(py::module& m) {
  pybind_deterministic_on_demand_fst<fst::StdArc>(
						  m, "","DeterministicOnDemandStdFst");

  pybind_backoff_deterministic_on_demand_fst<fst::StdArc>(
							  m, "","BackoffDeterministicOnDemandStdFst");
  
  pybind_compose_deterministic_on_demand_fst<fst::StdArc>(
							  m, "", "ComposeDeterministicOnDemandStdFst");

  pybind_scale_deterministic_on_demand_fst(m);
}
