#ifndef GUARD_ZCTreeControlPlotCombiner_h
#define GUARD_ZCTreeControlPlotCombiner_h

// ZCControlPlotCombiner.h
// Class that takes root file output of ZCControlPlotMaker.h/cpp
//   and stacks the histograms from data and simulation to make B-E-A-Utiful control plots.


#include <iostream>
#include <map>
#include <TAttFill.h>
#include <TAttLine.h>
#include <TDirectory.h>
#include <TFile.h>
#include <TList.h>
#include <TObject.h>
#include <TH1.h>
#include <TROOT.h>
#include <TString.h>
#include "ZCStandardVariables.h"

using std::map;
using namespace ZCStandardVariables;

class ZCControlPlotCombiner
{
public:
    ZCControlPlotCombiner(TFile*, map<TString, TFile*>&, const TString option = "");
   ~ZCControlPlotCombiner(){}

private:
  // Functions that recursively do most of the work.
    void combinePlots(TDirectory*, TDirectory*);
    void combinePlots(TDirectory*, TH1*);
    TString getFullPath(TDirectory*);

  // Internal Variables
    map<TString, TFile*> &inputFile;    // Map of files containing data, signal sim, and bkgd.
    TFile                *comboFile;    // Output file for combination plots.
    bool                  useLogAxis;   // Option set in the constructor to set output plots' Y-axis to log scale.
    bool                  useLegStats;  // Option to set legend to display integral of each entry.
};


ZCControlPlotCombiner::ZCControlPlotCombiner(TFile* cF, map<TString, TFile*>& iF, const TString option = "")
  : comboFile(cF), inputFile(iF)
{
    gStyle->SetOptStat("");     // Gets rid of the stats panel in canvas

  // Extract options
    useLogAxis  = (option.Contains("log",      TString::kIgnoreCase) ? true : false);
    useLegStats = (option.Contains("legstat", TString::kIgnoreCase) ? true : false);

  // CHECK that map is working 
    //typedef map<TString, TFile*>::const_iterator mapIter;
    //for(auto inFile : inputFile) cout << "  " << inFile.first << ":   \t" << (inFile.second)->GetName() << "\n";

  // Run combinePlots on the input data, adding to the output a combo plot or directory for each item in data.
    combinePlots(comboFile, inputFile["data"]);
    comboFile->Write();
    comboFile->Close();
}

void ZCControlPlotCombiner::combinePlots(TDirectory* parentDir, TDirectory* dataDir)
{
    TDirectory* dirToPass = parentDir;      // Directory to pass on to future calls of combinePlots()
    TString dirTitle = dataDir->GetTitle(); // Extract the name of the directory to be copied and its contents
    TList*  contents = dataDir->GetListOfKeys();

  // TEST: Make sure this is called correctly for each directory.
    cout << "  Working through Directory: " << dataDir->GetName() << "  " << dataDir->GetTitle() << "\n";
    
  // If not the top directory, make a copy of the dataDir in the new parent directory and pass this to future calls of combinePlots
    if(dirTitle!="") dirToPass = parentDir->mkdir(dirTitle);

  // Make an iterator from the directory contents and call combinePlots on each entry.
    TIter nextItem(contents); TObject *item = 0;
    while ((item = nextItem()))
    {
        item = ((TKey*)item)->ReadObj();
        //cout << "   Passing a " << item->ClassName() << "\n";
        if(TString(item->ClassName())=="TDirectoryFile") combinePlots(dirToPass, (TDirectory*) item);
        else                                             combinePlots(dirToPass,        (TH1*) item);
        // Replace previous else with this to go through a single histogram per directory. For testing purposes.
        //else {  combinePlots(dirToPass,        (TH1*) item);
        //        return;
        //     }
    }

}


