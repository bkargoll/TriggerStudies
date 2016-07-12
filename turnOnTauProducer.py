import ROOT
from DataFormats.FWLite import Events, Handle
import array
import imp
from tdrstyle import setTDRStyle
from time import time
from helpers import *


eventCount = 0

#xbin = [10,15,18,20,22,25,30,35,40,45,50,60,75,100,160]
#xbin = [5,10,15,17,18,19,20,25,30,35,40,45,50,55,60,120,200] # normal bins
xbin = [5,10,15,17,18,19,20,22,24,26,28,30,32,34,36,38,40,42.5,45,47.5,50,52.5,55,60,70,80,100,120,200] # small bins, labelled "smB"
xbins = array.array('d',xbin)

#xbineta = [0.,0.25,0.5,0.75,1.0,1.2221,1.4442,1.556,1.8,2.1]
#xbineta = [-2.1,-1.8,-1.556,-1.4442,-1.2221,-1.0,-0.75,-0.5,-0.25,0.,0.25,0.5,0.75,1.0,1.2221,1.4442,1.556,1.8,2.1]
#xbineta = [-2.5, -2.4, -2.3, -2.2, -2.1, -2.0, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5]
# xbins accordnig to the size of trigger regions
xbineta = [-3.0, -2.172, -1.740, -1.392, -1.044, -0.696, -0.348, 0.0, 0.348, 0.696, 1.044, 1.392, 1.740, 2.172, 3.0]

xbinseta = array.array('d',xbineta)

