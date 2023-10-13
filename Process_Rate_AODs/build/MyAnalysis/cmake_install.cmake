# Install script for directory: /afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/source/MyAnalysis

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/UserAnalysis/0.0.0/InstallArea/x86_64-centos7-gcc11-opt")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/cvmfs/sft.cern.ch/lcg/releases/binutils/2.37-355ed/x86_64-centos7/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/src/MyAnalysis" TYPE DIRECTORY FILES "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/source/MyAnalysis/" USE_SOURCE_PERMISSIONS REGEX "/\\.svn$" EXCLUDE REGEX "/\\.git$" EXCLUDE REGEX "/[^/]*\\~$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE OPTIONAL FILES "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/x86_64-centos7-gcc11-opt/lib/libMyAnalysisLib_rdict.pcm")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
  
      set( _destdir "$ENV{DESTDIR}")
      if( NOT _destdir STREQUAL "" )
         set( _destdir "${_destdir}/" )
      endif()
      execute_process( COMMAND ${CMAKE_COMMAND}
         -E make_directory
         ${_destdir}${CMAKE_INSTALL_PREFIX}/include )
      unset( _destdir )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
  
         set( _destdir "$ENV{DESTDIR}")
         if( NOT _destdir STREQUAL "" )
            set( _destdir "${_destdir}/" )
         endif()
         execute_process( COMMAND ${CMAKE_COMMAND}
            -E create_symlink ../src/MyAnalysis/MyAnalysis
            ${_destdir}${CMAKE_INSTALL_PREFIX}/include/MyAnalysis )
         unset( _destdir )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Debug" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE OPTIONAL FILES "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/x86_64-centos7-gcc11-opt/lib/libMyAnalysisLib.so.dbg")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY OPTIONAL FILES "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/x86_64-centos7-gcc11-opt/lib/libMyAnalysisLib.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libMyAnalysisLib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libMyAnalysisLib.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/cvmfs/sft.cern.ch/lcg/releases/binutils/2.37-355ed/x86_64-centos7/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libMyAnalysisLib.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Debug" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE OPTIONAL FILES "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/x86_64-centos7-gcc11-opt/lib/libMyAnalysis.so.dbg")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE MODULE OPTIONAL FILES "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/x86_64-centos7-gcc11-opt/lib/libMyAnalysis.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libMyAnalysis.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libMyAnalysis.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/cvmfs/sft.cern.ch/lcg/releases/binutils/2.37-355ed/x86_64-centos7/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libMyAnalysis.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/python/MyAnalysis" TYPE FILE OPTIONAL FILES "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/build/x86_64-centos7-gcc11-opt/python/MyAnalysis/MyAnalysisConf.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process( COMMAND ${CMAKE_COMMAND} -E touch
      $ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/python/MyAnalysis/__init__.py )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Main" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/jobOptions/MyAnalysis" TYPE FILE RENAME "ATestRunLocal_jobOptions.py" FILES "/afs/cern.ch/user/a/asudhaka/hlt_bbtautau_trigger_emulation/Process_Rate_AODs/source/MyAnalysis/share/ATestRunLocal_jobOptions.py")
endif()

