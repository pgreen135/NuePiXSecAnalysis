#include "StackedHistTool.h"

// -------------------------- Constructor -------------------------- //
// Intended to be very general so you can make histograms of whatever you like
StackedHistTool::StackedHistTool(std::string histname, std::string title, int nbins, double lowlimit, double highlimit, const Utility &utility): _utility{ utility }
{

  InstantiateHistOrder();
  stack = new THStack(histname.c_str(),title.c_str());
  for (int i_hist=0; i_hist < nHists; i_hist++){
    std::string histname_i = std::string(histname)+std::string("_")+std::to_string(i_hist);
    hists[i_hist] = new TH1F(histname_i.c_str(),"",nbins,lowlimit,highlimit);
  }

  // Style the histograms
  StyleHistsStack();

  invalid_total_x = 0.;

  // set event counts to zero
  eventCount = std::vector<double>(nHists, 0.0);
}

// Set histogram order (moved to be in a separate function from the constructor to allow for overload of constructor for 1D or 2D histograms)
void StackedHistTool::InstantiateHistOrder(){

  // Topology categories for the histograms  
  hist_order.push_back(_utility.kCCNue1pi0p);
  hist_order.push_back(_utility.kCCNue1piNp);
  hist_order.push_back(_utility.kCCNueNpi);
  hist_order.push_back(_utility.kCCNuepizero);
  hist_order.push_back(_utility.kCCNue1p);
  hist_order.push_back(_utility.kCCNueNp);
  hist_order.push_back(_utility.kCCNueOther);
  hist_order.push_back(_utility.kCCNumuOther);
  hist_order.push_back(_utility.kCCNumupizero);
  hist_order.push_back(_utility.kNCOther);
  hist_order.push_back(_utility.kNCpizero);
  hist_order.push_back(_utility.kCosmic);
  hist_order.push_back(_utility.kOutFV);
  hist_order.push_back(_utility.kOutOfCryo);
  hist_order.push_back(_utility.kBeamOff);
  hist_order.push_back(_utility.kUnknown);

  nHists = hist_order.size();
}

// -------------------------- Function to fill the correct histogram -------------------------- //
void StackedHistTool::Fill(Utility::ClassificationEnums topology, double value)
{
  unsigned int n_hist = StackedHistTool::GetHistN(topology);
  hists[n_hist]->Fill(value);
  eventCount[n_hist] += 1;
}

// -------------------------- Function to fill the correct histogram -------------------------- //
// Overloaded to allow for weights
void StackedHistTool::Fill(Utility::ClassificationEnums topology, double value, double weight)
{
  unsigned int n_hist = StackedHistTool::GetHistN(topology);
  hists[n_hist]->Fill(value, weight);
  eventCount[n_hist] += weight;
}

// -------------------------- Function to draw the histograms -------------------------- //
void StackedHistTool::DrawStack(TCanvas *c1, Utility::PlotVariableEnums plotvariable)
{

	// Next: add histograms to the stack and make TLegend
	// Only do this for histograms that have entries
	TLegend *leg = new TLegend(0.1,0.88,0.65,0.99);
	// leg->SetTextFont(132);
	leg->SetLineColor(kWhite);
	leg->SetTextAlign(12);
	leg->SetNColumns(6);

	TPaveText *pt = new TPaveText(0.65,0.88,0.9,0.99,"NDC NB");
	pt->SetLineColor(kWhite);
	pt->SetFillColor(kWhite);
	pt->SetTextAlign(12);

	double underflow_total = 0.;
	double overflow_total = 0.;

	for (int i_hist = 0; i_hist < nHists; i_hist++) {
	  if (hists[i_hist]->GetEntries() == 0)
		continue;

	  stack->Add(hists[i_hist]);
	  Utility::ClassificationEnums topology_for_legend = StackedHistTool::GetTopologyFromHistN((unsigned int)i_hist);
	  leg->AddEntry(hists[i_hist], topologyenum2str(topology_for_legend).c_str(), "f");

	  underflow_total += hists[i_hist]->GetBinContent(0);
	  overflow_total += hists[i_hist]->GetBinContent(hists[i_hist]->GetXaxis()->GetNbins()+1);
	}

	pt->AddText(TString::Format("Underflow (Invalid): %.2f (%.2f)",underflow_total,invalid_total_x).Data());
	pt->AddText(TString::Format("Overflow: %.2f",overflow_total).Data());

	c1->cd();
	c1->SetTopMargin(0.13);

	stack->Draw("hist");

	stack->GetXaxis()->SetTitle(PlotVariableEnum2str(plotvariable).c_str());
	stack->GetYaxis()->SetTitle("Entries");
	
  stack->GetXaxis()->SetTitleSize(0.045);
  stack->GetYaxis()->SetTitleSize(0.045);

  c1->Modified();
	
	leg->Draw();
	pt->Draw();
}