void ZCControlPlotCombiner::combinePlots(TDirectory* parentDir, TH1* dataHisto)
{
  // Get the location where you'll find the other histograms in their separate files.
    TString     plotName    = dataHisto->GetName();
    TString     plotDirName = getFullPath(parentDir);

    cout << "    Looking For: " << plotName << " in " << plotDirName << ":   " << plotDirName+plotName << endl;

  // Create a 2-pad canvas for the stacked control plot and the ratio plot.
  // NOTE: To keep canvas from drawing (i.e. to prevent solitaire screen overload), run root with -b tag (batch/no-graphic mode).
    TString cName  = plotName + "_stacked";
    TString cTitle = dataHisto->GetTitle();
    TCanvas *plot  = new TCanvas(cName,cTitle, 600, 600);
    plot->cd();
    TPad * stackPad = new TPad("stackPad", "stackPad", 0, 0.2, 1, 1);
    stackPad->Draw();
    plot->cd();
    TPad * ratioPad = new TPad("ratioPad", "ratioPad", 0, 0, 1, 0.2);
    ratioPad->Draw();

  // Extract the sim plots from file
    if(inputFile.find("dy"    ) == inputFile.end() && inputFile["dy"    ]==NULL) {cout << "InputFile for dy"    " not found in map. Ending function." << endl; return;}
    if(inputFile.find("zz"    ) == inputFile.end() && inputFile["zz"    ]==NULL) {cout << "InputFile for zz"    " not found in map. Ending function." << endl; return;}
    if(inputFile.find("wz"    ) == inputFile.end() && inputFile["wz"    ]==NULL) {cout << "InputFile for wz"    " not found in map. Ending function." << endl; return;}
    if(inputFile.find("ww"    ) == inputFile.end() && inputFile["ww"    ]==NULL) {cout << "InputFile for ww"    " not found in map. Ending function." << endl; return;}
    if(inputFile.find("ttlep" ) == inputFile.end() && inputFile["ttlep" ]==NULL) {cout << "InputFile for ttlep" " not found in map. Ending function." << endl; return;}
    if(inputFile.find("ttsemi") == inputFile.end() && inputFile["ttsemi"]==NULL) {cout << "InputFile for ttsemi"" not found in map. Ending function." << endl; return;}
    if(inputFile.find("tthad" ) == inputFile.end() && inputFile["tthad" ]==NULL) {cout << "InputFile for tthad" " not found in map. Ending function." << endl; return;}
    TH1F *h_dy     = (TH1F*)(inputFile["dy"    ]->Get(plotDirName+plotName+";1"));
    TH1F *h_zz     = (TH1F*)(inputFile["zz"    ]->Get(plotDirName+plotName+";1"));
    TH1F *h_wz     = (TH1F*)(inputFile["wz"    ]->Get(plotDirName+plotName+";1"));
    TH1F *h_ww     = (TH1F*)(inputFile["ww"    ]->Get(plotDirName+plotName+";1"));
    TH1F *h_ttlep  = (TH1F*)(inputFile["ttlep" ]->Get(plotDirName+plotName+";1"));
    TH1F *h_ttsemi = (TH1F*)(inputFile["ttsemi"]->Get(plotDirName+plotName+";1"));
    TH1F *h_tthad  = (TH1F*)(inputFile["tthad" ]->Get(plotDirName+plotName+";1"));

  // Set styles for each of the sim sets and add to stack
    h_dy    ->SetLineWidth(1);   h_dy    ->SetFillColor(kRed  +1);   h_dy    ->SetLineColor(kGray+3);   //h_dy    ->SetFillStyle(1001);
    h_zz    ->SetLineWidth(1);   h_zz    ->SetFillColor(kGreen-1);   h_zz    ->SetLineColor(kGray+3);   //h_zz    ->SetFillStyle(3001);
    h_wz    ->SetLineWidth(1);   h_wz    ->SetFillColor(kGreen-2);   h_wz    ->SetLineColor(kGray+3);   //h_wz    ->SetFillStyle(3002);
    h_ww    ->SetLineWidth(1);   h_ww    ->SetFillColor(kGreen-3);   h_ww    ->SetLineColor(kGray+3);   //h_ww    ->SetFillStyle(3003);
    h_ttlep ->SetLineWidth(1);   h_ttlep ->SetFillColor(kBlue -0);   h_ttlep ->SetLineColor(kGray+3);   //h_ttlep ->SetFillStyle(3001);
    h_ttsemi->SetLineWidth(1);   h_ttsemi->SetFillColor(kBlue -2);   h_ttsemi->SetLineColor(kGray+3);   //h_ttsemi->SetFillStyle(3002);
    h_tthad ->SetLineWidth(1);   h_tthad ->SetFillColor(kBlue -3);   h_tthad ->SetLineColor(kGray+3);   //h_tthad ->SetFillStyle(3003);
    
  // Set up a stack for simulation (IMPORTANT to get the ordering right from here on in.)
    TString stackName = TString("h_stack_")+dataHisto->GetName();
    THStack *simStack = new THStack(stackName, stackName);

  // Scale backgrounds using weights, then stack bkgd/sgnl in plot
    h_ww    ->Scale(wt_ww    );   simStack->Add(h_ww    );
    h_wz    ->Scale(wt_wz    );   simStack->Add(h_wz    );
    h_zz    ->Scale(wt_zz    );   simStack->Add(h_zz    );
    h_tthad ->Scale(wt_tthad );   simStack->Add(h_tthad );
    h_ttsemi->Scale(wt_ttsemi);   simStack->Add(h_ttsemi);
    h_ttlep ->Scale(wt_ttlep );   simStack->Add(h_ttlep );
    h_dy    ->Scale(wt_dy    );   simStack->Add(h_dy    );

  // Get a combined sim-stack histogram for the ratio plot.
    TH1F * h_simSum = (TH1F*)h_dy->Clone();   h_simSum->Sumw2();
    h_simSum->Add(h_ww    );    h_simSum->Add(h_wz    );    h_simSum->Add(h_zz    );
    h_simSum->Add(h_tthad );    h_simSum->Add(h_ttsemi);    h_simSum->Add(h_ttlep );

  // Modify y-range based on type of plot. Set max to 110% max value of either data or mc-stack.
    float simMax  = simStack ->GetMaximum();
    float dataMax = dataHisto->GetMaximum();
    float plotMax = dataMax>simMax ? dataMax : simMax;
    float plotMin = useLogAxis ? 1 : 0;
    plotMax      *= useLogAxis ? 5 : 1.1;
    //dataHisto->SetAxisRange(plotMin, plotMax, "Y");    // Doesn't work for log plots.
    dataHisto->SetMinimum(plotMin);
    dataHisto->SetMaximum(plotMax);

  // Draw data histo, then sim-stack
    stackPad->cd();
    if(useLogAxis) stackPad->SetLogy();   // If log variable asked for, set log axis.

  // Modify the data plot's style and draw over bkgd/sgnl
    dataHisto->SetMarkerStyle(8);
    dataHisto->SetMarkerSize(0.8);
    dataHisto->Draw();
    simStack->Draw("hist sames");
    dataHisto->Draw("EP sames");
    dataHisto->Draw("axis same");

  // Set up legend stats
    TString leg_data   = "Data"          ;
    TString leg_dy     = "Drell-Yan"     ;
    TString leg_ttlep  = "t#bar{t}(lep)" ;
    TString leg_ttsemi = "t#bar{t}(semi)";
    TString leg_tthad  = "t#bar{t}(had)" ;
    TString leg_zz     = "ZZ"            ;
    TString leg_wz     = "WZ"            ;
    TString leg_ww     = "WW"            ;
    if(useLegStats)
    {
        leg_data   += TString(" (") + Form("%.1f",dataHisto->Integral()) + ")";
        leg_dy     += TString(" (") + Form("%.1f",h_dy     ->Integral()) + ")";
        leg_ttlep  += TString(" (") + Form("%.1f",h_ttlep  ->Integral()) + ")";
        leg_ttsemi += TString(" (") + Form("%.1f",h_ttsemi ->Integral()) + ")";
        leg_tthad  += TString(" (") + Form("%.1f",h_tthad  ->Integral()) + ")";
        leg_zz     += TString(" (") + Form("%.1f",h_zz     ->Integral()) + ")";
        leg_wz     += TString(" (") + Form("%.1f",h_wz     ->Integral()) + ")";
        leg_ww     += TString(" (") + Form("%.1f",h_ww     ->Integral()) + ")";
    }

  // Make legend
    TLegend *leg = new TLegend(0.6,0.55,0.95,0.85);
    leg->AddEntry(dataHisto, leg_data  , "P");
    leg->AddEntry(h_dy     , leg_dy    , "F");
    leg->AddEntry(h_ttlep  , leg_ttlep , "F");
    leg->AddEntry(h_ttsemi , leg_ttsemi, "F");
    leg->AddEntry(h_tthad  , leg_tthad , "F");
    leg->AddEntry(h_zz     , leg_zz    , "F");
    leg->AddEntry(h_wz     , leg_wz    , "F");
    leg->AddEntry(h_ww     , leg_ww    , "F");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

  // Add ratio plot
    ratioPad->cd();
    ratioPad->SetLogy(0);   // Set ratio pad to linear scale
    ratioPad->SetGrid();
    ratioPad->SetTopMargin(0);
    TH1F * h_ratio = (TH1F*) dataHisto->Clone();
    h_ratio->SetTitle("");
    h_ratio->GetYaxis()->SetTitle("(Data-MC)/MC");
    h_ratio->GetXaxis()->SetTitle("");
    h_ratio->SetTitleSize(  0.12, "y" );
    h_ratio->SetTitleOffset(0.30, "y");
    h_ratio->SetLabelSize(  0.08, "xy");

    h_ratio->Add(h_simSum, -1.0);    h_ratio->Divide(h_simSum);
    h_ratio->SetMinimum(-1.0);
    h_ratio->SetMaximum(+1.0);
    h_ratio->DrawCopy("ep");

  // Delete cloned histograms
    delete h_simSum;
    delete h_ratio;

  // Append to parent directory.
    plot->Update();
    parentDir->Append(plot);
}


TString ZCControlPlotCombiner::getFullPath(TDirectory *dir)
{
    TString path = dir->GetName();
    if(path.Contains(".root")) return "";
    return getFullPath(dir->GetMotherDir())+path+"/";
}

#endif