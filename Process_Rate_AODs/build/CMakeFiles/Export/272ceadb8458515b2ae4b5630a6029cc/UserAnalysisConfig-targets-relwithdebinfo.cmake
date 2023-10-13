#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "UserAnalysis::MyAnalysisLib" for configuration "RelWithDebInfo"
set_property(TARGET UserAnalysis::MyAnalysisLib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(UserAnalysis::MyAnalysisLib PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libMyAnalysisLib.so"
  IMPORTED_SONAME_RELWITHDEBINFO "libMyAnalysisLib.so"
  )

list(APPEND _cmake_import_check_targets UserAnalysis::MyAnalysisLib )
list(APPEND _cmake_import_check_files_for_UserAnalysis::MyAnalysisLib "${_IMPORT_PREFIX}/lib/libMyAnalysisLib.so" )

# Import target "UserAnalysis::MyAnalysis" for configuration "RelWithDebInfo"
set_property(TARGET UserAnalysis::MyAnalysis APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(UserAnalysis::MyAnalysis PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELWITHDEBINFO ""
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libMyAnalysis.so"
  IMPORTED_NO_SONAME_RELWITHDEBINFO "TRUE"
  )

list(APPEND _cmake_import_check_targets UserAnalysis::MyAnalysis )
list(APPEND _cmake_import_check_files_for_UserAnalysis::MyAnalysis "${_IMPORT_PREFIX}/lib/libMyAnalysis.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
