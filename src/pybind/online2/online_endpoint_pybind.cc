//  pybind/online2/online_nnet2_feature_pipeline_pybind.cc

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
#include "online2/online_endpoint_pybind.h"

#include "online2/online-endpoint.h"


using namespace kaldi;

void pybind_online_endpoint(py::module& m) {

  {
    using PyClass = OnlineEndpointConfig;
    py::class_<PyClass>(m, "OnlineEndpointConfig")
      .def(py::init<>());
  }
  //m.def("EndpointDetected", &EndpointDetected, py::arg("config"), py::arg("num_frames_decoded"),py::arg("trailing_silence_frames"), py::arg("frame_shift_in_seconds"), py::arg("final_relative_cost"));
  
}