// -------------------------- Function to style the histograms -------------------------- //
// Private: only called by DrawStack function in this file
void StackedHistTool::StyleHistsStack()
{
  // Set fill color for all histograms
  hists[0] ->SetFillColor(kCyan+2); // CC nue 1pi 0p
  hists[1] ->SetFillColor(kCyan+3); // CC nue 1pi Np
  hists[2] ->SetFillColor(kCyan-3); // CC nue Npi
  hists[3] ->SetFillColor(kRed+1); // CC nue pizero
  hists[4] ->SetFillColor(kRed+2); // CC nue 1p
  hists[5] ->SetFillColor(kRed+3); // CC nue Np
  hists[6] ->SetFillColor(kRed-7); // CC nue other
  hists[7] ->SetFillColor(kOrange+2); // CC numu other
  hists[8] ->SetFillColor(kOrange+4); // CC numu pizero
  hists[9] ->SetFillColor(kMagenta+1); // NC other
  hists[10] ->SetFillColor(kMagenta+3); // NC pizero
  hists[11] ->SetFillColor(kBlue+1); // Cosmic
  hists[12] ->SetFillColor(kGray+1); // OutFV
  hists[13]->SetFillColor(kRed-3); // Out of Cryo
  hists[14]->SetFillColor(kGray+3); // Beam Off
  hists[15]->SetFillColor(kBlack); // Unknown


  // Set line color for all histograms
  hists[0] ->SetLineColor(kCyan+2); // CC nue 1pi 0p
  hists[1] ->SetLineColor(kCyan+3); // CC nue 1pi Np
  hists[2] ->SetLineColor(kCyan-3); // CC nue Npi
  hists[3] ->SetLineColor(kRed+1); // CC nue pizero
  hists[4] ->SetLineColor(kRed+2); // CC nue 1p
  hists[5] ->SetLineColor(kRed+3); // CC nue Np
  hists[6] ->SetLineColor(kRed-7); // CC nue other
  hists[7] ->SetLineColor(kOrange+2); // CC numu other
  hists[8] ->SetLineColor(kOrange+4); // CC numu pizero
  hists[9] ->SetLineColor(kMagenta+1); // NC other
  hists[10] ->SetLineColor(kMagenta+3); // NC pizero
  hists[11] ->SetLineColor(kBlue+1); // Cosmic
  hists[12] ->SetLineColor(kGray+1); // OutFV
  hists[13]->SetLineColor(kRed-3); // Out of Cryo
  hists[14]->SetLineColor(kGray+3); // Beam Off  
  hists[15]->SetLineColor(kBlack); // Unknown

  // Set fill style
  hists[13]->SetFillStyle(3004); // Out of Cryo
  hists[14]->SetFillStyle(3005); // Beam Off

}


