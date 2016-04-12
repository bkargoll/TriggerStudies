### input files

dataset = "Run2012A_rerunH2TauHLTPaths"


## Run2012C first part: 24Aug2012 rereco
protocol = "dcap://grid-dcap-extern.physik.rwth-aachen.de"
#protocol = "srm://grid-srm.physik.rwth-aachen.de:8443/srm/managerv2?SFN="
folder = "/pnfs/physik.rwth-aachen.de/cms/store/user/bkargoll/TriggerEfficiencies/forHCP/CorrectHLTMenus/SingleMuDataset/MuTauSkim/RerunH2TauHLTpaths/Run2012A13Jul2012Skimv1/"
files = ["rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_16_1_AnB.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_13_1_HQ5.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_10_1_rdI.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_6_2_R8C.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_11_1_beP.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_8_1_TJC.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_15_1_Eau.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_3_1_Tef.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_4_1_eOc.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_17_1_oOW.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_7_1_BXc.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_18_1_L2C.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_2_1_tdi.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_12_1_5YZ.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_9_1_DZo.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_14_1_xwl.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_5_1_dub.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_1_1_7sH.root",
        "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012A_19_1_qWA.root"]

input = []
for file in files:
    input.append(protocol+folder+file)