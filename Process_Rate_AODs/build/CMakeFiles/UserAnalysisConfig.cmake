# Copyright (C) 2002-2022 CERN for the benefit of the ATLAS collaboration
#
# Configuration file for an ATLAS CMake release installation.
# It defines the following variables:
#
#  UserAnalysis_INSTALL_DIR  - Base install directory for the release
#  UserAnalysis_INCLUDE_DIR  - Include directory for the release
#  UserAnalysis_LIBRARY_DIR  - Library directory for the release
#  UserAnalysis_BINARY_DIR   - Runtime directory for the release
#  UserAnalysis_CMAKE_DIR    - Directory holding CMake files
#  UserAnalysis_PYTHON_DIR   - Directory holding python code
#  UserAnalysis_VERSION      - The version number of the release
#  UserAnalysis_TARGET_NAMES - The names of the targets provided by the
#                                      release
#  UserAnalysis_PLATFORM     - The name of the platform of the release
#
# Note however that most of the time you should not be using any of these
# variables, but the imported targets of the project instead. Even more, in most
# cases you will want to use atlas_project(...) to handle the imported targets
# in a "smart way".

# Require CMake 3.11 for aliasing global imported targets.
cmake_minimum_required( VERSION 3.11 )

# Add the CMake provided initialisation code.

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was ProjectConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

####################################################################################

# Set various directory variables.
set( UserAnalysis_INSTALL_DIR "${PACKAGE_PREFIX_DIR}/" )
set( UserAnalysis_INCLUDE_DIR "${PACKAGE_PREFIX_DIR}/include" )
set( UserAnalysis_LIBRARY_DIR "${PACKAGE_PREFIX_DIR}/lib" )
set( UserAnalysis_BINARY_DIR "${PACKAGE_PREFIX_DIR}/bin" )
set( UserAnalysis_CMAKE_DIR "${PACKAGE_PREFIX_DIR}/cmake" )
set( UserAnalysis_PYTHON_DIR "${PACKAGE_PREFIX_DIR}/python" )

# Set the version of the project.
set( UserAnalysis_VERSION "0.0.0" )

# Set the names of the targets that the project exported.
set( UserAnalysis_TARGET_NAMES "MyAnalysisLib;MyAnalysis" )

# Print what project/release was found just now.
include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( UserAnalysis
   REQUIRED_VARS CMAKE_CURRENT_LIST_FILE
   VERSION_VAR UserAnalysis_VERSION )

# The base projects that this project was built on top of:
set( UserAnalysis_BASE_PROJECTS Athena;24.0.8 )

# The platform name used for the build.
set( UserAnalysis_PLATFORM "x86_64-centos7-gcc11-opt" )
set( ATLAS_PLATFORM "x86_64-centos7-gcc11-opt" )

# Include the project-specific pre-include file, if it exists:
include( "${UserAnalysis_CMAKE_DIR}/PreConfig.cmake" OPTIONAL )

# Include the base projects, in the order in which they were given to
# the atlas_project call.
set( _baseProjectsUserAnalysis
   ${UserAnalysis_BASE_PROJECTS} )
while( _baseProjectsUserAnalysis )
   # Extract the release name and version, and then remove these entries
   # from the list:
   list( GET _baseProjectsUserAnalysis 0
      _base_projectUserAnalysis )
   list( GET _baseProjectsUserAnalysis 1
      _base_versionUserAnalysis )
   list( REMOVE_AT _baseProjectsUserAnalysis 0 1 )
   # Make sure that the project version is a regular version number:
   if( NOT _base_versionUserAnalysis MATCHES "^[0-9]+[0-9.]*" )
      # Let's not specify a version in this case...
      message( STATUS "Using base project "
         "\"${_base_projectUserAnalysis}\" without "
         "its \"${_base_versionUserAnalysis}\" version name/number" )
      set( _base_versionUserAnalysis )
   endif()
   # Find the base release:
   if( UserAnalysis_FIND_QUIETLY )
      find_package( ${_base_projectUserAnalysis}
         ${_base_versionUserAnalysis} EXACT QUIET )
   else()
      find_package( ${_base_projectUserAnalysis}
         ${_base_versionUserAnalysis} EXACT )
   endif()
endwhile()
unset( _baseProjectsUserAnalysis )
unset( _base_projectUserAnalysis )
unset( _base_versionUserAnalysis )

# Make CMake find the release's installed modules. Optionally append the module
# library instead of prepending it. To allow the user to override the
# modules packaged with the release.
if( ATLAS_DONT_PREPEND_PROJECT_MODULES )
   list( APPEND CMAKE_MODULE_PATH "${UserAnalysis_CMAKE_DIR}/modules" )
