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

  class Lattice_Generation{
	public:	
		Lattice_Generation(std::string nnet3_rxfilename,
							std::string fst_rxfilename,
				   std::string word_syms_rxfilename,
				   std::string config_rxfilename);
		
		void LatRescore(CompactLattice &clat);
							
		void generate(std::string spk,
			      std::vector<std::string> uttlist,
			      Vector<BaseFloat> wave_data,
			      BaseFloat samp_freq,
			      nnet3::NnetSimpleLoopedComputationOptions decodable_opts,
			      nnet3::DecodableNnetSimpleLoopedInfo decodable_info,
			      CompactLattice &clat);
		
		void GetDiagnosticsAndPrintOutput(const std::string &utt,
                                  const fst::SymbolTable *word_syms,
                                  const CompactLattice &clat,
                                  int64 *tot_num_frames,
                                  double *tot_like);
    private :
		OnlineNnet2FeaturePipelineConfig feature_opts;
                OnlineNnet2FeaturePipelineInfo feature_info;
                //nnet3::NnetSimpleLoopedComputationOptions decodable_opts;
                LatticeFasterDecoderConfig decoder_opts;
		//nnet3::DecodableNnetSimpleLoopedInfo decodable_info_;
                OnlineEndpointConfig endpoint_opts;
                BaseFloat chunk_length_secs;
                bool do_endpointing;
                bool online;
                int32 num_done , num_err ;
                double tot_like;
                int64 num_frames;
		bool initialized=false;
		OnlineIvectorExtractorAdaptationState* astate;
                Matrix<double> global_cmvn_stats;
                TransitionModel trans_model;
                nnet3::AmNnetSimple am_nnet;
                OnlineTimingStats timing_stats;
                //CompactLattice clat;
                fst::SymbolTable *word_syms;

		fst::Fst<fst::StdArc> *decode_fst;

		std::string config;
		
};
} // namespace kaldi
#endif  // KALDI_ONLINE2_ONLINE_WAV_NNET3_LATGEN_H_
