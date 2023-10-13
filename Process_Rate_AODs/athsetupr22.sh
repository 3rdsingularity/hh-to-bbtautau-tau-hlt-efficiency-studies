setupATLAS
mkdir build
cd build/
#asetup AthAnalysis,22.2.51
asetup Athena 22.0.101
#asetup Athena,22.0.56
#lsetup -a testing asetup
#lsetup "asetup AnalysisBase,here,latest,master"
cmake ../source/
make
source x86_64-*/setup.sh
lsetup panda
