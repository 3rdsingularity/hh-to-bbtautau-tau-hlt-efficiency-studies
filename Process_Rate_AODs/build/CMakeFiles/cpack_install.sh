#!/usr/bin/bash
#
# Copyright (C) 2002-2022 CERN for the benefit of the ATLAS collaboration
#
# Script used for installing a project for CPack. Hiding any build errors
# from the package generator.
#

# Turn off error reporting:
set +e

# Install the project:
DESTDIR="${DESTDIR}/usr"
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.26.4/Linux-x86_64/bin/cmake" --install "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build" 2>&1 | tee "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/cmake_cpack_install.log"

# Remove the .dbg files from being packaged, in case we are in RelWithDebInfo
# build mode:
OUTDIR="${DESTDIR}/UserAnalysis/0.0.0/InstallArea/x86_64-centos7-gcc11-opt"
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.26.4/Linux-x86_64/bin/cmake" -E remove -f ${OUTDIR}/bin/*.dbg \
   2>&1 | tee -a "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/cmake_cpack_install.log"
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.26.4/Linux-x86_64/bin/cmake" -E remove -f ${OUTDIR}/lib/*.dbg \
   2>&1 | tee -a "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/cmake_cpack_install.log"

# Exit gracefully:
exit 0
