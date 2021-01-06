//  pybind/online2/online_ivector_feature_pybind.cc

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
#include "online2/online_ivector_feature_pybind.h"

#include "online2/online-ivector-feature.h"


using namespace kaldi;

void pybind_online_ivector_feature(py::module& m) {

  {
    using PyClass = OnlineIvectorExtractionConfig;
    py::class_<PyClass>(m, "OnlineIvectorExtractionConfig")
      .def(py::init<>());
  }
  {
    using PyClass = OnlineIvectorExtractionInfo;
    py::class_<PyClass>(m, "OnlineIvectorExtractionInfo")
      .def(py::init<const OnlineIvectorExtractionConfig &>(),py::arg("config"))
      .def_readwrite("use_most_recent_ivector", &PyClass::use_most_recent_ivector)
      .def_readwrite("greedy_ivector_extractor", &PyClass::greedy_ivector_extractor);
  }
  {
    using PyClass = OnlineIvectorExtractorAdaptationState;
    py::class_<PyClass>(m, "OnlineIvectorExtractorAdaptationState")
      .def(py::init<const OnlineIvectorExtractionInfo &>(),py::arg("info"))
      .def(py::init<const OnlineIvectorExtractorAdaptationState &>(),py::arg("other"));
  }


  {
    using PyClass = OnlineSilenceWeightingConfig;
    py::class_<PyClass>(m, "OnlineSilenceWeightingConfig")
      .def(py::init<>());
  }
  {
    using PyClass = OnlineSilenceWeighting;
    py::class_<PyClass>(m, "OnlineSilenceWeighting")
      .def(py::init<const TransitionModel &, const OnlineSilenceWeightingConfig &, int32>(),py::arg("trans_model"),py::arg("config"),py::arg("frame_subsampling_factor"))
      .def("Active",&PyClass::Active);
      //.def("ComputeCurrentTraceback",&PyClass::ComputeCurrentTraceback<fst::StdArc>,py::arg("decoder"),py::arg("use_final_probs")= false)
      //.def("GetDeltaWeights",&PyClass::GetDeltaWeights,py::arg("num_frames_ready"),py::arg("first_decoder_frame"),py::arg("delta_weights"))
      //.def("GetDeltaWeights",&PyClass::GetDeltaWeights,py::arg("num_frames_ready"),py::arg("delta_weights"));
  }
}
