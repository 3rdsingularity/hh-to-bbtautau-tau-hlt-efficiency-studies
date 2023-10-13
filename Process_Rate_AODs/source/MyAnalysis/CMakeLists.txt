# The name of the package:
atlas_subdir (MyAnalysis)

# Find the needed external(s):
find_package( ROOT COMPONENTS Core RIO Hist Tree Matrix )

# Build a CINT dictionary for the library 
atlas_add_root_dictionary ( MyAnalysisLib MyAnalysisCintDict 
        ROOT_HEADERS MyAnalysis/MyxAODAnalysis.h Root/LinkDef.h
                            EXTERNAL_PACKAGES ROOT)

# Add the shared library:
atlas_add_library (MyAnalysisLib
  MyAnalysis/*.h Root/*.cxx ${MyAnalysisCintDict}
  PUBLIC_HEADERS MyAnalysis
  LINK_LIBRARIES  ${ROOT_LIBRARIES} AnaAlgorithmLib xAODEventInfo xAODTau xAODMuon xAODBase xAODTrigger
  AsgTools xAODRootAccess TrigConfxAODLib TrigDecisionToolLib TauAnalysisToolsLib)

if (XAOD_STANDALONE)
 # Add the dictionary (for AnalysisBase only):
 atlas_add_dictionary (MyAnalysisDict
  MyAnalysis/MyAnalysisDict.h
  MyAnalysis/selection.xml
  LINK_LIBRARIES MyAnalysisLib)
endif ()

if (NOT XAOD_STANDALONE)
  # Add a component library for AthAnalysis only:
  atlas_add_component (MyAnalysis
    src/*.h src/*.cxx src/components/*.cxx
    LINK_LIBRARIES GaudiKernel MyAnalysisLib)
endif ()

# Install files from the package:
atlas_install_joboptions( share/*_jobOptions.py )
#atlas_install_scripts( share/*_eljob.py ) #comment out for r22