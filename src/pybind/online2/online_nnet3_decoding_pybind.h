// pybind/online2/online_nnet3_decoding_pybind.h

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

#ifndef KALDI_PYBIND_ONLINE2_ONLINE_NNET3_DECODING_PYBIND_H_
#define KALDI_PYBIND_ONLINE2_ONLINE_NNET3_DECODING_PYBIND_H_

#include "pybind/kaldi_pybind.h"
#include "online2/online-nnet3-decoding.h"
using namespace kaldi;
template <typename FST>
void pybind_single_utterance_nnet_decoder_tpl(py::module& m, const char* name) {
  using PyClass = kaldi::SingleUtteranceNnet3DecoderTpl<FST>;
  py::class_<PyClass, std::unique_ptr<PyClass, py::nodelete>> pyclass(m, name);
  pyclass.def(py::init<const LatticeFasterDecoderConfig &, const TransitionModel &, const nnet3::DecodableNnetSimpleLoopedInfo &, const FST &, OnlineNnet2FeaturePipeline *>(), py::arg("decoder_opts"), py::arg("trans_model"), py::arg("info"), py::arg("fst"), py::arg("features"));
  pyclass.def("InitDecoding",&PyClass::InitDecoding, py::arg("frame_offset"));
  pyclass.def("AdvanceDecoding",&PyClass::AdvanceDecoding);
  pyclass.def("FinalizeDecoding",&PyClass::FinalizeDecoding);
  pyclass.def("NumFramesDecoded",&PyClass::NumFramesDecoded);
  pyclass.def("GetLattice",&PyClass::GetLattice, py::arg("end_of_utterance"), py::arg("clat"));
  pyclass.def("GetBestPath",&PyClass::GetBestPath, py::arg("end_of_utterance"), py::arg("best_path"));
  pyclass.def("EndpointDetected",&PyClass::EndpointDetected, py::arg("config"));

  /* KALDI code
     const LatticeFasterOnlineDecoderTpl<FST> &Decoder() const { return decoder_; }
  */

  
   pyclass.def("Decoder",overload_cast_<>()(&PyClass::Decoder<fst::StdArc>, py::const_));
  
   pyclass.def("Decoder",&PyClass::Decoder);
}
void pybind_online_nnet3_decoding(py::module& m);

#endif  // KALDI_PYBIND_ONLINE2_ONLINE_NNET3_DECODING_PYBIND_H_
