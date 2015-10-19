#ifndef GUARD_ZCStandardVariables_h
#define GUARD_ZCStandardVariables_h

// ZCStandardVariables.h
// Standard Variables for ZC analysis
//
// TO DO - add JSON, trigger cuts to projection cuts.
//
// CONTROL PLOT VERSION - April 2015


#include "TCut.h"
#include "TString.h"

namespace ZCStandardVariables
{

// INPUT FILE NAMES/LOCATION
  // Files containing data, signal and bkgd MC
    //TString inputLocation = "/uscms_data/d2/godshalk/2015-01_ZHbb_cp/CMSSW_5_3_23_patch1/src/step2_ntuples/";
    const TString inputLocation = "/home/godshalk/Work/2015-01_step2ntuples/";
    const TString dataLocation =  "/home/godshalk/Work/2015-04-23_step2ntuple_reproc/";
//    const TString fn_data           = inputLocation + "zcStep2_SingleMuon2012.root";         // Old muon data location.
    const TString fn_muon           = dataLocation + "muon.root"    ;
    const TString fn_elec           = dataLocation + "elec.root"    ;
    const TString fn_dy             = "/eos/uscms/store/user/godshalk/noreplica/2015-10-16_ZJNtuples/dy.root";
//    const TString fn_dy             = inputLocation + "dy.root"     ;
    const TString fn_dy1j           = inputLocation + "dy1j.root"   ;
    const TString fn_ww             = inputLocation + "ww.root"     ;
    const TString fn_wz             = inputLocation + "wz.root"     ;
    const TString fn_zz             = inputLocation + "zz.root"     ;
    const TString fn_tthad          = inputLocation + "tthad.root"  ;
    const TString fn_ttlep          = inputLocation + "ttlep.root"  ;
    const TString fn_ttsemi         = inputLocation + "ttsemi.root" ;
    const TString fn_t_s            = inputLocation + "t_s.root"    ;
    const TString fn_t_t            = inputLocation + "t_t.root"    ;
    const TString fn_t_tw           = inputLocation + "t_tw.root"   ;
    const TString fn_tbar_s         = inputLocation + "tbar_s.root" ;
    const TString fn_tbar_t         = inputLocation + "tbar_t.root" ;
    const TString fn_tbar_tw        = inputLocation + "tbar_tw.root";

// SCALE FACTORS
  // Background weights and b-tagging scale factor. Weights calculated from cross section * number of data events / number of bkgd events analyzed.
    // VV xs taken from papers cited at https://twiki.cern.ch/twiki/bin/view/CMSPublic/PhysicsResultsSMP & https://twiki.cern.ch/twiki/bin/view/CMSPublic/PhysicsResultsCombined
    const float wt_dy      = 2.27996742;      //(3503.71      *19040)/(2.925947*10**7);  xs from VHbb spreadsheet. May need to find new one.
    const float wt_ww      = 0.133085;        //( 69.9        *19040)/(1.000036*10**7);  xs from: http://arxiv.org/abs/1301.4698
    const float wt_wz      = 0.046856;        //( 24.61       *19040)/(1.000022*10**7);  xs from: http://cds.cern.ch/record/1564318
    const float wt_zz      = 0.014960;        //(  7.7        *19040)/(9.799842*10**6);  xs from: http://arxiv.org/pdf/1406.0113v2.pdf
    const float wt_tthad   = 0.0826369;       //(239.1*(36/81)*19040)/(2.448444*10**7);  xs from ttbar public results page
    const float wt_ttlep   = 0.0438557;       //(239.1*( 9/81)*19040)/(1.153394*10**7);
    const float wt_ttsemi  = 0.0807116;       //(239.1*(36/81)*19040)/(2.506849*10**7);
    const float wt_t_s     = 0.22556139034;   //(3.79         *19040)/(319920        ); xs from VHbb spreadsheet. Will need to find better numbers.
    const float wt_t_t     = 0.31976911598;   //(56.4         *19040)/(3358223       );
    const float wt_t_tw    = 0.42467974801;   //(11.1         *19040)/(497655        );
    const float wt_tbar_s  = 0.18622372142;   //(1.76         *19040)/(179947        );
    const float wt_tbar_t  = 0.10921775439;   //(30.7         *19040)/(1935070       );
    const float wt_tbar_tw = 0.99745060765;   //(11.1         *19040)/(586022        );

