''' 
_____________________________________________________________________________________________________
----------------LM RESCORE START-------------------
fst1 type =<class 'kaldi_pybind.fst.ScaleDeterministicOnDemandStdFst'>
fst2 type =<class 'kaldi_pybind.ConstArpaLmDeterministicFst'>

__init__(): incompatible constructor arguments. The following argument types are supported:
    1. kaldi_pybind.fst.ComposeDeterministicOnDemandStdFst(fst1: kaldi_pybind.fst.DeterministicOnDemandStdFst, fst2: kaldi_pybind.fst.DeterministicOnDemandStdFst)

Invoked with: <kaldi_pybind.fst.ScaleDeterministicOnDemandStdFst object at 0x7f1cf9923228>, <kaldi_pybind.ConstArpaLmDeterministicFst object at 0x7f1cf9923148>
exception
----------------LM RESCORE END-------------------
_____________________________________________________________________________________________________
'''
import kaldi
from kaldi import fst

def lm_rescorer(lm_to_subtract_rxfilename, lm_to_add_rxfilename, lats_rspecifier, lats_wspecifier):
    try:
        lm_scale = 1.0;
        acoustic_scale = 1.0;
        
        lm_to_subtract_fst = fst.ReadAndPrepareLmFst(rxfilename=lm_to_subtract_rxfilename)

        ki = kaldi.Input()
        is_opened,x1 = ki.Open(lm_to_add_rxfilename, read_header=True)

        const_arpa = kaldi.ConstArpaLm()
        const_arpa.Read(ki.Stream(), binary=True)
        ki.Close()
        
        lm_to_add = kaldi.ConstArpaLmDeterministicFst(const_arpa)
        
        lm_to_subtract_det_backoff=fst.BackoffDeterministicOnDemandStdFst(fst=lm_to_subtract_fst)
        
        lm_to_subtract_det_scale= fst.ScaleDeterministicOnDemandStdFst(-lm_scale, lm_to_subtract_det_backoff)
    

        writer = kaldi.CompactLatticeWriter(lattice_rescore)
        data = dict()
        reader = kaldi.SequentialCompactLatticeReader(lattice_all)
        for key, value in reader:
            data[key] = value.Copy()
            kaldi.TopSortCompactLatticeIfNeeded(data[key])
            '''
            fst::ComposeDeterministicOnDemandFst<StdArc> combined_lms(&lm_to_subtract_det_scale, lm_to_add);
            #pybind:-
            '''
            print("fst1 type ={}".format(type(lm_to_subtract_det_scale)))
            print("fst2 type ={}".format(type(lm_to_add)))
            combined_lms=fst.ComposeDeterministicOnDemandStdFst(lm_to_subtract_det_scale, lm_to_add)
            
            
            kaldi.ComposeCompactLatticePruned(compose_opts,clat,combined_lms,composed_clat)
            writer.Write(key,composed_clat)
        reader.Close()
        writer.Close()
    except Exception as e:
        print(e)
        print("exception")
    return 1

if __name__ == "__main__":
    old_lm="/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/graph_0/G.prj.fst"
    new_lm="/home/ubuntu/project_ASR/ab-ondemand-standalone/ASR/graph_0/G.carpa"
    lattice_all='ark:/tmp/audioburst/ASR/1_0//data/split1//..//lat_all.ark'
    lattice_rescore='ark:/tmp/audioburst/ASR/1_0//data/split1//..//lat_rescore.ark'
    print("----------------LM RESCORE START-------------------")
    temp=lm_rescorer(old_lm, new_lm ,lattice_all,lattice_rescore)
    print("----------------LM RESCORE END-------------------")
