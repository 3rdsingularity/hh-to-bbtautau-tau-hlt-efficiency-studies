# HLT_bbtautau_trigger_emulation

## Overview
This repository is dedicated to the optimization studies of the $hh \rightarrow \bar{b} b \tau_{had}^+ \tau_{had}^-$ analysis triggers. The primary goal of this repository is to facilitate the emulation of various trigger chain configurations and evaluate their corresponding efficiency and rates. Trigger optimization is essential to ensure that the chosen trigger chains effectively select the desired events while managing data rates.

As of the current version, the repository supports the emulation of crucial High-Level Trigger (HLT) parameters. All the parameters of the di tau trigger :

- HLT_tau35_mediumRNN_tracktwoMVA_tau25_mediumRNN_tracktwoMVA_03dRAB30_L1DRTAU20ITAU12I-J25
- HLT_tau35_mediumRNN_tracktwoMVA_tau25_mediumRNN_tracktwoMVA_03dRAB_L1TAU20IM_-2TAU12IM_4J12p0ETA25

can be accurately emulated without issues.

## Recommended Sample Data

For efficient emulation, the Monte Carlo sample of the signal is recommended. For rate emulation, you will require Enhanced Bias Samples along with their corresponding weights. These are essential to accurately assess the performance of the trigger chains.

- For efficiency emulation of any trigger chain within the $hh \rightarrow \bar{b} b \tau_{had}^+ \tau_{had}^-$ analysis, the following sample was used during the creation of this repository: 
```mc23_13p6TeV.601477.PhPy8EG_HHbbttHadHad_cHHH01d0.recon.AOD.e8514_s4111_r14668/```

- To emulate the rate of the di-tau trigger, the following Enhanced Bias sample was employed at the time of creating this repository, as documented in [ATR-27517](https://its.cern.ch/jira/browse/ATR-27517):

```data22_13p6TeV:data22_13p6TeV.00440499.physics_EnhancedBias.recon.AOD.r14669_r14670_tid33426406_00```

The corresponding weights can be found at:
```/afs/cern.ch/work/a/aporeba/public/TrigCostRootAnalysis/EnhancedBiasWeights_440499.xml```

Please note that the selected sample should include a trigger chain within the trigger menu that is looser than the loosest chain being emulated.


## Processing AODs and Generating NTuples

Given the complexity of AODs, this repository provides scripts for processing AODs into simpler NTuples. Two sets of scripts, located in `hlt_bbtautau_trigger_emulation/Process_EB_AODs` and `hlt_bbtautau_trigger_emulation/Process_MC_AODs`, are available for this purpose. These scripts draw inspiration from [Jem's tau trigger analysis script](https://gitlab.cern.ch/jguhit/bbtautautriggeranalysis/-/tree/HLT_studies). Although the same script theoretically should process both signal and Enhanced Bias (EB) samples, two separate scripts are temporarily provided to process MC and EB AODs, due to some encountered issues.
For the Enhanced Bias AOD, a weights.root file has to be generated for weighs corresponding to each event using the *makefriends.py* in ```hlt_bbtautau_trigger_emulation/Process_EB_AODs/makefriends.py``` (Credits to Heather Russell). You may have to change the path of the weights.xml file and the NTuples.root to get it running. 

## Emulating Trigger Rates

To perform trigger rate emulation and assess the rates of various triggers, use the scripts in `hlt_bbtautau_trigger_emulation/di_tau_trigger/Rates_analysis` and `hlt_bbtautau_trigger_emulation/b+tau_trigger/Rates_analysis`. These scripts leverage information from a [twiki page](https://studip-ecampus.uni-goettingen.de/dispatch.php/course/details?sem_id=ca1ca2a43d94d8262654e401f8c61553&again=yes) authored by Heather Russell.

In this project, you can find all the functions required for trigger emulation conveniently located in the *Trigger_functions.py* file. 

To perform rate and efficiency emulation for various trigger chains, you can use the dedicated scripts named *Emulate_\*_\*.py*. 




## Project Status
The current status of the project is ongoing, with continuous development and refinement of trigger emulation and analysis tools for the $b+\tau$ triggers. Please refer to the repository for the latest updates and developments.
