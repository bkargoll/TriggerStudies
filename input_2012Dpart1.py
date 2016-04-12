### input files

dataset = "Run2012Dpart1_rerunH2TauHLTPaths"


## Run2012C first part: 24Aug2012 rereco
protocol = "dcap://grid-dcap-extern.physik.rwth-aachen.de"
folder = "/pnfs/physik.rwth-aachen.de/cms/store/user/bkargoll/TriggerEfficiencies/forMoriond2013/SingleMuDataset/MuTauSkim/RerunH2TauHLTpaths/Run2012Dpart1/"
files = [   "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_25_1_vCY.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_33_1_fCx.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_15_1_nvA.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_36_1_Tvb.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_30_1_GLi.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_24_1_Hbg.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_27_1_zhv.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_14_1_mgk.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_22_1_1uA.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_5_1_JaL.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_21_1_IdU.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_13_1_ZRf.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_20_1_xEx.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_23_1_d6s.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_6_1_Rf3.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_2_1_WyA.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_31_1_zuP.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_35_1_Gf1.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_12_1_rd5.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_7_1_hyq.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_8_1_wEC.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_10_1_NWz.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_17_1_06p.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_29_1_HAg.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_11_1_xL0.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_19_1_oSD.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_34_1_dwR.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_26_1_3u7.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_9_1_8Gu.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_18_1_AeA.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_16_1_gku.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_1_1_lae.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_4_1_sFV.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_3_1_Xvb.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_32_1_Aw7.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_28_1_wMF.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Dpart1_37_1_SyW.root" ]
              

input = []
for file in files:
    input.append(protocol+folder+file)



