#ifndef GUARD_ZCControlPlotMaker_h
#define GUARD_ZCControlPlotMaker_h

// ZCTreeControlPlotMaker
// Class inheritted from TSelector (root).
// Runs over zcStep2 trees and plots histograms of interesting variables.


#include <TROOT.h>
#include <TBranch.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1.h>
#include <vector>
#include "ZCStandardVariables.h"

using namespace ZCStandardVariables;

typedef unsigned long counter;

class ZCControlPlotMaker : public TSelector
{
public:
    ZCControlPlotMaker(TTree* /*tree*/= 0) : fChain(0){} 
    virtual        ~ZCControlPlotMaker(){}

  // Overloaded TSelector Functions
    virtual Int_t   Version() const { return 2; }
    virtual void    Begin     (TTree *tree);
    virtual void    SlaveBegin(TTree *tree);
    virtual void    Init      (TTree *tree);
    virtual Bool_t  Notify();
    virtual Bool_t  Process   (Long64_t entry);

    virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
    virtual void    SetOption(const char *option) { fOption = option; }
    virtual void    SetObject(TObject *obj)       { fObject = obj;    }
    virtual void    SetInputList(TList *input)    { fInput  = input;  }
    virtual TList  *GetOutputList() const         { return fOutput;   }

    virtual void    SlaveTerminate();
    virtual void    Terminate();

  // New Functions
    TString saveOutputToFile(TString);

  // TTree
    TTree *fChain;

  // Counters
    counter nEntries;            // Total number of entries in tree/chain
    counter nEventsProcessed;    // Total number of events processed from chain
    counter nRawEvents;          // Events that pass JSON Selection
    counter nRawMuonEvents;      // Events of Muon type that pass JSON Selection
    counter nRawElecEvents;      // Events of Electron type that pass JSON Selection
    std::vector<counter> nZJEEvents;  // Z+N jet events(exclusive)
    std::vector<counter> nZJIEvents;  // Z+N jet events(inclusive)
    std::vector<counter> nZHEEvents;  // Z+N HFjet events(exclusive)
    std::vector<counter> nZHIEvents;  // Z+N HFjet events(inclusive)

  // Log file
    std::stringstream log;

  // Selection Variables
    bool        usingSim  ; // Simulation events. For plotting sim-truth information.
    bool        usingZee  ; // Simulation events. For plotting sim-truth information.
    bool        usingZuu  ; // Simulation events. For plotting sim-truth information.
    bool        validJSON ; // Event has a certain trigger and comes from an event in a good run.
    bool        validMuons; // Muon isolation, eta, pt cuts met
    bool        validElecs; // Electron isolation, eta, pt cuts met
    bool        validZ    ; // Invariant dimuon mass within range
    bool        validMET  ; // MET maximum not exceeded
    bool        isZpJEvent; // Combination of above Muon, Z, MET checks
    std::vector<int> validJets ; // Numbers for valid jets from this event(pt, eta cuts met)
    std::vector<int> HFJets    ; // Numbers for HF-tagged jets from this event(csv & msv cuts)

  // Directories w/i file for storing histograms
    // Event Selection Sets
    //   raw - Before selection (But with JSON, Trigger selection?)
    //   std - Standard selection (Muon, Z, MET, JSON, Trigger selection)
    //   zpj - Z+j (at least one valid jet)
    //   tag - B-Tagged
    // Jet prop subdirectories
    //   inc - inclusive. Properties for all jets in an n-jet event
    //   exc - exclusive. Properties for nth jet

    // Two type of events: incl-n and excl-n   -- events with n or more jets, and events with only n jets.
    // So you need 2*numJetsPlotted directories for each selection set. One for inclusive plots, one for exclusive plots.

    TDirectory* d_raw;
    TDirectory* d_zpj; std::vector<TDirectory*> d_zpj_inc, d_zpj_exc;
    TDirectory* d_tag; std::vector<TDirectory*> d_tag_inc, d_tag_exc;

