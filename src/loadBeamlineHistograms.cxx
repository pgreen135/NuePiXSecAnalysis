void loadBeamlineHistograms() {

	// load beamline variations TH2D
	TFile *beamlineVariationsFile = NULL;
	beamlineVariationsFile = new TFile("/Users/patrick/Documents/MicroBooNE/CrossSections/NuePiXSec_Analysis/NuMIBeamLineWeights/NuMI_Beamline_Variations_to_CV_Ratios.root");
	
	std::vector<TH2F> h_nue_fhc;
	std::vector<TH2F> h_nuebar_fhc;
	std::vector<TH2F> h_numu_fhc;
	std::vector<TH2F> h_numubar_fhc;

	// loop over beamline variations
	for (int i = 1; i <= 20; i++) {
		// construct names
		stringstream name_nue_ss; name_nue_ss << "EnergyTheta2D/ratio_run" << i <<  "_FHC_nue_CV_AV_TPC_2D";
		stringstream name_nuebar_ss; name_nuebar_ss << "EnergyTheta2D/ratio_run" << i <<  "_FHC_nuebar_CV_AV_TPC_2D";
		stringstream name_numu_ss; name_numu_ss << "EnergyTheta2D/ratio_run" << i <<  "_FHC_numu_CV_AV_TPC_2D";
		stringstream name_numubar_ss; name_numubar_ss << "EnergyTheta2D/ratio_run" << i <<  "_FHC_numubar_CV_AV_TPC_2D";
		string name_nue = name_nue_ss.str();
		string name_nuebar = name_nuebar_ss.str();
		string name_numu = name_numu_ss.str();
		string name_numubar = name_numubar_ss.str();		

		// load histograms
		h_nue_fhc.push_back(*(TH2F*)beamlineVariationsFile->Get(name_nue.c_str()));
		h_nuebar_fhc.push_back(*(TH2F*)beamlineVariationsFile->Get(name_nuebar.c_str()));
		h_numu_fhc.push_back(*(TH2F*)beamlineVariationsFile->Get(name_numu.c_str()));
		h_numubar_fhc.push_back(*(TH2F*)beamlineVariationsFile->Get(name_numubar.c_str()));
	}


	//h1->Draw("COLZ");
	
	float xValue = 1.2; // GeV
	float yValue = 10; 	// Degrees 

	std::cout << h_numu_fhc.size() << std::endl;

	for (int i = 0; i < h_numu_fhc.size(); i++) {
	
		int binx = h_numu_fhc[i].GetXaxis()->FindBin(xValue);
		int biny = h_numu_fhc[i].GetYaxis()->FindBin(yValue);
		float weight = h_numu_fhc[i].GetBinContent(binx,biny);

		std::cout << weight << std::endl;
	}
}