  // Flat scale factors for background simulation, to correct for underestimation of b-jets
    const float sf_CSVS    = 0.90;
    const float sf_CSVT    = 0.90;
    const float sf_CSVM    = 0.95;
    const float sf_CSVL    = 0.98;   // See https://twiki.cern.ch/twiki/bin/view/CMSPublic/PhysicsResultsBTV
    const float sf_CSVS_ljmis = 1.17;  // Scale factor for super tight light jet misidentification cut


// ITERATIVE CUTS
  // Muon (also includes isolation, opposite charge)
    const int    maxNumMuons = 100;    // Max number of raw muons stored in ntuples. 
    const double muonPtMin   = 20.0;  // GeV
    const double muonEtaMax  =  2.4;
  // Electron
    const int    maxNumElecs = 100;
    const double elecPtMin   = 20.0;  // GeV
    const double elecEtaInnerMax = 1.442;
    const double elecEtaOuterMin = 1.556;
    const double elecEtaOuterMax = 2.4  ; 
  // Dilepton
    const double dilepInvMassMin =  70;  // GeV
    const double dilepInvMassMax = 110;  // GeV
  // MET
    const double metMax = 40.0;
    //const double metMax = 10000000.0;
  // Jets
    const int    nJetsAnalyzed =   6;    // Number of jets analyzed in control plots, etc.
    const int    maxNumJets    = 130;    // Max number of raw jets stored in ntuples. 
    const double jetPtMin      =  30.0;  // GeV
    const double jetEtaMax     =   2.4;
  // BTagging - Operating points found at https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP
    const double csvOpPtSup = 0.950;
    const double csvOpPtTgt = 0.898;
    const double csvOpPtMed = 0.679;
    const double csvOpPtLow = 0.244;
  // Secondary Vertex Mass
    const double minSVT = 0;
    const double noSVT  = -100;
  // JSON & Trigger
    const int    jsonSelect = 1;
    const int    numTriggersSelected = 2;
    const int    triggersSelected[] = {
         0,    //"HLT_IsoMu17_v.*" , #0
        // 1,    //"HLT_DoubleMu7_v.*", #1
        // 2,    //"HLT_Mu13_Mu8_v.*", #2
        // 3,    //"HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v.*", #3
        // 4,    //"HLT_Ele27_WP80_PFMHT50_v.*", #4
        // 5,    //"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v.*", #5
         6,    //"HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v.*", #6    // <- Used in 8TeV DiffXS Z+j paper for DOuble Electron ident.
        // 7,    //"HLT_DiCentralJet20_BTagIP_MET65_v.*", #7
        // 8,    //"HLT_MET120_v.*", #8
        // 9,    //"HLT_CentralJet80_MET80_v.*", #9
        //10,    //"HLT_PFMHT150_v.*", #10
        //11,    //"HLT_DiCentralJet20_MET80_v.*", #11
        //12,    //"HLT_DiCentralJet20_MET100_HBHENoiseFiltered_v.*", #12
        //13,    //"HLT_IsoMu20_v.*", #13
        //14,    //"HLT_IsoMu24_v.*", #14
        //15,    //"HLT_IsoMu30_eta2p1_v.*", #15
        //16,    //"HLT_Mu17_Mu8_v.*", #16
        //17,    //"HLT_Ele17_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralJet30_CentralJet25_PFMHT15_v.*", #17
        //18,    //"HLT_Ele22_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralJet30_CentralJet25_PFMHT20_v.*", #18
        //19,    //"HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralJet30_CentralJet25_PFMHT20_v.*", #19
        //20,    //"HLT_Mu30_v.*", #20 
        //21,    //"HLT_Mu40_v.*", #21
        //22,    //"HLT_Mu40_eta2p1_v.*", #22
        //23,    //"HLT_IsoMu24_eta2p1_v.*", #23
        //24,    //"HLT_IsoMu17_eta2p1_DiCentralJet30_v.*", #24
        //25,    //"HLT_IsoMu17_eta2p1_DiCentralPFJet25_PFMHT15_v.*", #25
        //26,    //"HLT_Ele30_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_DiCentralJet30_PFMHT25_v.*", #26
        //27,    //"HLT_Ele27_WP80_DiCentralPFJet25_PFMHT15_v.*", #27
        //28,    //"HLT_IsoPFTau35_Trk20_v.*", #28
        //29,    //"HLT_IsoPFTau35_Trk20_MET45_v.*", #29
        //30,    //"HLT_IsoPFTau35_Trk20_MET60_v.*", #30
        //31,    //"HLT_IsoPFTau45_Trk20_MET60_v.*", #31
        //32,    //"HLT_IsoPFTau35_Trk20_MET70_v.*", #32
        //33,    //"HLT_MediumIsoPFTau35_Trk20_v.*", #33
        //34,    //"HLT_MediumIsoPFTau35_Trk20_MET60_v.*", #34
        //35,    //"HLT_MediumIsoPFTau35_Trk20_MET70_v.*", #35
        //36,    //"HLT_LooseIsoPFTau35_Trk20_v.*", #36
        //37,    //"HLT_LooseIsoPFTau35_Trk20_MET70_v.*", #37
        //38,    //"HLT_LooseIsoPFTau35_Trk20_MET75_v.*", #38
        //39,    //"HLT_DiCentralJetSumpT100_dPhi05_DiCentralPFJet60_25_PFMET100_HBHENoiseCleaned_v.*", #39
        //40,    //"HLT_DiCentralJet20_CaloMET65_BTagCSV07_PFMHT80_v.*", #40
        //41,    //"HLT_DiCentralPFJet30_PFMET80_BTagCSV07_v.*", #41
        //42,    //"HLT_PFMET150_v.*", #42
        //43,    //"HLT_L1ETM40_v.*", #43
        //44,    //"HLT_Ele27_WP80_v.*", #44
        //45,    //"HLT_Ele27_WP80_WCandPt80_v.*", #45
        //46,    //"HLT_IsoMu20_eta2p1_WCandPt80_v.*", #46
        //47,    //"HLT_IsoMu20_WCandPt80_v.*", #47
        //48,    //"HLT_Mu17_TkMu8_v.*", #48
        //49,    //"HLT_DiCentralPFJet30_PFMHT80_v.*", #49 ## run2012A
        //50,    //"HLT_DiCentralPFJet30_PFMET80_v.*", #50 ## run2012B prescaled       
        //51,    //"HLT_LooseIsoPFTau35_Trk20_Prong1_v.*", #51
        //52,    //"HLT_LooseIsoPFTau35_Trk20_Prong1_MET70_v.*", #52
        //53,    //"HLT_LooseIsoPFTau35_Trk20_Prong1_MET75_v.*", #53
        54     // BLANK, for ease in commenting above triggers
    };

}
#endif
