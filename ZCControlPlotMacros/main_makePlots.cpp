// MAIN macro for ZCControlPlotMaker

// April 2015 version. Created by Andrew Godshalk
// Requires files: main_makePlots.C, ZCControlPlotMaker.h/cpp, ZCStandardVariables.h (control plot version), timestamp.h
// To compile: g++ -o ZCControlPlotter ZCControlPlotMaker.cpp main_makePlots.cpp `root-config --cflags --glibs`

// To run: ./ZCControlPlotter <Z-decay-pref> <dataset> <maxEvents>
//    <Z-decay-pref> - Either zuu or zee (or zttuu or zttee if you'd like to look at ztt that are spoofing uu/ee decays.)
//    <dataset>      - one of the following: muon, elec, dy, dy1j, ww, wz, zz, ttlep, ttsemi, tthad
//    <maxEvents>    - If not specfied or negative, runs through full file
//


#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include "timestamp.h"
#include "ZCControlPlotMaker.h"
#include "ZCStandardVariables.h"

using namespace ZCStandardVariables;
using std::cout;   using std::endl;

//void main_makePlots()
int main(int argc, char* argv[])
{
  // Output filenames options - for creation of a log file and a histogram file in the given directory
    TString dir = "control_plots/";
    TString tst = fileTimeStamp();
    TString pfx = "_plots_";
    TString sfx = "_NO_MET_CUT";

  // Process input
    if(argc<3)
    {
        cout << "\n    ERROR: Please enter a decay chain, dataset, and (optional) a max number of events.\n" << endl;
        return 1;
    }

    TString decayChain       = argv[1];
    TString dataset          = argv[2];
    TString maxEventsStr     = ""     ;
    if(argc>=4)
    {
        maxEventsStr = argv[3];
        if(!maxEventsStr.IsFloat())
        {
            cout << "\n    ERROR: Please enter the number of events you want to process for your third option"
                    "\n    (or nothing if you want to process them all).\n"
                 << endl;
            return 1;
        }
    }

    if(decayChain!="Zuu" && decayChain!="Zee" decayChain!="Zttuu" && decayChain!="Zttee")
    {
        cout << "\n    ERROR: Please specify one of the following decay chains for your first option: Zuu, Zee, Zttuu, Zttee\n" << endl;
        return 1;
    }

  // Open files and map trees
    TFile* f_input;
    if     (dataset == "muon"    ) f_input = TFile::Open(fn_muon   );
    else if(dataset == "elec"    ) f_input = TFile::Open(fn_elec   );
    else if(dataset == "dy"      ) f_input = TFile::Open(fn_dy     );
    else if(dataset == "dy1j"    ) f_input = TFile::Open(fn_dy1j   );
    else if(dataset == "ww"      ) f_input = TFile::Open(fn_ww     );
    else if(dataset == "wz"      ) f_input = TFile::Open(fn_wz     );
    else if(dataset == "zz"      ) f_input = TFile::Open(fn_zz     );
    else if(dataset == "tthad"   ) f_input = TFile::Open(fn_tthad  );
    else if(dataset == "ttlep"   ) f_input = TFile::Open(fn_ttlep  );
    else if(dataset == "ttsemi"  ) f_input = TFile::Open(fn_ttsemi );
    else if(dataset == "t_s"     ) f_input = TFile::Open(fn_t_s    );
    else if(dataset == "t_t"     ) f_input = TFile::Open(fn_t_t    );
    else if(dataset == "t_tw"    ) f_input = TFile::Open(fn_t_tw   );
    else if(dataset == "tbar_s"  ) f_input = TFile::Open(fn_tbar_s );
    else if(dataset == "tbar_t"  ) f_input = TFile::Open(fn_tbar_t );
    else if(dataset == "tbar_tw" ) f_input = TFile::Open(fn_tbar_tw);
    else
    {
        cout << "\n    ERROR: Please specify one of the following datasets for your second option:"
                "\n                muon, elec, dy, dy1j, ww, wz, zz, tthad, ttlep, ttsemi, t(bar)_(s/t/tw)\n" << endl;
        return 1;
    }

    // If tau tau decays specified on a non-dy set.
    if( (decayChain=="Zttuu" || decayChain=="Zttee") && (dataset!="dy" && dataset!="dy1j"))
    {
        cout << "\n    ERROR: Tau decay split only valid for DY datasets\n" << endl;
        return 1;
    }

    TTree* t_input = (TTree*)f_input->Get("tree");
    
  // Create an instance of the ZCControlPlotMaker and input options
    ZCControlPlotMaker *plotMaker = new ZCControlPlotMaker();
    TString outputFileName = dir+tst+pfx+decayChain+"_"+dataset+sfx;
    TString options = decayChain;
    if(dataset!="muon" && dataset!="elec") options+=",sim";
    if(dataset=="dy")                      options+=",dy";

  // Process tree and save output
    if(maxEventsStr!="")
         t_input->Process(plotMaker, options, maxEventsStr.Atoi() );
    else t_input->Process(plotMaker, options                      );
    cout << plotMaker->saveOutputToFile(outputFileName) << endl;


return 0;

}
