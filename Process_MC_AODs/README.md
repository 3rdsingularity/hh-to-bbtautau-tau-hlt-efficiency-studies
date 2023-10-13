# bbtautautriggeranalysis

## Setup 
----
### Clone repository in your directory 
```
git clone --branch HLT_studies ssh://git@gitlab.cern.ch:7999/jguhit/bbtautautriggeranalysis.git

```

### Create directories
```
mkdir build 
```

### Build and compile 
```
source athsetupr22.sh
```
**For future logins, do:** `source athloginr22.sh`

### Run joboptions 
```
cd run/

#For local run, do:
source localrun.sh

#For grid run, do:
source gridrun.sh
```

### Extracting Tau Info
For extracting **passed** tau information, in `source/MyAnalysis/Root/MyxAODAnalysis.cxx`:
```
auto vec = m_trigDecTool->features<xAOD::TauJetContainer>(trigname, TrigDefs::Physics ,tauContainerName);
```
For extracting **passed and failed** tau information, in `source/MyAnalysis/Root/MyxAODAnalysis.cxx`:
```
auto vec = m_trigDecTool->features<xAOD::TauJetContainer>(trigname, TrigDefs::includeFailedDecisions ,tauContainerName);
```

### Datasets
Currently running custom R22 Samples: \
kl1: `valid1.600023.PhH7EG_PDF4LHC15_HHbbtautauHadHad_cHHH01d0.merge.AOD.e7954_e7400_s3775_r13561_r13491_tid28764607_00`\
kl10: `valid1.600024.PhH7EG_PDF4LHC15_HHbbtautauHadHad_cHHH10d0.merge.AOD.e7954_e7400_s3775_r13561_r13491_tid28764613_00`

To download, use rucio:
```
setupATLAS
lsetup rucio
voms-proxy-init -voms atlas
rucio download <name of container>
```

Note: You may have to edit the file directory in the `../source/MyAnalysis/share/ATestRunLocal_jobOptions.py` to get it running 
