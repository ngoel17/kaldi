// online2/online-wav-nnet3-latgen2.cc

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

#include "online2/online-wav-nnet3-latgen-n.h"
#include <string>
#include <algorithm>

namespace kaldi {
  void GetDiagnosticsAndPrintOutput2(const std::string &utt,
				     const fst::SymbolTable *word_syms,
				     const CompactLattice &clat,
				     int64 *tot_num_frames,
				     double *tot_like) {
    if (clat.NumStates() == 0) {
      KALDI_WARN << "Empty lattice.";
      return;
    }
    CompactLattice best_path_clat;
    CompactLatticeShortestPath(clat, &best_path_clat);

    Lattice best_path_lat;
    ConvertLattice(best_path_clat, &best_path_lat);

    double likelihood;
    LatticeWeight weight;
    int32 num_frames;
    std::vector<int32> alignment;
    std::vector<int32> words;
    GetLinearSymbolSequence(best_path_lat, &alignment, &words, &weight);
    num_frames = alignment.size();
    likelihood = -(weight.Value1() + weight.Value2());
    *tot_num_frames += num_frames;
    *tot_like += likelihood;
    KALDI_VLOG(2) << "Likelihood per frame for utterance " << utt << " is "
		  << (likelihood / num_frames) << " over " << num_frames
		  << " frames, = " << (-weight.Value1() / num_frames)
		  << ',' << (weight.Value2() / num_frames);

    if (word_syms != NULL) {
      std::cerr << utt << ' ';
      for (size_t i = 0; i < words.size(); i++) {
	std::string s = word_syms->Find(words[i]);
	if (s == "")
	  KALDI_ERR << "Word-id " << words[i] << " not in symbol table.";
	std::cerr << s << ' ';
      }
      std::cerr << std::endl;
    }

  }
  void LatRescore(fst::ScaleDeterministicOnDemandFst &lm_to_subtract_det_scale,
		  fst::DeterministicOnDemandFst<fst::StdArc> &lm_to_add,
		  CompactLattice &clat, CompactLattice *composed_clat){
    
    ComposeLatticePrunedOptions compose_opts;

    TopSortCompactLatticeIfNeeded(&clat);
  

    // To avoid memory gradually increasing with time, we reconstruct the
    // composed-LM FST for each lattice we process.
    //   It shouldn't make a difference in which order we provide the
    // arguments to the composition; either way should work.  They are both
    // acceptors so the result is the same either way.
    fst::ComposeDeterministicOnDemandFst<fst::StdArc> combined_lms(&lm_to_subtract_det_scale, &lm_to_add);
  
    ComposeCompactLatticePruned(compose_opts,
				clat,
				&combined_lms,
				composed_clat);
    KALDI_LOG <<"Rescoring successfull";
    //delete lm_to_subtract_fst;
    //delete lm_to_add_fst;

    //delete lm_to_add;

  }

