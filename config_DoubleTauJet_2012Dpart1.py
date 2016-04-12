### config file to be read by turnOnTau.py

# general parameters
from input_2012Dpart1 import *
path = "DoubleTauJet"

offlineTauLabel = "offlineSelectedTausXXMisomvaMelecrej" 

# tau efficiency related
l1Label = "hltL1extraParticles"
l2Label = "hltL2TauJets"
l2JetLabel = "hltCaloJetL1FastJetCorrected"
l2p5Label = "hltL2TauJetsIso"
l3Label = "hltSelectedPFTausTrackPt1MediumIsolationProng4"
l1tauPt = 44
l1jetPt = 64
l2Pt = 30
l3Pt = 30
offlinePt = 45
MT = 40
nProngs = 0 # 0 = no additional prongs cut 
dZ = 0.2
offlProngs = 0 # 0 = all, 1 =1prongs, 3=3prongs
invMCut = 0 # 0 = no cut on invM

# specify various eta regions in the format [lower |eta| border, upper |eta| border, string as name]
etaBins = [ [0.0, 1.4, "Central"],
            [1.4, 2.1, "Forward"],
            [0.0, 2.1, "Total"]
            ]

# jet efficiency related
jetHltPt = 30
jetMT = 60
offlineJetPt = 50

jetEtaBins = [ [0.0, 1.4, "Central"],
            [1.4, 2.1, "Forward"],
            [2.1, 3.0, "VeryForward"],
            [0.0, 2.1, "CentralForward"],
            [0.0, 3.0, "Total"]
            ]