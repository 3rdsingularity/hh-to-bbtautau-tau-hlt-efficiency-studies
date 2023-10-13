#!/usr/bin/bash
#
# Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
#
# This script is used during the build to set up a functional runtime
# environment for running scripts/executables.
#

# Transmit errors:
set -e

# Set up the environment:
source /afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/x86_64-centos7-gcc11-opt/setup.sh || exit 1

# Run the command:
exec "$@" || exit 1
