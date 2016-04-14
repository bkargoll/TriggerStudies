#include "TH1F.h"
#include "TFile.h"
#include "TF2.h"
#include "TF1.h"
#include "TChain.h"
#include "TCut.h"
#include "TMath.h"
#include "TMinuit.h"
#include "TGraphAsymmErrors.h"
#include "Math/TDataPoint.h"
#include <iostream> 

double eff[100], p[100], logp[100];
int Ntrial[500], Npass[500];
int minBinUsedByFit;
TH1F* _all, *_pass, *eff0;
TGraphAsymmErrors* _Tgae;
TF1* _fitfunc;

void effic(TH1F* numer, TH1F* denom, TH1F* ratio) {
	//eff->Reset();
	// Loop over the two histograms and take the ratio
	std::cout << "number of bins = " << ratio->GetNbinsX() << "\n";
	for (int i = 0; i < (ratio->GetNbinsX()) + 1; i++) {
		float numval = numer->GetBinContent(i);
		float denval = denom->GetBinContent(i);
		if (denval != 0.0 && numval != 0.0) {
			float effval = numval / denval;
			float efferr = sqrt(effval * (1 - effval) / denval);
			//printf(" Bin %i Efficiency %f Error %f \n",i,effval,efferr);
			ratio->SetBinContent(i, effval);
			ratio->SetBinError(i, efferr);
		} else if (denval == 0.)
			ratio->SetBinContent(i, 0);
	}
}

double tailfunc(double x, double start, double coeff, double n){
	return start + coeff/(1-n) * TMath::Power(x,1-n);
}
double tailplot(double *x, double *par){
	return tailfunc(x[0],par[0],par[1],par[2]);
}

double errorfunc(double x, double norm, double effTurnOn, double width) {
	return norm * 0.5 * (TMath::Erf((x - effTurnOn) / width / sqrt(2)) + 1.);
}

double crystalballfunc(double m, double m0, double sigma, double alpha, double n,
		double norm) {
	const double sqrtPiOver2 = 1.2533141373;
	const double sqrt2 = 1.4142135624;
	double sig = fabs((double) sigma);
	double t = (m - m0) / sig;
	if (alpha < 0)
		t = -t;
	double absAlpha = fabs(alpha / sig);
	double a = TMath::Power(n / absAlpha, n) * exp(-0.5 * absAlpha * absAlpha);
	double b = absAlpha - n / absAlpha;
	double ApproxErf;
	double arg = absAlpha / sqrt2;
	if (arg > 5.)
		ApproxErf = 1;
	else if (arg < -5.)
		ApproxErf = -1;
	else
		ApproxErf = TMath::Erf(arg);
	double leftArea = (1 + ApproxErf) * sqrtPiOver2;
	double rightArea = (a * 1 / TMath::Power(absAlpha - b, n - 1)) / (n - 1);
	double area = leftArea + rightArea;
	if (t <= absAlpha) {
		arg = t / sqrt2;
		if (arg > 5.)
			ApproxErf = 1;
		else if (arg < -5.)
			ApproxErf = -1;
		else
			ApproxErf = TMath::Erf(arg);
		return norm * (1 + ApproxErf) * sqrtPiOver2 / area;
	} else {
		return norm * (leftArea + a * (1 / TMath::Power(t - b, n - 1) - 1
				/ TMath::Power(absAlpha - b, n - 1)) / (1 - n)) / area;
	}
}

double crystalballplot(double *x, double *par){
	return crystalballfunc(x[0],par[0],par[1],par[2],par[3],par[4]);
}

void fcn(int &npar, double *gin, double &f, double *par, int iflag) {
	int minBin = minBinUsedByFit;
	int maxBin = _all->GetNbinsX();
	double logL = 0.;
	for (int i = minBin; i < (maxBin + 1); i++) {
		double x = _all->GetBinCenter(i);
		//eff[i] = errorfunc(x, par[0], par[1], par[2]);
		eff[i] = crystalballfunc(x,par[0],par[1],par[2],par[3],par[4]);
		Ntrial[i] = int(_all->GetBinContent(i));
		Npass[i] = int(_pass->GetBinContent(i));
		if ((Ntrial[i] == 0))
			continue;

		double logfactor = 0.;
		for (int ii = 1; ii <= Npass[i]; ii++) {
			logfactor = logfactor + log(1. * (Ntrial[i] - Npass[i] + ii))
					- log(1. * ii);
		}
		logp[i] = logfactor + 1. * Npass[i] * log(eff[i]) + log(1. - eff[i])
				* (Ntrial[i] - Npass[i]);
		logL = logL - logp[i];
	}
	f = 1. * logL;
}

