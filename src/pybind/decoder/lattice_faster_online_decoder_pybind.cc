// pybind/decoder/lattice_faster_decoder_pybind.h

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

#include "decoder/lattice_faster_online_decoder_pybind.h"
#include "decoder/lattice_faster_decoder_pybind.h"
#include "decoder/lattice-faster-decoder.h"
#include "decoder/lattice-faster-online-decoder.h"
#include "fst/fst.h"

using namespace kaldi;

namespace {

template <typename FST, typename Token = decoder::StdToken>
void pybind_lattice_faster_online_decoder_impl(
    py::module& m, const std::string& class_name,
    const std::string& class_help_doc = "") {
  using PyClass = LatticeFasterOnlineDecoderTpl<FST>;
  py::class_<PyClass,LatticeFasterDecoderTpl<FST, decoder::BackpointerToken>>(m, class_name.c_str(), class_help_doc.c_str())
      .def(py::init<const FST&, const LatticeFasterDecoderConfig&>(),
         "Instantiate this class once for each thing you have to decode. "
         "This version of the constructor does not take ownership of 'fst'.",
         py::arg("fst"), py::arg("config"))
    
      .def("GetBestPath",&PyClass::GetBestPath, py::arg("ofst"), py::arg("use_final_probs")= true);
 
}

  }  // namespace

void pybind_lattice_faster_online_decoder(py::module& m) {
  
  pybind_lattice_faster_online_decoder_impl<fst::StdFst>(
							 m, "LatticeFasterOnlineDecoder",
							  R"doc(This is the "normal" lattice-generating decoder.
See `lattices_generation` `decoders_faster` and `decoders_simple`
for more information.

The decoder is templated on the FST type and the token type.  The token type
will normally be StdToken, but also may be BackpointerToken which is to support
quick lookup of the current best path (see lattice-faster-online-decoder.h)

The FST you invoke this decoder which is expected to equal
Fst::Fst<fst::StdArc>, a.k.a. StdFst, or GrammarFst.  If you invoke it with
FST == StdFst and it notices that the actual FST type is
fst::VectorFst<fst::StdArc> or fst::ConstFst<fst::StdArc>, the decoder object
will internally cast itself to one that is templated on those more specific
types; this is an optimization for speed.)doc");
}