def histograms(fileName, labelOffline, labelL1, labelL2, labelL2p5, labelL3, L1TauPtCut=0, L1JetPtCut=0, L2PtCut=25., L3PtCut=25., MTCut=40., invertMT=False,
               nProngsCut=5, dZCut=0.2, offlineProngs=0, maxInvM=10000., offlinePtCut=40., etaBinList=[]):

    events = Events(fileName)
    # vertex
    VertexHandle = Handle('std::vector<reco::Vertex>')
    vertexLabel = "offlinePrimaryVertices"
    # vertexLabel = "hltPixelVertices"

    # taus
    TauHandle = Handle('std::vector<reco::PFTau>')
    JetHandle = Handle('std::vector<reco::CaloJet>')
    L1Handle = Handle('std::vector<l1extra::L1JetParticle>')
    METHandle = Handle('std::vector<reco::PFMET>')
    #PFJetHandle = Handle('std::vector<reco::PFJet>')
    MuonHandle = Handle('std::vector<reco::Muon>')
    
    # parse eta etaBin information
    if etaBinList == []: etaBinList = [[0.0, 2.1, "Total"]]
    
    # book histograms
    deltaZTauTau     = ROOT.TH1F("deltaZTauTau","",200,0,10.)
    mTH              = ROOT.TH1F("mTH","",100,0,100)
    invM             = ROOT.TH1F("invM","",200,0,200)
    invMSel          = ROOT.TH1F("invMSel","",200,0,200)
    nTaus            = ROOT.TH1I("NTaus","",20,-0.5,19.5)
    deltaRL1L3       = ROOT.TH1F("deltaRL1L3","",200,0.,5.)
    tauPt = ROOT.TH1F("tauPt", "", 500, 0., 500.)
    tauEta = ROOT.TH1F("tauEta", "", 500, -2.5, 2.5)
    # efficiency histos
    numeratorL1Tau   = []
    numeratorL1Jet   = []
    numeratorL1      = []
    numeratorL2      = []
    numeratorL1L2    = []
    numeratorL2p5    = []
    numeratorL1L2L2p5= []
    numeratorL2L2p5= []
    numeratorL3      = []
    numeratorL1_HLT  = []
    denominator      = []
    numeratorEtaL1Tau= []
    numeratorEtaL1Jet= []
    numeratorEtaL1   = []
    numeratorEtaL2   = []
    numeratorEtaL1L2 = []
    numeratorEtaL2p5 = []
    numeratorEtaL1L2L2p5 = []
    numeratorEtaL2L2p5 = []
    numeratorEtaL3   = []
    numeratorEtaL1_HLT = []
    denominatorEta = []
    # resolution histos
    resEtaL1Tau  = []
    resEtaL1Jet  = []
    resEtaL1     = []
    resPhiL1Tau  = []
    resPhiL1Jet  = []
    resPhiL1     = []
    resRL1Tau       = []
    resRL1Jet       = []
    resRL1       = []
    resPtL1Tau      = []
    resPtL1Jet      = []
    resPtL1      = []
    resRelptL1Tau   = []
    resRelptL1Jet   = []
    resRelptL1   = []
    resEtaL2     = []
    resPhiL2     = []
    resRL2       = []
    resPtL2      = []
    resRelptL2   = []
    resEtaL2p5   = []
    resPhiL2p5   = []
    resRL2p5     = []
    resPtL2p5    = []
    resRelptL2p5 = []
    resEtaL3     = []
    resPhiL3     = []
    resRL3       = []
    resPtL3      = []
    resRelptL3   = []
    
    NEvt = 0
    NEvtMuon = 0
    NEvtMuonMT = 0
    NEvtMuonMTTau = 0
    NMatchedL1 = [] 
    NMatchedL2 = [] 
    NMatchedL2p5 = [] 
    NMatchedL3 = []  
    
    for etaBin in etaBinList:
        numeratorL1Tau.append(ROOT.TH1F("numeratorL1Tau_"+etaBin[2],"",len(xbin)-1,xbins))
        numeratorL1Jet.append(ROOT.TH1F("numeratorL1Jet_"+etaBin[2],"",len(xbin)-1,xbins))
        numeratorL1.append(ROOT.TH1F("numeratorL1_"+etaBin[2],"",len(xbin)-1,xbins))
        numeratorL2.append(ROOT.TH1F("numeratorL2_"+etaBin[2],"",len(xbin)-1,xbins))
        numeratorL1L2.append(ROOT.TH1F("numeratorL1L2_"+etaBin[2],"",len(xbin)-1,xbins))
        numeratorL2p5.append(ROOT.TH1F("numeratorL2p5_"+etaBin[2],"",len(xbin)-1,xbins))
        numeratorL1L2L2p5.append(ROOT.TH1F("numeratorL1L2L2p5_"+etaBin[2],"",len(xbin)-1,xbins))
        numeratorL2L2p5.append(ROOT.TH1F("numeratorL2L2p5_"+etaBin[2],"",len(xbin)-1,xbins))
        numeratorL3.append(ROOT.TH1F("numeratorL3_"+etaBin[2],"",len(xbin)-1,xbins))
        numeratorL1_HLT.append(ROOT.TH1F("numeratorL1_HLT_"+etaBin[2],"",len(xbin)-1,xbins))
        
        denominator.append(ROOT.TH1F("denominator_"+etaBin[2],"",len(xbin)-1,xbins))
        
        numeratorEtaL1.append(ROOT.TH1F("numeratorEtaL1_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        numeratorEtaL1Tau.append(ROOT.TH1F("numeratorEtaL1Tau_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        numeratorEtaL1Jet.append(ROOT.TH1F("numeratorEtaL1Jet_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        numeratorEtaL2.append(ROOT.TH1F("numeratorEtaL2_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        numeratorEtaL1L2.append(ROOT.TH1F("numeratorEtaL1L2_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        numeratorEtaL2p5.append(ROOT.TH1F("numeratorEtaL2p5_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        numeratorEtaL1L2L2p5.append(ROOT.TH1F("numeratorEtaL1L2L2p5_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        numeratorEtaL2L2p5.append(ROOT.TH1F("numeratorEtaL2L2p5_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        numeratorEtaL3.append(ROOT.TH1F("numeratorEtaL3_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        numeratorEtaL1_HLT.append(ROOT.TH1F("numeratorEtaL1_HLT_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        
        denominatorEta.append(ROOT.TH1F("denominatorEta_"+etaBin[2],"",len(xbineta)-1,xbinseta))
        
        resEtaL1Tau.append(ROOT.TH1F("resEtaL1Tau_"+etaBin[2],"",400,-1.0,1.0))   
        resPhiL1Tau.append(ROOT.TH1F("resPhiL1Tau_"+etaBin[2],"",400,-1.,1.))   
        resRL1Tau.append(ROOT.TH1F("resRL1Tau_"+etaBin[2],"",400,0.,1.))      
        resPtL1Tau.append(ROOT.TH1F("resPtL1Tau_"+etaBin[2],"",1000,-100.,100.))     
        resRelptL1Tau.append(ROOT.TH1F("resRelptL1Tau_"+etaBin[2],"",1000,-5.,5.))
        resEtaL1Jet.append(ROOT.TH1F("resEtaL1Jet_"+etaBin[2],"",400,-1.0,1.0))   
        resPhiL1Jet.append(ROOT.TH1F("resPhiL1Jet_"+etaBin[2],"",400,-1.,1.))   
        resRL1Jet.append(ROOT.TH1F("resRL1Jet_"+etaBin[2],"",400,0.,1.))      
        resPtL1Jet.append(ROOT.TH1F("resPtL1Jet_"+etaBin[2],"",1000,-100.,100.))     
        resRelptL1Jet.append(ROOT.TH1F("resRelptL1Jet_"+etaBin[2],"",1000,-5.,5.))
        resEtaL1.append(ROOT.TH1F("resEtaL1_"+etaBin[2],"",400,-1.0,1.0))   
        resPhiL1.append(ROOT.TH1F("resPhiL1_"+etaBin[2],"",400,-1.,1.))   
        resRL1.append(ROOT.TH1F("resRL1_"+etaBin[2],"",400,0.,1.))      
        resPtL1.append(ROOT.TH1F("resPtL1_"+etaBin[2],"",1000,-100.,100.))     
        resRelptL1.append(ROOT.TH1F("resRelptL1_"+etaBin[2],"",1000,-5.,5.))
          
        resEtaL2.append(ROOT.TH1F("resEtaL2_"+etaBin[2],"",400,-1.0,1.0)) 
        resPhiL2 .append(ROOT.TH1F("resPhiL2_"+etaBin[2],"",400,-1.,1.))   
        resRL2.append(ROOT.TH1F("resRL2_"+etaBin[2],"",400,0.,1.))       
        resPtL2.append(ROOT.TH1F("resPtL2_"+etaBin[2],"",1000,-100.,100.))      
        resRelptL2.append(ROOT.TH1F("resRelptL2_"+etaBin[2],"",1000,-5.,5.))   
        resEtaL2p5.append(ROOT.TH1F("resEtaL2p5_"+etaBin[2],"",400,-1.0,1.0))  
        resPhiL2p5.append(ROOT.TH1F("resPhiL2p5_"+etaBin[2],"",400,-1.,1.))  
        resRL2p5.append(ROOT.TH1F("resRL2p5_"+etaBin[2],"",400,0.,1.))     
        resPtL2p5.append(ROOT.TH1F("resPtL2p5_"+etaBin[2],"",1000,-100.,100.))    
        resRelptL2p5.append(ROOT.TH1F("resRelptL2p5_"+etaBin[2],"",1000,-5.,5.)) 
        resEtaL3.append(ROOT.TH1F("resEtaL3_"+etaBin[2],"",400,-1.0,1.0))    
        resPhiL3.append(ROOT.TH1F("resPhiL3_"+etaBin[2],"",400,-1.,1.))    
        resRL3.append(ROOT.TH1F("resRL3_"+etaBin[2],"",400,0.,1.))       
        resPtL3.append(ROOT.TH1F("resPtL3_"+etaBin[2],"",1000,-100.,100.))      
        resRelptL3.append(ROOT.TH1F("resRelptL3_"+etaBin[2],"",1000,-5.,5.))   
        
        NMatchedL1.append(0) 
        NMatchedL2.append(0) 
        NMatchedL2p5.append(0) 
        NMatchedL3.append(0)      

    print "Start event loop..."
    for event in events:
        if NEvt == 0: print "    ...started"
        NEvt += 1
        if NEvt % 5000 == 0: print "Process Event ", NEvt
        #if NEvt > 2000: break
         
        # getting the handle from the event
        event.getByLabel(labelOffline, TauHandle)
        offlineTaus = TauHandle.product()
        
        #event.getByLabel("ak5PFJets", PFJetHandle)
        #offlineJets = PFJetHandle.product()
        
        event.getByLabel(labelL1, "Tau", L1Handle)
        l1Taus = L1Handle.product()             

        event.getByLabel(labelL1, "Central", L1Handle)
        l1Jets = L1Handle.product()             

        event.getByLabel(labelL2, JetHandle)
        l2Taus = JetHandle.product()

        # event.getByLabel("hltCaloJetL1FastJetCorrected",JetHandle)
        # l2Jets = JetHandle.product()

        event.getByLabel(labelL2p5, JetHandle)
        l2p5Taus = JetHandle.product()             

        event.getByLabel(labelL3, TauHandle)
        l3Taus = TauHandle.product()

        event.getByLabel("pfMet", METHandle)
        met = METHandle.product().at(0)
        
        event.getByLabel("offlineSelectedMuons", MuonHandle)
        muons = MuonHandle.product()
        
        event.getByLabel(vertexLabel, VertexHandle)
        offlinevertex = VertexHandle.product().at(0).position()
        #vertexSize = VertexHandle.product().size()

        # matching variables
        matchingConeL1 = 0.5
        matchingConeHLT = 0.3
        foundL1Tau = False
        foundL1Jet = False
        foundL1 = False
        foundL2 = False
        foundL2p5 = False
        foundL3 = False
        # making MT variable
        MT = 0.
        myMuons = []
        for muon in muons:
            if muon.pt() < 10: continue
            if abs(muon.eta()) > 2.1: continue
            # apply vertex cuts which have been missing in muon selection before
            if abs(muon.innerTrack().dxy(offlinevertex)) > 0.045: continue
            if abs(muon.innerTrack().dz(offlinevertex)) > 0.1: continue
            myMuons.append((muon.pt(), muon))
        myMuons.sort()
        # get at least 1 muon
        if len(myMuons) < 1: continue 
        # additional muon veto
        if len(myMuons) > 1: continue
        NEvtMuon += 1
        muon = myMuons.pop()[1]
        MT = (muon.pt() + met.pt()) * (muon.pt() + met.pt()) - (muon.px() + met.px()) * (muon.px() + met.px()) - (muon.py() + met.py()) * (muon.py() + met.py())
        MT = math.sqrt(MT)
        # Remove W+Jets
        mTH.Fill(MT)
        # normal MTCut
        if not invertMT:
            if MT > MTCut: continue
        else:
            # inverse MT cut
            if MT < MTCut: continue
                
        NEvtMuonMT += 1

   
        # select best tau
        cntTaus = 0
        tau = None
        bestZmass = 999999.0
        for iTau in offlineTaus:
            cntTaus += 1
            if iTau.pt() < 5: continue
            if abs(iTau.eta()) > 2.5: continue
            # check: select only taus in 2nd peak structure 
            # if ((iTau.pt() < 55) or  (iTau.pt() > 100)): continue
            # muon and tau with opposite charge
            if iTau.charge() != -1 * muon.charge(): continue
            # require seperation between muon and tau
            dR_mutau = deltaR(iTau.eta(), iTau.phi(), muon.eta(), muon.phi())
            if dR_mutau < 0.5 : continue
            # make sure tau has a leading track, which is needed later for the dZ cut
            if not iTau.leadPFChargedHadrCand().trackRef().isNonnull(): continue
            # offline taus: only 1prongs, only 3prongs or all?
            if not offlineProngs == 0:
                if not iTau.signalPFChargedHadrCands().size() == offlineProngs: continue
            NEvtMuonMTTau += 1
            Zmass = 2 * (iTau.mass() * muon.mass() + muon.energy() * iTau.energy() - muon.px() * iTau.px() - muon.py() * iTau.py() - muon.pz() * iTau.pz())
            Zmass = math.sqrt(Zmass)
            invM.Fill(Zmass)
            if tau == None:
                bestZmass = Zmass
                tau = iTau
                continue
            if iTau.pt() > tau.pt():
                bestZmass = Zmass
                tau = iTau
        
        # skip Z->mumu events, where 1 mu fakes a tau
        if ((maxInvM != 0) & (bestZmass > maxInvM)): continue
        
        nTaus.Fill(cntTaus)
        if tau == None: continue
        invMSel.Fill(bestZmass)
        
        # check which eta bins to run on
        doEtaBin = []
        for etaBin in etaBinList:
            if (abs(tau.eta()) >= etaBin[0]) & (abs(tau.eta()) <= etaBin[1]):
                doEtaBin.append(True)
            else: doEtaBin.append(False)
        
        tauPt.Fill(tau.pt())
        tauEta.Fill(tau.eta())
        
        #fill denominator
        for i in range(len(etaBinList)):
            if doEtaBin[i] == True:
                denominator[i].Fill(tau.pt())
                if tau.pt() > offlinePtCut:
                    denominatorEta[i].Fill(tau.eta())
        
        # loop on numerators
        myL1Taus = []
        myL1Jets = []
        myL2Taus = []
        myL2p5Taus = []
        myL3Taus = []
        
        for l1Tau in l1Taus:
            if l1Tau.pt() < L1TauPtCut: continue
            if abs(l1Tau.eta()) > 2.1: continue
            dr = deltaR(tau.eta(), tau.phi(), l1Tau.eta(), l1Tau.phi())
            myL1Taus.append((dr, l1Tau))            
        for l1Jet in l1Jets:
            if l1Jet.pt() < L1JetPtCut: continue
            if abs(l1Jet.eta()) > 2.1: continue
            dr = deltaR(tau.eta(), tau.phi(), l1Jet.eta(), l1Jet.phi())
            myL1Jets.append((dr, l1Jet))
        for l2Tau in l2Taus:
            if l2Tau.pt() < L2PtCut: continue
            if abs(l2Tau.eta()) > 2.1: continue
            dr = deltaR(tau.eta(), tau.phi(), l2Tau.eta(), l2Tau.phi())
            myL2Taus.append((dr, l2Tau))            
        for l2p5Tau in l2p5Taus:
            if l2p5Tau.pt() < L2PtCut: continue
            if abs(l2p5Tau.eta()) > 2.1: continue
            dr = deltaR(tau.eta(), tau.phi(), l2p5Tau.eta(), l2p5Tau.phi())
            myL2p5Taus.append((dr, l2p5Tau))
        for l3Tau in l3Taus:
            if l3Tau.pt() < L3PtCut: continue
            if abs(l3Tau.eta()) > 2.1: continue
            dr = deltaR(tau.eta(), tau.phi(), l3Tau.eta(), l3Tau.phi())
            myL3Taus.append((dr, l3Tau))    
               
        # Filling L1 condition
        if ((L1TauPtCut == 0) & (L1JetPtCut == 0)):
            foundL1 = True
            for i in range(len(etaBinList)):
                if doEtaBin[i] == True:
                    NMatchedL1[i] += 1
        else:
            if len(myL1Taus) > 0:
                myL1Taus.sort()
                if myL1Taus[0][0] < matchingConeL1:
                    for i in range(len(etaBinList)):
                        if doEtaBin[i] == True:
                            numeratorL1Tau[i].Fill(tau.pt())
                            numeratorL1[i].Fill(tau.pt())
                            NMatchedL1[i] += 1
                            if tau.pt() > offlinePtCut:
                                numeratorEtaL1Tau[i].Fill(tau.eta())
                                numeratorEtaL1[i].Fill(tau.eta())
                            # fill resolution plots
                            resEtaL1Tau[i].Fill(myL1Taus[0][1].eta()-tau.eta())
                            resPhiL1Tau[i].Fill(deltaPhiWithSign(myL1Taus[0][1].phi(),tau.phi()))
                            resRL1Tau[i].Fill(myL1Taus[0][0])
                            resPtL1Tau[i].Fill(myL1Taus[0][1].pt()-tau.pt())
                            resRelptL1Tau[i].Fill((myL1Taus[0][1].pt()-tau.pt())/tau.pt())
                            resEtaL1[i].Fill(myL1Taus[0][1].eta()-tau.eta())
                            resPhiL1[i].Fill(deltaPhiWithSign(myL1Taus[0][1].phi(),tau.phi()))
                            resRL1[i].Fill(myL1Taus[0][0])
                            resPtL1[i].Fill(myL1Taus[0][1].pt()-tau.pt())
                            resRelptL1[i].Fill((myL1Taus[0][1].pt()-tau.pt())/tau.pt())
                    foundL1Tau = True
                    foundL1 = True

            if len(myL1Jets) > 0:
                myL1Jets.sort()
                if myL1Jets[0][0] < matchingConeL1:
                    for i in range(len(etaBinList)):
                        if doEtaBin[i] == True:
                            numeratorL1Jet[i].Fill(tau.pt())
                            numeratorL1[i].Fill(tau.pt())
                            NMatchedL1[i] += 1
                            if tau.pt() > offlinePtCut:
                                numeratorEtaL1Jet[i].Fill(tau.eta())
                                numeratorEtaL1[i].Fill(tau.eta())
                            # fill resolution plots
                            resEtaL1Jet[i].Fill(myL1Jets[0][1].eta()-tau.eta())
                            resPhiL1Jet[i].Fill(deltaPhiWithSign(myL1Jets[0][1].phi(),tau.phi()))
                            resRL1Jet[i].Fill(myL1Jets[0][0])
                            resPtL1Jet[i].Fill(myL1Jets[0][1].pt()-tau.pt())
                            resRelptL1Jet[i].Fill((myL1Jets[0][1].pt()-tau.pt())/tau.pt())
                            resEtaL1[i].Fill(myL1Jets[0][1].eta()-tau.eta())
                            resPhiL1[i].Fill(deltaPhiWithSign(myL1Jets[0][1].phi(),tau.phi()))
                            resRL1[i].Fill(myL1Jets[0][0])
                            resPtL1[i].Fill(myL1Jets[0][1].pt()-tau.pt())
                            resRelptL1[i].Fill((myL1Jets[0][1].pt()-tau.pt())/tau.pt())
                    foundL1Jet = True
                    foundL1 = True

        # Filling L2 condition
        if len(myL2Taus) >0:
            myL2Taus.sort()
            if myL2Taus[0][0] < matchingConeHLT:
                for i in range(len(etaBinList)):
                    if doEtaBin[i] == True:
                        numeratorL2[i].Fill(tau.pt())
                        NMatchedL2[i] += 1
                        if tau.pt() > offlinePtCut:
                            numeratorEtaL2[i].Fill(tau.eta())
                        # fill resolution plots
                        resEtaL2[i].Fill(myL2Taus[0][1].eta()-tau.eta())
                        resPhiL2[i].Fill(deltaPhiWithSign(myL2Taus[0][1].phi(),tau.phi()))
                        resRL2[i].Fill(myL2Taus[0][0])
                        resPtL2[i].Fill(myL2Taus[0][1].pt()-tau.pt())
                        resRelptL2[i].Fill((myL2Taus[0][1].pt()-tau.pt())/tau.pt())
                foundL2 = True
                 
        if len(myL2p5Taus) >0:
            myL2p5Taus.sort()
            if myL2p5Taus[0][0] < matchingConeHLT:
                for i in range(len(etaBinList)):
                    if doEtaBin[i] == True:
                        numeratorL2p5[i].Fill(tau.pt())
                        NMatchedL2p5[i] += 1
                        if tau.pt() > offlinePtCut:
                            numeratorEtaL2p5[i].Fill(tau.eta())
                        # fill resolution plots
                        resEtaL2p5[i].Fill(myL2p5Taus[0][1].eta()-tau.eta())
                        resPhiL2p5[i].Fill(deltaPhiWithSign(myL2p5Taus[0][1].phi(),tau.phi()))
                        resRL2p5[i].Fill(myL2p5Taus[0][0])
                        resPtL2p5[i].Fill(myL2p5Taus[0][1].pt()-tau.pt())
                        resRelptL2p5[i].Fill((myL2p5Taus[0][1].pt()-tau.pt())/tau.pt())
                foundL2p5 = True
                  
        if len(myL3Taus) >0:
            myL3Taus.sort()
            if myL3Taus[0][0] < matchingConeHLT:
                if myL3Taus[0][1].leadPFChargedHadrCand().isNonnull():
                    if ( (nProngsCut == 0) | (myL3Taus[0][1].signalPFChargedHadrCands().size() < nProngsCut) ):
                        if myL3Taus[0][1].leadPFChargedHadrCand().trackRef().isNonnull():
                            # create histogram to check/mimic impact on L3 dZ cut
                            dZ = abs(tau.leadPFChargedHadrCand().trackRef().dz(offlinevertex) - myL3Taus[0][1].leadPFChargedHadrCand().trackRef().dz(offlinevertex))
                            deltaZTauTau.Fill(dZ)
                            if dZ < dZCut:
                                # create histogram to check/mimic impact of matching between L3 and L1 objects at HLT
                                dRl1l3 = matchL3toL1(myL3Taus[0], myL1Taus, myL1Jets)
                                deltaRL1L3.Fill(dRl1l3)
                                #if dRl1l3 < 0.5: # matching cut of 0.5 is hard-coded in HLT filter module
                                foundL3 = True
                                for i in range(len(etaBinList)):
                                    if doEtaBin[i] == True:
                                        numeratorL3[i].Fill(tau.pt())
                                        NMatchedL3[i] += 1
                                        if tau.pt() > offlinePtCut:
                                            numeratorEtaL3[i].Fill(tau.eta())
                                        # fill resolution plots
                                        resEtaL3[i].Fill(myL3Taus[0][1].eta()-tau.eta())
                                        resPhiL3[i].Fill(deltaPhiWithSign(myL3Taus[0][1].phi(),tau.phi()))
                                        resRL3[i].Fill(myL3Taus[0][0])
                                        resPtL3[i].Fill(myL3Taus[0][1].pt()-tau.pt())
                                        resRelptL3[i].Fill((myL3Taus[0][1].pt()-tau.pt())/tau.pt())    
                                    #else:
                                    #    if (foundL1 & foundL2 & foundL2p5):
                                    #        print "*** L1L3 matching failed, min(dR)=", dRl1l3
        
        # save accumulated requirements
        for i in range(len(etaBinList)):
            if doEtaBin[i] == True:
                if foundL1 and foundL2 :
                    numeratorL1L2[i].Fill(tau.pt())
                    if tau.pt() > offlinePtCut:
                        numeratorEtaL1L2[i].Fill(tau.eta())
                    if foundL2p5:
                        numeratorL1L2L2p5[i].Fill(tau.pt())
                        if tau.pt() > offlinePtCut:
                            numeratorEtaL1L2L2p5[i].Fill(tau.eta())
                        if foundL3:
                            numeratorL1_HLT[i].Fill(tau.pt())
                            if tau.pt() > offlinePtCut:
                                numeratorEtaL1_HLT[i].Fill(tau.eta())
                if foundL2 and foundL2p5:
                    numeratorL2L2p5[i].Fill(tau.pt())
                    if tau.pt() > offlinePtCut:
                        numeratorEtaL2L2p5[i].Fill(tau.eta())

    for i in range(len(etaBinList)):
        numeratorL1Tau[i].Sumw2()
        numeratorL1Jet[i].Sumw2()
        numeratorL1[i].Sumw2()
        numeratorL2[i].Sumw2()
        numeratorL2p5[i].Sumw2()
        numeratorL3[i].Sumw2()
        numeratorL1L2[i].Sumw2()
        numeratorL1L2L2p5[i].Sumw2()
        numeratorL2L2p5[i].Sumw2()
        numeratorL1_HLT[i].Sumw2()
        denominator[i].Sumw2()
        denominatorEta[i].Sumw2()
        numeratorEtaL1Tau[i].Sumw2()
        numeratorEtaL1Jet[i].Sumw2()
        numeratorEtaL1[i].Sumw2()
        numeratorEtaL2[i].Sumw2()
        numeratorEtaL2p5[i].Sumw2()
        numeratorEtaL3[i].Sumw2()
        numeratorEtaL1L2[i].Sumw2()
        numeratorEtaL1L2L2p5[i].Sumw2()
        numeratorEtaL2L2p5[i].Sumw2()
        numeratorEtaL1_HLT[i].Sumw2()
    
    #eventCount = NEvt
    
    print "Events: ", NEvt, ", with Muon: ", NEvtMuon, ", with good MT: ", NEvtMuonMT, ", with tau: ", NEvtMuonMTTau
    for i in range(len(etaBinList)):
        print "****** Eta etaBin '", etaBinList[i][2], "':"
        print "       Matched Taus:   L1: ", NMatchedL1[i], ", L2: ", NMatchedL2[i], ", L2.5: ", NMatchedL2p5[i], ", L3: ", NMatchedL3[i]

    return  denominator, numeratorL1Tau, numeratorL1Jet, numeratorL1, numeratorL2, numeratorL2p5, numeratorL3, numeratorL1L2, numeratorL1L2L2p5, numeratorL2L2p5, numeratorL1_HLT, \
            denominatorEta, numeratorEtaL1Tau, numeratorEtaL1Jet, numeratorEtaL1, numeratorEtaL2, numeratorEtaL2p5, numeratorEtaL3, numeratorEtaL1L2, numeratorEtaL1L2L2p5, numeratorEtaL2L2p5, numeratorEtaL1_HLT, \
            resEtaL1Tau, resPhiL1Tau, resRL1Tau, resPtL1Tau, resRelptL1Tau, resEtaL1Jet, resPhiL1Jet, resRL1Jet, resPtL1Jet, resRelptL1Jet, resEtaL1, resPhiL1, resRL1, resPtL1, resRelptL1, \
             resEtaL2, resPhiL2, resRL2, resPtL2, resRelptL2, resEtaL2p5, resPhiL2p5, \
            resRL2p5, resPtL2p5, resRelptL2p5, resEtaL3, resPhiL3, resRL3, resPtL3, resRelptL3, \
            deltaZTauTau, mTH, invM, invMSel, nTaus, deltaRL1L3, tauPt, tauEta

    

def executeCode(cfgFileName):
    cfgFile = open(cfgFileName, 'r')
    cfg = imp.load_source('configuration', cfgFileName, cfgFile)
    cfgFile.close()
    
    print "++++ Process dataset ", cfg.dataset
    
    # settings
    invertMtCut = False
    if invertMtCut: print "Warning: mT cut is inversed"
    
    # parse info for file name
    offlProngsLabel = ""
    if cfg.offlProngs == 0: offlProngsLabel = ""
    else: offlProngsLabel = "_" + str(cfg.offlProngs) + "OfflineProngs"
    if cfg.invMCut == 0: invMLabel = ""
    else: invMLabel = "_maxInvM" + str(cfg.invMCut)
    if cfg.nProngs == 0: prongLabel = ""
    else: prongLabel = "_" + str(cfg.nProngs) + "Prongs"
    mtLabel = ""
    if invertMtCut: mtLabel = "Inversed"
    offlineLabel = cfg.offlineTauLabel.split("XX")[-1]
    ptThresholds = "ptThr"
    if ((cfg.l1tauPt != 0) | (cfg.l1jetPt != 0)): ptThresholds += ("-" + str(cfg.l1tauPt) + "-" + str(cfg.l1jetPt))
    ptThresholds += "-" + str(cfg.l2Pt) + "-" + str(cfg.l3Pt)
    outputFileName = "/user/kargoll/results/TurnOns/forPhdThesis/Eta2p5/" + cfg.path + "/turnOn_" + cfg.dataset + "_" + offlineLabel + "_L3" + cfg.l3Label[-10:] + "_" + ptThresholds + "_dZ" + str(cfg.dZ) + prongLabel + "_MT" + str(cfg.MT) + mtLabel + offlProngsLabel + invMLabel + "_smB.root"



    myhistos = histograms(cfg.input, cfg.offlineTauLabel, cfg.l1Label, cfg.l2Label, cfg.l2p5Label, cfg.l3Label, cfg.l1tauPt, cfg.l1jetPt, cfg.l2Pt, cfg.l3Pt, cfg.MT, invertMtCut, cfg.nProngs, cfg.dZ, cfg.offlProngs, cfg.invMCut, cfg.offlinePt, cfg.etaBins)
    newfile = ROOT.TFile(outputFileName, "RECREATE")
    nHistos = len(myhistos)
    for i in range(nHistos - 8):
        for j in range(len(cfg.etaBins)):
            myhistos[i][j].Write()
    for i in range(nHistos - 8, nHistos):
        myhistos[i].Write()
    newfile.Close()
    
    print nHistos, " histograms have been saved to ", outputFileName



# running the macro

# just to avoid opening windows
print "Let's go!"
ROOT.gROOT.SetBatch()

setTDRStyle(1)
frame = ROOT.TH1F("frame","",len(xbin)-1,xbins)
frame.SetMinimum(0.01)
frame.SetMaximum(1.01)

# MSSM Higgs
#executeCode("config_DoubleTauProng1_2012A.py")
#executeCode("config_DoubleTauProng1_2012B.py")
#executeCode("config_DoubleTauProng1_2012Cv3.py")
#executeCode("config_DoubleTauProng1_2012Cv4.py")
#executeCode("config_DoubleTauProng1_2012Dpart1.py")
#executeCode("config_DoubleTauProng1_2012Dpart2.py")
# ## SM Higgs
executeCode("config_DoubleTauJet_2012A.py")
executeCode("config_DoubleTauJet_2012B.py")
executeCode("config_DoubleTauJet_2012Cv3.py")
executeCode("config_DoubleTauJet_2012Cv4.py")
executeCode("config_DoubleTauJet_2012Dpart1.py")
executeCode("config_DoubleTauJet_2012Dpart2.py")
