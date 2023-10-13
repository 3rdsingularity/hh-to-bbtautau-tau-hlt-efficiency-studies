# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/source;/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "Debug;Main;Unspecified")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.26.4/Linux-x86_64/share/cmake-3.26/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "UserAnalysis built using CMake")
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE "ON")
set(CPACK_GENERATOR "RPM")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_COMMANDS "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/CMakeFiles/cpack_install.sh")
set(CPACK_INSTALL_PREFIX "usr/UserAnalysis/0.0.0/InstallArea/x86_64-centos7-gcc11-opt")
set(CPACK_INSTALL_SCRIPT "/cvmfs/atlas.cern.ch/repo/sw/software/24.0/Athena/24.0.8/InstallArea/x86_64-centos7-gcc11-opt/cmake/modules/scripts/cpack_install.cmake")
set(CPACK_MODULE_PATH "/cvmfs/atlas.cern.ch/repo/sw/software/24.0/Athena/24.0.8/InstallArea/x86_64-centos7-gcc11-opt/cmake/modules;/cvmfs/atlas.cern.ch/repo/sw/software/24.0/AthenaExternals/24.0.8/InstallArea/x86_64-centos7-gcc11-opt/cmake/modules;/cvmfs/atlas.cern.ch/repo/sw/software/24.0/AthenaExternals/24.0.8/InstallArea/x86_64-centos7-gcc11-opt/lib64/cmake/VecCore")
set(CPACK_NSIS_DISPLAY_NAME "UserAnalysis/0.0.0/InstallArea/x86_64-centos7-gcc11-opt")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "UserAnalysis/0.0.0/InstallArea/x86_64-centos7-gcc11-opt")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "/cvmfs/sft.cern.ch/lcg/releases/binutils/2.37-355ed/x86_64-centos7/bin/objcopy")
set(CPACK_OBJDUMP_EXECUTABLE "/cvmfs/sft.cern.ch/lcg/releases/binutils/2.37-355ed/x86_64-centos7/bin/objdump")
set(CPACK_OUTPUT_CONFIG_FILE "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "atlas-sw-core@cern.ch")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/usr")
set(CPACK_PACKAGE_DESCRIPTION "UserAnalysis - 0.0.0")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/CMakeFiles/README.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "UserAnalysis - 0.0.0")
set(CPACK_PACKAGE_FILE_NAME "UserAnalysis_0.0.0_x86_64-centos7-gcc11-opt")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "UserAnalysis/0.0.0/InstallArea/x86_64-centos7-gcc11-opt")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "UserAnalysis/0.0.0/InstallArea/x86_64-centos7-gcc11-opt")
set(CPACK_PACKAGE_NAME "UserAnalysis")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "ATLAS Collaboration")
set(CPACK_PACKAGE_VERSION "0.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PROJECT_CONFIG_FILE "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/CMakeFiles/CPackOptions.cmake")
set(CPACK_READELF_EXECUTABLE "/cvmfs/sft.cern.ch/lcg/releases/binutils/2.37-355ed/x86_64-centos7/bin/readelf")
set(CPACK_RESOURCE_FILE_LICENSE "/cvmfs/atlas.cern.ch/repo/sw/software/24.0/Athena/24.0.8/InstallArea/x86_64-centos7-gcc11-opt/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/CMakeFiles/README.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.26.4/Linux-x86_64/share/cmake-3.26/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_ARCHITECTURE "noarch")
set(CPACK_RPM_PACKAGE_AUTOREQ " no")
set(CPACK_RPM_PACKAGE_AUTOREQPROV " no")
set(CPACK_RPM_PACKAGE_GROUP "ATLAS Software")
set(CPACK_RPM_PACKAGE_LICENSE "Apache License Version 2.0")
set(CPACK_RPM_PACKAGE_NAME "UserAnalysis_0.0.0_x86_64-centos7-gcc11-opt")
set(CPACK_RPM_PACKAGE_PROVIDES "/bin/sh")
set(CPACK_RPM_PACKAGE_REQUIRES "Athena_24.0.8_x86_64-centos7-gcc11-opt, LCG_102b_ATLAS_21_jsonmcpp_3.10.5_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_freetype_2.10.0_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_Qt5_5.15.2_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_gtest_1.11.0_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_expat_2.2.6_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_XercesC_3.2.3_x86_64_centos7_gcc11_opt, ATLAS_Geant4Data_geant4.10.6.patch03.atlasmt07, LCG_102b_ATLAS_21_Python_3.9.12_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_future_0.17.1_x86_64_centos7_gcc11_opt, tdaq-common-10-00-00_x86_64-centos7-gcc11-opt, LCG_102b_ATLAS_21_tbb_2020_U2_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_cppgsl_3.1.0_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_AIDA_3.2.1_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_HepPDT_2.06.01_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_CppUnit_1.14.0_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_libunwind_1.3.1_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_zlib_1.2.11_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_fmt_7.1.3_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_ROOT_6.26.08_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_Boost_1.78.0_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_rangev3_0.11.0_x86_64_centos7_gcc11_opt, LCG_102b_ATLAS_21_clhep_2.4.5.1_x86_64_centos7_gcc11_opt")
set(CPACK_RPM_PACKAGE_VERSION "0.0.0")
set(CPACK_RPM_SPEC_MORE_DEFINE "
%global __os_install_post %{nil}
%define _unpackaged_files_terminate_build 0
%define _binaries_in_noarch_packages_terminate_build 0
%define _source_payload w2.xzdio
%define _binary_payload w2.xzdio
%undefine __brp_mangle_shebangs")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "RPM")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/CPackSourceConfig.cmake")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
