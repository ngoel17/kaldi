'''
______________________________________________________________________________________________
                              ERROR
______________________________________________________________________________________________

__init__(): incompatible constructor arguments. The following argument types are supported:
    1. kaldi_pybind.fst.BackoffDeterministicOnDemandStdFst(fst: kaldi_pybind.fst.StdFst)

Invoked with: kwargs: fst=<kaldi_pybind.fst.StdVectorFst object at 0x7faa92d15c38>

______________________________________________________________________________________________
'''
import kaldi
from kaldi import fst

def lm_rescorer(lm_to_subtract_rxfilename, lm_to_add_rxfilename, lats_rspecifier, lats_wspecifier):
    try:
        lm_scale = 1.0;
        acoustic_scale = 1.0;
        
        lm_to_subtract_fst = fst.ReadAndPrepareLmFst(rxfilename=lm_to_subtract_rxfilename)
        
        
        #read ConstArpaLm
        ki = kaldi.Input()
        is_opened,x1 = ki.Open(lm_to_add_rxfilename, read_header=True)

        const_arpa = kaldi.ConstArpaLm()
        const_arpa.Read(ki.Stream(), binary=True)
        ki.Close()
        
        lm_to_add = kaldi.ConstArpaLmDeterministicFst(const_arpa)

        '''
        fst::BackoffDeterministicOnDemandFst<StdArc> lm_to_subtract_det_backoff(*lm_to_subtract_fst);
        fst::ScaleDeterministicOnDemandFst lm_to_subtract_det_scale(-lm_scale, &lm_to_subtract_det_backoff)
        #pybind:-
        '''

        lm_to_subtract_det_backoff=fst.BackoffDeterministicOnDemandStdFst(lm_to_subtract_fst)
        lm_to_subtract_det_scale= fst.ScaleDeterministicOnDemandStdFst(-lm_scale, lm_to_subtract_det_backoff)
    

        writer = kaldi.CompactLatticeWriter(lattice_rescore)
        data = dict()
        reader = kaldi.SequentialCompactLatticeReader(lattice_all)
        for key, value in reader:
            data[key] = value.Copy()
            kaldi.TopSortCompactLatticeIfNeeded(data[key])
            combined_lms=kaldi.ComposeDeterministicOnDemandFst(lm_to_subtract_det_scale, lm_to_add)
            
            kaldi.ComposeCompactLatticePruned(compose_opts,clat,combined_lms,composed_clat)
            writer.Write(key,composed_clat)
        reader.Close()
        writer.Close()
    except Exception as e:
        print(e)



if __name__ == "__main__":
    old_lm="G.prj.fst"
    new_lm="G.carpa"
    lattice_all='ark:lat_all.ark'
    lattice_rescore='ark:lat_rescore.ark'

    lm_rescorer(old_lm, new_lm ,lattice_all,lattice_rescore)
    