// ---------------------- Function to get histogram number for given topology ---------------------- //
// Private: only called by functions in this class
unsigned int StackedHistTool::GetHistN(Utility::ClassificationEnums topology)
{
  unsigned int HistN;
  bool found_hist=false;

  for (int i=0; i<nHists; i++){
    if (hist_order.at(i) == topology){
      HistN = i;
      found_hist = true;
      break;
    }
  }

  if (!found_hist){
    std::cout << "[ERROR: StackedHistTool.h] Could not find histogram for topology " << topology << std::endl;
    HistN = nHists-1;
  }

  return HistN;
}


// ---------------------- Function to get topology code for given histogram number ---------------------- //
// Private: only called by functions in this class
Utility::ClassificationEnums StackedHistTool::GetTopologyFromHistN(unsigned int hist_n)
{
  return hist_order.at(hist_n);
}

// ---------------------- Function to get histogram integrals ---------------------- //
void StackedHistTool::PrintHistIntegrals()
{
  // Calculate and print out relative integrals (percentage of events that are each topology)
    // Compute total integral
    double total_integral = 0;
    for (int i_hist=0; i_hist < nHists; i_hist++){
      if (hists[i_hist]->GetEntries() == 0) continue;

      double integral = hists[i_hist]->Integral();
      total_integral += integral;
    }
    std::cout << "Total number of events: " << total_integral << std::endl;
    for (int i_hist=0; i_hist < nHists; i_hist++){
      if (hists[i_hist]->GetEntries() == 0) continue;

      Utility::ClassificationEnums topology = StackedHistTool::GetTopologyFromHistN((unsigned int)i_hist);

      double integral = hists[i_hist]->Integral();

      std::cout << "Number of events for toplogy " << topologyenum2str(topology) << ": " << integral << std::endl;// << "\t\t Fraction of total: " << integral/total_integral << std::endl;

    }
}
void StackedHistTool::PrintEventIntegrals()
{
  // Calculate and print out relative integrals (percentage of events that are each topology)
	// Compute total integral
	double total_integral = 0;
	for (int i_hist=0; i_hist < nHists; i_hist++){
	  total_integral += eventCount[i_hist];
	}
	std::cout << "Total number of events: " << total_integral << std::endl;
	for (int i_hist=0; i_hist < nHists; i_hist++){
	  Utility::ClassificationEnums topology = StackedHistTool::GetTopologyFromHistN((unsigned int)i_hist);

	  std::cout << "Number of events for toplogy " << topologyenum2str(topology) << ": " << eventCount[i_hist] << std::endl;// << "\t\t Fraction of total: " << integral/total_integral << std::endl;
	}
}

// ---------------------- Function to get histogram integrals ---------------------- //
double StackedHistTool::GetTotalIntegral()
{
  // Compute total integral
  double total_integral = 0;
  for (int i_hist=0; i_hist < nHists; i_hist++){
    if (hists[i_hist]->GetEntries() == 0) continue;

    double integral = hists[i_hist]->Integral();
    total_integral += integral;
  }
  return total_integral; 
}

std::string StackedHistTool::topologyenum2str(Utility::ClassificationEnums topology)
{
  std::string returnString = "";

  switch(topology){

  case Utility::kCCNueOther:
    returnString = "#nu_{e} CC Other";
    break;
  case Utility::kCCNue1pi0p:
    returnString = "#nu_{e} CC 1#pi 0p";
    break;
  case Utility::kCCNue1piNp:
    returnString = "#nu_{e} CC 1#pi Np";
    break;
  case Utility::kCCNueNpi:
    returnString = "#nu_{e} CC N#pi";
    break;
  case Utility::kCCNuepizero:
    returnString = "#nu_{e} CC #pi^{0}";
    break;
  case Utility::kCCNue1p:
    returnString = "#nu_{e} CC 1p";
    break;
  case Utility::kCCNueNp:
    returnString = "#nu_{e} CC Np";
    break;
  case Utility::kCCNumuOther:
    returnString = "#nu_{#mu} CC Other";
    break;
  case Utility::kCCNumupizero:
    returnString = "#nu_{#mu} CC #pi^{0}";
    break;
  case Utility::kNCOther:
    returnString = "NC Other";
    break;
  case Utility::kNCpizero:
    returnString = "NC #pi^{0}";
    break;
  case Utility::kCosmic:
    returnString = "Cosmic";
    break;
  case Utility::kOutFV:
    returnString = "Out of FV";
    break;
  case Utility::kBeamOff:
    returnString = "Beam Off";
    break;
  case Utility::kOutOfCryo:
    returnString = "Out of Cryo";
    break;
  case Utility::kUnknown:
    returnString = "Unknown";
    break;
  default:
    std::cout << "[ERROR: StackedHistTool] Could not find string conversion for " << topology << std::endl;
    returnString = "Unknown";
    break;
  }

  return returnString;
}

