#########################################################################################################################################################
# IMPORTS #
#########################################################################################################################################################

import ROOT
import pandas as pd
import numpy as np
import csv
from Trigger_functions import *

#########################################################################################################################################################
# PREPARING THE DATA #
#########################################################################################################################################################

print('Loading the root file...')

# Your MC NTuples
# rdf = ROOT.RDataFrame('analysis', 'path/to/your/NTuples.root')
rdf = ROOT.RDataFrame('analysis', '/eos/home-a/asudhaka/tau_trigger/mc23_13p6TeV.601477.PhPy8EG_HHbbttHadHad_cHHH01d0.recon.AOD.e8514_e8528_s4111_s4114_r14668/mc23_RNN studies.root')

# Execute the processing steps and get a pandas DataFrame
analysis_tree = rdf.AsNumpy()

# Convert the NumPy array to a pandas DataFrame
df = pd.DataFrame(analysis_tree)

print('Loading dataframe successful! Now emulating triggers...')
# Current L1Topo Trigger Working Points
l0_current = 1-0.90
l1_current = 1-0.99
lm_current = 1-0.94
m0_current = 1-0.65
m1_current = 1-0.97
mm_current = 1-0.895

# Events that pass selection cut
sel_events = []
for event in range(df.shape[0]):
    if selection_cond(df,event):
        sel_events.append(event)
sel_pass = len(sel_events)

#########################################################################################################################################################
# Efficiency emulation formula #
#########################################################################################################################################################

# Eff_emu = N_emu_pass / N_selection_pass

##############################################################
####### Customize your emulation parameter range here ########
##############################################################

m1_thresholds = np.linspace(m1_current-0.02,m1_current+0.02,1)
mm_thresholds = np.linspace(mm_current-0.02,mm_current+0.02,1)
pt1 = np.linspace(20, 22, 1)
pt0 = np.linspace(30, 40, 2)

##############################################################

#########################################################################################################################################################
# EMULATION #
#########################################################################################################################################################

# Total trigger combinations to be emulated
t_combo = len(mm_thresholds) * len(m1_thresholds) * len(pt0) * len(pt1)

count = 0
eff = 0

with open('L1Topo_Efficiency_Emulation.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['pt0', 'pt1', 'wp-mRNN-0p', 'wp-mRNN-1p', 'wp-mRNN-mp', 'Eff', 'Eff_err'])
    for m1 in m1_thresholds:
        for mm in mm_thresholds:
            for pti in pt0:
                for ptj in pt1:
                    if pti > ptj:
                        hlt_events = 0
                        print(f'{count} combination(s) completed of {t_combo} |   Previous eff: {eff}   |   Current combination =>  m1:{np.round(m1, 4)},mm:{np.round(mm, 4)},pt1:{pti}, pt2:{ptj}',end='', flush=True)
                        for event in sel_events:
                            hlt_flag = 0
                            for tau_i in range(len(df['TrigMatched_Taus_HLTptfl'][event])):
                                if HLT_L1Topo_cond(df,event, tau_i, pt0=pti, pt1=ptj, m1=m1, mm=mm) and hlt_flag == 0:
                                    hlt_flag = 1
                                    hlt_events += 1
                        eff = hlt_events/sel_pass
                        eff_err = ((df.shape[0] * (hlt_events / df.shape[0]) * (1 - (hlt_events / df.shape[0])))**0.5) / sel_pass
                        writer.writerow([str(pti), str(ptj), np.round(m0_current, 4), np.round(m1, 4), np.round(mm, 4), np.round(eff, 4), np.round(eff_err, 4)])   
                        count+=1
                        print('\r', end='', flush=True)

print(f'{count} combination(s) completed of {t_combo} |   Efficiency: {eff}   |   Combination =>  m1:{np.round(m1, 4)},mm:{np.round(mm, 4)},pt1:{pti}, pt2:{ptj}',end='', flush=True)
print('\nEmulation completed Successfully!')