  // Histograms
    // Jet Plots - for n from 0 to n-max
    //   nExc - For events w/ exactly n jets
    //   nInc - For events w/ n or more jets
    // Exclusive plots created first, then combined into inclusive plots.
    // Plots: Z, muons, MET, Jets, HF Jet props (mult, pt, eta, etc.)
    //  Jet properties for all jets and nth jet
    TH1F *h_raw_Zmass         ;   std::vector<TH1F*> h_zpj_inc_Zmass         , h_zpj_exc_Zmass         , h_tag_inc_Zmass         , h_tag_exc_Zmass         ;
    TH1F *h_raw_Zpt           ;   std::vector<TH1F*> h_zpj_inc_Zpt           , h_zpj_exc_Zpt           , h_tag_inc_Zpt           , h_tag_exc_Zpt           ;
    TH1F *h_raw_Zeta          ;   std::vector<TH1F*> h_zpj_inc_Zeta          , h_zpj_exc_Zeta          , h_tag_inc_Zeta          , h_tag_exc_Zeta          ;
    TH1F *h_raw_Zphi          ;   std::vector<TH1F*> h_zpj_inc_Zphi          , h_zpj_exc_Zphi          , h_tag_inc_Zphi          , h_tag_exc_Zphi          ;
    TH1F *h_raw_ZDelR         ;   std::vector<TH1F*> h_zpj_inc_ZDelR         , h_zpj_exc_ZDelR         , h_tag_inc_ZDelR         , h_tag_exc_ZDelR         ;
    TH1F *h_raw_nMuons        ;   std::vector<TH1F*> h_zpj_inc_nMuons        , h_zpj_exc_nMuons        , h_tag_inc_nMuons        , h_tag_exc_nMuons        ;
    TH1F *h_raw_MuonPt        ;   std::vector<TH1F*> h_zpj_inc_MuonPt        , h_zpj_exc_MuonPt        , h_tag_inc_MuonPt        , h_tag_exc_MuonPt        ;
    TH1F *h_raw_MuonPtLead    ;   std::vector<TH1F*> h_zpj_inc_MuonPtLead    , h_zpj_exc_MuonPtLead    , h_tag_inc_MuonPtLead    , h_tag_exc_MuonPtLead    ;
    TH1F *h_raw_MuonPtSubLead ;   std::vector<TH1F*> h_zpj_inc_MuonPtSubLead , h_zpj_exc_MuonPtSubLead , h_tag_inc_MuonPtSubLead , h_tag_exc_MuonPtSubLead ;
    TH1F *h_raw_MuonPtExtra   ;   std::vector<TH1F*> h_zpj_inc_MuonPtExtra   , h_zpj_exc_MuonPtExtra   , h_tag_inc_MuonPtExtra   , h_tag_exc_MuonPtExtra   ;
    TH1F *h_raw_MuonEta       ;   std::vector<TH1F*> h_zpj_inc_MuonEta       , h_zpj_exc_MuonEta       , h_tag_inc_MuonEta       , h_tag_exc_MuonEta       ;
    TH1F *h_raw_MuonEtaLead   ;   std::vector<TH1F*> h_zpj_inc_MuonEtaLead   , h_zpj_exc_MuonEtaLead   , h_tag_inc_MuonEtaLead   , h_tag_exc_MuonEtaLead   ;
    TH1F *h_raw_MuonEtaSubLead;   std::vector<TH1F*> h_zpj_inc_MuonEtaSubLead, h_zpj_exc_MuonEtaSubLead, h_tag_inc_MuonEtaSubLead, h_tag_exc_MuonEtaSubLead;
    TH1F *h_raw_MuonEtaExtra  ;   std::vector<TH1F*> h_zpj_inc_MuonEtaExtra  , h_zpj_exc_MuonEtaExtra  , h_tag_inc_MuonEtaExtra  , h_tag_exc_MuonEtaExtra  ;
    TH1F *h_raw_MuonPhi       ;   std::vector<TH1F*> h_zpj_inc_MuonPhi       , h_zpj_exc_MuonPhi       , h_tag_inc_MuonPhi       , h_tag_exc_MuonPhi       ;
    TH1F *h_raw_MuonPhiLead   ;   std::vector<TH1F*> h_zpj_inc_MuonPhiLead   , h_zpj_exc_MuonPhiLead   , h_tag_inc_MuonPhiLead   , h_tag_exc_MuonPhiLead   ;
    TH1F *h_raw_MuonPhiSubLead;   std::vector<TH1F*> h_zpj_inc_MuonPhiSubLead, h_zpj_exc_MuonPhiSubLead, h_tag_inc_MuonPhiSubLead, h_tag_exc_MuonPhiSubLead;
    TH1F *h_raw_MuonPhiExtra  ;   std::vector<TH1F*> h_zpj_inc_MuonPhiExtra  , h_zpj_exc_MuonPhiExtra  , h_tag_inc_MuonPhiExtra  , h_tag_exc_MuonPhiExtra  ;
    TH1F *h_raw_MuonIso       ;   std::vector<TH1F*> h_zpj_inc_MuonIso       , h_zpj_exc_MuonIso       , h_tag_inc_MuonIso       , h_tag_exc_MuonIso       ;
    TH1F *h_raw_MuonIsoLead   ;   std::vector<TH1F*> h_zpj_inc_MuonIsoLead   , h_zpj_exc_MuonIsoLead   , h_tag_inc_MuonIsoLead   , h_tag_exc_MuonIsoLead   ;
    TH1F *h_raw_MuonIsoSubLead;   std::vector<TH1F*> h_zpj_inc_MuonIsoSubLead, h_zpj_exc_MuonIsoSubLead, h_tag_inc_MuonIsoSubLead, h_tag_exc_MuonIsoSubLead;
    TH1F *h_raw_MuonIsoExtra  ;   std::vector<TH1F*> h_zpj_inc_MuonIsoExtra  , h_zpj_exc_MuonIsoExtra  , h_tag_inc_MuonIsoExtra  , h_tag_exc_MuonIsoExtra  ;
    TH1F *h_raw_nElecs        ;   std::vector<TH1F*> h_zpj_inc_nElecs        , h_zpj_exc_nElecs        , h_tag_inc_nElecs        , h_tag_exc_nElecs        ;
    TH1F *h_raw_ElecPt        ;   std::vector<TH1F*> h_zpj_inc_ElecPt        , h_zpj_exc_ElecPt        , h_tag_inc_ElecPt        , h_tag_exc_ElecPt        ;
    TH1F *h_raw_ElecPtLead    ;   std::vector<TH1F*> h_zpj_inc_ElecPtLead    , h_zpj_exc_ElecPtLead    , h_tag_inc_ElecPtLead    , h_tag_exc_ElecPtLead    ;
    TH1F *h_raw_ElecPtSubLead ;   std::vector<TH1F*> h_zpj_inc_ElecPtSubLead , h_zpj_exc_ElecPtSubLead , h_tag_inc_ElecPtSubLead , h_tag_exc_ElecPtSubLead ;
    TH1F *h_raw_ElecPtExtra   ;   std::vector<TH1F*> h_zpj_inc_ElecPtExtra   , h_zpj_exc_ElecPtExtra   , h_tag_inc_ElecPtExtra   , h_tag_exc_ElecPtExtra   ;
    TH1F *h_raw_ElecEta       ;   std::vector<TH1F*> h_zpj_inc_ElecEta       , h_zpj_exc_ElecEta       , h_tag_inc_ElecEta       , h_tag_exc_ElecEta       ;
    TH1F *h_raw_ElecEtaLead   ;   std::vector<TH1F*> h_zpj_inc_ElecEtaLead   , h_zpj_exc_ElecEtaLead   , h_tag_inc_ElecEtaLead   , h_tag_exc_ElecEtaLead   ;
    TH1F *h_raw_ElecEtaSubLead;   std::vector<TH1F*> h_zpj_inc_ElecEtaSubLead, h_zpj_exc_ElecEtaSubLead, h_tag_inc_ElecEtaSubLead, h_tag_exc_ElecEtaSubLead;
    TH1F *h_raw_ElecEtaExtra  ;   std::vector<TH1F*> h_zpj_inc_ElecEtaExtra  , h_zpj_exc_ElecEtaExtra  , h_tag_inc_ElecEtaExtra  , h_tag_exc_ElecEtaExtra  ;
    TH1F *h_raw_ElecPhi       ;   std::vector<TH1F*> h_zpj_inc_ElecPhi       , h_zpj_exc_ElecPhi       , h_tag_inc_ElecPhi       , h_tag_exc_ElecPhi       ;
    TH1F *h_raw_ElecPhiLead   ;   std::vector<TH1F*> h_zpj_inc_ElecPhiLead   , h_zpj_exc_ElecPhiLead   , h_tag_inc_ElecPhiLead   , h_tag_exc_ElecPhiLead   ;
    TH1F *h_raw_ElecPhiSubLead;   std::vector<TH1F*> h_zpj_inc_ElecPhiSubLead, h_zpj_exc_ElecPhiSubLead, h_tag_inc_ElecPhiSubLead, h_tag_exc_ElecPhiSubLead;
    TH1F *h_raw_ElecPhiExtra  ;   std::vector<TH1F*> h_zpj_inc_ElecPhiExtra  , h_zpj_exc_ElecPhiExtra  , h_tag_inc_ElecPhiExtra  , h_tag_exc_ElecPhiExtra  ;
    TH1F *h_raw_MET           ;   std::vector<TH1F*> h_zpj_inc_MET           , h_zpj_exc_MET           , h_tag_inc_MET           , h_tag_exc_MET           ;