  void generateLattice(Vector<BaseFloat> data,
		       BaseFloat samp_freq,
		       std::vector<CompactLattice *> clat_vec){
    
    OnlineNnet2FeaturePipelineConfig feature_opts;
    nnet3::NnetSimpleLoopedComputationOptions decodable_opts;
    decodable_opts.frame_subsampling_factor=3;
    decodable_opts.acoustic_scale=1.0;
    LatticeFasterDecoderConfig decoder_opts;
    //nnet3::DecodableNnetSimpleLoopedInfo decodable_info_;
    OnlineEndpointConfig endpoint_opts;
    BaseFloat chunk_length_secs;
    bool do_endpointing;
    bool online;
    Matrix<double> global_cmvn_stats;
    TransitionModel trans_model;
    nnet3::AmNnetSimple am_nnet;
    OnlineTimingStats timing_stats;
    //CompactLattice clat;


    std::string config;
		

    //-------------------------------------------------------------------------------------------------------CONSTRUCTOR CODE------------
    std::string config_rxfilename = "/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/conf/online.conf";
    std::string word_syms_rxfilename = "/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/graph_0/words.txt";
    std::string nnet3_rxfilename = "/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/graph_0/final.mdl";
    std::string fst_rxfilename = "/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/graph_0/HCLG.fst";
    chunk_length_secs = 0.18;
    word_syms_rxfilename ="/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/graph_0/words.txt";
	  
    using namespace kaldi;
    using namespace fst;


    typedef kaldi::int32 int32;
    typedef kaldi::int64 int64;

    chunk_length_secs = 0.18;
    do_endpointing = false;
    online = false;

    int32 num_done = 0, num_err = 0;
    double tot_like = 0.0;
    int64 num_frames = 0;

    config = config_rxfilename;


    //---------------------------config--------------------------
    feature_opts.global_cmvn_stats_rxfilename="/mnt1/AudioBurst.OnDemand/InitScripts/../ASR/ivector_extractor/global_cmvn.stats";
    feature_opts.mfcc_config="/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/conf/mfcc.conf";
    feature_opts.ivector_extraction_config = "/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/conf/ivector_extractor.conf";
    decoder_opts.max_active = 7000;
    decoder_opts.beam = 15.0;

    //------------------------------------------------------------
    OnlineNnet2FeaturePipelineInfo feature_info(feature_opts);

    if (!online) {
      feature_info.ivector_extractor_info.use_most_recent_ivector = true;
      feature_info.ivector_extractor_info.greedy_ivector_extractor = true;
      chunk_length_secs = -1.0;
    }
        
    feature_info.global_cmvn_stats_rxfilename = "/mnt1/AudioBurst.OnDemand/InitScripts/../ASR/ivector_extractor/global_cmvn.stats";
        


    if (feature_info.global_cmvn_stats_rxfilename != "")
      ReadKaldiObject(feature_info.global_cmvn_stats_rxfilename,
		      &global_cmvn_stats);
        
    {
      bool binary;
      Input ki(nnet3_rxfilename, &binary);
      trans_model.Read(ki.Stream(), binary);
      am_nnet.Read(ki.Stream(), binary);
      SetBatchnormTestMode(true, &(am_nnet.GetNnet()));
      SetDropoutTestMode(true, &(am_nnet.GetNnet()));
      nnet3::CollapseModel(nnet3::CollapseModelConfig(), &(am_nnet.GetNnet()));
    }

    // this object contains precomputed stuff that is used by all decodable
    // objects.  It takes a pointer to am_nnet because if it has iVectors it has
    // to modify the nnet to accept iVectors at intervals.
    //      decodable_info = nnet3::DecodableNnetSimpleLoopedInfo(decodable_opts, &am_nnet);
    nnet3::DecodableNnetSimpleLoopedInfo decodable_info(decodable_opts, &am_nnet);
      
	  
    fst::Fst<fst::StdArc> *decode_fst = ReadFstKaldiGeneric(fst_rxfilename);

    fst::SymbolTable *word_syms = NULL;
    if (word_syms_rxfilename != "")
      if (!(word_syms = fst::SymbolTable::ReadText(word_syms_rxfilename)))
	KALDI_ERR << "Could not read symbol table from file "
		  << word_syms_rxfilename;

    //--------Rescoring Code ---------------------
    std::string lm_to_subtract_rxfilename = "/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/graph_0/G.prj.fst";
    std::string lm_to_add_rxfilename = "/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/graph_0/G.carpa" ;
    fst::VectorFst<fst::StdArc> *lm_to_subtract_fst = fst::ReadAndPrepareLmFst(
									       lm_to_subtract_rxfilename);
    BaseFloat lm_scale = 1.0;
    ConstArpaLm const_arpa;
    ReadKaldiObject(lm_to_add_rxfilename, &const_arpa);
    fst::BackoffDeterministicOnDemandFst<fst::StdArc> lm_to_subtract_det_backoff(*lm_to_subtract_fst);
    fst::ScaleDeterministicOnDemandFst lm_to_subtract_det_scale(-lm_scale, &lm_to_subtract_det_backoff);
    fst::DeterministicOnDemandFst<fst::StdArc> *lm_to_add = NULL;
    lm_to_add = new ConstArpaLmDeterministicFst(const_arpa);

    //    ConstArpaLmDeterministicFst lm_to_add(const_arpa);
    //----------------------------------------------------
	
    OnlineIvectorExtractorAdaptationState adaptation_state(
							   feature_info.ivector_extractor_info);
    OnlineCmvnState cmvn_state(global_cmvn_stats);

    int segmentLength=15;
    int segmentStep=10;
    int s = samp_freq*segmentStep;
    int a = samp_freq*segmentLength;
    int b = data.Dim();
    int end = std::min(a,b);
    int start = 0;
    CompactLattice clat;
    while (end < data.Dim()) {
      CompactLattice *composed_clat = new CompactLattice;

      SubVector<BaseFloat> wav(data,start,end);
      OnlineNnet2FeaturePipeline feature_pipeline(feature_info);


      feature_pipeline.SetAdaptationState(adaptation_state);

      feature_pipeline.SetCmvnState(cmvn_state);

      OnlineSilenceWeighting silence_weighting(
					       trans_model,
					       feature_info.silence_weighting_config,
					       decodable_opts.frame_subsampling_factor);

      SingleUtteranceNnet3Decoder decoder(decoder_opts, trans_model,
					  decodable_info,
					  *decode_fst, &feature_pipeline);
      //      OnlineTimer decoding_timer(utt);


      //BaseFloat samp_freq = wave_data.SampFreq();
      int32 chunk_length;
      if (chunk_length_secs > 0) {
	chunk_length = int32(samp_freq * chunk_length_secs);
	if (chunk_length == 0) chunk_length = 1;
      } else {
	chunk_length = std::numeric_limits<int32>::max();
      }

      int32 samp_offset = 0;
      std::vector<std::pair<int32, BaseFloat> > delta_weights;
      while (samp_offset < wav.Dim()) {

	int32 samp_remaining = wav.Dim() - samp_offset;
	int32 num_samp = chunk_length < samp_remaining ? chunk_length: samp_remaining;

	SubVector<BaseFloat> wave_part(wav, samp_offset, num_samp);
	feature_pipeline.AcceptWaveform(samp_freq, wave_part);

	samp_offset += num_samp;
	//	decoding_timer.WaitUntil(samp_offset / samp_freq);
	if (samp_offset == wav.Dim()) {
	  // no more input. flush out last frames
	  feature_pipeline.InputFinished();
	}
		  
		  
	if (silence_weighting.Active() &&
	    feature_pipeline.IvectorFeature() != NULL) {
	  silence_weighting.ComputeCurrentTraceback(decoder.Decoder());
	  silence_weighting.GetDeltaWeights(feature_pipeline.NumFramesReady(),
					    &delta_weights);
	  feature_pipeline.IvectorFeature()->UpdateFrameWeights(delta_weights);
	}

	decoder.AdvanceDecoding();

	if (do_endpointing && decoder.EndpointDetected(endpoint_opts)) {
	  break;
	}
      }
      decoder.FinalizeDecoding();
		
      bool end_of_utterance = true;
      decoder.GetLattice(end_of_utterance, &clat);
      std::string utt = std::to_string(start);
      GetDiagnosticsAndPrintOutput2(utt, word_syms, clat,&num_frames, &tot_like);

      //      decoding_timer.OutputStats(&timing_stats);

      // In an application you might avoid updating the adaptation state if
      // you felt the utterance had low confidence.  See lat/confidence.h
      feature_pipeline.GetAdaptationState(&adaptation_state);

      feature_pipeline.GetCmvnState(&cmvn_state);

      // we want to output the lattice with un-scaled acoustics.
      BaseFloat inv_acoustic_scale =
	1.0 / decodable_opts.acoustic_scale;
      ScaleLattice(fst::AcousticLatticeScale(inv_acoustic_scale), &clat);
      KALDI_LOG<< "LATTICE GENERATION SUCESSFULL ";
      LatRescore(lm_to_subtract_det_scale,*lm_to_add,clat,composed_clat);
      clat_vec.push_back(composed_clat);
		
      //delete decode_fst;
      //delete word_syms;
      //---------------------------------------------------Rescore Starts
		

      //---------------------------------------------------Rescore Ends
      start=start+s;
      end=std::min(end+s,data.Dim());
      
    }


    

  }
	
}// namespace kaldi
