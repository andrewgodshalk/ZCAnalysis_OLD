// ZCControlPlotMaker.cpp

#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <TBranch.h>
#include <TDirectory.h>
#include <TLeaf.h>
#include <TROOT.h>
#include <TString.h>
#include "timestamp.h"
#include "ZCControlPlotMaker.h"
#include "ZCStandardVariables.h"

using namespace ZCStandardVariables;
using std::cout;  using std::endl;   using std::setw;     using std::ofstream;
using std::min;   using std::sqrt;   using std::vector;

typedef unsigned long counter;

void ZCControlPlotMaker::Begin(TTree * /*tree*/)
{
    TString option = GetOption();
}


void ZCControlPlotMaker::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  // Check the option to see if we're working with Simulation or Data, and whether you're looking for Zee or Zuu events
    TString option = GetOption();
    usingZee = usingZuu = usingZtt = false;
    usingSim = (option.Contains("Sim", TString::kIgnoreCase) ? true : false);
    usingZee = (option.Contains("Zee", TString::kIgnoreCase) ? true : false);
    usingZuu = (option.Contains("Zuu", TString::kIgnoreCase) ? true : false);
    if(option.Contains("Zttuu", TString::kIgnoreCase) usingZuu = usingZtt = true;
    if(option.Contains("Zttuu", TString::kIgnoreCase) usingZuu = usingZtt = true;

    // Initialize Histograms
    h_raw_Zmass          = new TH1F( "h_raw_Zmass"         , "Z Mass"                     " (Raw)" "; Mass (GeV)"          ";Number of Events" , 100, 50, 250    );
    h_raw_Zpt            = new TH1F( "h_raw_Zpt"           , "Z p_{T}"                    " (Raw)" "; p_{T} (GeV)"         ";Number of Events" , 100,  0, 250    );
    h_raw_Zeta           = new TH1F( "h_raw_Zeta"          , "Z #eta"                     " (Raw)" "; #eta"                ";Number of Events" , 100, -6,   6    );
    h_raw_Zphi           = new TH1F( "h_raw_Zphi"          , "Z #phi"                     " (Raw)" "; #phi"                ";Number of Events" , 100, -4,   4    );
    h_raw_ZDelR          = new TH1F( "h_raw_ZDelR"         , "Z #DeltaR"                  " (Raw)" "; #DeltaR"             ";Number of Events" , 100,  0,   6    );
    h_raw_nMuons         = new TH1F( "h_raw_nMuons"        , "Muon Multiplicity"          " (Raw)" "; Number of Muons"     ";Number of Events" ,  10,  0,  10    );
    h_raw_MuonPt         = new TH1F( "h_raw_MuonPt"        ,             "Muon p_{T}"     " (Raw)" "; p_{T}"               ";Number of Events" , 100,  0, 200    );
    h_raw_MuonPtLead     = new TH1F( "h_raw_MuonPtLead"    , "Lead "     "Muon p_{T}"     " (Raw)" "; p_{T}"               ";Number of Events" , 100,  0, 200    );
    h_raw_MuonPtSubLead  = new TH1F( "h_raw_MuonPtSubLead" , "Sub-lead " "Muon p_{T}"     " (Raw)" "; p_{T}"               ";Number of Events" , 100,  0, 200    );
    h_raw_MuonPtExtra    = new TH1F( "h_raw_MuonPtExtra"   , "Extra "    "Muon p_{T}"     " (Raw)" "; p_{T}"               ";Number of Events" , 100,  0, 200    );
    h_raw_MuonEta        = new TH1F( "h_raw_MuonEta"       ,             "Muon #eta"      " (Raw)" "; #eta"                ";Number of Events" , 100, -4,   4    );
    h_raw_MuonEtaLead    = new TH1F( "h_raw_MuonEtaLead"   , "Lead "     "Muon #eta"      " (Raw)" "; #eta"                ";Number of Events" , 100, -4,   4    );
    h_raw_MuonEtaSubLead = new TH1F( "h_raw_MuonEtaSubLead", "Sub-lead " "Muon #eta"      " (Raw)" "; #eta"                ";Number of Events" , 100, -4,   4    );
    h_raw_MuonEtaExtra   = new TH1F( "h_raw_MuonEtaExtra"  , "Extra "    "Muon #eta"      " (Raw)" "; #eta"                ";Number of Events" , 100, -4,   4    );
    h_raw_MuonPhi        = new TH1F( "h_raw_MuonPhi"       ,             "Muon #phi"      " (Raw)" "; #phi"                ";Number of Events" , 100, -4,   4    );
    h_raw_MuonPhiLead    = new TH1F( "h_raw_MuonPhiLead"   , "Lead "     "Muon #phi"      " (Raw)" "; #phi"                ";Number of Events" , 100, -4,   4    );
    h_raw_MuonPhiSubLead = new TH1F( "h_raw_MuonPhiSubLead", "Sub-lead " "Muon #phi"      " (Raw)" "; #phi"                ";Number of Events" , 100, -4,   4    );
    h_raw_MuonPhiExtra   = new TH1F( "h_raw_MuonPhiExtra"  , "Extra "    "Muon #phi"      " (Raw)" "; #phi"                ";Number of Events" , 100, -4,   4    );
    h_raw_MuonIso        = new TH1F( "h_raw_MuonIso"       ,             "Muon pfCorrIso" " (Raw)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 );
    h_raw_MuonIsoLead    = new TH1F( "h_raw_MuonIsoLead"   , "Lead "     "Muon pfCorrIso" " (Raw)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 );
    h_raw_MuonIsoSubLead = new TH1F( "h_raw_MuonIsoSubLead", "Sub-lead " "Muon pfCorrIso" " (Raw)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 );
    h_raw_MuonIsoExtra   = new TH1F( "h_raw_MuonIsoExtra"  , "Extra "    "Muon pfCorrIso" " (Raw)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 );
    h_raw_nElecs         = new TH1F( "h_raw_nElecs"        , "Electron Multiplicity"      " (Raw)" "; Number of Electrons" ";Number of Events" ,  10,  0,  10    );
    h_raw_ElecPt         = new TH1F( "h_raw_ElecPt"        ,             "Electron p_{T}" " (Raw)" "; p_{T}"               ";Number of Events" , 100,  0, 200    );
    h_raw_ElecPtLead     = new TH1F( "h_raw_ElecPtLead"    , "Lead "     "Electron p_{T}" " (Raw)" "; p_{T}"               ";Number of Events" , 100,  0, 200    );
    h_raw_ElecPtSubLead  = new TH1F( "h_raw_ElecPtSubLead" , "Sub-lead " "Electron p_{T}" " (Raw)" "; p_{T}"               ";Number of Events" , 100,  0, 200    );
    h_raw_ElecPtExtra    = new TH1F( "h_raw_ElecPtExtra"   , "Extra "    "Electron p_{T}" " (Raw)" "; p_{T}"               ";Number of Events" , 100,  0, 200    );
    h_raw_ElecEta        = new TH1F( "h_raw_ElecEta"       ,             "Electron #eta"  " (Raw)" "; #eta"                ";Number of Events" , 100, -4,   4    );
    h_raw_ElecEtaLead    = new TH1F( "h_raw_ElecEtaLead"   , "Lead "     "Electron #eta"  " (Raw)" "; #eta"                ";Number of Events" , 100, -4,   4    );
    h_raw_ElecEtaSubLead = new TH1F( "h_raw_ElecEtaSubLead", "Sub-lead " "Electron #eta"  " (Raw)" "; #eta"                ";Number of Events" , 100, -4,   4    );
    h_raw_ElecEtaExtra   = new TH1F( "h_raw_ElecEtaExtra"  , "Extra "    "Electron #eta"  " (Raw)" "; #eta"                ";Number of Events" , 100, -4,   4    );
    h_raw_ElecPhi        = new TH1F( "h_raw_ElecPhi"       ,             "Electron #phi"  " (Raw)" "; #phi"                ";Number of Events" , 100, -4,   4    );
    h_raw_ElecPhiLead    = new TH1F( "h_raw_ElecPhiLead"   , "Lead "     "Electron #phi"  " (Raw)" "; #phi"                ";Number of Events" , 100, -4,   4    );
    h_raw_ElecPhiSubLead = new TH1F( "h_raw_ElecPhiSubLead", "Sub-lead " "Electron #phi"  " (Raw)" "; #phi"                ";Number of Events" , 100, -4,   4    );
    h_raw_ElecPhiExtra   = new TH1F( "h_raw_ElecPhiExtra"  , "Extra "    "Electron #phi"  " (Raw)" "; #phi"                ";Number of Events" , 100, -4,   4    );
    h_raw_MET            = new TH1F( "h_raw_MET"           , "MET"                        " (Raw)" "; MET (GeV)"           ";Number of Events" , 100,  0, 200    );
    h_raw_nJets          = new TH1F( "h_raw_nJets"         , "Jet Multiplicity"           " (Raw)" ";Number of Jets"       ";Number of Jets"   ,  10,  0,  10    );
    h_raw_JetPt          = new TH1F( "h_raw_JetPt"         , "p_{T}"                      " (Raw)" ";p_{T} (GeV)"          ";Number of Jets"   , 100,  0, 100    );
    h_raw_JetEta         = new TH1F( "h_raw_JetEta"        , "#eta"                       " (Raw)" ";#eta"                 ";Number of Jets"   , 100, -6,   6    );
    h_raw_JetPhi         = new TH1F( "h_raw_JetPhi"        , "#phi"                       " (Raw)" ";#phi"                 ";Number of Jets"   , 100, -4,   4    );
    h_raw_JetCSV         = new TH1F( "h_raw_JetCSV"        , "CSV"                        " (Raw)" ";CSV"                  ";Number of Jets"   , 100,  0,   1    );
    h_raw_JetMSV         = new TH1F( "h_raw_JetMSV"        , "M_{SV}"                     " (Raw)" ";M_{SV} (GeV)"         ";Number of Jets"   , 100,  0,   6    );

    for(int i=0; i<=nJetsAnalyzed; i++)
    {
        // Make a number to add to titles
        TString iLabel; iLabel.Form("%d", i);
        if(i==nJetsAnalyzed) iLabel += "om";

        h_zpj_inc_Zmass         .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_Zmass"         , TString("Z Mass"                     " (Z+")+iLabel+"j  in.)" "; Mass (GeV)"          ";Number of Events" , 100, 50, 250    ));
        h_zpj_exc_Zmass         .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_Zmass"         , TString("Z Mass"                     " (Z+")+iLabel+"j  ex.)" "; Mass (GeV)"          ";Number of Events" , 100, 50, 250    ));
        h_tag_inc_Zmass         .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_Zmass"         , TString("Z Mass"                     " (Z+")+iLabel+"HF in.)" "; Mass (GeV)"          ";Number of Events" , 100, 50, 250    ));
        h_tag_exc_Zmass         .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_Zmass"         , TString("Z Mass"                     " (Z+")+iLabel+"HF ex.)" "; Mass (GeV)"          ";Number of Events" , 100, 50, 250    ));
        h_zpj_inc_Zpt           .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_Zpt"           , TString("Z p_{T}"                    " (Z+")+iLabel+"j  in.)" "; p_{T} (GeV)"         ";Number of Events" , 100,  0, 250    ));
        h_zpj_exc_Zpt           .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_Zpt"           , TString("Z p_{T}"                    " (Z+")+iLabel+"j  ex.)" "; p_{T} (GeV)"         ";Number of Events" , 100,  0, 250    ));
        h_tag_inc_Zpt           .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_Zpt"           , TString("Z p_{T}"                    " (Z+")+iLabel+"HF in.)" "; p_{T} (GeV)"         ";Number of Events" , 100,  0, 250    ));
        h_tag_exc_Zpt           .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_Zpt"           , TString("Z p_{T}"                    " (Z+")+iLabel+"HF ex.)" "; p_{T} (GeV)"         ";Number of Events" , 100,  0, 250    ));
        h_zpj_inc_Zeta          .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_Zeta"          , TString("Z #eta"                     " (Z+")+iLabel+"j  in.)" "; #eta"                ";Number of Events" , 100, -6,   6    ));
        h_zpj_exc_Zeta          .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_Zeta"          , TString("Z #eta"                     " (Z+")+iLabel+"j  ex.)" "; #eta"                ";Number of Events" , 100, -6,   6    ));
        h_tag_inc_Zeta          .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_Zeta"          , TString("Z #eta"                     " (Z+")+iLabel+"HF in.)" "; #eta"                ";Number of Events" , 100, -6,   6    ));
        h_tag_exc_Zeta          .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_Zeta"          , TString("Z #eta"                     " (Z+")+iLabel+"HF ex.)" "; #eta"                ";Number of Events" , 100, -6,   6    ));
        h_zpj_inc_Zphi          .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_Zphi"          , TString("Z #phi"                     " (Z+")+iLabel+"j  in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_Zphi          .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_Zphi"          , TString("Z #phi"                     " (Z+")+iLabel+"j  ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_Zphi          .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_Zphi"          , TString("Z #phi"                     " (Z+")+iLabel+"HF in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_Zphi          .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_Zphi"          , TString("Z #phi"                     " (Z+")+iLabel+"HF ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_ZDelR         .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ZDelR"         , TString("Z #DeltaR"                  " (Z+")+iLabel+"j  in.)" "; #DeltaR"             ";Number of Events" , 100,  0,   6    ));
        h_zpj_exc_ZDelR         .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ZDelR"         , TString("Z #DeltaR"                  " (Z+")+iLabel+"j  ex.)" "; #DeltaR"             ";Number of Events" , 100,  0,   6    ));
        h_tag_inc_ZDelR         .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ZDelR"         , TString("Z #DeltaR"                  " (Z+")+iLabel+"HF in.)" "; #DeltaR"             ";Number of Events" , 100,  0,   6    ));
        h_tag_exc_ZDelR         .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ZDelR"         , TString("Z #DeltaR"                  " (Z+")+iLabel+"HF ex.)" "; #DeltaR"             ";Number of Events" , 100,  0,   6    ));
        h_zpj_inc_nMuons        .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_nMuons"        , TString("Muon Multiplicity"          " (Z+")+iLabel+"j  in.)" "; Number of Muons"     ";Number of Events" ,  10,  0,  10    ));
        h_zpj_exc_nMuons        .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_nMuons"        , TString("Muon Multiplicity"          " (Z+")+iLabel+"j  ex.)" "; Number of Muons"     ";Number of Events" ,  10,  0,  10    ));
        h_tag_inc_nMuons        .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_nMuons"        , TString("Muon Multiplicity"          " (Z+")+iLabel+"HF in.)" "; Number of Muons"     ";Number of Events" ,  10,  0,  10    ));
        h_tag_exc_nMuons        .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_nMuons"        , TString("Muon Multiplicity"          " (Z+")+iLabel+"HF ex.)" "; Number of Muons"     ";Number of Events" ,  10,  0,  10    ));
        h_zpj_inc_MuonPt        .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonPt"        , TString(            "Muon p_{T}"     " (Z+")+iLabel+"j  in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_exc_MuonPt        .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonPt"        , TString(            "Muon p_{T}"     " (Z+")+iLabel+"j  ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_inc_MuonPt        .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonPt"        , TString(            "Muon p_{T}"     " (Z+")+iLabel+"HF in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_exc_MuonPt        .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonPt"        , TString(            "Muon p_{T}"     " (Z+")+iLabel+"HF ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_inc_MuonPtLead    .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonPtLead"    , TString("Lead "     "Muon p_{T}"     " (Z+")+iLabel+"j  in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_exc_MuonPtLead    .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonPtLead"    , TString("Lead "     "Muon p_{T}"     " (Z+")+iLabel+"j  ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_inc_MuonPtLead    .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonPtLead"    , TString("Lead "     "Muon p_{T}"     " (Z+")+iLabel+"HF in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_exc_MuonPtLead    .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonPtLead"    , TString("Lead "     "Muon p_{T}"     " (Z+")+iLabel+"HF ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_inc_MuonPtSubLead .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonPtSubLead" , TString("Sub-lead " "Muon p_{T}"     " (Z+")+iLabel+"j  in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_exc_MuonPtSubLead .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonPtSubLead" , TString("Sub-lead " "Muon p_{T}"     " (Z+")+iLabel+"j  ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_inc_MuonPtSubLead .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonPtSubLead" , TString("Sub-lead " "Muon p_{T}"     " (Z+")+iLabel+"HF in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_exc_MuonPtSubLead .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonPtSubLead" , TString("Sub-lead " "Muon p_{T}"     " (Z+")+iLabel+"HF ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_inc_MuonPtExtra   .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonPtExtra"   , TString("Extra "    "Muon p_{T}"     " (Z+")+iLabel+"j  in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_exc_MuonPtExtra   .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonPtExtra"   , TString("Extra "    "Muon p_{T}"     " (Z+")+iLabel+"j  ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_inc_MuonPtExtra   .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonPtExtra"   , TString("Extra "    "Muon p_{T}"     " (Z+")+iLabel+"HF in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_exc_MuonPtExtra   .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonPtExtra"   , TString("Extra "    "Muon p_{T}"     " (Z+")+iLabel+"HF ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_inc_MuonEta       .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonEta"       , TString(            "Muon #eta"      " (Z+")+iLabel+"j  in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_MuonEta       .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonEta"       , TString(            "Muon #eta"      " (Z+")+iLabel+"j  ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_MuonEta       .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonEta"       , TString(            "Muon #eta"      " (Z+")+iLabel+"HF in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_MuonEta       .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonEta"       , TString(            "Muon #eta"      " (Z+")+iLabel+"HF ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_MuonEtaLead   .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonEtaLead"   , TString("Lead "     "Muon #eta"      " (Z+")+iLabel+"j  in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_MuonEtaLead   .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonEtaLead"   , TString("Lead "     "Muon #eta"      " (Z+")+iLabel+"j  ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_MuonEtaLead   .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonEtaLead"   , TString("Lead "     "Muon #eta"      " (Z+")+iLabel+"HF in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_MuonEtaLead   .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonEtaLead"   , TString("Lead "     "Muon #eta"      " (Z+")+iLabel+"HF ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_MuonEtaSubLead.push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonEtaSubLead", TString("Sub-lead " "Muon #eta"      " (Z+")+iLabel+"j  in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_MuonEtaSubLead.push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonEtaSubLead", TString("Sub-lead " "Muon #eta"      " (Z+")+iLabel+"j  ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_MuonEtaSubLead.push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonEtaSubLead", TString("Sub-lead " "Muon #eta"      " (Z+")+iLabel+"HF in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_MuonEtaSubLead.push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonEtaSubLead", TString("Sub-lead " "Muon #eta"      " (Z+")+iLabel+"HF ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_MuonEtaExtra  .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonEtaExtra"  , TString("Extra "    "Muon #eta"      " (Z+")+iLabel+"j  in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_MuonEtaExtra  .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonEtaExtra"  , TString("Extra "    "Muon #eta"      " (Z+")+iLabel+"j  ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_MuonEtaExtra  .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonEtaExtra"  , TString("Extra "    "Muon #eta"      " (Z+")+iLabel+"HF in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_MuonEtaExtra  .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonEtaExtra"  , TString("Extra "    "Muon #eta"      " (Z+")+iLabel+"HF ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_MuonPhi       .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonPhi"       , TString(            "Muon #phi"      " (Z+")+iLabel+"j  in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_MuonPhi       .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonPhi"       , TString(            "Muon #phi"      " (Z+")+iLabel+"j  ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_MuonPhi       .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonPhi"       , TString(            "Muon #phi"      " (Z+")+iLabel+"HF in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_MuonPhi       .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonPhi"       , TString(            "Muon #phi"      " (Z+")+iLabel+"HF ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_MuonPhiLead   .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonPhiLead"   , TString("Lead "     "Muon #phi"      " (Z+")+iLabel+"j  in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_MuonPhiLead   .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonPhiLead"   , TString("Lead "     "Muon #phi"      " (Z+")+iLabel+"j  ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_MuonPhiLead   .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonPhiLead"   , TString("Lead "     "Muon #phi"      " (Z+")+iLabel+"HF in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_MuonPhiLead   .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonPhiLead"   , TString("Lead "     "Muon #phi"      " (Z+")+iLabel+"HF ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_MuonPhiSubLead.push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonPhiSubLead", TString("Sub-lead " "Muon #phi"      " (Z+")+iLabel+"j  in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_MuonPhiSubLead.push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonPhiSubLead", TString("Sub-lead " "Muon #phi"      " (Z+")+iLabel+"j  ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_MuonPhiSubLead.push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonPhiSubLead", TString("Sub-lead " "Muon #phi"      " (Z+")+iLabel+"HF in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_MuonPhiSubLead.push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonPhiSubLead", TString("Sub-lead " "Muon #phi"      " (Z+")+iLabel+"HF ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_MuonPhiExtra  .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonPhiExtra"  , TString("Extra "    "Muon #phi"      " (Z+")+iLabel+"j  in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_MuonPhiExtra  .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonPhiExtra"  , TString("Extra "    "Muon #phi"      " (Z+")+iLabel+"j  ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_MuonPhiExtra  .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonPhiExtra"  , TString("Extra "    "Muon #phi"      " (Z+")+iLabel+"HF in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_MuonPhiExtra  .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonPhiExtra"  , TString("Extra "    "Muon #phi"      " (Z+")+iLabel+"HF ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_MuonIso       .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonIso"       , TString(            "Muon pfCorrIso" " (Z+")+iLabel+"j  in.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_zpj_exc_MuonIso       .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonIso"       , TString(            "Muon pfCorrIso" " (Z+")+iLabel+"j  ex.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_tag_inc_MuonIso       .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonIso"       , TString(            "Muon pfCorrIso" " (Z+")+iLabel+"HF in.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_tag_exc_MuonIso       .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonIso"       , TString(            "Muon pfCorrIso" " (Z+")+iLabel+"HF ex.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_zpj_inc_MuonIsoLead   .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonIsoLead"   , TString("Lead "     "Muon pfCorrIso" " (Z+")+iLabel+"j  in.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_zpj_exc_MuonIsoLead   .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonIsoLead"   , TString("Lead "     "Muon pfCorrIso" " (Z+")+iLabel+"j  ex.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_tag_inc_MuonIsoLead   .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonIsoLead"   , TString("Lead "     "Muon pfCorrIso" " (Z+")+iLabel+"HF in.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_tag_exc_MuonIsoLead   .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonIsoLead"   , TString("Lead "     "Muon pfCorrIso" " (Z+")+iLabel+"HF ex.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_zpj_inc_MuonIsoSubLead.push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonIsoSubLead", TString("Sub-lead " "Muon pfCorrIso" " (Z+")+iLabel+"j  in.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_zpj_exc_MuonIsoSubLead.push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonIsoSubLead", TString("Sub-lead " "Muon pfCorrIso" " (Z+")+iLabel+"j  ex.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_tag_inc_MuonIsoSubLead.push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonIsoSubLead", TString("Sub-lead " "Muon pfCorrIso" " (Z+")+iLabel+"HF in.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_tag_exc_MuonIsoSubLead.push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonIsoSubLead", TString("Sub-lead " "Muon pfCorrIso" " (Z+")+iLabel+"HF ex.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_zpj_inc_MuonIsoExtra  .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MuonIsoExtra"  , TString("Extra "    "Muon pfCorrIso" " (Z+")+iLabel+"j  in.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_zpj_exc_MuonIsoExtra  .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MuonIsoExtra"  , TString("Extra "    "Muon pfCorrIso" " (Z+")+iLabel+"j  ex.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_tag_inc_MuonIsoExtra  .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MuonIsoExtra"  , TString("Extra "    "Muon pfCorrIso" " (Z+")+iLabel+"HF in.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_tag_exc_MuonIsoExtra  .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MuonIsoExtra"  , TString("Extra "    "Muon pfCorrIso" " (Z+")+iLabel+"HF ex.)" "; pfCorrIso"           ";Number of Events" , 100,  0,   0.13 ));
        h_zpj_inc_nElecs        .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_nElecs"        , TString("Electron Multiplicity"      " (Z+")+iLabel+"j  in.)" "; Number of Electrons" ";Number of Events" ,  10,  0,  10    ));
        h_zpj_exc_nElecs        .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_nElecs"        , TString("Electron Multiplicity"      " (Z+")+iLabel+"j  ex.)" "; Number of Electrons" ";Number of Events" ,  10,  0,  10    ));
        h_tag_inc_nElecs        .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_nElecs"        , TString("Electron Multiplicity"      " (Z+")+iLabel+"HF in.)" "; Number of Electrons" ";Number of Events" ,  10,  0,  10    ));
        h_tag_exc_nElecs        .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_nElecs"        , TString("Electron Multiplicity"      " (Z+")+iLabel+"HF ex.)" "; Number of Electrons" ";Number of Events" ,  10,  0,  10    ));
        h_zpj_inc_ElecPt        .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecPt"        , TString(            "Electron p_{T}" " (Z+")+iLabel+"j  in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_exc_ElecPt        .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecPt"        , TString(            "Electron p_{T}" " (Z+")+iLabel+"j  ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_inc_ElecPt        .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecPt"        , TString(            "Electron p_{T}" " (Z+")+iLabel+"HF in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_exc_ElecPt        .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecPt"        , TString(            "Electron p_{T}" " (Z+")+iLabel+"HF ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_inc_ElecPtLead    .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecPtLead"    , TString("Lead "     "Electron p_{T}" " (Z+")+iLabel+"j  in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_exc_ElecPtLead    .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecPtLead"    , TString("Lead "     "Electron p_{T}" " (Z+")+iLabel+"j  ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_inc_ElecPtLead    .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecPtLead"    , TString("Lead "     "Electron p_{T}" " (Z+")+iLabel+"HF in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_exc_ElecPtLead    .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecPtLead"    , TString("Lead "     "Electron p_{T}" " (Z+")+iLabel+"HF ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_inc_ElecPtSubLead .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecPtSubLead" , TString("Sub-lead " "Electron p_{T}" " (Z+")+iLabel+"j  in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_exc_ElecPtSubLead .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecPtSubLead" , TString("Sub-lead " "Electron p_{T}" " (Z+")+iLabel+"j  ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_inc_ElecPtSubLead .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecPtSubLead" , TString("Sub-lead " "Electron p_{T}" " (Z+")+iLabel+"HF in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_exc_ElecPtSubLead .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecPtSubLead" , TString("Sub-lead " "Electron p_{T}" " (Z+")+iLabel+"HF ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_inc_ElecPtExtra   .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecPtExtra"   , TString("Extra "    "Electron p_{T}" " (Z+")+iLabel+"j  in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_exc_ElecPtExtra   .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecPtExtra"   , TString("Extra "    "Electron p_{T}" " (Z+")+iLabel+"j  ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_inc_ElecPtExtra   .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecPtExtra"   , TString("Extra "    "Electron p_{T}" " (Z+")+iLabel+"HF in.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_tag_exc_ElecPtExtra   .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecPtExtra"   , TString("Extra "    "Electron p_{T}" " (Z+")+iLabel+"HF ex.)" "; p_{T}"               ";Number of Events" , 100,  0, 200    ));
        h_zpj_inc_ElecEta       .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecEta"       , TString(            "Electron #eta"  " (Z+")+iLabel+"j  in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_ElecEta       .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecEta"       , TString(            "Electron #eta"  " (Z+")+iLabel+"j  ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_ElecEta       .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecEta"       , TString(            "Electron #eta"  " (Z+")+iLabel+"HF in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_ElecEta       .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecEta"       , TString(            "Electron #eta"  " (Z+")+iLabel+"HF ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_ElecEtaLead   .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecEtaLead"   , TString("Lead "     "Electron #eta"  " (Z+")+iLabel+"j  in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_ElecEtaLead   .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecEtaLead"   , TString("Lead "     "Electron #eta"  " (Z+")+iLabel+"j  ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_ElecEtaLead   .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecEtaLead"   , TString("Lead "     "Electron #eta"  " (Z+")+iLabel+"HF in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_ElecEtaLead   .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecEtaLead"   , TString("Lead "     "Electron #eta"  " (Z+")+iLabel+"HF ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_ElecEtaSubLead.push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecEtaSubLead", TString("Sub-lead " "Electron #eta"  " (Z+")+iLabel+"j  in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_ElecEtaSubLead.push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecEtaSubLead", TString("Sub-lead " "Electron #eta"  " (Z+")+iLabel+"j  ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_ElecEtaSubLead.push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecEtaSubLead", TString("Sub-lead " "Electron #eta"  " (Z+")+iLabel+"HF in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_ElecEtaSubLead.push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecEtaSubLead", TString("Sub-lead " "Electron #eta"  " (Z+")+iLabel+"HF ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_ElecEtaExtra  .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecEtaExtra"  , TString("Extra "    "Electron #eta"  " (Z+")+iLabel+"j  in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_ElecEtaExtra  .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecEtaExtra"  , TString("Extra "    "Electron #eta"  " (Z+")+iLabel+"j  ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_ElecEtaExtra  .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecEtaExtra"  , TString("Extra "    "Electron #eta"  " (Z+")+iLabel+"HF in.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_ElecEtaExtra  .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecEtaExtra"  , TString("Extra "    "Electron #eta"  " (Z+")+iLabel+"HF ex.)" "; #eta"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_ElecPhi       .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecPhi"       , TString(            "Electron #phi"  " (Z+")+iLabel+"j  in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_ElecPhi       .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecPhi"       , TString(            "Electron #phi"  " (Z+")+iLabel+"j  ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_ElecPhi       .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecPhi"       , TString(            "Electron #phi"  " (Z+")+iLabel+"HF in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_ElecPhi       .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecPhi"       , TString(            "Electron #phi"  " (Z+")+iLabel+"HF ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_ElecPhiLead   .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecPhiLead"   , TString("Lead "     "Electron #phi"  " (Z+")+iLabel+"j  in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_ElecPhiLead   .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecPhiLead"   , TString("Lead "     "Electron #phi"  " (Z+")+iLabel+"j  ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_ElecPhiLead   .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecPhiLead"   , TString("Lead "     "Electron #phi"  " (Z+")+iLabel+"HF in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_ElecPhiLead   .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecPhiLead"   , TString("Lead "     "Electron #phi"  " (Z+")+iLabel+"HF ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_ElecPhiSubLead.push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecPhiSubLead", TString("Sub-lead " "Electron #phi"  " (Z+")+iLabel+"j  in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_ElecPhiSubLead.push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecPhiSubLead", TString("Sub-lead " "Electron #phi"  " (Z+")+iLabel+"j  ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_ElecPhiSubLead.push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecPhiSubLead", TString("Sub-lead " "Electron #phi"  " (Z+")+iLabel+"HF in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_ElecPhiSubLead.push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecPhiSubLead", TString("Sub-lead " "Electron #phi"  " (Z+")+iLabel+"HF ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_ElecPhiExtra  .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_ElecPhiExtra"  , TString("Extra "    "Electron #phi"  " (Z+")+iLabel+"j  in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_exc_ElecPhiExtra  .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_ElecPhiExtra"  , TString("Extra "    "Electron #phi"  " (Z+")+iLabel+"j  ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_inc_ElecPhiExtra  .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_ElecPhiExtra"  , TString("Extra "    "Electron #phi"  " (Z+")+iLabel+"HF in.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_tag_exc_ElecPhiExtra  .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_ElecPhiExtra"  , TString("Extra "    "Electron #phi"  " (Z+")+iLabel+"HF ex.)" "; #phi"                ";Number of Events" , 100, -4,   4    ));
        h_zpj_inc_MET           .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_MET"           , TString("MET "                       " (Z+")+iLabel+"j  in.)" "; MET (GeV)"           ";Number of Events" , 100,  0, 200    ));
        h_zpj_exc_MET           .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_MET"           , TString("MET "                       " (Z+")+iLabel+"j  ex.)" "; MET (GeV)"           ";Number of Events" , 100,  0, 200    ));
        h_tag_inc_MET           .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_MET"           , TString("MET "                       " (Z+")+iLabel+"HF in.)" "; MET (GeV)"           ";Number of Events" , 100,  0, 200    ));
        h_tag_exc_MET           .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_MET"           , TString("MET "                       " (Z+")+iLabel+"HF ex.)" "; MET (GeV)"           ";Number of Events" , 100,  0, 200    ));
        h_zpj_inc_nJets         .push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_nJets"         , TString("Jet Multiplicity "          " (Z+")+iLabel+"j  in.)" ";Number of Jets"       ";Number of Events" ,  10,  0,  10    ));
        h_zpj_exc_nJets         .push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_nJets"         , TString("Jet Multiplicity "          " (Z+")+iLabel+"j  ex.)" ";Number of Jets"       ";Number of Events" ,  10,  0,  10    ));
        h_tag_inc_nJets         .push_back(new TH1F(TString("h_tag_inc")+iLabel+"_nJets"         , TString("Jet Multiplicity "          " (Z+")+iLabel+"HF in.)" ";Number of Jets"       ";Number of Events" ,  10,  0,  10    ));
        h_tag_exc_nJets         .push_back(new TH1F(TString("h_tag_exc")+iLabel+"_nJets"         , TString("Jet Multiplicity "          " (Z+")+iLabel+"HF ex.)" ";Number of Jets"       ";Number of Events" ,  10,  0,  10    ));

      // Jet properties - Inclusive events have plot for all jets, as well as 1st through max jets (nJetsAnalyzed+1)
      //                - Exclusive events have plot for all jets and 1st through nth jet (n+1 plots)
      // Add new vectors to double vectors
        h_zpj_inc_JetPt .push_back(vector<TH1F*>(0));   h_zpj_exc_JetPt .push_back(vector<TH1F*>(0));   h_tag_inc_JetPt .push_back(vector<TH1F*>(0));   h_tag_exc_JetPt .push_back(vector<TH1F*>(0));
        h_zpj_inc_JetEta.push_back(vector<TH1F*>(0));   h_zpj_exc_JetEta.push_back(vector<TH1F*>(0));   h_tag_inc_JetEta.push_back(vector<TH1F*>(0));   h_tag_exc_JetEta.push_back(vector<TH1F*>(0));
        h_zpj_inc_JetPhi.push_back(vector<TH1F*>(0));   h_zpj_exc_JetPhi.push_back(vector<TH1F*>(0));   h_tag_inc_JetPhi.push_back(vector<TH1F*>(0));   h_tag_exc_JetPhi.push_back(vector<TH1F*>(0));
        h_zpj_inc_JetCSV.push_back(vector<TH1F*>(0));   h_zpj_exc_JetCSV.push_back(vector<TH1F*>(0));   h_tag_inc_JetCSV.push_back(vector<TH1F*>(0));   h_tag_exc_JetCSV.push_back(vector<TH1F*>(0));
        h_zpj_inc_JetMSV.push_back(vector<TH1F*>(0));   h_zpj_exc_JetMSV.push_back(vector<TH1F*>(0));   h_tag_inc_JetMSV.push_back(vector<TH1F*>(0));   h_tag_exc_JetMSV.push_back(vector<TH1F*>(0));

        for(int j=0; j<=nJetsAnalyzed; j++)
        {
            TString jLabel;
            if     (j==0) jLabel = "";
            else if(j==1) jLabel = "1st";
            else if(j==2) jLabel = "2nd";
            else {        jLabel.Form("%d", j);
                          jLabel += "th";
                 }
            TString space = (j ? " " : "" );   // A white space for titles for all-jet plots.

          // Inclusive: First histogram includes all jets. Then one histogram for each of the jets up to nJetsAnalyzed.
            h_zpj_inc_JetPt [i].push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_"+jLabel+"JetPt"  , jLabel+space+"Jet p_{T}"  " (Z+" +iLabel+ "j  in.)" ";p_{T} (GeV)"  ";Number of Jets", 100,  0, 200 ));
            h_tag_inc_JetPt [i].push_back(new TH1F(TString("h_tag_inc")+iLabel+"_"+jLabel+"JetPt"  , jLabel+space+"Jet p_{T}"  " (Z+" +iLabel+ "HF in.)" ";p_{T} (GeV)"  ";Number of Jets", 100,  0, 200 ));
            h_zpj_inc_JetEta[i].push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_"+jLabel+"JetEta" , jLabel+space+"Jet #eta"   " (Z+" +iLabel+ "j  in.)" ";#eta"         ";Number of Jets", 100, -4,   4 ));
            h_tag_inc_JetEta[i].push_back(new TH1F(TString("h_tag_inc")+iLabel+"_"+jLabel+"JetEta" , jLabel+space+"Jet #eta"   " (Z+" +iLabel+ "HF in.)" ";#eta"         ";Number of Jets", 100, -4,   4 ));
            h_zpj_inc_JetPhi[i].push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_"+jLabel+"JetPhi" , jLabel+space+"Jet #phi"   " (Z+" +iLabel+ "j  in.)" ";#phi"         ";Number of Jets", 100, -4,   4 ));
            h_tag_inc_JetPhi[i].push_back(new TH1F(TString("h_tag_inc")+iLabel+"_"+jLabel+"JetPhi" , jLabel+space+"Jet #phi"   " (Z+" +iLabel+ "HF in.)" ";#phi"         ";Number of Jets", 100, -4,   4 ));
            h_zpj_inc_JetCSV[i].push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_"+jLabel+"JetCSV" , jLabel+space+"Jet CSV"    " (Z+" +iLabel+ "j  in.)" ";CSV"          ";Number of Jets", 100,  0,   1 ));
            h_tag_inc_JetCSV[i].push_back(new TH1F(TString("h_tag_inc")+iLabel+"_"+jLabel+"JetCSV" , jLabel+space+"Jet CSV"    " (Z+" +iLabel+ "HF in.)" ";CSV"          ";Number of Jets", 100,  0,   1 ));
            h_zpj_inc_JetMSV[i].push_back(new TH1F(TString("h_zpj_inc")+iLabel+"_"+jLabel+"JetMSV" , jLabel+space+"Jet M_{SV}" " (Z+" +iLabel+ "j  in.)" ";M_{SV} (GeV)" ";Number of Jets", 100,  0,   6 ));
            h_tag_inc_JetMSV[i].push_back(new TH1F(TString("h_tag_inc")+iLabel+"_"+jLabel+"JetMSV" , jLabel+space+"Jet M_{SV}" " (Z+" +iLabel+ "HF in.)" ";M_{SV} (GeV)" ";Number of Jets", 100,  0,   6 ));

          // Exclusive: First histogram includes all jets, then a histo for each jet up to i.
            if(j > i) continue;     // If j (jet we're filling for) is larger than i (number of jets in exclusive event), don't create histogram. No "jth" jet in an Z+i jets selection.
            h_zpj_exc_JetPt [i].push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_"+jLabel+"JetPt"  , jLabel+space+"Jet p_{T}"  " (Z+" +iLabel+ "j  ex.)" ";p_{T} (GeV)"  ";Number of Jets", 100,  0, 200 ));
            h_tag_exc_JetPt [i].push_back(new TH1F(TString("h_tag_exc")+iLabel+"_"+jLabel+"JetPt"  , jLabel+space+"Jet p_{T}"  " (Z+" +iLabel+ "HF ex.)" ";p_{T} (GeV)"  ";Number of Jets", 100,  0, 200 ));
            h_zpj_exc_JetEta[i].push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_"+jLabel+"JetEta" , jLabel+space+"Jet #eta"   " (Z+" +iLabel+ "j  ex.)" ";#eta"         ";Number of Jets", 100, -4,   4 ));
            h_tag_exc_JetEta[i].push_back(new TH1F(TString("h_tag_exc")+iLabel+"_"+jLabel+"JetEta" , jLabel+space+"Jet #eta"   " (Z+" +iLabel+ "HF ex.)" ";#eta"         ";Number of Jets", 100, -4,   4 ));
            h_zpj_exc_JetPhi[i].push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_"+jLabel+"JetPhi" , jLabel+space+"Jet #phi"   " (Z+" +iLabel+ "j  ex.)" ";#phi"         ";Number of Jets", 100, -4,   4 ));
            h_tag_exc_JetPhi[i].push_back(new TH1F(TString("h_tag_exc")+iLabel+"_"+jLabel+"JetPhi" , jLabel+space+"Jet #phi"   " (Z+" +iLabel+ "HF ex.)" ";#phi"         ";Number of Jets", 100, -4,   4 ));
            h_zpj_exc_JetCSV[i].push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_"+jLabel+"JetCSV" , jLabel+space+"Jet CSV"    " (Z+" +iLabel+ "j  ex.)" ";CSV"          ";Number of Jets", 100,  0,   1 ));
            h_tag_exc_JetCSV[i].push_back(new TH1F(TString("h_tag_exc")+iLabel+"_"+jLabel+"JetCSV" , jLabel+space+"Jet CSV"    " (Z+" +iLabel+ "HF ex.)" ";CSV"          ";Number of Jets", 100,  0,   1 ));
            h_zpj_exc_JetMSV[i].push_back(new TH1F(TString("h_zpj_exc")+iLabel+"_"+jLabel+"JetMSV" , jLabel+space+"Jet M_{SV}" " (Z+" +iLabel+ "j  ex.)" ";M_{SV} (GeV)" ";Number of Jets", 100,  0,   6 ));
            h_tag_exc_JetMSV[i].push_back(new TH1F(TString("h_tag_exc")+iLabel+"_"+jLabel+"JetMSV" , jLabel+space+"Jet M_{SV}" " (Z+" +iLabel+ "HF ex.)" ";M_{SV} (GeV)" ";Number of Jets", 100,  0,   6 ));
        }
    }

  // Initialize log, counters
    log.str("");
    nEntries         = 0;   nZJEEvents = vector<counter>(nJetsAnalyzed+1, 0);
    nEventsProcessed = 0;   nZJIEvents = vector<counter>(nJetsAnalyzed+1, 0);
    nRawEvents       = 0;   nZHEEvents = vector<counter>(nJetsAnalyzed+1, 0);
    nRawMuonEvents   = 0;   nZHIEvents = vector<counter>(nJetsAnalyzed+1, 0);
    nRawElecEvents   = 0;

}


void ZCControlPlotMaker::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize a new tree or chain.
  // Map tree variables to local in this function.
  // Init() will be called many times when running on PROOF (once per file to be processed).

  // Initialize the current tree.
    if (!tree) return;
    fChain = tree;              // Commented, don't think I need to access tree information outside of this function.
    fChain->SetMakeClass(1);    // ??? Can't seem to get a good answer about what this is.
                                //    I think it recreates classes stored in the root tree as opposed to just mapping variables from the object.
    //treeReader.SetTree(tree);
    nEntries += tree->GetEntries();

  // Map variables to local variables using the TTreeReader
    //l_nJets = TTreeReaderValue<Int_t>( treeReader, "nallJets");
    TBranch * temp_branch; 	// Temporary branch to get at members of struct-branches.


  // Z variables
    fChain->SetBranchAddress("Vtype", &m_Vtype);
    if(usingTT)
        fChain->SetBranchAddress("zdecayMode",          &m_Z_decayMode );
    temp_branch = fChain->GetBranch("V");
    temp_branch->GetLeaf( "mass" )->SetAddress(     &m_Z_mass      );
    temp_branch->GetLeaf( "pt"   )->SetAddress(     &m_Z_pt        );
    temp_branch->GetLeaf( "eta"  )->SetAddress(     &m_Z_eta       );
    temp_branch->GetLeaf( "phi"  )->SetAddress(     &m_Z_phi       );
  // JSON
    temp_branch = fChain->GetBranch("EVENT");
    temp_branch->GetLeaf( "json" )->SetAddress(     &m_json        );
  // Muon variables
    fChain->SetBranchAddress( "nallMuons"         , &m_nMuons      );
    fChain->SetBranchAddress( "allMuon_pt"        ,  m_muon_pt     );
    fChain->SetBranchAddress( "allMuon_eta"       ,  m_muon_eta    );
    fChain->SetBranchAddress( "allMuon_phi"       ,  m_muon_phi    );
    fChain->SetBranchAddress( "allMuon_charge"    ,  m_muon_charge );
    fChain->SetBranchAddress( "allMuon_pfCorrIso" ,  m_muon_iso    );
  // Muon variables
    fChain->SetBranchAddress( "nallElectrons"     , &m_nElecs      );
    fChain->SetBranchAddress( "allElectron_pt"    ,  m_elec_pt     );
    fChain->SetBranchAddress( "allElectron_eta"   ,  m_elec_eta    );
    fChain->SetBranchAddress( "allElectron_phi"   ,  m_elec_phi    );
    fChain->SetBranchAddress( "allElectron_charge",  m_elec_charge );
  // Jet variables
    fChain->SetBranchAddress( "nallJets"          , &m_nJets       );
    fChain->SetBranchAddress( "allJet_pt"         ,  m_jet_pt      );
    fChain->SetBranchAddress( "allJet_eta"        ,  m_jet_eta     );
    fChain->SetBranchAddress( "allJet_phi"        ,  m_jet_phi     );
    fChain->SetBranchAddress( "allJet_csv"        ,  m_jet_csv     );
    fChain->SetBranchAddress( "allJet_vtxMass"    ,  m_jet_msv     );
  // MET variables
    temp_branch = fChain->GetBranch("MET");
    temp_branch->GetLeaf( "et"    )->SetAddress(    &m_MET_et      );
    temp_branch->GetLeaf( "phi"   )->SetAddress(    &m_MET_phi     );
    temp_branch->GetLeaf( "sig"   )->SetAddress(    &m_MET_sig     );
    temp_branch->GetLeaf( "sumet" )->SetAddress(    &m_MET_sumet   );
  // Trigger variables
    fChain->SetBranchAddress("triggerFlags", m_triggers);

}


Bool_t ZCControlPlotMaker::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


Bool_t ZCControlPlotMaker::Process(Long64_t entry)
{
  // This function should contain the "body" of the analysis.
  // It can contain simple or elaborate selection criteria, run algorithms on the data of the event and typically fill histograms.
  // The processing can be stopped by calling Abort().

  // Load current entry
    fChain->GetEntry(entry);    nEventsProcessed++;
    if(entry%100000 == 0) cout << "  #" << entry << endl;

  // If event isn't in JSON and isn't a simulation event, move on to the next event.
    if(!(validJSON = m_json) && !usingSim) return kTRUE;

  // Otherwise, increment appropriate counters.
    nRawEvents++;

  // Look at type of dileptons that make up Z. If they aren't the type we specified in the options, move on to the next event.
    if(m_Vtype==0) nRawMuonEvents++;
    if(m_Vtype==1) nRawElecEvents++;
    if(!usingZee && m_Vtype==1)      return kTRUE;
    if(!usingZuu && m_Vtype==0)      return kTRUE;
    if(usingZtt && m_Z_decayMode!=3) return kTRUE

  // Perform selection on Muons, Z, Eta
    validMuons = m_nMuons >=2 && m_muon_pt[0]>muonPtMin && fabs(m_muon_eta[0])<=muonEtaMax
                && m_Vtype==0 && m_muon_pt[1]>muonPtMin && fabs(m_muon_eta[1])<=muonEtaMax;
    validElecs = m_nElecs >=2 && m_elec_pt[0]>elecPtMin && (fabs(m_elec_eta[0])<=elecEtaInnerMax || (fabs(m_elec_eta[0])>=elecEtaOuterMin && fabs(m_elec_eta[0])<=elecEtaOuterMax))
                && m_Vtype==1 && m_elec_pt[1]>elecPtMin && (fabs(m_elec_eta[1])<=elecEtaInnerMax || (fabs(m_elec_eta[1])>=elecEtaOuterMin && fabs(m_elec_eta[1])<=elecEtaOuterMax));
    validZ     = m_Z_mass > dilepInvMassMin && m_Z_mass < dilepInvMassMax;
    validMET   = m_MET_et < metMax;
    isZpJEvent = (validMuons||validElecs) && validZ && validMET;

  // Cycle through jets and find valid and heavy flavor jets.
    validJets = vector<int>(0);
    HFJets    = vector<int>(0);
    for(int i=0; i<m_nJets; i++)
    {
        if(m_jet_pt[i]>jetPtMin && fabs(m_jet_eta[i])<jetEtaMax)
        {
            validJets.push_back(i);
            if(m_jet_csv[i]>csvOpPtTgt && m_jet_msv[i]>=0) HFJets.push_back(i);
        }
    }

  // Calculate some quantities
    float Z_delR = 0;
    if(m_nMuons >= 2 && m_Vtype == 0)
    {
        float Z_delEta = m_muon_eta[0]-m_muon_eta[1];
        float Z_delPhi = m_muon_phi[0]-m_muon_phi[1];
        Z_delR   = sqrt(Z_delEta*Z_delEta+Z_delPhi*Z_delPhi);
    }
    else if(m_nElecs >= 2 && m_Vtype == 1)
    {
        float Z_delEta = m_elec_eta[0]-m_elec_eta[1];
        float Z_delPhi = m_elec_phi[0]-m_elec_phi[1];
        Z_delR   = sqrt(Z_delEta*Z_delEta+Z_delPhi*Z_delPhi);
    }

  // Fill raw histograms
    h_raw_Zmass ->Fill(m_Z_mass);   h_raw_Zphi  ->Fill(m_Z_phi );
    h_raw_Zpt   ->Fill(m_Z_pt  );   h_raw_ZDelR ->Fill(Z_delR  );
    h_raw_Zeta  ->Fill(m_Z_eta );   h_raw_nMuons->Fill(m_nMuons);
    h_raw_MET   ->Fill(m_MET_et);   h_raw_nElecs->Fill(m_nElecs);
    for(int i=0; i<m_nMuons; i++)
    {
        h_raw_MuonPt ->Fill(m_muon_pt [i]);   h_raw_MuonEta->Fill(m_muon_eta[i]);
        h_raw_MuonPhi->Fill(m_muon_phi[i]);   h_raw_MuonIso->Fill(m_muon_iso[i]);
        if(i==0)
        {
            h_raw_MuonPtLead ->Fill(m_muon_pt [i]);    h_raw_MuonEtaLead->Fill(m_muon_eta[i]);
            h_raw_MuonPhiLead->Fill(m_muon_phi[i]);    h_raw_MuonIsoLead->Fill(m_muon_iso[i]);
        }
        else if(i==1)
        {
            h_raw_MuonPtSubLead ->Fill(m_muon_pt [i]); h_raw_MuonEtaSubLead->Fill(m_muon_eta[i]);
            h_raw_MuonPhiSubLead->Fill(m_muon_phi[i]); h_raw_MuonIsoSubLead->Fill(m_muon_iso[i]);
        }
        else
        {
            h_raw_MuonPtExtra ->Fill(m_muon_pt [i]);   h_raw_MuonEtaExtra->Fill(m_muon_eta[i]);
            h_raw_MuonPhiExtra->Fill(m_muon_phi[i]);   h_raw_MuonIsoExtra->Fill(m_muon_iso[i]);
        }
    }
    for(int i=0; i<m_nElecs; i++)
    {
        h_raw_ElecPt ->Fill(m_elec_pt [i]);   h_raw_ElecEta->Fill(m_elec_eta[i]);
        h_raw_ElecPhi->Fill(m_elec_phi[i]);
        if(i==0)
        {
            h_raw_ElecPtLead ->Fill(m_elec_pt [i]);    h_raw_ElecEtaLead->Fill(m_elec_eta[i]);
            h_raw_ElecPhiLead->Fill(m_elec_phi[i]);
        }
        else if(i==1)
        {
            h_raw_ElecPtSubLead ->Fill(m_elec_pt [i]); h_raw_ElecEtaSubLead->Fill(m_elec_eta[i]);
            h_raw_ElecPhiSubLead->Fill(m_elec_phi[i]);
        }
        else
        {
            h_raw_ElecPtExtra ->Fill(m_elec_pt [i]);   h_raw_ElecEtaExtra->Fill(m_elec_eta[i]);
            h_raw_ElecPhiExtra->Fill(m_elec_phi[i]);
        }
    }
    h_raw_nJets ->Fill(m_nJets);
    for(int i=0; i<m_nJets; i++)
    {
        h_raw_JetPt ->Fill(m_jet_pt [i]);
        h_raw_JetEta->Fill(m_jet_eta[i]);
        h_raw_JetPhi->Fill(m_jet_phi[i]);
        h_raw_JetCSV->Fill(m_jet_csv[i]);
        h_raw_JetMSV->Fill(m_jet_msv[i]);
    }

  // Fill exclusive histograms
    int i = min((int)(validJets.size()),nJetsAnalyzed);     // Find number of valid jets, fill that set of exclusive histograms
    
    if((validMuons||validElecs) && validMET) h_zpj_exc_Zmass[i]->Fill(m_Z_mass);  // Fill these outside of ZpJ. Gives cut parts of plots, for comparison.
    if((validMuons||validElecs) && validZ  ) h_zpj_exc_MET  [i]->Fill(m_MET_et);
    if(isZpJEvent)
    {
        nZJEEvents[i]++;
        h_zpj_exc_Zphi  [i]->Fill(m_Z_phi );
        h_zpj_exc_Zpt   [i]->Fill(m_Z_pt  );
        h_zpj_exc_ZDelR [i]->Fill(Z_delR  );
        h_zpj_exc_Zeta  [i]->Fill(m_Z_eta );
        h_zpj_exc_nMuons[i]->Fill(m_nMuons);
        h_zpj_exc_nElecs[i]->Fill(m_nElecs);
        h_zpj_exc_nJets [i]->Fill(validJets.size());
        for(int j=0; j<m_nMuons; j++)
        {
            h_zpj_exc_MuonPt [i]->Fill(m_muon_pt [j]);   h_zpj_exc_MuonEta[i]->Fill(m_muon_eta[j]);
            h_zpj_exc_MuonPhi[i]->Fill(m_muon_phi[j]);   h_zpj_exc_MuonIso[i]->Fill(m_muon_iso[j]);
            if(j==0)
            {
                h_zpj_exc_MuonPtLead [i]->Fill(m_muon_pt [j]);    h_zpj_exc_MuonEtaLead[i]->Fill(m_muon_eta[j]);
                h_zpj_exc_MuonPhiLead[i]->Fill(m_muon_phi[j]);    h_zpj_exc_MuonIsoLead[i]->Fill(m_muon_iso[j]);
            }
            else if(j==1)
            {
                h_zpj_exc_MuonPtSubLead [i]->Fill(m_muon_pt [j]); h_zpj_exc_MuonEtaSubLead[i]->Fill(m_muon_eta[j]);
                h_zpj_exc_MuonPhiSubLead[i]->Fill(m_muon_phi[j]); h_zpj_exc_MuonIsoSubLead[i]->Fill(m_muon_iso[j]);
            }
            else
            {
                h_zpj_exc_MuonPtExtra [i]->Fill(m_muon_pt [j]);   h_zpj_exc_MuonEtaExtra[i]->Fill(m_muon_eta[j]);
                h_zpj_exc_MuonPhiExtra[i]->Fill(m_muon_phi[j]);   h_zpj_exc_MuonIsoExtra[i]->Fill(m_muon_iso[j]);
            }
        }
        for(int j=0; j<m_nElecs; j++)
        {
            h_zpj_exc_ElecPt [i]->Fill(m_elec_pt [j]);   h_zpj_exc_ElecEta[i]->Fill(m_elec_eta[j]);
            h_zpj_exc_ElecPhi[i]->Fill(m_elec_phi[j]);
            if(j==0)
            {
                h_zpj_exc_ElecPtLead [i]->Fill(m_elec_pt [j]);    h_zpj_exc_ElecEtaLead[i]->Fill(m_elec_eta[j]);
                h_zpj_exc_ElecPhiLead[i]->Fill(m_elec_phi[j]);
            }
            else if(j==1)
            {
                h_zpj_exc_ElecPtSubLead [i]->Fill(m_elec_pt [j]); h_zpj_exc_ElecEtaSubLead[i]->Fill(m_elec_eta[j]);
                h_zpj_exc_ElecPhiSubLead[i]->Fill(m_elec_phi[j]);
            }
            else
            {
                h_zpj_exc_ElecPtExtra [i]->Fill(m_elec_pt [j]);   h_zpj_exc_ElecEtaExtra[i]->Fill(m_elec_eta[j]);
                h_zpj_exc_ElecPhiExtra[i]->Fill(m_elec_phi[j]);
            }
        }
        for(int j=0; j!=validJets.size(); j++)
        {
            int jetNum = min(j+1, i); // Fill histograms for nth jet, including jets beyond number of jets analyzed in the final histogram.
            h_zpj_exc_JetPt [i][jetNum]->Fill(m_jet_pt [validJets[j]]);
            h_zpj_exc_JetEta[i][jetNum]->Fill(m_jet_eta[validJets[j]]);
            h_zpj_exc_JetPhi[i][jetNum]->Fill(m_jet_phi[validJets[j]]);
            h_zpj_exc_JetCSV[i][jetNum]->Fill(m_jet_csv[validJets[j]]);
            h_zpj_exc_JetMSV[i][jetNum]->Fill(m_jet_msv[validJets[j]]);
        }
    }

  // HF(tagged) fills.
    // Fill exclusive histograms
    i = min((int)(HFJets.size()),nJetsAnalyzed);     // Find number of valid jets, fill that set of exclusive histograms

    if((validMuons||validElecs) && validMET) h_tag_exc_Zmass[i]->Fill(m_Z_mass);  // Fill these outside of ZpJ. Gives cut parts of plots, for comparison.
    if((validMuons||validElecs) && validZ  ) h_tag_exc_MET  [i]->Fill(m_MET_et);
    if(isZpJEvent)
    {
        nZHEEvents[i]++;
        h_tag_exc_Zphi  [i]->Fill(m_Z_phi );
        h_tag_exc_Zpt   [i]->Fill(m_Z_pt  );
        h_tag_exc_ZDelR [i]->Fill(Z_delR  );
        h_tag_exc_Zeta  [i]->Fill(m_Z_eta );
        h_tag_exc_nMuons[i]->Fill(m_nMuons);
        h_tag_exc_nElecs[i]->Fill(m_nElecs);
        h_tag_exc_nJets [i]->Fill(HFJets.size());
        for(int j=0; j<m_nMuons; j++)
        {
            h_tag_exc_MuonPt [i]->Fill(m_muon_pt [j]);   h_tag_exc_MuonEta[i]->Fill(m_muon_eta[j]);
            h_tag_exc_MuonPhi[i]->Fill(m_muon_phi[j]);   h_tag_exc_MuonIso[i]->Fill(m_muon_iso[j]);
            if(j==0)
            {
                h_tag_exc_MuonPtLead [i]->Fill(m_muon_pt [j]);    h_tag_exc_MuonEtaLead[i]->Fill(m_muon_eta[j]);
                h_tag_exc_MuonPhiLead[i]->Fill(m_muon_phi[j]);    h_tag_exc_MuonIsoLead[i]->Fill(m_muon_iso[j]);
            }
            else if(j==1)
            {
                h_tag_exc_MuonPtSubLead [i]->Fill(m_muon_pt [j]); h_tag_exc_MuonEtaSubLead[i]->Fill(m_muon_eta[j]);
                h_tag_exc_MuonPhiSubLead[i]->Fill(m_muon_phi[j]); h_tag_exc_MuonIsoSubLead[i]->Fill(m_muon_iso[j]);
            }
            else
            {
                h_tag_exc_MuonPtExtra [i]->Fill(m_muon_pt [j]);   h_tag_exc_MuonEtaExtra[i]->Fill(m_muon_eta[j]);
                h_tag_exc_MuonPhiExtra[i]->Fill(m_muon_phi[j]);   h_tag_exc_MuonIsoExtra[i]->Fill(m_muon_iso[j]);
            }
        }
        for(int j=0; j<m_nElecs; j++)
        {
            h_tag_exc_ElecPt [i]->Fill(m_elec_pt [j]);   h_tag_exc_ElecEta[i]->Fill(m_elec_eta[j]);
            h_tag_exc_ElecPhi[i]->Fill(m_elec_phi[j]);
            if(j==0)
            {
                h_tag_exc_ElecPtLead [i]->Fill(m_elec_pt [j]);    h_tag_exc_ElecEtaLead[i]->Fill(m_elec_eta[j]);
                h_tag_exc_ElecPhiLead[i]->Fill(m_elec_phi[j]);
            }
            else if(j==1)
            {
                h_tag_exc_ElecPtSubLead [i]->Fill(m_elec_pt [j]); h_tag_exc_ElecEtaSubLead[i]->Fill(m_elec_eta[j]);
                h_tag_exc_ElecPhiSubLead[i]->Fill(m_elec_phi[j]);
            }
            else
            {
                h_tag_exc_ElecPtExtra [i]->Fill(m_elec_pt [j]);   h_tag_exc_ElecEtaExtra[i]->Fill(m_elec_eta[j]);
                h_tag_exc_ElecPhiExtra[i]->Fill(m_elec_phi[j]);
            }
        }
        for(int j=0; j!=HFJets.size(); j++)
        {
            int jetNum = min(j+1, i); // Fill histograms for nth jet, including jets beyond number of jets analyzed in the final histogram.
            h_tag_exc_JetPt [i][jetNum]->Fill(m_jet_pt [HFJets[j]]);
            h_tag_exc_JetEta[i][jetNum]->Fill(m_jet_eta[HFJets[j]]);
            h_tag_exc_JetPhi[i][jetNum]->Fill(m_jet_phi[HFJets[j]]);
            h_tag_exc_JetCSV[i][jetNum]->Fill(m_jet_csv[HFJets[j]]);
            h_tag_exc_JetMSV[i][jetNum]->Fill(m_jet_msv[HFJets[j]]);
        }
    }


    return kTRUE;
}


void ZCControlPlotMaker::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}


void ZCControlPlotMaker::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}


TString ZCControlPlotMaker::saveOutputToFile(TString outputFileName)
{
  // Combine exclusive histograms into all-jet exclusive histograms
    for    (int i=0; i<=nJetsAnalyzed; i++)
        for(int j=1; j<=i; j++)
        {
            h_zpj_exc_JetPt [i][0]->Add(h_zpj_exc_JetPt [i][j]);
            h_zpj_exc_JetEta[i][0]->Add(h_zpj_exc_JetEta[i][j]);
            h_zpj_exc_JetPhi[i][0]->Add(h_zpj_exc_JetPhi[i][j]);
            h_zpj_exc_JetCSV[i][0]->Add(h_zpj_exc_JetCSV[i][j]);
            h_zpj_exc_JetMSV[i][0]->Add(h_zpj_exc_JetMSV[i][j]);
        }

  // Combine exclusive histograms to make inclusive histograms
    for    (int i=0; i<=nJetsAnalyzed; i++)
        for(int j=i; j<=nJetsAnalyzed; j++)
        {
            nZJIEvents[i] += nZJEEvents[j];
            h_zpj_inc_Zmass         [i]->Add(h_zpj_exc_Zmass         [j]);
            h_zpj_inc_Zpt           [i]->Add(h_zpj_exc_Zpt           [j]);
            h_zpj_inc_Zeta          [i]->Add(h_zpj_exc_Zeta          [j]);
            h_zpj_inc_Zphi          [i]->Add(h_zpj_exc_Zphi          [j]);
            h_zpj_inc_ZDelR         [i]->Add(h_zpj_exc_ZDelR         [j]);
            h_zpj_inc_nMuons        [i]->Add(h_zpj_exc_nMuons        [j]);
            h_zpj_inc_MuonPt        [i]->Add(h_zpj_exc_MuonPt        [j]);
            h_zpj_inc_MuonPtLead    [i]->Add(h_zpj_exc_MuonPtLead    [j]);
            h_zpj_inc_MuonPtSubLead [i]->Add(h_zpj_exc_MuonPtSubLead [j]);
            h_zpj_inc_MuonPtExtra   [i]->Add(h_zpj_exc_MuonPtExtra   [j]);
            h_zpj_inc_MuonEta       [i]->Add(h_zpj_exc_MuonEta       [j]);
            h_zpj_inc_MuonEtaLead   [i]->Add(h_zpj_exc_MuonEtaLead   [j]);
            h_zpj_inc_MuonEtaSubLead[i]->Add(h_zpj_exc_MuonEtaSubLead[j]);
            h_zpj_inc_MuonEtaExtra  [i]->Add(h_zpj_exc_MuonEtaExtra  [j]);
            h_zpj_inc_MuonPhi       [i]->Add(h_zpj_exc_MuonPhi       [j]);
            h_zpj_inc_MuonPhiLead   [i]->Add(h_zpj_exc_MuonPhiLead   [j]);
            h_zpj_inc_MuonPhiSubLead[i]->Add(h_zpj_exc_MuonPhiSubLead[j]);
            h_zpj_inc_MuonPhiExtra  [i]->Add(h_zpj_exc_MuonPhiExtra  [j]);
            h_zpj_inc_MuonIso       [i]->Add(h_zpj_exc_MuonIso       [j]);
            h_zpj_inc_MuonIsoLead   [i]->Add(h_zpj_exc_MuonIsoLead   [j]);
            h_zpj_inc_MuonIsoSubLead[i]->Add(h_zpj_exc_MuonIsoSubLead[j]);
            h_zpj_inc_MuonIsoExtra  [i]->Add(h_zpj_exc_MuonIsoExtra  [j]);
            h_zpj_inc_nElecs        [i]->Add(h_zpj_exc_nElecs        [j]);
            h_zpj_inc_ElecPt        [i]->Add(h_zpj_exc_ElecPt        [j]);
            h_zpj_inc_ElecPtLead    [i]->Add(h_zpj_exc_ElecPtLead    [j]);
            h_zpj_inc_ElecPtSubLead [i]->Add(h_zpj_exc_ElecPtSubLead [j]);
            h_zpj_inc_ElecPtExtra   [i]->Add(h_zpj_exc_ElecPtExtra   [j]);
            h_zpj_inc_ElecEta       [i]->Add(h_zpj_exc_ElecEta       [j]);
            h_zpj_inc_ElecEtaLead   [i]->Add(h_zpj_exc_ElecEtaLead   [j]);
            h_zpj_inc_ElecEtaSubLead[i]->Add(h_zpj_exc_ElecEtaSubLead[j]);
            h_zpj_inc_ElecEtaExtra  [i]->Add(h_zpj_exc_ElecEtaExtra  [j]);
            h_zpj_inc_ElecPhi       [i]->Add(h_zpj_exc_ElecPhi       [j]);
            h_zpj_inc_ElecPhiLead   [i]->Add(h_zpj_exc_ElecPhiLead   [j]);
            h_zpj_inc_ElecPhiSubLead[i]->Add(h_zpj_exc_ElecPhiSubLead[j]);
            h_zpj_inc_ElecPhiExtra  [i]->Add(h_zpj_exc_ElecPhiExtra  [j]);
            h_zpj_inc_MET           [i]->Add(h_zpj_exc_MET           [j]);
            h_zpj_inc_nJets         [i]->Add(h_zpj_exc_nJets         [j]);
            for(int k=1; k<=j; k++)
            {   // Working with Z+iJ(incl.) event. Equals sum of Z+jJ exclusive events, where j=[i,nJetsAnalyzed]. 
                h_zpj_inc_JetPt [i][0]->Add(h_zpj_exc_JetPt [j][k]);   h_zpj_inc_JetPt [i][k]->Add(h_zpj_exc_JetPt [j][k]);
                h_zpj_inc_JetEta[i][0]->Add(h_zpj_exc_JetEta[j][k]);   h_zpj_inc_JetEta[i][k]->Add(h_zpj_exc_JetEta[j][k]);
                h_zpj_inc_JetPhi[i][0]->Add(h_zpj_exc_JetPhi[j][k]);   h_zpj_inc_JetPhi[i][k]->Add(h_zpj_exc_JetPhi[j][k]);
                h_zpj_inc_JetCSV[i][0]->Add(h_zpj_exc_JetCSV[j][k]);   h_zpj_inc_JetCSV[i][k]->Add(h_zpj_exc_JetCSV[j][k]);
                h_zpj_inc_JetMSV[i][0]->Add(h_zpj_exc_JetMSV[j][k]);   h_zpj_inc_JetMSV[i][k]->Add(h_zpj_exc_JetMSV[j][k]);
            }
        }

  // Do it all again for HF jet histograms
  // Combine exclusive HF histograms into all-jet exclusive histograms
    for    (int i=0; i<=nJetsAnalyzed; i++)
        for(int j=1; j<=i; j++)
        {
            h_tag_exc_JetPt [i][0]->Add(h_tag_exc_JetPt [i][j]);
            h_tag_exc_JetEta[i][0]->Add(h_tag_exc_JetEta[i][j]);
            h_tag_exc_JetPhi[i][0]->Add(h_tag_exc_JetPhi[i][j]);
            h_tag_exc_JetCSV[i][0]->Add(h_tag_exc_JetCSV[i][j]);
            h_tag_exc_JetMSV[i][0]->Add(h_tag_exc_JetMSV[i][j]);
        }

  // Combine exclusive HF histograms to make inclusive histograms
    for    (int i=0; i<=nJetsAnalyzed; i++)
        for(int j=i; j<=nJetsAnalyzed; j++)
        {
            nZHIEvents[i] += nZHEEvents[j];
            h_tag_inc_Zmass         [i]->Add(h_tag_exc_Zmass         [j]); 
            h_tag_inc_Zpt           [i]->Add(h_tag_exc_Zpt           [j]); 
            h_tag_inc_Zeta          [i]->Add(h_tag_exc_Zeta          [j]); 
            h_tag_inc_Zphi          [i]->Add(h_tag_exc_Zphi          [j]); 
            h_tag_inc_ZDelR         [i]->Add(h_tag_exc_ZDelR         [j]); 
            h_tag_inc_nMuons        [i]->Add(h_tag_exc_nMuons        [j]); 
            h_tag_inc_MuonPt        [i]->Add(h_tag_exc_MuonPt        [j]); 
            h_tag_inc_MuonPtLead    [i]->Add(h_tag_exc_MuonPtLead    [j]); 
            h_tag_inc_MuonPtSubLead [i]->Add(h_tag_exc_MuonPtSubLead [j]); 
            h_tag_inc_MuonPtExtra   [i]->Add(h_tag_exc_MuonPtExtra   [j]); 
            h_tag_inc_MuonEta       [i]->Add(h_tag_exc_MuonEta       [j]); 
            h_tag_inc_MuonEtaLead   [i]->Add(h_tag_exc_MuonEtaLead   [j]); 
            h_tag_inc_MuonEtaSubLead[i]->Add(h_tag_exc_MuonEtaSubLead[j]); 
            h_tag_inc_MuonEtaExtra  [i]->Add(h_tag_exc_MuonEtaExtra  [j]); 
            h_tag_inc_MuonPhi       [i]->Add(h_tag_exc_MuonPhi       [j]); 
            h_tag_inc_MuonPhiLead   [i]->Add(h_tag_exc_MuonPhiLead   [j]); 
            h_tag_inc_MuonPhiSubLead[i]->Add(h_tag_exc_MuonPhiSubLead[j]); 
            h_tag_inc_MuonPhiExtra  [i]->Add(h_tag_exc_MuonPhiExtra  [j]); 
            h_tag_inc_MuonIso       [i]->Add(h_tag_exc_MuonIso       [j]); 
            h_tag_inc_MuonIsoLead   [i]->Add(h_tag_exc_MuonIsoLead   [j]); 
            h_tag_inc_MuonIsoSubLead[i]->Add(h_tag_exc_MuonIsoSubLead[j]); 
            h_tag_inc_MuonIsoExtra  [i]->Add(h_tag_exc_MuonIsoExtra  [j]); 
            h_tag_inc_nElecs        [i]->Add(h_tag_exc_nElecs        [j]); 
            h_tag_inc_ElecPt        [i]->Add(h_tag_exc_ElecPt        [j]); 
            h_tag_inc_ElecPtLead    [i]->Add(h_tag_exc_ElecPtLead    [j]); 
            h_tag_inc_ElecPtSubLead [i]->Add(h_tag_exc_ElecPtSubLead [j]); 
            h_tag_inc_ElecPtExtra   [i]->Add(h_tag_exc_ElecPtExtra   [j]); 
            h_tag_inc_ElecEta       [i]->Add(h_tag_exc_ElecEta       [j]); 
            h_tag_inc_ElecEtaLead   [i]->Add(h_tag_exc_ElecEtaLead   [j]); 
            h_tag_inc_ElecEtaSubLead[i]->Add(h_tag_exc_ElecEtaSubLead[j]); 
            h_tag_inc_ElecEtaExtra  [i]->Add(h_tag_exc_ElecEtaExtra  [j]); 
            h_tag_inc_ElecPhi       [i]->Add(h_tag_exc_ElecPhi       [j]); 
            h_tag_inc_ElecPhiLead   [i]->Add(h_tag_exc_ElecPhiLead   [j]); 
            h_tag_inc_ElecPhiSubLead[i]->Add(h_tag_exc_ElecPhiSubLead[j]); 
            h_tag_inc_ElecPhiExtra  [i]->Add(h_tag_exc_ElecPhiExtra  [j]); 
            h_tag_inc_MET           [i]->Add(h_tag_exc_MET           [j]); 
            h_tag_inc_nJets         [i]->Add(h_tag_exc_nJets         [j]);
            for(int k=1; k<=j; k++)
            {   // Working with Z+iJ(incl.) event. Equals sum of Z+jJ exclusive events, where j=[i,nJetsAnalyzed]. 
                h_tag_inc_JetPt [i][0]->Add(h_tag_exc_JetPt [j][k]);   h_tag_inc_JetPt [i][k]->Add(h_tag_exc_JetPt [j][k]);
                h_tag_inc_JetEta[i][0]->Add(h_tag_exc_JetEta[j][k]);   h_tag_inc_JetEta[i][k]->Add(h_tag_exc_JetEta[j][k]);
                h_tag_inc_JetPhi[i][0]->Add(h_tag_exc_JetPhi[j][k]);   h_tag_inc_JetPhi[i][k]->Add(h_tag_exc_JetPhi[j][k]);
                h_tag_inc_JetCSV[i][0]->Add(h_tag_exc_JetCSV[j][k]);   h_tag_inc_JetCSV[i][k]->Add(h_tag_exc_JetCSV[j][k]);
                h_tag_inc_JetMSV[i][0]->Add(h_tag_exc_JetMSV[j][k]);   h_tag_inc_JetMSV[i][k]->Add(h_tag_exc_JetMSV[j][k]);
            }
        }

  // Open a file, add directory substructure
    TFile * outputFile = new TFile(outputFileName + ".root", "RECREATE");
    TString dirRawLabel = "raw";   d_raw = outputFile->mkdir(dirRawLabel);
    TString dirZpJLabel = "zpj";   d_zpj = outputFile->mkdir(dirZpJLabel);
    TString dirTagLabel = "tag";   d_tag = outputFile->mkdir(dirTagLabel);
    TString dirIncLabel = "inc";   TString dirExcLabel = "exc";

    for(int i=0; i<=nJetsAnalyzed; i++)
    {
        TString number; number.Form("%d", i);
        d_zpj_inc.push_back(d_zpj->mkdir(dirIncLabel+number));
        d_tag_inc.push_back(d_tag->mkdir(dirIncLabel+number));
    }
    for(int i=0; i<=nJetsAnalyzed; i++)
    {
        TString number; number.Form("%d", i);
        d_zpj_exc.push_back(d_zpj->mkdir(dirExcLabel+number));
        d_tag_exc.push_back(d_tag->mkdir(dirExcLabel+number));
    }

  // Save all of the current histograms to this file, and close.
    // Raw histograms
    d_raw->Append(h_raw_Zmass  );   d_raw->Append(h_raw_Zpt);    d_raw->Append( h_raw_Zeta    );    d_raw->Append( h_raw_Zphi    );    d_raw->Append( h_raw_ZDelR   );
    d_raw->Append(h_raw_nMuons );
    d_raw->Append(h_raw_MuonPt );   d_raw->Append(h_raw_MuonPtLead );   d_raw->Append(h_raw_MuonPtSubLead );   d_raw->Append(h_raw_MuonPtExtra );
    d_raw->Append(h_raw_MuonEta);   d_raw->Append(h_raw_MuonEtaLead);   d_raw->Append(h_raw_MuonEtaSubLead);   d_raw->Append(h_raw_MuonEtaExtra);
    d_raw->Append(h_raw_MuonPhi);   d_raw->Append(h_raw_MuonPhiLead);   d_raw->Append(h_raw_MuonPhiSubLead);   d_raw->Append(h_raw_MuonPhiExtra);
    d_raw->Append(h_raw_MuonIso);   d_raw->Append(h_raw_MuonIsoLead);   d_raw->Append(h_raw_MuonIsoSubLead);   d_raw->Append(h_raw_MuonIsoExtra);
    d_raw->Append(h_raw_nElecs );
    d_raw->Append(h_raw_ElecPt );   d_raw->Append(h_raw_ElecPtLead );   d_raw->Append(h_raw_ElecPtSubLead );   d_raw->Append(h_raw_ElecPtExtra );
    d_raw->Append(h_raw_ElecEta);   d_raw->Append(h_raw_ElecEtaLead);   d_raw->Append(h_raw_ElecEtaSubLead);   d_raw->Append(h_raw_ElecEtaExtra);
    d_raw->Append(h_raw_ElecPhi);   d_raw->Append(h_raw_ElecPhiLead);   d_raw->Append(h_raw_ElecPhiSubLead);   d_raw->Append(h_raw_ElecPhiExtra);
    d_raw->Append(h_raw_MET    );   d_raw->Append(h_raw_nJets );
    d_raw->Append(h_raw_JetPt  );   d_raw->Append(h_raw_JetEta);   d_raw->Append(h_raw_JetPhi);   d_raw->Append(h_raw_JetCSV);   d_raw->Append(h_raw_JetMSV);

    for(int i=0; i<=nJetsAnalyzed; i++)
    {
        d_zpj_inc[i]->Append(h_zpj_inc_Zmass[i]);           d_zpj_exc[i]->Append(h_zpj_exc_Zmass[i]);           d_tag_inc[i]->Append(h_tag_inc_Zmass[i]);           d_tag_exc[i]->Append(h_tag_exc_Zmass[i]);           
        d_zpj_inc[i]->Append(h_zpj_inc_Zpt[i]);             d_zpj_exc[i]->Append(h_zpj_exc_Zpt[i]);             d_tag_inc[i]->Append(h_tag_inc_Zpt[i]);             d_tag_exc[i]->Append(h_tag_exc_Zpt[i]);             
        d_zpj_inc[i]->Append(h_zpj_inc_Zeta[i]);            d_zpj_exc[i]->Append(h_zpj_exc_Zeta[i]);            d_tag_inc[i]->Append(h_tag_inc_Zeta[i]);            d_tag_exc[i]->Append(h_tag_exc_Zeta[i]);            
        d_zpj_inc[i]->Append(h_zpj_inc_Zphi[i]);            d_zpj_exc[i]->Append(h_zpj_exc_Zphi[i]);            d_tag_inc[i]->Append(h_tag_inc_Zphi[i]);            d_tag_exc[i]->Append(h_tag_exc_Zphi[i]);            
        d_zpj_inc[i]->Append(h_zpj_inc_ZDelR[i]);           d_zpj_exc[i]->Append(h_zpj_exc_ZDelR[i]);           d_tag_inc[i]->Append(h_tag_inc_ZDelR[i]);           d_tag_exc[i]->Append(h_tag_exc_ZDelR[i]);           
        d_zpj_inc[i]->Append(h_zpj_inc_nMuons[i]);          d_zpj_exc[i]->Append(h_zpj_exc_nMuons[i]);          d_tag_inc[i]->Append(h_tag_inc_nMuons[i]);          d_tag_exc[i]->Append(h_tag_exc_nMuons[i]);          
        d_zpj_inc[i]->Append(h_zpj_inc_MuonPt[i]);          d_zpj_exc[i]->Append(h_zpj_exc_MuonPt[i]);          d_tag_inc[i]->Append(h_tag_inc_MuonPt[i]);          d_tag_exc[i]->Append(h_tag_exc_MuonPt[i]);          
        d_zpj_inc[i]->Append(h_zpj_inc_MuonPtLead[i]);      d_zpj_exc[i]->Append(h_zpj_exc_MuonPtLead[i]);      d_tag_inc[i]->Append(h_tag_inc_MuonPtLead[i]);      d_tag_exc[i]->Append(h_tag_exc_MuonPtLead[i]);      
        d_zpj_inc[i]->Append(h_zpj_inc_MuonPtSubLead[i]);   d_zpj_exc[i]->Append(h_zpj_exc_MuonPtSubLead[i]);   d_tag_inc[i]->Append(h_tag_inc_MuonPtSubLead[i]);   d_tag_exc[i]->Append(h_tag_exc_MuonPtSubLead[i]);   
        d_zpj_inc[i]->Append(h_zpj_inc_MuonPtExtra[i]);     d_zpj_exc[i]->Append(h_zpj_exc_MuonPtExtra[i]);     d_tag_inc[i]->Append(h_tag_inc_MuonPtExtra[i]);     d_tag_exc[i]->Append(h_tag_exc_MuonPtExtra[i]);     
        d_zpj_inc[i]->Append(h_zpj_inc_MuonEta[i]);         d_zpj_exc[i]->Append(h_zpj_exc_MuonEta[i]);         d_tag_inc[i]->Append(h_tag_inc_MuonEta[i]);         d_tag_exc[i]->Append(h_tag_exc_MuonEta[i]);         
        d_zpj_inc[i]->Append(h_zpj_inc_MuonEtaLead[i]);     d_zpj_exc[i]->Append(h_zpj_exc_MuonEtaLead[i]);     d_tag_inc[i]->Append(h_tag_inc_MuonEtaLead[i]);     d_tag_exc[i]->Append(h_tag_exc_MuonEtaLead[i]);     
        d_zpj_inc[i]->Append(h_zpj_inc_MuonEtaSubLead[i]);  d_zpj_exc[i]->Append(h_zpj_exc_MuonEtaSubLead[i]);  d_tag_inc[i]->Append(h_tag_inc_MuonEtaSubLead[i]);  d_tag_exc[i]->Append(h_tag_exc_MuonEtaSubLead[i]);  
        d_zpj_inc[i]->Append(h_zpj_inc_MuonEtaExtra[i]);    d_zpj_exc[i]->Append(h_zpj_exc_MuonEtaExtra[i]);    d_tag_inc[i]->Append(h_tag_inc_MuonEtaExtra[i]);    d_tag_exc[i]->Append(h_tag_exc_MuonEtaExtra[i]);    
        d_zpj_inc[i]->Append(h_zpj_inc_MuonPhi[i]);         d_zpj_exc[i]->Append(h_zpj_exc_MuonPhi[i]);         d_tag_inc[i]->Append(h_tag_inc_MuonPhi[i]);         d_tag_exc[i]->Append(h_tag_exc_MuonPhi[i]);         
        d_zpj_inc[i]->Append(h_zpj_inc_MuonPhiLead[i]);     d_zpj_exc[i]->Append(h_zpj_exc_MuonPhiLead[i]);     d_tag_inc[i]->Append(h_tag_inc_MuonPhiLead[i]);     d_tag_exc[i]->Append(h_tag_exc_MuonPhiLead[i]);     
        d_zpj_inc[i]->Append(h_zpj_inc_MuonPhiSubLead[i]);  d_zpj_exc[i]->Append(h_zpj_exc_MuonPhiSubLead[i]);  d_tag_inc[i]->Append(h_tag_inc_MuonPhiSubLead[i]);  d_tag_exc[i]->Append(h_tag_exc_MuonPhiSubLead[i]);  
        d_zpj_inc[i]->Append(h_zpj_inc_MuonPhiExtra[i]);    d_zpj_exc[i]->Append(h_zpj_exc_MuonPhiExtra[i]);    d_tag_inc[i]->Append(h_tag_inc_MuonPhiExtra[i]);    d_tag_exc[i]->Append(h_tag_exc_MuonPhiExtra[i]);    
        d_zpj_inc[i]->Append(h_zpj_inc_MuonIso[i]);         d_zpj_exc[i]->Append(h_zpj_exc_MuonIso[i]);         d_tag_inc[i]->Append(h_tag_inc_MuonIso[i]);         d_tag_exc[i]->Append(h_tag_exc_MuonIso[i]);         
        d_zpj_inc[i]->Append(h_zpj_inc_MuonIsoLead[i]);     d_zpj_exc[i]->Append(h_zpj_exc_MuonIsoLead[i]);     d_tag_inc[i]->Append(h_tag_inc_MuonIsoLead[i]);     d_tag_exc[i]->Append(h_tag_exc_MuonIsoLead[i]);     
        d_zpj_inc[i]->Append(h_zpj_inc_MuonIsoSubLead[i]);  d_zpj_exc[i]->Append(h_zpj_exc_MuonIsoSubLead[i]);  d_tag_inc[i]->Append(h_tag_inc_MuonIsoSubLead[i]);  d_tag_exc[i]->Append(h_tag_exc_MuonIsoSubLead[i]);  
        d_zpj_inc[i]->Append(h_zpj_inc_MuonIsoExtra[i]);    d_zpj_exc[i]->Append(h_zpj_exc_MuonIsoExtra[i]);    d_tag_inc[i]->Append(h_tag_inc_MuonIsoExtra[i]);    d_tag_exc[i]->Append(h_tag_exc_MuonIsoExtra[i]);    
        d_zpj_inc[i]->Append(h_zpj_inc_nElecs[i]);          d_zpj_exc[i]->Append(h_zpj_exc_nElecs[i]);          d_tag_inc[i]->Append(h_tag_inc_nElecs[i]);          d_tag_exc[i]->Append(h_tag_exc_nElecs[i]);          
        d_zpj_inc[i]->Append(h_zpj_inc_ElecPt[i]);          d_zpj_exc[i]->Append(h_zpj_exc_ElecPt[i]);          d_tag_inc[i]->Append(h_tag_inc_ElecPt[i]);          d_tag_exc[i]->Append(h_tag_exc_ElecPt[i]);          
        d_zpj_inc[i]->Append(h_zpj_inc_ElecPtLead[i]);      d_zpj_exc[i]->Append(h_zpj_exc_ElecPtLead[i]);      d_tag_inc[i]->Append(h_tag_inc_ElecPtLead[i]);      d_tag_exc[i]->Append(h_tag_exc_ElecPtLead[i]);      
        d_zpj_inc[i]->Append(h_zpj_inc_ElecPtSubLead[i]);   d_zpj_exc[i]->Append(h_zpj_exc_ElecPtSubLead[i]);   d_tag_inc[i]->Append(h_tag_inc_ElecPtSubLead[i]);   d_tag_exc[i]->Append(h_tag_exc_ElecPtSubLead[i]);   
        d_zpj_inc[i]->Append(h_zpj_inc_ElecPtExtra[i]);     d_zpj_exc[i]->Append(h_zpj_exc_ElecPtExtra[i]);     d_tag_inc[i]->Append(h_tag_inc_ElecPtExtra[i]);     d_tag_exc[i]->Append(h_tag_exc_ElecPtExtra[i]);     
        d_zpj_inc[i]->Append(h_zpj_inc_ElecEta[i]);         d_zpj_exc[i]->Append(h_zpj_exc_ElecEta[i]);         d_tag_inc[i]->Append(h_tag_inc_ElecEta[i]);         d_tag_exc[i]->Append(h_tag_exc_ElecEta[i]);         
        d_zpj_inc[i]->Append(h_zpj_inc_ElecEtaLead[i]);     d_zpj_exc[i]->Append(h_zpj_exc_ElecEtaLead[i]);     d_tag_inc[i]->Append(h_tag_inc_ElecEtaLead[i]);     d_tag_exc[i]->Append(h_tag_exc_ElecEtaLead[i]);     
        d_zpj_inc[i]->Append(h_zpj_inc_ElecEtaSubLead[i]);  d_zpj_exc[i]->Append(h_zpj_exc_ElecEtaSubLead[i]);  d_tag_inc[i]->Append(h_tag_inc_ElecEtaSubLead[i]);  d_tag_exc[i]->Append(h_tag_exc_ElecEtaSubLead[i]);  
        d_zpj_inc[i]->Append(h_zpj_inc_ElecEtaExtra[i]);    d_zpj_exc[i]->Append(h_zpj_exc_ElecEtaExtra[i]);    d_tag_inc[i]->Append(h_tag_inc_ElecEtaExtra[i]);    d_tag_exc[i]->Append(h_tag_exc_ElecEtaExtra[i]);    
        d_zpj_inc[i]->Append(h_zpj_inc_ElecPhi[i]);         d_zpj_exc[i]->Append(h_zpj_exc_ElecPhi[i]);         d_tag_inc[i]->Append(h_tag_inc_ElecPhi[i]);         d_tag_exc[i]->Append(h_tag_exc_ElecPhi[i]);         
        d_zpj_inc[i]->Append(h_zpj_inc_ElecPhiLead[i]);     d_zpj_exc[i]->Append(h_zpj_exc_ElecPhiLead[i]);     d_tag_inc[i]->Append(h_tag_inc_ElecPhiLead[i]);     d_tag_exc[i]->Append(h_tag_exc_ElecPhiLead[i]);     
        d_zpj_inc[i]->Append(h_zpj_inc_ElecPhiSubLead[i]);  d_zpj_exc[i]->Append(h_zpj_exc_ElecPhiSubLead[i]);  d_tag_inc[i]->Append(h_tag_inc_ElecPhiSubLead[i]);  d_tag_exc[i]->Append(h_tag_exc_ElecPhiSubLead[i]);  
        d_zpj_inc[i]->Append(h_zpj_inc_ElecPhiExtra[i]);    d_zpj_exc[i]->Append(h_zpj_exc_ElecPhiExtra[i]);    d_tag_inc[i]->Append(h_tag_inc_ElecPhiExtra[i]);    d_tag_exc[i]->Append(h_tag_exc_ElecPhiExtra[i]);    
        d_zpj_inc[i]->Append(h_zpj_inc_MET[i]);             d_zpj_exc[i]->Append(h_zpj_exc_MET[i]);             d_tag_inc[i]->Append(h_tag_inc_MET[i]);             d_tag_exc[i]->Append(h_tag_exc_MET[i]);             
        d_zpj_inc[i]->Append(h_zpj_inc_nJets[i]);           d_zpj_exc[i]->Append(h_zpj_exc_nJets[i]);           d_tag_inc[i]->Append(h_tag_inc_nJets[i]);           d_tag_exc[i]->Append(h_tag_exc_nJets[i]);           

        for(int j=0; j<=nJetsAnalyzed; j++)
        {
          // Inclusive: First histogram inc
            d_zpj_inc[i]->Append(h_zpj_inc_JetPt [i][j]);   d_tag_inc[i]->Append(h_tag_inc_JetPt [i][j]);
            d_zpj_inc[i]->Append(h_zpj_inc_JetEta[i][j]);   d_tag_inc[i]->Append(h_tag_inc_JetEta[i][j]);
            d_zpj_inc[i]->Append(h_zpj_inc_JetPhi[i][j]);   d_tag_inc[i]->Append(h_tag_inc_JetPhi[i][j]);
            d_zpj_inc[i]->Append(h_zpj_inc_JetCSV[i][j]);   d_tag_inc[i]->Append(h_tag_inc_JetCSV[i][j]);
            d_zpj_inc[i]->Append(h_zpj_inc_JetMSV[i][j]);   d_tag_inc[i]->Append(h_tag_inc_JetMSV[i][j]);

            if(j > i) continue;
            d_zpj_exc[i]->Append(h_zpj_exc_JetPt [i][j]);   d_tag_exc[i]->Append(h_tag_exc_JetPt [i][j]);
            d_zpj_exc[i]->Append(h_zpj_exc_JetEta[i][j]);   d_tag_exc[i]->Append(h_tag_exc_JetEta[i][j]);
            d_zpj_exc[i]->Append(h_zpj_exc_JetPhi[i][j]);   d_tag_exc[i]->Append(h_tag_exc_JetPhi[i][j]);
            d_zpj_exc[i]->Append(h_zpj_exc_JetCSV[i][j]);   d_tag_exc[i]->Append(h_tag_exc_JetCSV[i][j]);
            d_zpj_exc[i]->Append(h_zpj_exc_JetMSV[i][j]);   d_tag_exc[i]->Append(h_tag_exc_JetMSV[i][j]);
        }
    }

    outputFile->Write();
    outputFile->Close();

  // Create the log file text.
    log << "  ===ZCControlPlotMaker - " << outputFileName << "===\n"
           "  Counts -\n"
           "    Entries in chain: " << setw(14) << nEntries         << "\n"
           "    Events Processed: " << setw(14) << nEventsProcessed << "\n"
           "    Raw Events:       " << setw(14) << nRawEvents       << "\n"
           "    Raw Muon Events:  " << setw(14) << nRawMuonEvents   << "\n"
           "    Raw Elec Events:  " << setw(14) << nRawElecEvents   << "\n";
    log <<   "  Exclusive Z+j: ";  for(int i=0; i!=nJetsAnalyzed+1; i++) log << setw(14) << nZJEEvents[i];
    log << "\n  Inclusive Z+j: ";  for(int i=0; i!=nJetsAnalyzed+1; i++) log << setw(14) << nZJIEvents[i];
    log << "\n  Exclusive Z+HF:";  for(int i=0; i!=nJetsAnalyzed+1; i++) log << setw(14) << nZHEEvents[i];
    log << "\n  Inclusive Z+HF:";  for(int i=0; i!=nJetsAnalyzed+1; i++) log << setw(14) << nZHIEvents[i];
    log << "\n\n";

  // Open a log file, save the contents of log to the file, and close.
    TString  logFileName = outputFileName + ".log";
    ofstream logFile(logFileName);
    logFile << log.str();
    logFile.close();

return log.str();
}

