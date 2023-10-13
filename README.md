# HLT_bbtautau_trigger_emulation

## Description
This repository is created for the trigger optimization studies of the $hh \rightarrow \bar{b} b \tau_{had}^+ \tau_{had}^-$ analysis. For optimizing a trigger chain, it is important to look at its efficiency and the rates. This repository can be used to emulate various trigger chain configurations and determine the corresponding efficiency and rates.

As of now, all the important HLT parameters of the di tau trigger - L1Topo and 4J12, i.e 

HLT_tau35_mediumRNN_tracktwoMVA_tau25_mediumRNN_tracktwoMVA_03dRAB30_L1DRTAU20ITAU12I-J25
and 
HLT_tau35_mediumRNN_tracktwoMVA_tau25_mediumRNN_tracktwoMVA_03dRAB_L1TAU20IM_-2TAU12IM_4J12p0ETA25

can be emulated without any issues. 

## Recommended Samples

 For efficiency emulation, the Monte Carlo sample of the signal sammple is used. For rates emulation, an [Enhanced Bias Samples](https://twiki.cern.ch/twiki/bin/view/Atlas/EnhancedBiasData) and their weights are required.  

 - For efficiency emulation of any trigger chain in the $hh \rightarrow \bar{b} b \tau_{had}^+ \tau_{had}^-$ analysis, the following sample was used at the time of creating this repository
```mc23_13p6TeV.601477.PhPy8EG_HHbbttHadHad_cHHH01d0.recon.AOD.e8514_s4111_r14668/ ```

- For the di tau trigger rate emulation, the following Enhanced Bias sample was used at the time of creating this repository ([ATR-27517](https://its.cern.ch/jira/browse/ATR-27517))
. 
```data22_13p6TeV:data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14669_r14670_tid33426406_00```

    For which the weights are at
 ```/afs/cern.ch/work/a/aporeba/public TrigCostRootAnalysis/EnhancedBiasWeights_440499.xml ``` 

(It is important to note that the chosen sample has a trigger chain in the trigger menu with a chain looser than the loosest chain being emulated.)

## Process the AODs and derive NTuples

Since AODs are difficult to handle, they are processed to simple NTuples using the scripts in 
```hlt_bbtautau_trigger_emulation/Process_EB_AODs``` and ```hlt_bbtautau_trigger_emulation/Process_MC_AODs```. These are AOD processers inspired from [Jem's tau trigger analysis script](https://gitlab.cern.ch/jguhit/bbtautautriggeranalysis/-/tree/HLT_studies)
In theory, the same script should be able to process both signal and EB samples. But since I encountered some issues with using the script for MC NTupler to process EB AODs, two separate scripts are present temporarily to process MC and ED AODs.


## Emulating the Rate
Use the ```hlt_bbtautau_trigger_emulation/di_tau_trigger/Rates_analysis``` and ```hlt_bbtautau_trigger_emulation/b+tau_trigger/Rates_analysis``` for emulating various triggers and determining its rates. The rates are calulated using the information provided in the [twiki page](https://studip-ecampus.uni-goettingen.de/dispatch.php/course/details?sem_id=ca1ca2a43d94d8262654e401f8c61553&again=yes) written by Heather Russell.  


## Project status