void fcnSimone(int &npar, double *gin, double &f, double *par, int iflag){
  int minBin = minBinUsedByFit;
  int maxBin = _all->GetNbinsX();
  double logL =0.;
  for (int i = minBin; i<(maxBin+1); i++){
    double x = _all->GetBinCenter(i);
    eff[i] =  par[0]*0.5*(TMath::Erf((x-par[1])/2./par[2]/sqrt(x))+1.);
    Ntrial[i] = int(_all->GetBinContent(i));
    Npass[i] =  int(_pass->GetBinContent(i));
    if ((Ntrial[i] ==0)) continue;

    double logfactor = 0.;
    for (int ii = 1; ii<=Npass[i]; ii++){
	 logfactor = logfactor+log(1.*(Ntrial[i]-Npass[i]+ii)) - log(1.*ii);
    }
    logp[i] = logfactor+ 1.*Npass[i]*log(eff[i])+log(1.-eff[i])*(Ntrial[i]-Npass[i]);
    logL = logL -logp[i];
  }
  f = 1.*logL;
}
double effplotSimone(double *x, double *par) {
  double func = par[0]*0.5*(TMath::Erf((x[0]-par[1])/2./par[2]/sqrt(x[0]))+1.);
  return func;
}

double fcnPlot2D(double *var, double *par){
	int minBin = minBinUsedByFit;
	int maxBin = _all->GetNbinsX();
	double logL = 0.;
	for (int i = minBin; i < (maxBin + 1); i++) {
		double x = _all->GetBinCenter(i);
		//eff[i] = errorfunc(x, par[0], par[1], par[2]);
		eff[i] = crystalballfunc(x,par[0],par[1],var[0],var[1],par[2]);
		Ntrial[i] = int(_all->GetBinContent(i));
		Npass[i] = int(_pass->GetBinContent(i));
		if ((Ntrial[i] == 0))
			continue;

		double logfactor = 0.;
		for (int ii = 1; ii <= Npass[i]; ii++) {
			logfactor = logfactor + log(1. * (Ntrial[i] - Npass[i] + ii))
					- log(1. * ii);
		}
		logp[i] = logfactor + 1. * Npass[i] * log(eff[i]) + log(1. - eff[i])
				* (Ntrial[i] - Npass[i]);
		logL = logL - logp[i];
	}
	return 1. * logL;
}


void prefcn(int &npar, double *gin, double &f, double *par, int iflag) {
	int minBin = minBinUsedByFit;
	int maxBin = _all->GetNbinsX();
	double logL = 0.;
	for (int i = minBin; i < (maxBin + 1); i++) {
		double x = _all->GetBinCenter(i);
		eff[i] = errorfunc(x, par[0], par[1], par[2]);
		//eff[i] = crystalballfunc(x,par[0],par[1],par[2],par[3],par[4]);
		Ntrial[i] = int(_all->GetBinContent(i));
		Npass[i] = int(_pass->GetBinContent(i));
		if ((Ntrial[i] == 0))
			continue;

		double logfactor = 0.;
		for (int ii = 1; ii <= Npass[i]; ii++) {
			logfactor = logfactor + log(1. * (Ntrial[i] - Npass[i] + ii))
					- log(1. * ii);
		}
		logp[i] = logfactor + 1. * Npass[i] * log(eff[i]) + log(1. - eff[i])
				* (Ntrial[i] - Npass[i]);
		logL = logL - logp[i];
	}
	f = 1. * logL;
}




//double efffunc(double x, double *par) {
//	double func = errorfunc(x, par[0],par[1],par[2]);
//	return func;
//}

double errorplot(double *x, double *par) {
	double func = errorfunc(x[0], par[0],par[1],par[2]);
	return func;
}

// chi2 parameter scan
double chi2scan(double *var, double *par){
	_fitfunc->SetParameters(par[0],par[1],var[0],var[1],par[2]);
	return _Tgae->Chisquare(_fitfunc);
}