    // Jet properties - Inclusive events have plot for all jets, as well as 1st through max jets (nJetsAnalyzed+1)
    //                - Exclusive events have plot for all jets and 1st through nth jet (n+1 plots)
    TH1F *h_raw_nJets ;         std::vector<TH1F*>   h_zpj_inc_nJets         , h_zpj_exc_nJets         , h_tag_inc_nJets         , h_tag_exc_nJets         ;
    TH1F *h_raw_JetPt ;  std::vector<std::vector<TH1F*> > h_zpj_inc_JetPt         , h_zpj_exc_JetPt         , h_tag_inc_JetPt         , h_tag_exc_JetPt         ;
    TH1F *h_raw_JetEta;  std::vector<std::vector<TH1F*> > h_zpj_inc_JetEta        , h_zpj_exc_JetEta        , h_tag_inc_JetEta        , h_tag_exc_JetEta        ;
    TH1F *h_raw_JetPhi;  std::vector<std::vector<TH1F*> > h_zpj_inc_JetPhi        , h_zpj_exc_JetPhi        , h_tag_inc_JetPhi        , h_tag_exc_JetPhi        ;
    TH1F *h_raw_JetCSV;  std::vector<std::vector<TH1F*> > h_zpj_inc_JetCSV        , h_zpj_exc_JetCSV        , h_tag_inc_JetCSV        , h_tag_exc_JetCSV        ;
    TH1F *h_raw_JetMSV;  std::vector<std::vector<TH1F*> > h_zpj_inc_JetMSV        , h_zpj_exc_JetMSV        , h_tag_inc_JetMSV        , h_tag_exc_JetMSV        ;

  // Leaf & Branch map variables
    float m_Z_mass;   int   m_nJets;                 int   m_nMuons;                     int   m_nElecs;                     float m_MET_et      ;
    float m_Z_pt  ;   float m_jet_pt [maxNumJets];   float m_muon_pt    [maxNumMuons];   float m_elec_pt    [maxNumElecs];   float m_MET_phi     ;
    float m_Z_eta ;   float m_jet_eta[maxNumJets];   float m_muon_eta   [maxNumMuons];   float m_elec_eta   [maxNumElecs];   float m_triggers[54];
    float m_Z_phi ;   float m_jet_phi[maxNumJets];   float m_muon_phi   [maxNumMuons];   float m_elec_phi   [maxNumElecs];   int   m_json        ;
    int   m_Vtype ;   float m_jet_csv[maxNumJets];   float m_muon_charge[maxNumMuons];   float m_elec_charge[maxNumElecs];
                      float m_jet_msv[maxNumJets];   float m_muon_iso   [maxNumMuons];

    //ClassDef(ZCControlPlotMaker,0);
};


#endif