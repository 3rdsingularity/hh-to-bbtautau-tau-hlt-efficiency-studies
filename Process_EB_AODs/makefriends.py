#!/usr/bin/env python
import sys,re, array
import ROOT

weights = {}
events = {}
#If you use a new EB run, you need to change this file! They're all located in
# the folder 
with open('path/to/your/AOD/weights/file.xml') as fp:
    for line in fp:
        if "<weight " in line :
            sid = line.split(" ")[1]
            svalue = line.split(" ")[2]
            idd =  re.findall("\d+", sid)
            value = re.findall("[-+]?\d+[\.]?\d*[eE]?[-+]?\d*", svalue )
            print(idd[0], svalue, value[0])
            weights[idd[0]] =  value[0]

        if "<e " in line :
            sid = line.split(" ")[1]
            svalue = line.split(" ")[2]
            iv =  int(re.findall("\-?\d+", sid)[0])
            if(iv & 0x80000000):
                ev = -0x100000000 + iv
            else :
                ev = iv
            value =  re.findall("\d+", svalue)[0]
            events[ev] =  float(weights[value])
            if "-1680982068" in line :
                print(line, value, ev)

print("Created events of length ", len(events))
fileName = 'path/to/your/NTuples/file.root'
fTrig=ROOT.TFile(fileName)
tTrig=fTrig.Get("analysis")
tTrig.SetBranchStatus("*",0)

tTrig.SetBranchStatus("EventNumber",1)

fOut =ROOT.TFile(fileName[:-5]+".EBweights.root", "UPDATE")
fOut.cd()
tOut = ROOT.TTree("trig","trig")
#tOut = tTrig.CloneTree()

EBweight = array.array("f",(0 for i in range(0,1)))
tOut.Branch("EBweight",EBweight ,"EBweight/F")


for entry in range( tTrig.GetEntries() ):
    if entry%10000 == 1 :
        print(entry , " out of ",  tTrig.GetEntries())
    tTrig.GetEntry( entry )
    #if tTrig.eventNumber not in events.keys() :
    #    EBweight[0] = 0 
    #    print "Can not find event ", tTrig.eventNumber
    #else :
    iv = tTrig.EventNumber
    if(iv & 0x80000000):
        iv = -0x100000000 + iv
    #print iv
    EBweight[0] = events[iv] 
    tOut.Fill()

print("Write out EB ntuple ", fOut.GetName() , " with ", tOut.GetEntries(), " events")
fOut.Write()
fOut.Close()
exit(0)

