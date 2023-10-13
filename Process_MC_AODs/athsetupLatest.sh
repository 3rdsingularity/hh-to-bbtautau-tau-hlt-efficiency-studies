export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'

setupATLAS
lsetup -a testing asetup
# lsetup "asetup Athena,here,latest,master"
asetup Athena 22.0.78
# asetup Athena,22.0.0

mkdir build; cd build

cmake ../source/
make
source x86_64-*/setup.sh
