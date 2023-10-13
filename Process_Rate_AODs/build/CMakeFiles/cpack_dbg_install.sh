#!/usr/bin/bash
#
# Copyright (C) 2002-2022 CERN for the benefit of the ATLAS collaboration
#
# Script used for installing a project for CPack. Hiding any build errors
# from the package generator.
#

# Turn off error reporting:
set +e

# Set the output directory:
OUTDIR="${DESTDIR}/usr/UserAnalysis/0.0.0/InstallArea/x86_64-centos7-gcc11-opt"

# Create the bin and lib directories:
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.26.4/Linux-x86_64/bin/cmake" -E make_directory "${OUTDIR}/bin" \
    2>&1 | tee "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/cmake_cpack_dbg_install.log"
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.26.4/Linux-x86_64/bin/cmake" -E make_directory "${OUTDIR}/lib" \
    2>&1 | tee -a "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/cmake_cpack_dbg_install.log"

# Copy the debug files into the place CPack expects to find them:
RUNTIME_OUTPUT_DIR="/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/x86_64-centos7-gcc11-opt/bin"
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.26.4/Linux-x86_64/bin/cmake" -E copy ${RUNTIME_OUTPUT_DIR}/*.dbg \
    "${OUTDIR}/bin/" 2>&1 | \
    tee -a "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/cmake_cpack_dbg_install.log"
LIBRARY_OUTPUT_DIR="/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/x86_64-centos7-gcc11-opt/lib"
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.26.4/Linux-x86_64/bin/cmake" -E copy ${LIBRARY_OUTPUT_DIR}/*.dbg \
    "${OUTDIR}/lib/" 2>&1 | \
    tee -a "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/cmake_cpack_dbg_install.log"

# Exit gracefully:
exit 0
