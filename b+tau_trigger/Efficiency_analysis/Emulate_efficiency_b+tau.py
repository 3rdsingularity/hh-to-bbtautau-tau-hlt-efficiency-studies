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

#########################################################################################################################################################
# Efficiency emulation formula #
#########################################################################################################################################################

# Eff_emu = N_emu_pass / N_selection_pass
# In case of b+tau triggers, we are looking at the absolute efficiency so there is no selection cut

##############################################################
####### Customize your emulation parameter range here ########
##############################################################

gn1s = ['gn170','gn177','gn185']
tpts = [35,30,25,20]
tau_IDs = ['medium','tight'] 
bpt0s = [40, 60, 75, 80, 100]
bpt1s = [30, 40, 50, 60, 70]
bpt2s = [20, 25, 30]
bpt3s = [20, 25, 30]

# TO determine the total trigger combinations to be emulated
for gn1 in gn1s:
    for tpt in tpts:
        for tau_ID in tau_IDs:
            for bpt0 in bpt0s:
                for bpt1 in bpt1s:
                    for bpt2 in bpt2s:
                        for bpt3 in bpt3s:                  
                            if bpt0 > bpt1 and bpt1 > bpt2 and bpt2 > bpt3:
                                t_combo+=1

##############################################################

#########################################################################################################################################################
# EMULATION #
#########################################################################################################################################################

count = 0
eff = 0

with open('b+tau_Efficiency_Emulation.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['tau_pt','tau_ID','j0_pt','j1_pt','j2_pt','j3_pt','gn1_wp','Eff','Eff_err'])
    for gn1 in gn1s:
        for tpt in tpts:
            for tau_ID in tau_IDs:
                for bpt0 in bpt0s:
                    for bpt1 in bpt1s:
                        for bpt2 in bpt2s:
                            for bpt3 in bpt3s:                  
                                if bpt0 > bpt1 and bpt1 > bpt2 and bpt2 > bpt3:
                                    hlt_events = 0
                                    print(f'{count} combination(s) completed of {t_count-1} |   Previous eff: {eff}   |  Current combination => tau with {tpt}, {tau_ID} and jets with {bpt0,bpt1,bpt2,bpt3} and {gn1}',end='', flush=True)
                                    for event in range(df.shape[0]):
                                        if pass_selection(event):
                                            if pass_3b1j(event, pt_tau=tpt, cond=tau_ID, pt_j0=bpt0, pt_j1=bpt1, pt_j2=bpt2, pt_j3=bpt3, jvt=0.2, b_WP_tag=gn1):
                                                hlt_events+=1
                                    eff = hlt_events/df.shape[0]
                                    eff_err = ((df.shape[0] * (hlt_events / df.shape[0]) * (1 - (hlt_events / df.shape[0])))**0.5) / df.shape[0]
                                    writer.writerow([str(tpt), tau_ID, str(bpt0), str(bpt1), str(bpt2), str(bpt3), gn1, np.round(eff, 4) ,np.round(eff_err, 4)])   
                                    count+=1
                                    print('\r', end='', flush=True)

print(f'{count} combination(s) completed of {t_combo} |   Efficiency: {eff}   |   Combination =>  m1:{np.round(m1, 4)},mm:{np.round(mm, 4)},pt1:{pti}, pt2:{ptj}',end='', flush=True)
print('\nEmulation completed Successfully!')