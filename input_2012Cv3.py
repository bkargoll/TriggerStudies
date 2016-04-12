### input files

dataset = "Run2012Cv3_rerunH2TauHLTPaths"


## Run2012C first part: 24Aug2012 rereco
protocol = "dcap://grid-dcap-extern.physik.rwth-aachen.de"
folder = "/pnfs/physik.rwth-aachen.de/cms/store/user/bkargoll/TriggerEfficiencies/forHCP/CorrectHLTMenus/SingleMuDataset/MuTauSkim/RerunH2TauHLTpaths/Run2012C24Aug2012Skimv1SmallJobs/"
files = [   "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_24_4_jxo.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_11_1_HHT.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_13_1_Ly0.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_2_1_ku8.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_21_1_ore.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_5_1_zAl.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_4_1_PsN.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_6_1_FoU.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_23_1_S7L.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_14_1_OnP.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_16_1_hFk.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_22_1_Rtk.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_3_1_ZVG.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_12_1_8ZV.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_8_1_aMj.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_17_1_wpL.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_10_1_fcU.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_18_1_GS7.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_20_1_znK.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_19_1_mrd.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_7_1_vKi.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_26_1_UJf.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_1_1_Kda.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_27_1_uzo.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_15_1_zSq.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_9_1_Hu9.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_25_1_dqd.root"]

input = []
for file in files:
    input.append(protocol+folder+file)


folder = "/pnfs/physik.rwth-aachen.de/cms/store/user/bkargoll/TriggerEfficiencies/forHCP/CorrectHLTMenus/SingleMuDataset/MuTauSkim/RerunH2TauHLTpaths/Run2012CPromptSkimv3_menu2012Cv3/"
files = [   "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_7_1_0U4.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_2_1_Sis.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_3_1_xAa.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_5_1_UmT.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_1_1_nff.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_4_1_fcU.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_8_1_1TA.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_12_1_97i.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_10_1_bdU.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_11_1_Fy8.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_9_1_FJu.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_6_1_rb8.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_13_1_G3E.root",
            "rerunH2TauHLTPaths_offlineSelectedMuTau_menu2012Cv3_14_1_TOm.root"]

for file in files:
    input.append(protocol+folder+file)

