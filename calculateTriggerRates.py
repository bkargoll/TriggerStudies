#!/usr/bin/env python

import argparse
from operator import add
import ROOT

LSinSec = 23.3

def rate(nLS, nEvents, scale = 1):
    return scale * nEvents / (nLS * LSinSec)

parser = argparse.ArgumentParser(description='Calculate trigger rates from lumiContext.py output.')
# lumiCalc2.py  lumibyls -n 0.0429 -i <JSON-File> -o LumiPerLS.csv
parser.add_argument('lumiInfo', nargs='?', type=argparse.FileType('r'), help="Input file containing lumi information.")
# lumiContext.py hltbyls --name <HLT_TriggerName> -i <JSON-File> -o <outputFile.csv>
parser.add_argument('triggerInfo', nargs='+', type=argparse.FileType('r'), help="List of input files containing trigger info.")
parser.add_argument('--output', nargs='+', help="Output root file.", default = "triggerRates.root")
args = parser.parse_args()

outfile = ROOT.TFile(args.output, "recreate")

# read lumi information
lumi = {} # dict to map runs to [nLS, Ldelivered, Lrecorded]
args.lumiInfo.next() # skip first line
for line in args.lumiInfo:
    fields = line.split(',')
    run = int(fields[0].split(':')[0])
    delivered = float(fields[-3])
    recorded = float(fields[-2])
    
    if run in lumi.keys():
        lumi[run] = map(add, lumi[run], [1, delivered, recorded])
    else:
        lumi[run] = [1, delivered, recorded]


for inFile in args.triggerInfo:
    print "Analyse", inFile.name
    inFile.next() # skip first line
    
    triggerNames = set()
    # dictionary to map runs to [nLS, l1pass, hltaccept]
    nEvents = {}
    
    for line in inFile:
        fields = line.split(',')
        run = int(fields[0])
        name = fields[2].strip( '("' )
        
        # dirty hack to remove early runs from parking trigger
        if ("eta2p1_v" in name) and run < 194240:
            print "  skipping", name, run
            continue
        
        triggerNames.add(name)
        
        nHLT = int(fields[-1].strip().strip( '")' ))
        nL1 = int(fields[-2])
        if run in nEvents.keys():
            nEvents[run] = map(add, nEvents[run], [1, nL1, nHLT])
        else:
            nEvents[run] = [1, nL1, nHLT]
            
    print "The following trigger paths were combined:"
    for name in triggerNames: print " * ", name
    
    trigName = triggerNames.pop() #used to label graphs
    
    pureRate = ROOT.TGraphErrors(0)
    for run in sorted(nEvents):
        r = rate(nEvents[run][0], nEvents[run][2])
        #print idx, ":", run, r
        pureRate.SetPoint(pureRate.GetN(), run, r)
    
    pureRate.SetName("pureRate_"+trigName)
    pureRate.SetTitle("pureRate_"+trigName)
    pureRate.Write()

    # rate normalized to 5E33/scm2
    normRate = ROOT.TGraphErrors(0)
    instLumi = 5000 # 10^30 /cm^2 s
    for run in sorted(nEvents):
        #print run
        if nEvents[run][0] != lumi[run][0]:
            print 'nLS not matching! Run', run, 'trigger Info:', nEvents[run][0], '; lumi Info:', lumi[run][0]
            continue
            #raise ValueError('Number of LS not identical in trigger and lumi info')
        
        l = lumi[run][1] / (lumi[run][0]*LSinSec) # inst. Lumi in this run
        r = rate(nEvents[run][0], nEvents[run][2], instLumi/l) 
        #print normRate.GetN(), ":", run, l, r
        normRate.SetPoint(normRate.GetN(), run, r)
    
    
    normRate.SetName("normRate_"+trigName)
    normRate.SetTitle("normRate_"+trigName)
    normRate.Write()
