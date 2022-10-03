#ifndef STACKEDHISTTOOL
#define STACKEDHISTTOOL

// class to contain and draw stacked histogram based on event classification

#include "Utility.h"

#include "TH1F.h"
#include "THStack.h"
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>

#include <vector>
#include <string>
#include <iostream>

class StackedHistTool{

 public:
  StackedHistTool(std::string histname, std::string title, int nbins, double lowlimit, double highlimit, const Utility &utility); // Constructor
  void Fill(Utility::ClassificationEnums topology, double value);
  void Fill(Utility::ClassificationEnums topology, double value, double weight);
  
  std::string topologyenum2str(Utility::ClassificationEnums topology);
  std::string PlotVariableEnum2str(Utility::PlotVariableEnums plotvariable);
  
  void DrawStack(TCanvas *c1, Utility::PlotVariableEnums plotvariable);
 
  void PrintHistIntegrals();
  double GetTotalIntegral();
 
  void SaveHistStack();

 protected:
  Utility _utility;

  int nHists;
  std::vector<Utility::ClassificationEnums> hist_order; // For keeping track of which hist goes with which topology

  THStack *stack;
  TH1F *hists[25];

  double invalid_total_x;
  double invalid_total_y;

  void InstantiateHistOrder();
  void StyleHistsStack();
  unsigned int GetHistN(Utility::ClassificationEnums topology);
  Utility::ClassificationEnums GetTopologyFromHistN(unsigned int hist_n);
};

#endif