TF1* crystalFit(TGraphAsymmErrors* theEff, double minEt = 15.) {
	std::cout << "~~~~~~~~~~~~~~~ Fit Error Function ~~~~~~~~~~~~~~~" << std::endl;
	TF1* prefit = new TF1("errorFunctionFit",errorplot,minEt,200.,3);
	prefit->SetParameters(0.95,30.,1.);
	prefit->SetParNames("norm","m0","sigma");
	prefit->SetLineColor(kGreen);
	theEff->Fit(prefit,"N","",minEt,200.);

//	std::cout << "~~~~~~~~~~~~~~~ Fit Tail Function ~~~~~~~~~~~~~~~" << std::endl;
//	TF1* tailfit = new TF1("tailFunctionFit",tailplot,40.,200.,3);
//	tailfit->SetParameters(0.8,1.,1.4);
//	tailfit->SetParNames("const","coeff","n");
//	tailfit->SetLineColor(kBlue);
//	theEff->Fit(tailfit,"N","",50.,200.);


	TF1* fit = new TF1("crystalBallFit",crystalballplot,minEt,200.,5);
	fit->SetParameters(prefit->GetParameter(0),prefit->GetParameter(2),1.7,1.4,prefit->GetParameter(1));

////	fit->SetParameters(prefit->GetParameter(0),prefit->GetParameter(2),1.7,tailfit->GetParameter(2),prefit->GetParameter(1));
	fit->SetParNames( "m0",  "sigma",  "alpha",  "n", "norm");

	for(unsigned int i=0;i<20;++i) {
		std::cout << "~~~~~~~~~~~~~~~ Fit " << i+1 << "~~~~~~~~~~~~~~~" << std::endl;
		Option_t * option = "NQ";
		if (i==19) option = "N";
		theEff->Fit(fit,option,"",minEt,200.);
	}

//	// chi2 scan
//	TCanvas* canvas2Dfcn = new TCanvas();
//	  gStyle->SetPalette(1);
//	  canvas2Dfcn->cd();
//	_Tgae = theEff;
//	_fitfunc = fit;
//	TF2* c2scan = new TF2("c2scan",chi2scan,-20.,20.,1.,10.,3);
//	c2scan->SetParameters(fit->GetParameter(0),fit->GetParameter(1),fit->GetParameter(4));
//	c2scan->Draw("colz");

	std::cout << "\n\n~~~~~~~~~~~~~~~ Fit Results: ~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Error function:" << std::endl;
	prefit->Print();
	std::cout << "Crystal ball function:" << std::endl;
	fit->Print();

	return fit;
}

TF1* logFitTest(int setMinBinUsedByFit, TH1F* passed, TH1F* all) {
   minBinUsedByFit =setMinBinUsedByFit;
   _all = all;
   _pass = passed;
   eff0 =(TH1F*)_all->Clone("eff0");

   TMinuit *minuit = new TMinuit(5);  //initialize TMinuit with a maximum of 5 params
   minuit->SetFCN(fcnSimone);
   minuit->SetPrintLevel(-1);
   double arglist[10];
   int ierflg = 0;

   arglist[0] = 1;
   minuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   double vstart[4] = {0.9, 30. , 1. , 0.01};
   double step[4] = {0.01 , 0.1 , 0.01 , 0.001};
   minuit->mnparm(0, "a1", vstart[0], step[0], 0.,1.0,ierflg);
   minuit->mnparm(1, "a2", vstart[1], step[1], 0,0,ierflg);
   minuit->mnparm(2, "a3", vstart[2], step[2], 0,0,ierflg);
   //minuit->mnparm(3, "a4", vstart[3], step[3], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 1000;
   arglist[1] = 10;

   minuit->mnexcm("MIGRAD", arglist ,2,ierflg);
   minuit->mnexcm("MINOS", arglist ,1,ierflg);
   double x0, dx0, y0, dy0, z0, dz0;
   minuit->GetParameter(0, x0, dx0);
   //std::cout << "x=" << x0 << "\n";
   minuit->GetParameter(1, y0, dy0);
   //std::cout << "y=" << y0 << "\n";
   minuit->GetParameter(2, z0, dz0);
   //std::cout << "z=" << z0 << "\n";

// Print results
   double amin,edm,errdef;
   int nvpar,nparx,icstat;
   minuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   minuit->mnprin(3,amin);

   eff0->Reset();

   TGraphAsymmErrors* theEff = new TGraphAsymmErrors(_pass, _all, "cl=0.683 b(1,1) mode");
   theEff->SetTitle("Efficiency");
   //theEff->Draw("AP");

   TF1 *f1 = new TF1("myfunc",effplotSimone,_all->GetBinLowEdge(setMinBinUsedByFit),200,3);
   //TF1 *f1 = new TF1("myfunc",effplot,30,100,3);
   f1->SetParameters(x0,y0,z0);
   f1->SetParNames("constant","coefficient","width");
   //f1->Draw("same");

   return f1;
}

