// online2/online-wav-nnet3-latgen2.h

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
#ifndef KALDI_ONLINE2_ONLINE_WAV_NNET3_LATGEN_H_
#define KALDI_ONLINE2_ONLINE_WAV_NNET3_LATGEN_H_

#include "feat/wave-reader.h"
#include "online2/online-nnet3-decoding.h"
#include "online2/online-nnet2-feature-pipeline.h"
#include "online2/onlinebin-util.h"
#include "online2/online-timing.h"
#include "online2/online-endpoint.h"
#include "fstext/fstext-lib.h"
#include "lat/lattice-functions.h"
#include "util/kaldi-thread.h"
#include "nnet3/nnet-utils.h"

#include "fstext/lattice-utils.h"
//---
#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "fstext/fstext-lib.h"
#include "fstext/kaldi-fst-io.h"
#include "lm/const-arpa-lm.h"
#include "lat/kaldi-lattice.h"
#include "lat/lattice-functions.h"
#include "lat/compose-lattice-pruned.h"
#include "fstext/kaldi-fst-io-inl.h"
namespace kaldi {

  void generateLattice(Vector<BaseFloat> data,
                       BaseFloat samp_freq,
                       std::vector<CompactLattice *> clat_vec);
  		
  /* void GetDiagnosticsAndPrintOutput2(const std::string &utt, */
  /* 				    const fst::SymbolTable *word_syms, */
  /* 				    const CompactLattice &clat, */
  /* 				    int64 *tot_num_frames, */
  /* 				    double *tot_like); */
  //  Void LatRescore(CompactLattice &clat);

} // namespace kaldi
#endif  // KALDI_ONLINE2_ONLINE_WAV_NNET3_LATGEN_H_
