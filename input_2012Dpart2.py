### input files

dataset = "Run2012Dpart2_rerunH2TauHLTPaths"


## Run2012C first part: 24Aug2012 rereco
protocol = "dcap://grid-dcap-extern.physik.rwth-aachen.de"
folder = "/pnfs/physik.rwth-aachen.de/cms/store/user/bkargoll/TriggerEfficiencies/forMoriond2013/SingleMuDataset/MuTauSkim/RerunH2TauHLTpaths/Run2012Dpart2/"
files = [   "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_12_1_4cg.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_11_1_Pp0.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_2_1_5ys.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_1_1_xj2.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_5_1_UKV.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_14_1_z1h.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_7_1_ow4.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_18_1_TCb.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_3_1_28L.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_24_1_H6v.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_23_1_6IM.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_27_1_Scy.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_16_1_1Ie.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_8_1_tdc.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_22_1_m09.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_26_1_lB5.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_15_1_KPH.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_4_1_9xE.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_17_1_Fag.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_20_1_4la.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_10_1_AJs.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_6_1_36F.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_19_1_zeA.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_21_1_1Be.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_9_1_yTR.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_25_1_Aoa.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart2_13_1_xbG.root"  ]
              

input = []
for file in files:
    input.append(protocol+folder+file)






































