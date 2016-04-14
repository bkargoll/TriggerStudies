import math
from array import array
import ROOT

def errorfunc(x, norm, effTurnOn, width):
    return norm * 0.5 * (ROOT.TMath.Erf((x - effTurnOn) / width / math.sqrt(2)) + 1.);



def fcnSimone(npar, gin, f, par, iflag):
    global minBinUsedByFit, num, denom
    
    maxBinUsedByFit = num.GetNbinsX()
    logL = 0
    effBin = []
    Ntrial = []
    Npass = []
    i = -1
    for bin in range(minBinUsedByFit,maxBinUsedByFit+1):
        i = i+1
        x = num.GetBinCenter(bin)
        effBin.append(errorfunc(x, par[0], par[1], par[2]))
        Ntrial.append(denom.GetBinContent(bin))
        Npass.append(num.GetBinContent(bin))
        if (Ntrial[i] == 0): continue
        
        logfactor = 0
        for ii in range(1,Npass[i]+1):
            NO INTEGER BIN ENTRIES!!! DOES NOT WORK!!!

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


def logFitTest(setMinBinUsedByFit, histEff):
    minuit = ROOT.TMinuit(5)    # initialize TMinuit with a maximum of 5 params
    minuit.SetFCN(fcnSimone)
    minuit.SetPrintLevel(-1)
    
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
  // minuit->mnprin(3,amin);

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