else()
   list( INSERT CMAKE_MODULE_PATH 0 "${UserAnalysis_CMAKE_DIR}/modules" )
endif()
list( REMOVE_DUPLICATES CMAKE_MODULE_PATH )

# Pull in the ATLAS code:
include( AtlasFunctions )

# Include the file listing all the imported targets and options:
include(
   "${UserAnalysis_CMAKE_DIR}/UserAnalysisConfig-targets.cmake"
   OPTIONAL )

# Check what build mode the release was built with. And set CMAKE_BUILD_TYPE
# to that value by default. While there should only be one build mode in
# a given install area, provide an explicit preference order to the different
# build modes:
foreach( _type "Debug" "RelWithDebInfo" "Release" "MinSizeRel" "Default" )
   string( TOLOWER "${_type}" _typeLower )
   set( _fileName "${UserAnalysis_CMAKE_DIR}/" )
   set( _fileName "${_fileName}UserAnalysisConfig-targets" )
   set( _fileName "${_fileName}-${_typeLower}.cmake" )
   if( EXISTS "${_fileName}" )
      # Set the build type forcefully. CMake (at least at the time of writing
      # [3.19]) needs to be handled in this weird way. (One would think that if
      # the variable is deemed not-yet-set, then you wouldn't need to use the
      # FORCE keyword. But you do...)
      if( NOT CMAKE_BUILD_TYPE )
         set( CMAKE_BUILD_TYPE "${_type}"
            CACHE STRING "Build mode for the release" FORCE )
      endif()
      break()
   endif()
   unset( _fileName )
   unset( _typeLower )
endforeach()

# If the libraries need to be set up...
if( UserAnalysis_FIND_COMPONENTS )

   # A sanity check.
   if( NOT ${UserAnalysis_FIND_COMPONENTS} STREQUAL "INCLUDE" )
      message( WARNING "Only the 'INCLUDE' component is understood. "
         "Continuing as if 'INCLUDE' would have been specified..." )
   endif()

   # Tell the user what's happening.
   message( STATUS "Including the packages from project "
      "UserAnalysis - 0.0.0..." )

   # Loop over the targets that this project has.
   foreach( _target ${UserAnalysis_TARGET_NAMES} )
      # If the target exists already, then don't do aything else.
      if( TARGET ${_target} )
         continue()
      endif()
      # Check whether the target in question is known in this release.
      if( NOT TARGET UserAnalysis::${_target} )
         message( SEND_ERROR
            "Target with name UserAnalysis::${_target} not found" )
         continue()
      endif()
      # And now create a deep copy of it.
      atlas_copy_target( UserAnalysis ${_target} )
   endforeach()

   # Include the base projects, in reverse order. So that the components from
   # the end of the list would get precedence over the components from the
   # front.
   set( _baseProjectsUserAnalysis
      ${UserAnalysis_BASE_PROJECTS} )
   while( _baseProjectsUserAnalysis )
      # Get the last project from the list:
      list( LENGTH _baseProjectsUserAnalysis
         _lengthUserAnalysis )
      math( EXPR _projNameIdxUserAnalysis
         "${_lengthUserAnalysis} - 2" )
      math( EXPR _projVersIdxUserAnalysis
         "${_lengthUserAnalysis} - 1" )
      list( GET _baseProjectsUserAnalysis
         ${_projNameIdxUserAnalysis}
         _base_projectUserAnalysis )
      list( GET _baseProjectsUserAnalysis
         ${_projVersIdxUserAnalysis}
         _base_versionUserAnalysis )
      list( REMOVE_AT _baseProjectsUserAnalysis
         ${_projNameIdxUserAnalysis}
         ${_projVersIdxUserAnalysis} )
      # Find the base release:
      find_package( ${_base_projectUserAnalysis}
         ${_base_versionUserAnalysis} EXACT COMPONENTS INCLUDE QUIET )
   endwhile()
   unset( _baseProjectsUserAnalysis )
   unset( _projNameIdxUserAnalysis )
   unset( _projVersIdxUserAnalysis )
   unset( _base_projectUserAnalysis )
   unset( _base_versionUserAnalysis )
   unset( _lengthUserAnalysis )

endif()

# Only do this if necessary:
if( NOT ATLAS_DONT_PREPEND_PROJECT_MODULES )
   # Make sure that after all of this, we still have this release's module
   # directory at the front of the list:
   list( INSERT CMAKE_MODULE_PATH 0 "${UserAnalysis_CMAKE_DIR}/modules" )
   list( REMOVE_DUPLICATES CMAKE_MODULE_PATH )
endif()

# Include the project-specific post-include file, if it exists:
include( "${UserAnalysis_CMAKE_DIR}/PostConfig.cmake" OPTIONAL )