///// test to get crystal ball fit done.. aborted
//TF1* logFitTest(int setMinBinUsedByFit, TH1F* passed, TH1F* all) {
//	minBinUsedByFit = setMinBinUsedByFit;
//	_all = all;
//	_pass = passed;
//	eff0 = (TH1F*) _all->Clone("eff0");
//
//	//*********************** first pass: fit of error function
//	TMinuit *preminuit = new TMinuit(3);
//	preminuit->SetFCN(prefcn);
//	double prearglist[10];
//	int preierflg = 0;
//
//	prearglist[0] = 1;
//	preminuit->mnexcm("SET ERR", prearglist, 1, preierflg);
//	// Set starting values and step sizes for parameters
//	double prevstart[4] = { 0.9, 30., 1., 0.01 };
//	double prestep[4] = { 0.01, 0.1, 0.01, 0.001 };
//	preminuit->mnparm(0, "a1", prevstart[0], prestep[0], 0., 1.0, preierflg);
//	preminuit->mnparm(1, "a2", prevstart[1], prestep[1], 0, 0, preierflg);
//	preminuit->mnparm(2, "a3", prevstart[2], prestep[2], 0, 0, preierflg);
//
//	// Now ready for minimization step
//	prearglist[0] = 1000;
//	prearglist[1] = 10;
//	preminuit->mnexcm("MIGRAD", prearglist, 2, preierflg);
//	preminuit->mnexcm("MINOS", prearglist, 1, preierflg);
//
//	double x0, dx0, y0, dy0, z0, dz0;
//	preminuit->GetParameter(0, x0, dx0);
//	//std::cout << "x=" << x0 << "\n";
//	preminuit->GetParameter(1, y0, dy0);
//	//std::cout << "y=" << y0 << "\n";
//	preminuit->GetParameter(2, z0, dz0);
//	//std::cout << "z=" << z0 << "\n";
//
//	TGraphAsymmErrors* theEff = new TGraphAsymmErrors(_pass, _all,
//			"cl=0.683 b(1,1) mode");
//	theEff->SetTitle("Efficiency");
//	theEff->Draw("AP");
//
//	TF1 *fError = new TF1("errorfunc", errorplot, 0, 200, 3);
//	fError->SetParameters(x0,y0,z0);
//	fError->SetParNames("norm", "m0", "slope");
//	fError->SetLineColor(kGray);
//	fError->Draw("same");
//
//	//*********************** second pass: fit of crystal ball function
//	TMinuit *minuit = new TMinuit(5); //initialize TMinuit with a maximum of 5 params
//	minuit->SetFCN(fcn);
//	//minuit->SetPrintLevel(-1);
//	double arglist[10];
//	int ierflg = 0;
//
//	arglist[0] = 1;
//	minuit->mnexcm("SET ERR", arglist, 1, ierflg);
//
//	// Set starting values and step sizes for parameters
//	minuit->mnparm(0, "m0", 	y0, 0.1,	0,	0,	ierflg);
//	minuit->mnparm(1, "sigma", 	z0, 0.01, 	0, 	0, 	ierflg);
//	minuit->mnparm(2, "alpha", 	5.0, 0.5,	0, 	0, 	ierflg);
//	minuit->mnparm(3, "n", 		2.0, 0.5,	0,	0.,	ierflg);
//	minuit->mnparm(4, "norm", 	x0, 0.01,	0.,	1.,	ierflg);
//
//	// Now ready for minimization step
//	arglist[0] = 1000;
//	arglist[1] = 10;
//
//	//minuit->mnexcm("MIGRAD", arglist, 2, ierflg);
//	//minuit->mnexcm("MINOS", arglist, 1, ierflg);
//
//	double fm0, fsigma, falpha, fn, fnorm;
//	double dm0, dsigma, dalpha, dn, dnorm;
//	minuit->GetParameter(0,fm0, dm0);
//	minuit->GetParameter(1,fsigma, dsigma);
//	minuit->GetParameter(2,falpha,dalpha );
//	minuit->GetParameter(3,fn, dn);
//	minuit->GetParameter(4,fnorm, dnorm);
//
//	// Print results
//	double amin, edm, errdef;
//	int nvpar, nparx, icstat;
//	minuit->mnstat(amin, edm, errdef, nvpar, nparx, icstat);
//	//minuit->mnprin(3,amin);
//
//	eff0->Reset();
//
////	TGraphAsymmErrors* theEff = new TGraphAsymmErrors(_pass, _all,
////			"cl=0.683 b(1,1) mode");
////	theEff->SetTitle("Efficiency");
////	//theEff->Draw("AP");
//
//	//TF1 *f1 = new TF1("myfunc", errorplot, 0, 200, 3);
//	TF1 *fCrystal = new TF1("crystalfunc",crystalballplot,0,200,5 );
//	//TF1 *f1 = new TF1("myfunc",errorplot,30,100,3);
//	fCrystal->SetParameters(fm0,fsigma,falpha,fn,fnorm);
//	fCrystal->SetParNames("m0", "sigma", "alpha", "n", "norm");
//	//f1->Draw("same");
//
//	  TCanvas* canvas2Dfcn = new TCanvas();
//	  gStyle->SetPalette(1);
//	  canvas2Dfcn->cd();
//	  TF2* fcn2D = new TF2("fcnfunc",fcnPlot2D,0.,10.,0.,10.,3);
//	  fcn2D->SetParameters(y0,z0,x0);
////	  fcn2D->GetXaxis->SetTitle("#alpha");
////	  fcn2D->GetYaxis->SetTitle("n");
//	  fcn2D->Draw("colz");
//
//	return fCrystal;
//}

