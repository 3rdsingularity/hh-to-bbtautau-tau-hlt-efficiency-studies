# bbtautautriggeranalysis

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

### Datasets
Currently running R22 Sample: mc20_13TeV.600023.PhH7EG_PDF4LHC15_HHbbtautauHadHad_cHHH01d0.recon.AOD.e7954_e7400_s3126_d1729_r13201. 

Sample AOD file: `/afs/cern.ch/work/j/jguhit/public/AOD.27382945._000067.pool.root.1`

Note: You may have to edit the file directory in the `../source/MyAnalysis/share/ATestRunLocal_jobOptions.py` to get it running 
