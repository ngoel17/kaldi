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
#include "online2/online_nnet2_feature_pipeline_pybind.h"

#include "online2/online-nnet2-feature-pipeline.h"


using namespace kaldi;

void pybind_online_nnet2_feature_pipeline(py::module& m) {

  {
    using PyClass = OnlineNnet2FeaturePipelineConfig;
    py::class_<PyClass>(m, "OnlineNnet2FeaturePipelineConfig")
      .def(py::init<>());
  }
  {
    using PyClass = OnlineNnet2FeaturePipelineInfo;
    py::class_<PyClass>(m, "OnlineNnet2FeaturePipelineInfo")
      .def(py::init<>())
      .def(py::init<const OnlineNnet2FeaturePipelineConfig &>(),py::arg("config"))
      //.def_readwrite("ivector_extractor_info", &PyClass::ivector_extractor_info)
      .def_readwrite("global_cmvn_stats_rxfilename", &PyClass::global_cmvn_stats_rxfilename)
      .def_readwrite("silence_weighting_config", &PyClass::silence_weighting_config);
  }
  {
    using PyClass = OnlineNnet2FeaturePipeline;
    py::class_<PyClass,OnlineFeatureInterface>(m, "OnlineNnet2FeaturePipeline")
      .def(py::init<OnlineNnet2FeaturePipelineInfo &>(),py::arg("info"))
      .def("UpdateFrameWeights",&PyClass::UpdateFrameWeights,py::arg("delta_weights"))
      .def("SetAdaptationState",&PyClass::SetAdaptationState,py::arg("adaptation_state"))
      .def("GetAdaptationState",&PyClass::GetAdaptationState,py::arg("adaptation_state"))
      .def("SetCmvnState",&PyClass::SetCmvnState,py::arg("cmvn_state"))
      .def("GetCmvnState",&PyClass::GetCmvnState,py::arg("cmvn_state"))
      .def("AcceptWaveform",&PyClass::AcceptWaveform,py::arg("sampling_rate"),py::arg("waveform"))
      .def("FrameShiftInSeconds",&PyClass::FrameShiftInSeconds)
      .def("InputFinished",&PyClass::InputFinished)
      //.def("IvectorFeature",&PyClass::IvectorFeature)
      .def("InputFeature",&PyClass::InputFeature);

  }
}
