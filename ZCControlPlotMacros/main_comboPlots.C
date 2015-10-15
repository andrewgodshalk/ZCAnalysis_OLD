// main_comboPlots.C
// Main macro for ZCControlPlotCombiner.h


// For the love of all that is holy, use this command to run:
//   root -l -b main_comboPlots.C
// Otherwise, your computer will burst into flames. -b keeps root from drawing every canvas.

#include <map>
#include <TFile.h>
#include <TString.h>
#include "ZCControlPlotCombiner.h"

using std::map;

void main_comboPlots()
{
  // Open files containing control plots, add them to map

    map<TString, TFile*> inputFiles;
    //inputFiles["data"  ] = TFile::Open("control_plots/2015-03-13_124917_plots_data_test.root  ");
    //inputFiles["dy"    ] = TFile::Open("control_plots/2015-03-13_210458_plots_dy_test.root    ");
    //inputFiles["ww"    ] = TFile::Open("control_plots/2015-03-13_211316_plots_ww_test.root    ");
    //inputFiles["wz"    ] = TFile::Open("control_plots/2015-03-13_211344_plots_wz_test.root    ");
    //inputFiles["zz"    ] = TFile::Open("control_plots/2015-03-13_211426_plots_zz_test.root    ");
    //inputFiles["tthad" ] = TFile::Open("control_plots/2015-03-13_211737_plots_tthad_test.root ");
    //inputFiles["ttlep" ] = TFile::Open("control_plots/2015-03-13_211831_plots_ttlep_test.root ");
    //inputFiles["ttsemi"] = TFile::Open("control_plots/2015-03-13_212101_plots_ttsemi_test.root");

   //For Zuu control plots:
//    inputFiles["data"   ] = TFile::Open("control_plots/muon.root "        );
//    inputFiles["dy"     ] = TFile::Open("control_plots/dy"    "_Zuu.root ");
//    inputFiles["ww"     ] = TFile::Open("control_plots/ww"    "_Zuu.root ");
//    inputFiles["wz"     ] = TFile::Open("control_plots/wz"    "_Zuu.root ");
//    inputFiles["zz"     ] = TFile::Open("control_plots/zz"    "_Zuu.root ");
//    inputFiles["tthad"  ] = TFile::Open("control_plots/tthad" "_Zuu.root ");
//    inputFiles["ttlep"  ] = TFile::Open("control_plots/ttlep" "_Zuu.root ");
//    inputFiles["ttsemi" ] = TFile::Open("control_plots/ttsemi""_Zuu.root ");
//    inputFiles["t_s"    ] = TFile::Open("control_plots/t_s"    "_Zuu.root ");
//    inputFiles["t_t"    ] = TFile::Open("control_plots/t_t"    "_Zuu.root ");
//    inputFiles["t_tw"   ] = TFile::Open("control_plots/t_tw"   "_Zuu.root ");
//    inputFiles["tbar_s" ] = TFile::Open("control_plots/tbar_s" "_Zuu.root ");
//    inputFiles["tbar_t" ] = TFile::Open("control_plots/tbar_t" "_Zuu.root ");
//    inputFiles["tbar_tw"] = TFile::Open("control_plots/tbar_tw""_Zuu.root ");

  // For Zee control plots:
    inputFiles["data"   ] = TFile::Open("control_plots/elec.root "        );
    inputFiles["dy"     ] = TFile::Open("control_plots/dy"     "_Zee.root ");
    inputFiles["ww"     ] = TFile::Open("control_plots/ww"     "_Zee.root ");
    inputFiles["wz"     ] = TFile::Open("control_plots/wz"     "_Zee.root ");
    inputFiles["zz"     ] = TFile::Open("control_plots/zz"     "_Zee.root ");
    inputFiles["tthad"  ] = TFile::Open("control_plots/tthad"  "_Zee.root ");
    inputFiles["ttlep"  ] = TFile::Open("control_plots/ttlep"  "_Zee.root ");
    inputFiles["ttsemi" ] = TFile::Open("control_plots/ttsemi" "_Zee.root ");
    inputFiles["t_s"    ] = TFile::Open("control_plots/t_s"    "_Zee.root ");
    inputFiles["t_t"    ] = TFile::Open("control_plots/t_t"    "_Zee.root ");
    inputFiles["t_tw"   ] = TFile::Open("control_plots/t_tw"   "_Zee.root ");
    inputFiles["tbar_s" ] = TFile::Open("control_plots/tbar_s" "_Zee.root ");
    inputFiles["tbar_t" ] = TFile::Open("control_plots/tbar_t" "_Zee.root ");
    inputFiles["tbar_tw"] = TFile::Open("control_plots/tbar_tw""_Zee.root ");

  // Create an output file for storing new plots
    //TFile *f_comboPlots = TFile::Open("control_plots/combined_Zuu_plots.root", "RECREATE");
    TFile *f_comboPlots = TFile::Open("control_plots/combined_Zee_plots.root", "RECREATE");

    ZCControlPlotCombiner combo(f_comboPlots, inputFiles, "log legstats");
//    ZCControlPlotCombiner combo(f_comboPlots, inputFiles, "");
    
    f_comboPlots->Close();
}








