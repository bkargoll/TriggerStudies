### input files

dataset = "Run2012Dpart1_menu2012Dpart2_rerunH2TauHLTPaths"


## Run2012C first part: 24Aug2012 rereco
protocol = "dcap://grid-dcap-extern.physik.rwth-aachen.de"
folder = "/pnfs/physik.rwth-aachen.de/cms/store/user/bkargoll/TriggerEfficiencies/forMoriond2013/SingleMuDataset/MuTauSkim/RerunH2TauHLTpaths/Run2012Dpart1/MenuOf2012Dpart2/"
files = [   "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_25_1_F5i.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_33_1_pab.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_30_1_F3X.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_36_1_LLL.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_15_1_UmD.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_22_1_RKW.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_35_1_Det.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_27_1_cDe.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_13_1_vt6.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_5_1_psO.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_21_1_LRd.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_31_1_kM5.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_6_1_0yv.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_23_1_s3i.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_20_1_RYL.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_24_1_e5h.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_10_1_fCD.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_2_1_0O5.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_11_1_DYf.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_14_1_n9K.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_7_1_Nbt.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_29_1_LGF.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_8_1_bO2.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_34_1_sXM.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_17_1_BCS.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_18_1_DKL.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_3_1_KJv.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_19_1_EZT.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_12_1_xAD.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_16_1_LxI.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_9_1_35E.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_1_1_EcX.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_4_1_U8g.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_26_1_vIU.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_32_1_YEu.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_28_1_Ajy.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_37_1_qeF.root"]

input = []
for file in files:
    input.append(protocol+folder+file)



