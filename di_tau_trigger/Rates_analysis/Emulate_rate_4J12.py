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

branches_to_select = ['HLT_4J12_idperf','TrigMatched_rnn_HLTetafl_perf','TrigMatched_prong_HLTetafl_perf','TrigMatched_Taus_HLTetafl_perf']


print('Loading the root file...')
# Your Enhnace bias NTUPLEs
# rdf1 = ROOT.RDataFrame('analysis', "path/to/your/NTUPLES")
rdf1 = ROOT.RDataFrame('analysis', "/afs/cern.ch/user/a/asudhaka/eos_space/tau_trigger/user.asudhaka.RATES_ANALYSIS_rnnStudies_corrected.root_ANALYSIS/user.asudhaka.34132919.ANALYSIS._000001.root")

# THe weights of your Enhanced Bias NTUPLEs
rdf2 = ROOT.RDataFrame('trig', "/afs/cern.ch/user/a/asudhaka/eos_space/tau_trigger/user.asudhaka.RATES_ANALYSIS_rnnStudies_corrected.root_ANALYSIS/user.asudhaka.34132919.ANALYSIS._000001.EBweights.root")
# rdf2 = ROOT.RDataFrame('trig', "path/to/your/weights")

# Convert the RDataFrame to a pandas DataFrame (Memory intensive !!! careful with the root file size)
analysis_tree = rdf1.AsNumpy(columns=branches_to_select)
weight_tree = rdf2.AsNumpy(columns=['EBweight'])
df1 = pd.DataFrame(analysis_tree)
df2 = pd.DataFrame(weight_tree)

# Make a dataframe with all the variables required for analysis
df = pd.concat([df1, df2], axis=1)

print('Loading dataframe successful! Now emulating triggers...')
# Current 4J12 Trigger Working Points
l0_current = 1-0.90
l1_current = 1-0.99
lm_current = 1-0.94
m0_current = 1-0.65
m1_current = 1-0.97
mm_current = 1-0.895

# Weighted number of events that pass 30(20) idperf 4J12 chain 
HLT_4J12_idperf_weights = 0  
for event in range(df.shape[0]):
    if df['HLT_4J12_idperf'][event]:
        HLT_4J12_idperf_weights+=df['EBweight'][event]

# Rate and the error of the idperf 4J12 chain from reprocessing page which is
# @ https://atlas-trig-cost.web.cern.ch/?dir=RateProcessings-2023&type=r2023-05-10&tag=rate-prediction-ATR-27517-noPS&run=440499&range=All&level=HLT&summary=Rate_ChainHLT
# All the rates are determined with a luminosity of 1.00e+34 cm^2s^-1

Rate_HLT_4J12_idperf = 1377.4168 # Hz
Err_Rate_HLT_4J12_idperf = 12.6041 # Hz

#########################################################################################################################################################
# Rate emulation formula #
#########################################################################################################################################################

# Rate_emu = N_event_passed_emu * Rate_std_chain / N_event_passed_std

##############################################################
####### Customize your emulation parameter range here ########
##############################################################

m1_thresholds = np.linspace(m1_current-0.02,m1_current+0.02,5)
mm_thresholds = np.linspace(mm_current-0.02,mm_current+0.02,5)
pt1 = np.linspace(20, 22, 5)
pt0 = np.linspace(30, 40, 11)

##############################################################

#########################################################################################################################################################
# EMULATION #
#########################################################################################################################################################

# Total trigger combinations to be emulated
t_combo = len(mm_thresholds) * len(m1_thresholds) * len(pt0) * len(pt1)

count = 0
rate = 0

with open('4J12_Rates_Emulation.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['pt0','pt1','wp-mRNN-0p','wp-mRNN-1p','wp-mRNN-mp','Events_passed','Rate','Err_Rate'])
    for m1 in m1_thresholds:
        for mm in mm_thresholds:
            for pti in pt0:
                for ptj in pt1:
                    if pti > ptj:
                        hlt_events = 0
                        hlt_events_wt = 0
                        hlt_event_wt_err = 0
                        print(f'{count} combination(s) completed of {t_combo} |   Previous rate: {rate} Hz   |   Current combination =>  m1:{np.round(m1, 4)},mm:{np.round(mm, 4)},pt1:{pti}, pt2:{ptj}',end='', flush=True)
                        for event in range(df.shape[0]):
                            if df['HLT_4J12_idperf'][event]:
                                hlt_flag = 0
                                for tau_i in range(len(df['TrigMatched_Taus_HLTetafl_perf'][event])):
                                    if HLT_4J12_cond(df,event, tau_i, pt0=pti, pt1=ptj, m1=m1, mm=mm) and hlt_flag == 0:
                                        hlt_flag = 1
                                        hlt_events_wt += df['EBweight'][event]
                                        hlt_event_wt_err += df['EBweight'][event]**2
                        rate = hlt_events_wt * (Rate_HLT_4J12_idperf/HLT_4J12_idperf_weights)
                        
                        rate_err = (((hlt_events_wt/HLT_4J12_idperf_weights)*Err_Rate_HLT_4J12_idperf)**2 + (np.sqrt(hlt_event_wt_err) * (Rate_HLT_4J12_idperf/HLT_4J12_idperf_weights))**2)**0.5
                        writer.writerow([pti,ptj, np.round(m0_current, 4), np.round(m1, 4), np.round(mm, 4), hlt_events_wt,rate,rate_err])
                        count+=1
                        print('\r \r', end='', flush=True)

print(f'{count} combination(s) completed of {t_combo} |   Rate: {rate} Hz   |  combination =>  m1:{np.round(m1, 4)},mm:{np.round(mm, 4)},pt1:{pti}, pt2:{ptj}',end='', flush=True)
print('\nEmulation completed Successfully!')