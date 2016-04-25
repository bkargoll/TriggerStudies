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
  TFile* hltFile = new TFile(folder + "turnOn_Run2012BCD_forPhdThesis.root");

  // style options
  int fitColor = 1;
  int fitWidth = 1;
//  int markerStyle = 20;
//  int markerSize = 1.2;
  tdrGrid(true,tdrStyle);
  //gStyle->SetOptFit(0);
  gStyle->SetTitleXOffset(0.95);

  // rebin x-axis for eff(eta) plots
  int rebin_eff = 2;

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
  TString t_xaxis_ptresol	= "p_{T}(#tau_{h}) resolution / GeV";
  TString t_xaxis_eta	= "#eta(#tau_{h})";
  TString t_xaxis_etaresol	= "#eta(#tau_{h}) resolution";
  TString t_yaxis_eff	= "Efficiency";
  TString t_yaxis_dens	= "Density";

    cout << " ***************** Plot: L1 eff. over pT ****************** " << endl;
    TCanvas* canvasL1 = new TCanvas("canvasL1", "canvasL1");
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
    TCanvas* canvasL1TauJet = new TCanvas("canvasL1TauJet","canvasL1TauJet");
    canvasL1TauJet->cd();

    TH1F* denomPtL1TauJet = (TH1F*)l1File->Get("denominator_Total");
    TH1F* numPtL1Tau = (TH1F*)l1File->Get("numeratorL1Tau_Total");
    TGraphAsymmErrors* theL1TauEff = new TGraphAsymmErrors(numPtL1Tau, denomPtL1TauJet, "cl=0.683 b(1,1) mode");
    theL1TauEff->GetYaxis()->SetTitle(t_yaxis_eff);
    theL1TauEff->GetXaxis()->SetTitle(t_xaxis_pt);
    theL1TauEff->GetXaxis()->SetRangeUser(0.,205.);
    theL1TauEff->GetYaxis()->SetRangeUser(0.,1.04);
    theL1TauEff->SetMarkerStyle(22);
    theL1TauEff->SetMarkerColor(l1TauColor);
    theL1TauEff->SetLineColor(l1TauColor);
    theL1TauEff->Draw("AP");

    TH1F* numPtL1Jet = (TH1F*)l1File->Get("numeratorL1Jet_Total");
    TGraphAsymmErrors* theL1JetEff = new TGraphAsymmErrors(numPtL1Jet, denomPtL1TauJet, "cl=0.683 b(1,1) mode");
    theL1JetEff->SetMarkerStyle(21);
    theL1JetEff->SetMarkerColor(l1JetColor);
    theL1JetEff->SetLineColor(l1JetColor);
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


    cout << " ***************** Plot: L1 eff. over eta ****************** " << endl;
    TCanvas* canvasL1eta = new TCanvas("canvasL1eta","canvasL1eta");
    canvasL1eta->cd();

    TH1F* denomEtaL1 = (TH1F*)l1File->Get("denominatorEta_Total");
    TH1F* numEtaL1 = (TH1F*)l1File->Get("numeratorEtaL1_Total");
    numEtaL1->Rebin(rebin_eff);
    denomEtaL1->Rebin(rebin_eff);
    TGraphAsymmErrors* theL1EtaEff = new TGraphAsymmErrors(numEtaL1, denomEtaL1, "cl=0.683 b(1,1) mode");
    theL1EtaEff->GetYaxis()->SetTitle(t_yaxis_eff);
    theL1EtaEff->GetXaxis()->SetTitle(t_xaxis_eta);
    theL1EtaEff->GetXaxis()->SetRangeUser(-2.5,2.5);
    theL1EtaEff->GetYaxis()->SetRangeUser(0.82,1.04);
    theL1EtaEff->GetYaxis()->SetNdivisions(508);
    theL1EtaEff->Draw("AP");
    latex.DrawLatex(xLatex,yLatex,latexText_fullL);
    canvasL1eta->SaveAs(savePath + "/L1TauEtaEfficiency.pdf");

    cout << " ***************** Plot: L2 eff. over pT ****************** " << endl;
    TCanvas* canvasL2 = new TCanvas("canvasL2","canvasL2");
    canvasL2->cd();

    TH1F* denomPtL2 = (TH1F*)hltFile->Get("denominator_Total");
    TH1F* numPtL2 = (TH1F*)hltFile->Get("numeratorL2_Total");
    TGraphAsymmErrors* theL2Eff = new TGraphAsymmErrors(numPtL2, denomPtL2, "cl=0.683 b(1,1) mode");
    theL2Eff->GetYaxis()->SetTitle(t_yaxis_eff);
    theL2Eff->GetXaxis()->SetTitle(t_xaxis_pt);
    theL2Eff->GetXaxis()->SetRangeUser(0.,205.);
    theL2Eff->GetYaxis()->SetRangeUser(0,1.04);
    theL2Eff->Draw("AP");
    TF1* L2Fit = logFitTest(15,numPtL2,denomPtL2);
    L2Fit->Draw("same");
    theL2Eff->Draw("P");
    latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
    canvasL2->SaveAs(savePath + "/L2TauPt.pdf");
	cout << " ***************** Plot: L2 eff. over eta ****************** " << endl;
	TCanvas* canvasL2eta = new TCanvas("canvasL2eta","canvasL2eta");
	canvasL2eta->cd();

	TH1F* denomEtaL2 = (TH1F*)hltFile->Get("denominatorEta_Total");
	TH1F* numEtaL2 = (TH1F*)hltFile->Get("numeratorEtaL2_Total");
	numEtaL2->Rebin(rebin_eff);
	denomEtaL2->Rebin(rebin_eff);
  	TGraphAsymmErrors* theL2EtaEff = new TGraphAsymmErrors(numEtaL2, denomEtaL2, "cl=0.683 b(1,1) mode");
  	theL2EtaEff->GetYaxis()->SetTitle(t_yaxis_eff);
  	theL2EtaEff->GetXaxis()->SetTitle(t_xaxis_eta);
  	theL2EtaEff->GetXaxis()->SetRangeUser(-2.5,2.5);
  	theL2EtaEff->GetYaxis()->SetRangeUser(0.62,1.04);
    theL2EtaEff->GetYaxis()->SetNdivisions(508);
  	theL2EtaEff->Draw("AP");
  	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
  	canvasL2eta->SaveAs(savePath + "/L2TauEta.pdf");

	cout << " ***************** Plot: L2L2p5 eff. over pT ****************** " << endl;
	TCanvas* canvasL2L2p5 = new TCanvas("canvasL2L2p5","canvasL2L2p5");
	canvasL2L2p5->cd();

	TH1F* denomPtL2L2p5 = (TH1F*)hltFile->Get("denominator_Total");
	TH1F* numPtL2L2p5 = (TH1F*)hltFile->Get("numeratorL2L2p5_Total");
	TGraphAsymmErrors* theL2L2p5Eff = new TGraphAsymmErrors(numPtL2L2p5, denomPtL2L2p5, "cl=0.683 b(1,1) mode");
	theL2L2p5Eff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL2L2p5Eff->GetXaxis()->SetTitle(t_xaxis_pt);
	theL2L2p5Eff->GetXaxis()->SetRangeUser(0.,205.);
	theL2L2p5Eff->GetYaxis()->SetRangeUser(0,1.04);
	theL2L2p5Eff->Draw("AP");
	TF1* L2L2p5Fit = logFitTest(15,numPtL2L2p5,denomPtL2L2p5);
	L2L2p5Fit->Draw("same");
	theL2L2p5Eff->Draw("P");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL2L2p5->SaveAs(savePath + "/L2L2p5TauPt.pdf");
	cout << " ***************** Plot: L2L2p5 eff. over eta ****************** " << endl;
	TCanvas* canvasL2L2p5eta = new TCanvas("canvasL2L2p5eta","canvasL2L2p5eta");
	canvasL2L2p5eta->cd();

	TH1F* denomEtaL2L2p5 = (TH1F*)hltFile->Get("denominatorEta_Total");
	TH1F* numEtaL2L2p5 = (TH1F*)hltFile->Get("numeratorEtaL2L2p5_Total");
	numEtaL2L2p5->Rebin(rebin_eff);
	// denomEtaL2L2p5->Rebin(rebin_eff);
	TGraphAsymmErrors* theL2L2p5EtaEff = new TGraphAsymmErrors(numEtaL2L2p5, denomEtaL2L2p5, "cl=0.683 b(1,1) mode");
	theL2L2p5EtaEff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL2L2p5EtaEff->GetXaxis()->SetTitle(t_xaxis_eta);
	theL2L2p5EtaEff->GetXaxis()->SetRangeUser(-2.5,2.5);
	theL2L2p5EtaEff->GetYaxis()->SetRangeUser(0.62,1.04);
	theL2L2p5EtaEff->GetYaxis()->SetNdivisions(508);
	theL2L2p5EtaEff->Draw("AP");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL2L2p5eta->SaveAs(savePath + "/L2L2p5TauEta.pdf");

	cout << " ***************** Plot: L3 eff. over pT ****************** " << endl;
	TCanvas* canvasL3 = new TCanvas("canvasL3","canvasL3");
	canvasL3->cd();

	TH1F* denomPtL3 = (TH1F*)hltFile->Get("denominator_Total");
	TH1F* numPtL3 = (TH1F*)hltFile->Get("numeratorL3_Total");
	TGraphAsymmErrors* theL3Eff = new TGraphAsymmErrors(numPtL3, denomPtL3, "cl=0.683 b(1,1) mode");
	theL3Eff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL3Eff->GetXaxis()->SetTitle(t_xaxis_pt);
	theL3Eff->GetXaxis()->SetRangeUser(0.,205.);
	theL3Eff->GetYaxis()->SetRangeUser(0,1.04);
	theL3Eff->Draw("AP");
	TF1* L3Fit = logFitTest(15,numPtL3,denomPtL3);
	L3Fit->Draw("same");
	theL3Eff->Draw("P");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL3->SaveAs(savePath + "/L3TauPt.pdf");
	cout << " ***************** Plot: L3 eff. over eta ****************** " << endl;
	TCanvas* canvasL3eta = new TCanvas("canvasL3eta","canvasL3eta");
	canvasL3eta->cd();

	TH1F* denomEtaL3 = (TH1F*)hltFile->Get("denominatorEta_Total");
	TH1F* numEtaL3 = (TH1F*)hltFile->Get("numeratorEtaL3_Total");
	numEtaL3->Rebin(rebin_eff);
	//denomEtaL3->Rebin(rebin_eff);
	TGraphAsymmErrors* theL3EtaEff = new TGraphAsymmErrors(numEtaL3, denomEtaL3, "cl=0.683 b(1,1) mode");
	theL3EtaEff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL3EtaEff->GetXaxis()->SetTitle(t_xaxis_eta);
	theL3EtaEff->GetXaxis()->SetRangeUser(-2.5,2.5);
	theL3EtaEff->GetYaxis()->SetRangeUser(0.62,1.04);
	theL3EtaEff->GetYaxis()->SetNdivisions(508);
	theL3EtaEff->Draw("AP");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL3eta->SaveAs(savePath + "/L3TauEta.pdf");





	cout << " ***************** Plot: L1L2 eff. over pT ****************** " << endl;
	TCanvas* canvasL1L2 = new TCanvas("canvasL1L2","canvasL1L2");
	canvasL1L2->cd();

	TH1F* denomPtL1L2 = (TH1F*)hltFile->Get("denominator_Total");
	TH1F* numPtL1L2 = (TH1F*)hltFile->Get("numeratorL1L2_Total");
	TGraphAsymmErrors* theL1L2Eff = new TGraphAsymmErrors(numPtL1L2, denomPtL1L2, "cl=0.683 b(1,1) mode");
	theL1L2Eff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL1L2Eff->GetXaxis()->SetTitle(t_xaxis_pt);
	theL1L2Eff->GetXaxis()->SetRangeUser(0.,205.);
	theL1L2Eff->GetYaxis()->SetRangeUser(0,1.04);
	theL1L2Eff->Draw("AP");
	TF1* L1L2Fit = logFitTest(15,numPtL1L2,denomPtL1L2);
	L1L2Fit->Draw("same");
	theL1L2Eff->Draw("P");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL1L2->SaveAs(savePath + "/L1L2TauPt.pdf");
	cout << " ***************** Plot: L1L2 eff. over eta ****************** " << endl;
	TCanvas* canvasL1L2eta = new TCanvas("canvasL1L2eta","canvasL1L2eta");
	canvasL1L2eta->cd();

	TH1F* denomEtaL1L2 = (TH1F*)hltFile->Get("denominatorEta_Total");
	TH1F* numEtaL1L2 = (TH1F*)hltFile->Get("numeratorEtaL1L2_Total");
	numEtaL1L2->Rebin(rebin_eff);
	//denomEtaL1L2->Rebin(rebin_eff);
	TGraphAsymmErrors* theL1L2EtaEff = new TGraphAsymmErrors(numEtaL1L2, denomEtaL1L2, "cl=0.683 b(1,1) mode");
	theL1L2EtaEff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL1L2EtaEff->GetXaxis()->SetTitle(t_xaxis_eta);
	theL1L2EtaEff->GetXaxis()->SetRangeUser(-2.5,2.5);
	theL1L2EtaEff->GetYaxis()->SetRangeUser(0.62,1.04);
	theL1L2EtaEff->GetYaxis()->SetNdivisions(508);
	theL1L2EtaEff->Draw("AP");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL1L2eta->SaveAs(savePath + "/L1L2TauEta.pdf");

	cout << " ***************** Plot: L1L2L2p5 eff. over pT ****************** " << endl;
	TCanvas* canvasL1L2L2p5 = new TCanvas("canvasL1L2L2p5","canvasL1L2L2p5");
	canvasL1L2L2p5->cd();

	TH1F* denomPtL1L2L2p5 = (TH1F*)hltFile->Get("denominator_Total");
	TH1F* numPtL1L2L2p5 = (TH1F*)hltFile->Get("numeratorL1L2L2p5_Total");
	TGraphAsymmErrors* theL1L2L2p5Eff = new TGraphAsymmErrors(numPtL1L2L2p5, denomPtL1L2L2p5, "cl=0.683 b(1,1) mode");
	theL1L2L2p5Eff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL1L2L2p5Eff->GetXaxis()->SetTitle(t_xaxis_pt);
	theL1L2L2p5Eff->GetXaxis()->SetRangeUser(0.,205.);
	theL1L2L2p5Eff->GetYaxis()->SetRangeUser(0,1.04);
	theL1L2L2p5Eff->Draw("AP");
	TF1* L1L2L2p5Fit = logFitTest(15,numPtL1L2L2p5,denomPtL1L2L2p5);
	L1L2L2p5Fit->Draw("same");
	theL1L2L2p5Eff->Draw("P");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL1L2L2p5->SaveAs(savePath + "/L1L2L2p5TauPt.pdf");
	cout << " ***************** Plot: L1L2L2p5 eff. over eta ****************** " << endl;
	TCanvas* canvasL1L2L2p5eta = new TCanvas("canvasL1L2L2p5eta","canvasL1L2L2p5eta");
	canvasL1L2L2p5eta->cd();

	TH1F* denomEtaL1L2L2p5 = (TH1F*)hltFile->Get("denominatorEta_Total");
	TH1F* numEtaL1L2L2p5 = (TH1F*)hltFile->Get("numeratorEtaL1L2L2p5_Total");
	numEtaL1L2L2p5->Rebin(rebin_eff);
	//denomEtaL1L2L2p5->Rebin(rebin_eff);
	TGraphAsymmErrors* theL1L2L2p5EtaEff = new TGraphAsymmErrors(numEtaL1L2L2p5, denomEtaL1L2L2p5, "cl=0.683 b(1,1) mode");
	theL1L2L2p5EtaEff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL1L2L2p5EtaEff->GetXaxis()->SetTitle(t_xaxis_eta);
	theL1L2L2p5EtaEff->GetXaxis()->SetRangeUser(-2.5,2.5);
	theL1L2L2p5EtaEff->GetYaxis()->SetRangeUser(0.62,1.04);
	theL1L2L2p5EtaEff->GetYaxis()->SetNdivisions(508);
	theL1L2L2p5EtaEff->Draw("AP");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL1L2L2p5eta->SaveAs(savePath + "/L1L2L2p5TauEta.pdf");

	cout << " ***************** Plot: L1_HLT eff. over pT ****************** " << endl;
	TCanvas* canvasL1_HLT = new TCanvas("canvasL1_HLT","canvasL1_HLT");
	canvasL1_HLT->cd();

	TH1F* denomPtL1_HLT = (TH1F*)hltFile->Get("denominator_Total");
	TH1F* numPtL1_HLT = (TH1F*)hltFile->Get("numeratorL1_HLT_Total");
	TGraphAsymmErrors* theL1_HLTEff = new TGraphAsymmErrors(numPtL1_HLT, denomPtL1_HLT, "cl=0.683 b(1,1) mode");
	theL1_HLTEff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL1_HLTEff->GetXaxis()->SetTitle(t_xaxis_pt);
	theL1_HLTEff->GetXaxis()->SetRangeUser(0.,205.);
	theL1_HLTEff->GetYaxis()->SetRangeUser(0,1.04);
	theL1_HLTEff->Draw("AP");
	TF1* L1_HLTFit = logFitTest(15,numPtL1_HLT,denomPtL1_HLT);
	L1_HLTFit->Draw("same");
	theL1_HLTEff->Draw("P");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL1_HLT->SaveAs(savePath + "/L1_HLTTauPt.pdf");
	cout << " ***************** Plot: L1_HLT eff. over eta ****************** " << endl;
	TCanvas* canvasL1_HLTeta = new TCanvas("canvasL1_HLTeta");
	canvasL1_HLTeta->cd();

	TH1F* denomEtaL1_HLT = (TH1F*)hltFile->Get("denominatorEta_Total");
	TH1F* numEtaL1_HLT = (TH1F*)hltFile->Get("numeratorEtaL1_HLT_Total");
	numEtaL1_HLT->Rebin(rebin_eff);
	//denomEtaL1_HLT->Rebin(rebin_eff);
	TGraphAsymmErrors* theL1_HLTEtaEff = new TGraphAsymmErrors(numEtaL1_HLT, denomEtaL1_HLT, "cl=0.683 b(1,1) mode");
	theL1_HLTEtaEff->GetYaxis()->SetTitle(t_yaxis_eff);
	theL1_HLTEtaEff->GetXaxis()->SetTitle(t_xaxis_eta);
	theL1_HLTEtaEff->GetXaxis()->SetRangeUser(-2.5,2.5);
	theL1_HLTEtaEff->GetYaxis()->SetRangeUser(0.62,1.04);
	theL1_HLTEtaEff->GetYaxis()->SetNdivisions(508);
	theL1_HLTEtaEff->Draw("AP");
	latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
	canvasL1_HLTeta->SaveAs(savePath + "/L1_HLTTauEta.pdf");

	cout << " ***************** Plot: eta resolutions ****************** " << endl;
	TCanvas* canvasetaResol = new TCanvas("canvasL1etaResol","canvasL1etaResol");
	canvasetaResol->cd();

	TH1F* etaResolL1 = (TH1F*)l1File->Get("resEtaL1_Total");
	etaResolL1->Sumw2();
	etaResolL1->Rebin(4);
	etaResolL1->Scale(1./etaResolL1->Integral());
    etaResolL1->GetYaxis()->SetTitle(t_yaxis_dens);
    etaResolL1->GetXaxis()->SetTitle(t_xaxis_etaresol);
    etaResolL1->GetXaxis()->SetRangeUser(-0.35,0.35);
    etaResolL1->GetYaxis()->SetTitleOffset(1.25);
    for (unsigned int i = 1; i<=etaResolL1->GetNbinsX(); i++){
    	if (etaResolL1->GetBinContent(i) == 0.)
    		etaResolL1->SetBinContent(i,0.000001);
    }
    etaResolL1->SetLineColor(l1Color);
    etaResolL1->SetLineWidth(2);
    etaResolL1->SetLineStyle(9);

	TH1F* etaResolL2 = (TH1F*)hltFile->Get("resEtaL2_Total");
	etaResolL2->Sumw2();
	etaResolL2->Rebin(4);
	etaResolL2->Scale(1./etaResolL2->Integral());
    for (unsigned int i = 1; i<=etaResolL2->GetNbinsX(); i++){
    	if (etaResolL2->GetBinContent(i) == 0.)
    		etaResolL2->SetBinContent(i,0.000001);
    }
    etaResolL2->SetLineColor(l2Color);
    etaResolL2->SetLineWidth(2);
    etaResolL2->SetLineStyle(2);

	TH1F* etaResolL3 = (TH1F*)hltFile->Get("resEtaL3_Total");
	etaResolL3->Sumw2();
	etaResolL3->Rebin(4);
	etaResolL3->Scale(1./etaResolL3->Integral());
    for (unsigned int i = 1; i<=etaResolL3->GetNbinsX(); i++){
    	if (etaResolL3->GetBinContent(i) == 0.)
    		etaResolL3->SetBinContent(i,0.000001);
    }
    etaResolL3->SetLineColor(l3Color);
    etaResolL3->SetLineWidth(2);
    etaResolL3->SetLineStyle(1);

    etaResolL1->GetYaxis()->SetRangeUser(0., 1.1 * etaResolL3->GetMaximum());

    etaResolL1->Draw("hist");
    etaResolL2->Draw("hist same");
    etaResolL3->Draw("hist same");

	TLegend* legendEtaResol = new TLegend(0.65,0.68,0.96,0.88);
	legendEtaResol->SetBorderSize(1);
	legendEtaResol->SetTextSize(0.028);
	legendEtaResol->SetBorderSize(0);
	legendEtaResol->SetFillColor(0);
	legendEtaResol->AddEntry(etaResolL1,	"L1 objects","l");
	legendEtaResol->AddEntry(etaResolL2,	"L2 objects","l");
	legendEtaResol->AddEntry(etaResolL3,	"L3 objects","l");
	legendEtaResol->Draw();

    latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
    canvasetaResol->SetGrid(0,0);
    canvasetaResol->SaveAs(savePath + "/EtaResolutions.pdf");

	cout << " ***************** Plot: pT resolutions ****************** " << endl;
	TCanvas* canvasptResol = new TCanvas("canvasptResol","canvasptResol");
	canvasptResol->cd();

	TH1F* ptResolL1 = (TH1F*)l1File->Get("resPtL1_Total");
	ptResolL1->Sumw2();
	ptResolL1->Rebin(8);
	ptResolL1->Scale(1./ptResolL1->Integral());
    ptResolL1->GetYaxis()->SetTitle(t_yaxis_dens);
    ptResolL1->GetXaxis()->SetTitle(t_xaxis_ptresol);
    ptResolL1->GetXaxis()->SetRangeUser(-25.0,65.0);
    ptResolL1->GetYaxis()->SetTitleOffset(1.25);
    ptResolL1->SetLineColor(l1Color);
    ptResolL1->SetLineStyle(9);
    ptResolL1->SetLineWidth(2);

	TH1F* ptResolL2 = (TH1F*)hltFile->Get("resPtL2_Total");
	ptResolL2->Sumw2();
	ptResolL2->Rebin(8);
	ptResolL2->Scale(1./ptResolL2->Integral());
	ptResolL2->SetLineColor(l2Color);
	ptResolL2->SetLineStyle(2);
	ptResolL2->SetLineWidth(2);

	TH1F* ptResolL3 = (TH1F*)hltFile->Get("resPtL3_Total");
	ptResolL3->Sumw2();
	ptResolL3->Rebin(8);
	ptResolL3->Scale(1./ptResolL3->Integral());
	ptResolL3->SetLineColor(l3Color);
	ptResolL3->SetLineStyle(1);
	ptResolL3->SetLineWidth(2);

    ptResolL1->GetYaxis()->SetRangeUser(0., 1.1 * ptResolL3->GetMaximum());

    ptResolL1->Draw("hist");
    ptResolL2->Draw("hist same");
    ptResolL3->Draw("hist same");

	TLegend* legendPtResol = new TLegend(0.65,0.68,0.96,0.88);
	legendPtResol->SetBorderSize(1);
	legendPtResol->SetTextSize(0.028);
	legendPtResol->SetBorderSize(0);
	legendPtResol->SetFillColor(0);
	legendPtResol->AddEntry(ptResolL1,	"L1 objects","l");
	legendPtResol->AddEntry(ptResolL2,	"L2 objects","l");
	legendPtResol->AddEntry(ptResolL3,	"L3 objects","l");
	legendPtResol->Draw();

    latex.DrawLatex(xLatex,yLatex,latexText_2012BCD);
    canvasptResol->SetGrid(0,0);
    canvasptResol->SaveAs(savePath + "/PtResolutions.pdf");


    cout << " ***************** Plot: L1 Rate vs. threshold ****************** " << endl;
    TCanvas* canvasL1rate = new TCanvas("canvasL1rate","canvasL1rate");
    canvasL1rate->cd();
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

    l1TauRate->GetYaxis()->SetTitle("Rate / Hz");
    l1TauRate->GetXaxis()->SetTitle("p_{T} threshold / GeV");
    l1TauRate->GetXaxis()->SetRangeUser(20., 105.); // for linear x axis
    //l1TauRate->GetXaxis()->SetRangeUser(10., 105.); // for log x axis
    l1TauRate->GetYaxis()->SetRangeUser(0.6, 2e6);
    l1TauRate->SetMarkerStyle(22);
    l1TauRate->SetMarkerColor(l1TauColor);
    l1TauRate->SetLineColor(l1TauColor);
    l1TauRate->Draw("AP");
    l1JetRate->SetMarkerStyle(21);
    l1JetRate->SetMarkerColor(l1JetColor);
    l1JetRate->SetLineColor(l1JetColor);
    l1JetRate->Draw("P");
	TLegend* legend = new TLegend(0.2,0.2,0.6,0.4);
	legend->SetBorderSize(1);
	legend->SetLineColor(1);
	legend->SetLineStyle(1);
	legend->SetLineWidth(1);
	legend->SetFillColor(0);
	legend->AddEntry(l1TauRate,"Double Tau, |#eta|<2.17","pel");
	legend->AddEntry(l1JetRate,"Double Jet, |#eta|<3.0","pel");
	legend->Draw();
	const char* latexText = "#sqrt{s}=8 TeV, L= 5 #times 10^{33} cm^{-2}s^{-1}";
	latex.DrawLatex(xLatex-0.15,yLatex,latexText);
	canvasL1rate->SaveAs(savePath + "/L1TauRate.pdf");
	cout << "All done. Results can be found here:\n     " << savePath << endl;
}

