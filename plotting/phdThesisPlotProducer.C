{
  gROOT->LoadMacro("./tdrstyle.C");
  setTDRStyle();

  gROOT->LoadMacro("./colors.h");

  //load fitter
  gROOT->LoadMacro("./logFitTest.C");

  //gROOT->SetBatch();

  // load input files
  TString folder = "/user/kargoll/results/TurnOns/forPhdThesis/DoubleTauJet/";
  TFile* l1File = new TFile(folder + "turnOn_Run2012ABCD_forPhdThesis.root");
  TFile* l2l2p5File = new TFile(folder + "turnOn_Run2012BCD_forPhdThesis.root");

  // style options
  int fitColor = 1;
  int fitWidth = 1;
//  int markerStyle = 20;
//  int markerSize = 1.2;
  tdrGrid(true,tdrStyle);
  //gStyle->SetOptFit(0);

  // time stamp for saving of files
  TDatime datetime = TDatime();
  TString timestamp = "";
  timestamp += datetime.GetDate();
  timestamp += "_";
  timestamp += datetime.GetTime();
  TString savePath = "/user/kargoll/CMSSW/CMSSW_5_3_11_patch5/src/TriggerStudies/plotting/results/";
  savePath += timestamp;
  system("mkdir " + savePath);
  system("cp phdThesisPlotProducer.C " + savePath);


  // Latex
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextFont(42);
  latex.SetTextAlign(11);
  const char* latexText_fullL = "19.7 fb^{-1}, #sqrt{s}=8 TeV";
  const char* latexText_2012BCD = "18.9 fb^{-1}, #sqrt{s}=8 TeV";
  double xLatex = 0.68;
  double yLatex = 0.96;

  // text templatex
  TString t_xaxis_pt	= "p_{T}(#tau_{h}) / GeV";
  TString t_yaxis_eff	= "Efficiency";


    cout << " ***************** Plot: L1 eff. over pT ****************** " << endl;
    TCanvas* canvasL1 = new TCanvas();
    canvasL1->cd();

    TH1F* denomPtL1 = (TH1F*)l1File->Get("denominator_Total");
    TH1F* numPtL1 = (TH1F*)l1File->Get("numeratorL1_Total");
    TGraphAsymmErrors* theL1Eff = new TGraphAsymmErrors(numPtL1, denomPtL1, "cl=0.683 b(1,1) mode");
    theL1Eff->GetYaxis()->SetTitle(t_yaxis_eff);
    theL1Eff->GetXaxis()->SetTitle(t_xaxis_pt);
    theL1Eff->GetXaxis()->SetRangeUser(0.,205.);
    theL1Eff->GetYaxis()->SetRangeUser(0.,1.04);
    theL1Eff->Draw("AP");
    latex.DrawLatex(xLatex,yLatex,latexText_fullL);
    canvasL1->SaveAs(savePath + "/L1TauPtEfficiency.pdf");

    cout << " ***************** Plot: L1 Tau and Jet eff. over pT ****************** " << endl;
    TCanvas* canvasL1TauJet = new TCanvas();
    canvasL1TauJet->cd();

    TH1F* denomPtL1TauJet = (TH1F*)l1File->Get("denominator_Total");
    TH1F* numPtL1Tau = (TH1F*)l1File->Get("numeratorL1Tau_Total");
    TGraphAsymmErrors* theL1TauEff = new TGraphAsymmErrors(numPtL1Tau, denomPtL1TauJet, "cl=0.683 b(1,1) mode");
    theL1TauEff->GetYaxis()->SetTitle(t_yaxis_eff);
    theL1TauEff->GetXaxis()->SetTitle(t_xaxis_pt);
    theL1TauEff->GetXaxis()->SetRangeUser(0.,205.);
    theL1TauEff->GetYaxis()->SetRangeUser(0.,1.04);
    theL1TauEff->SetMarkerStyle(22);
    theL1TauEff->SetMarkerColor(col_rwth_darkblue);
    theL1TauEff->SetLineColor(col_rwth_darkblue);
    theL1TauEff->Draw("AP");

    TH1F* numPtL1Jet = (TH1F*)l1File->Get("numeratorL1Jet_Total");
    TGraphAsymmErrors* theL1JetEff = new TGraphAsymmErrors(numPtL1Jet, denomPtL1TauJet, "cl=0.683 b(1,1) mode");
    theL1JetEff->SetMarkerStyle(21);
    theL1JetEff->SetMarkerColor(col_rwth_lightblue);
    theL1JetEff->SetLineColor(col_rwth_lightblue);
    theL1JetEff->Draw("P");

    theL1Eff->Draw("P");

	TLegend* legendL1TauJet = new TLegend(0.5,0.18,0.92,0.38);
	legendL1TauJet->SetBorderSize(1);
	legendL1TauJet->SetTextSize(0.028);
	legendL1TauJet->SetLineColor(1);
	legendL1TauJet->SetLineStyle(1);
	legendL1TauJet->SetLineWidth(1);
	legendL1TauJet->SetFillColor(0);
	legendL1TauJet->AddEntry(theL1TauEff,	"L1 Tau, p_{T}>44 GeV","pel");
	legendL1TauJet->AddEntry(theL1JetEff,	"L1 Central Jet, p_{T}>64 GeV","pel");
	legendL1TauJet->AddEntry(theL1Eff,		"L1 Tau or Central Jet","pel");
	legendL1TauJet->Draw();

    latex.DrawLatex(xLatex,yLatex,latexText_fullL);
    canvasL1TauJet->SaveAs(savePath + "/L1TauPtEfficiency_TauJetComp.pdf");
    /*

    cout << " ***************** Plot: L1 eff. over eta ****************** " << endl;
    TCanvas* canvasL1eta = new TCanvas();
    canvasL1eta->cd();

    TH1F* denomEtaL1 = (TH1F*)l1File->Get("denominatorEta_Total");
    TH1F* numEtaL1 = (TH1F*)l1File->Get("numeratorEtaL1_Total");
    numEtaL1->Sumw2();
    denomEtaL1->Sumw2();
    numEtaL1->Rebin(2);
    denomEtaL1->Rebin(2);
    TGraphAsymmErrors* theL1EtaEff = new TGraphAsymmErrors(numEtaL1, denomEtaL1, "cl=0.683 b(1,1) mode");
    //theL1EtaEff->SetTitle(0);
    theL1EtaEff->GetYaxis()->SetTitle(t_yaxis_eff);
    theL1EtaEff->GetXaxis()->SetTitle("#tau #eta");
    //theL1EtaEff->SetMinimum(0);
    //theL1EtaEff->SetMaximum(1.125);
    theL1EtaEff->GetXaxis()->SetRangeUser(-2.5,2.5);
    theL1EtaEff->GetYaxis()->SetRangeUser(0.82,1.04);
    theL1EtaEff->GetYaxis()->SetNdivisions(508);
//    theL1EtaEff->SetMarkerStyle(markerStyle);
//    theL1EtaEff->SetMarkerSize(markerSize);
    theL1EtaEff->Draw("AP");
    latex.DrawLatex(xLatex,yLatex,latexText_fullL);
    canvasL1eta->SaveAs(savePath + "/L1TauEtaEfficiency.pdf");

	cout << " ***************** Plot: L1 eta resolution ****************** " << endl;
	TCanvas* canvasL1etaResol = new TCanvas();
	canvasL1etaResol->cd();

	TH1F* etaResol = (TH1F*)l1File->Get("resEtaL1_Total");
	etaResol->Sumw2();
	etaResol->Rebin(4);
	etaResol->Scale(100./etaResol->Integral());
    etaResol->GetYaxis()->SetTitle("Frequency [%]");
    etaResol->GetXaxis()->SetTitle("#eta resolution");
    etaResol->GetXaxis()->SetRangeUser(-0.35,0.35);
    for (unsigned int i = 1; i<=etaResol->GetNbinsX(); i++){
    	if (etaResol->GetBinContent(i) == 0.)
    		etaResol->SetBinContent(i,0.000001);
    }
    etaResol->Draw("e1 P0");
    latex.DrawLatex(xLatex,yLatex,latexText_fullL);
    canvasL1etaResol->SaveAs(savePath + "/L1TauEtaResolution.pdf");

	cout << " ***************** Plot: L1 pT resolution ****************** " << endl;
	TCanvas* canvasL1ptResol = new TCanvas();
	canvasL1ptResol->cd();

	TH1F* ptResol = (TH1F*)l1File->Get("resPtL1_Total");
	ptResol->Sumw2();
	ptResol->Rebin(8);
	ptResol->Scale(100./ptResol->Integral());
    ptResol->GetYaxis()->SetTitle("Frequency [%]");
    ptResol->GetXaxis()->SetTitle("p_{T} resolution [GeV/c]");
    ptResol->GetXaxis()->SetRangeUser(-25.0,85.0);
    ptResol->Draw("e1 P0");
    latex.DrawLatex(xLatex,yLatex,latexText_fullL);
    canvasL1ptResol->SaveAs(savePath + "/L1TauPtResolution.pdf");



  cout << " ***************** Plot: L2L2p5 eff. over pT ****************** " << endl;
  TCanvas* canvasL2L2p5 = new TCanvas();
  canvasL2L2p5->cd();

  TH1F* denomPtL2L2p5 = (TH1F*)l2l2p5File->Get("denominator_Total");
  TH1F* numPtL2L2p5 = (TH1F*)l2l2p5File->Get("numeratorL2L2p5_Total");
  TGraphAsymmErrors* theL2L2p5Eff = new TGraphAsymmErrors(numPtL2L2p5, denomPtL2L2p5, "cl=0.683 b(1,1) mode");
//  theL2L2p5Eff->SetTitle(0);
  theL2L2p5Eff->GetYaxis()->SetTitle(t_yaxis_eff);
  theL2L2p5Eff->GetXaxis()->SetTitle(t_xaxis_pt);
//  theL2L2p5Eff->SetMinimum(0);
//  theL2L2p5Eff->SetMaximum(1.125);
  theL2L2p5Eff->GetXaxis()->SetRangeUser(0.,205.);
  theL2L2p5Eff->GetYaxis()->SetRangeUser(0,1.04);
//  theL2L2p5Eff->SetMarkerStyle(markerStyle);
//  theL2L2p5Eff->SetMarkerSize(markerSize);
  theL2L2p5Eff->Draw("AP");
//  TF1* L2L2p5Fit = logFitTest(15,numPtL2L2p5,denomPtL2L2p5);
  TF1* L2L2p5Fit = crystalFit(theL2L2p5Eff,15.);
//  L2L2p5Fit->SetLineColor(fitColor);
//  L2L2p5Fit->SetLineWidth(fitWidth);
  L2L2p5Fit->Draw("same");
  theL2L2p5Eff->Draw("P");
  latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
  canvasL2L2p5->SaveAs(savePath + "/L2TauPt.pdf");

    cout << " ***************** Plot: L2L2p5 eff. over eta ****************** " << endl;
    TCanvas* canvasL2L2p5eta = new TCanvas();
    canvasL2L2p5eta->cd();

    TH1F* denomEtaL2L2p5 = (TH1F*)l2l2p5File->Get("denominatorEta_Total");
    TH1F* numEtaL2L2p5 = (TH1F*)l2l2p5File->Get("numeratorEtaL2L2p5_Total");
    numEtaL2L2p5->Sumw2();
    denomEtaL2L2p5->Sumw2();
    numEtaL2L2p5->Rebin(2);
    denomEtaL2L2p5->Rebin(2);
	TGraphAsymmErrors* theL2L2p5EtaEff = new TGraphAsymmErrors(numEtaL2L2p5, denomEtaL2L2p5, "cl=0.683 b(1,1) mode");
//	theL2L2p5EtaEff->SetTitle(0);
	theL2L2p5EtaEff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL2L2p5EtaEff->GetXaxis()->SetTitle("#tau #eta");
//	theL2L2p5EtaEff->SetMaximum(1.125);
//	theL2L2p5EtaEff->SetMinimum(0);
	theL2L2p5EtaEff->GetXaxis()->SetRangeUser(-2.5,2.5);
	theL2L2p5EtaEff->GetYaxis()->SetRangeUser(0.62,1.04);
    theL2L2p5EtaEff->GetYaxis()->SetNdivisions(508);
//	theL2L2p5EtaEff->SetMarkerStyle(markerStyle);
//	theL2L2p5EtaEff->SetMarkerSize(markerSize);
	theL2L2p5EtaEff->Draw("AP");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL2L2p5eta->SaveAs(savePath + "/L2TauEta.pdf");


    cout << " ***************** Plot: L1 Rate vs. threshold ****************** " << endl;
    TCanvas* canvasL1rate = new TCanvas();
    canvasL1rate->cd();
    //canvasL1rate->SetLogx();
    canvasL1rate->SetLogy();

    TGraphErrors *l1TauRate = new TGraphErrors(26);
    l1TauRate->SetName("");
    l1TauRate->SetTitle("");
    l1TauRate->SetFillColor(1);
    l1TauRate->SetMarkerStyle(20);
    l1TauRate->SetPoint(0,0,622001.6);
    l1TauRate->SetPointError(0,0,600.2809);
    l1TauRate->SetPoint(1,4,622001.6);
    l1TauRate->SetPointError(1,0,600.2809);
    l1TauRate->SetPoint(2,8,622001.6);
    l1TauRate->SetPointError(2,0,600.2809);
    l1TauRate->SetPoint(3,12,622001.6);
    l1TauRate->SetPointError(3,0,600.2809);
    l1TauRate->SetPoint(4,16,563816.1);
    l1TauRate->SetPointError(4,0,571.5163);
    l1TauRate->SetPoint(5,20,333659.3);
    l1TauRate->SetPointError(5,0,439.6543);
    l1TauRate->SetPoint(6,24,143627.1);
    l1TauRate->SetPointError(6,0,288.4564);
    l1TauRate->SetPoint(7,28,46454.49);
    l1TauRate->SetPointError(7,0,164.0492);
    l1TauRate->SetPoint(8,32,17194.36);
    l1TauRate->SetPointError(8,0,99.80331);
    l1TauRate->SetPoint(9,36,7166.83);
    l1TauRate->SetPointError(9,0,64.43542);
    l1TauRate->SetPoint(10,40,3410.922);
    l1TauRate->SetPointError(10,0,44.45301);
    l1TauRate->SetPoint(11,44,1982.376);
    l1TauRate->SetPointError(11,0,33.88893);
    l1TauRate->SetPoint(12,48,1112.86);
    l1TauRate->SetPointError(12,0,25.39115);
    l1TauRate->SetPoint(13,52,668.5331);
    l1TauRate->SetPointError(13,0,19.67967);
    l1TauRate->SetPoint(14,56,433.9093);
    l1TauRate->SetPointError(14,0,15.85464);
    l1TauRate->SetPoint(15,60,286.1831);
    l1TauRate->SetPointError(15,0,12.87597);
    l1TauRate->SetPoint(16,64,196.9682);
    l1TauRate->SetPointError(16,0,10.68211);
    l1TauRate->SetPoint(17,68,132.0845);
    l1TauRate->SetPointError(17,0,8.74752);
    l1TauRate->SetPoint(18,72,81.68385);
    l1TauRate->SetPointError(18,0,6.879025);
    l1TauRate->SetPoint(19,76,57.93181);
    l1TauRate->SetPointError(19,0,5.79318);
    l1TauRate->SetPoint(20,80,46.34545);
    l1TauRate->SetPointError(20,0,5.181576);
    l1TauRate->SetPoint(21,84,33.02113);
    l1TauRate->SetPointError(21,0,4.373754);
    l1TauRate->SetPoint(22,88,20.27613);
    l1TauRate->SetPointError(22,0,3.427291);
    l1TauRate->SetPoint(23,92,16.22091);
    l1TauRate->SetPointError(23,0,3.065463);
    l1TauRate->SetPoint(24,96,11.58636);
    l1TauRate->SetPointError(24,0,2.590789);
    l1TauRate->SetPoint(25,100,11.00704);
    l1TauRate->SetPointError(25,0,2.525189);


    TGraphErrors *l1JetRate = new TGraphErrors(26);
    l1JetRate->SetName("");
    l1JetRate->SetTitle("");
    l1JetRate->SetFillColor(1);
    l1JetRate->SetMarkerStyle(20);
    l1JetRate->SetPoint(0,0,926028.8);
    l1JetRate->SetPointError(0,0,732.437);
    l1JetRate->SetPoint(1,4,926028.8);
    l1JetRate->SetPointError(1,0,732.437);
    l1JetRate->SetPoint(2,8,926028.8);
    l1JetRate->SetPointError(2,0,732.437);
    l1JetRate->SetPoint(3,12,926028.8);
    l1JetRate->SetPointError(3,0,732.437);
    l1JetRate->SetPoint(4,16,858929.5);
    l1JetRate->SetPointError(4,0,705.4023);
    l1JetRate->SetPoint(5,20,580569.6);
    l1JetRate->SetPointError(5,0,579.9456);
    l1JetRate->SetPoint(6,24,320584.7);
    l1JetRate->SetPointError(6,0,430.9544);
    l1JetRate->SetPoint(7,28,158483.5);
    l1JetRate->SetPointError(7,0,303.0065);
    l1JetRate->SetPoint(8,32,86867.69);
    l1JetRate->SetPointError(8,0,224.3314);
    l1JetRate->SetPoint(9,36,49586.37);
    l1JetRate->SetPointError(9,0,169.4891);
    l1JetRate->SetPoint(10,40,30547.99);
    l1JetRate->SetPointError(10,0,133.0287);
    l1JetRate->SetPoint(11,44,21018.01);
    l1JetRate->SetPointError(11,0,110.3436);
    l1JetRate->SetPoint(12,48,14494.1);
    l1JetRate->SetPointError(12,0,91.6325);
    l1JetRate->SetPoint(13,52,10443.92);
    l1JetRate->SetPointError(13,0,77.78482);
    l1JetRate->SetPoint(14,56,7728.8);
    l1JetRate->SetPointError(14,0,66.91379);
    l1JetRate->SetPoint(15,60,5938.663);
    l1JetRate->SetPointError(15,0,58.65496);
    l1JetRate->SetPoint(16,64,4576.584);
    l1JetRate->SetPointError(16,0,51.49144);
    l1JetRate->SetPoint(17,68,3630.475);
    l1JetRate->SetPointError(17,0,45.86159);
    l1JetRate->SetPoint(18,72,2896.503);
    l1JetRate->SetPointError(18,0,40.96382);
    l1JetRate->SetPoint(19,76,2312);
    l1JetRate->SetPointError(19,0,36.59797);
    l1JetRate->SetPoint(20,80,1909.967);
    l1JetRate->SetPointError(20,0,33.26422);
    l1JetRate->SetPoint(21,84,1541.534);
    l1JetRate->SetPointError(21,0,29.88429);
    l1JetRate->SetPoint(22,88,1256.524);
    l1JetRate->SetPointError(22,0,26.98045);
    l1JetRate->SetPoint(23,92,1060.146);
    l1JetRate->SetPointError(23,0,24.78242);
    l1JetRate->SetPoint(24,96,903.7363);
    l1JetRate->SetPointError(24,0,22.88119);
    l1JetRate->SetPoint(25,100,769.3345);
    l1JetRate->SetPointError(25,0,21.11124);

    l1TauRate->GetYaxis()->SetTitle("Rate [Hz]");
    l1TauRate->GetXaxis()->SetTitle("p_{T} threshold [GeV/c]");
    l1TauRate->GetXaxis()->SetRangeUser(20., 105.); // for linear x axis
    //l1TauRate->GetXaxis()->SetRangeUser(10., 105.); // for log x axis
    l1TauRate->GetYaxis()->SetRangeUser(0.6, 2e6);
    l1TauRate->Draw("AP");
    l1JetRate->SetMarkerColor(2);
    l1JetRate->SetMarkerStyle(21);
    l1JetRate->Draw("P");
	TLegend* legend = new TLegend(0.2,0.2,0.6,0.4);
	legend->SetBorderSize(1);
//	legend->SetTextFont(62);
//	legend->SetTextSize(0.03);
	legend->SetLineColor(1);
	legend->SetLineStyle(1);
	legend->SetLineWidth(1);
	legend->SetFillColor(0);
	//legend->SetFillStyle(0);
	legend->AddEntry(l1TauRate,"Double Tau, |#eta|<2.17","pel");
	legend->AddEntry(l1JetRate,"Double Jet, |#eta|<3.0","pel");
	legend->Draw();
    latexText = "CMS 2012, #sqrt{s}=8 TeV, L= 5 #times 10^{33} cm^{-2}s^{-1}";
	latex.DrawLatex(xLatex-0.05,yLatex,latexText);
	canvasL1rate->SaveAs(savePath + "/L1TauRate.pdf");

*/
	cout << "All done. Results can be found here:\n     " << savePath << endl;
}

