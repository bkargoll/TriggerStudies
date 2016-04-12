### input files

dataset = "Run2012Dpart2_menu2012Dpart1_rerunH2TauHLTPaths"


## Run2012C first part: 24Aug2012 rereco
protocol = "dcap://grid-dcap-extern.physik.rwth-aachen.de"
folder = "/pnfs/physik.rwth-aachen.de/cms/store/user/bkargoll/TriggerEfficiencies/forMoriond2013/SingleMuDataset/MuTauSkim/RerunH2TauHLTpaths/Run2012Dpart2/MenuOf2012Dpart1/"
files = [   "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_12_1_SsW.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_2_1_7zw.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_11_1_skX.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_27_1_Brh.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_14_1_kTv.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_4_1_QIu.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_24_1_hfe.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_5_1_hrM.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_7_1_rFm.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_18_1_ALV.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_26_1_b3y.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_1_1_3Or.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_8_1_Pdr.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_15_1_BSe.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_20_1_pqb.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_3_1_DsC.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_21_1_ZJQ.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_17_1_ic7.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_6_1_KjC.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_10_1_iPa.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_23_1_xk7.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_16_1_3BS.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_22_1_72L.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_19_1_UPU.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_13_1_Aaj.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_9_1_93A.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_25_1_n6z.root"]

input = []
for file in files:
    input.append(protocol+folder+file)






































