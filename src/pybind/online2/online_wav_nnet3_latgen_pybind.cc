//  pybind/online2/online_wav_nnet3_latgen_pybind.cc

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
#include "online2/online-wav-nnet3-latgen2.h"

#include "online2/online_wav_nnet3_latgen_pybind.h"


using namespace kaldi;

void pybind_online_wav_nnet3_latgen(py::module& m) {

  {
    using PyClass = Lattice_Generation;
    py::class_<PyClass>(m, "Lattice_Generation")
      .def(py::init<std::string, std::string, std::string, std::string>(), py::arg("nnet3_rxfilename"), py::arg("fst_rxfilename"), py::arg("word_syms_rxfilename"), py::arg("config_rxfilename"))
      
      .def("generate", &PyClass::generate, py::arg("spk"),py::arg("uttlist"),py::arg("wave_data"),py::arg("samp_freq"), py::arg("decodable_opts"), py::arg("decodable_info"), py::arg("clat"));
  }
  
}