std::string StackedHistTool::PlotVariableEnum2str(Utility::PlotVariableEnums plotvariable)
{
  std::string returnString = "";

  switch(plotvariable){

  case Utility::kSliceID:
    returnString = "SliceID";
    break;
  case Utility::kNuE:
    returnString = "True Neutrino Energy [GeV]";
    break;
  case Utility::kNShower:
  	returnString = "Shower Multiplicity";
  	break;
  case Utility::kNTrack:
  	returnString = "Track Multiplicity";
  	break;
  case Utility::kVertexInFV:
    returnString = "Vertex in Fiducial Volume";
    break;
  case Utility::kContainedFraction:
  	returnString = "Contained Fraction [Hits in FV / Hits in Slice]";
  	break;
  case Utility::kTopologicalScore:
  	returnString = "Pandora Topological Score";
  	break;
  case Utility::kCosmicImpactParameter:
  	returnString = "Cosmic Impact Parameter [cm]";
  	break;
  case Utility::kShowerScore:
  	returnString = "Shower Score";
  	break;
  case Utility::kShowerEnergy:
    returnString = "Shower Energy [GeV]";
    break;
  case Utility::kHitRatio:
  	returnString = "Shower Hit Ratio";
  	break;
  case Utility::kMoliereAverage:
    returnString = "Leading Shower Moliere Average [deg]";
    break;
  case Utility::kShowerEnergyRatio:
    returnString = "Leading Shower Energy / Total Shower Energy";
    break;
  case Utility::kShowerdEdxMax:
    returnString = "Leading Shower dE/dx [MeV/cm]";
    break;
  case Utility::kNeutralPionInvariantMass:
    returnString = "Neutral Pion Invariant Mass Difference [MeV]";
    break;  
  case Utility::kTrackLength:
    returnString = "Track Length [cm]";
    break;
  case Utility::kTrackBraggPion:
    returnString = "Pion Bragg Peak Score";
    break;
  case Utility::kTrackBraggP:
    returnString = "Proton Bragg Peak Score";
    break;
  case Utility::kTrackBraggMu:
    returnString = "Muon Bragg Peak Score";
    break;
  case Utility::kLLRPID:
    returnString = "LLR PID Score";
    break; 
  case Utility::kTrackScore:
    returnString = "Pandora Track Score";
    break;
  case Utility::kTrackdEdx:
    returnString = "Track dE/dx [MeV/cm]";
    break;
  case Utility::kTrackDistance:
    returnString = "Track Distance Vertex [cm]";
    break; 
  case Utility::kTrackTheta:
    returnString = "Track #theta [deg]";
    break;
  case Utility::kTrackPhi:
    returnString = "Track #phi [deg]";
    break;
  case Utility::kPi0InvMassDifference:
    returnString = "#pi^{0} Invariant Mass Difference [MeV]";
    break;
  case Utility::kTrackShowerAngle:
    returnString = "Track-Shower Opening Angle [deg]";
    break;   		  	  	
  default:
    std::cout << "[ERROR: StackedHistTool] Could not find string conversion for enum " << plotvariable << std::endl;
    returnString = "Unknown";
    break;
  }  

  return returnString;
}

void StackedHistTool::SaveHistStack() {
  // TO DO
}