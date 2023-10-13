testFile = '/afs/cern.ch/user/a/asudhaka/eos_space/tau_trigger/data22_13p6TeV(DeV)/AOD.33426411._000001.pool.root.1'
# testFile = '/afs/cern.ch/user/a/asudhaka/eos_space/tau_trigger/valid1.600023.PhH7EG_PDF4LHC15_HHbbtautauHadHad_cHHH01d0.merge.AOD.e7954_e7400_s3775_r13561_r13491/AOD.28764607._000001.pool.root.1'
# testFile = '/afs/cern.ch/user/a/asudhaka/eos_space/tau_trigger/data22_13p6TeV/AOD.35016412._001488.pool.root.1'
# testFile = '/afs/cern.ch/user/a/asudhaka/public/bbtautau_trig_analysis/AOD.33426411._000001.pool.root.1'
# testFile = '/afs/cern.ch/user/a/asudhaka/eos_space/tau_trigger/valid1.600023.PhH7EG_PDF4LHC15_HHbbtautauHadHad_cHHH01d0.merge.AOD.e7954_e7400_s3775_r13561_r13491/AOD.28764607._000001.pool.root.1'





#override next line on command line with: --filesInput=XXX
#jps.AthenaCommonFlags.FilesInput = testFile #
jps.AthenaCommonFlags.FilesInput = [testFile]
#Specify AccessMode (read mode) ... ClassAccess is good default for xAOD
jps.AthenaCommonFlags.AccessMode = "ClassAccess" 

jps.AthenaCommonFlags.HistOutputs = ["ANALYSIS:kl01_mc21.root"]
svcMgr.THistSvc.MaxFileSize=-1 #speeds up jobs that output lots of histograms

# First create all the public tools to be used in the job
from AthenaCommon.AppMgr import ToolSvc
from TrigDecisionTool.TrigDecisionToolConf import Trig__TrigDecisionTool
import AthenaCommon.CfgMgr as CfgMgr

ToolSvc += CfgMgr.TrigConf__xAODConfigTool("xAODConfigTool")
ToolSvc += CfgMgr.Trig__TrigDecisionTool(
        "TrigDecisionTool",
        ConfigTool = ToolSvc.xAODConfigTool,
        TrigDecisionKey = "xTrigDecision",
        NavigationFormat = "TrigComposite",
        HLTSummary="HLTNav_Summary_AODSlimmed") #NavigationFormat = "TrigComposite" 

from TrigEDMConfig.TriggerEDM import EDMLibraries
ToolSvc.TrigDecisionTool.Navigation.Dlls = [e for e in EDMLibraries if 'TPCnv' not in e]

ToolSvc += CfgMgr.TauAnalysisTools__TauTruthMatchingTool("TauTruthMatchingTool")

# Create the algorithm's configuration.
from AnaAlgorithm.DualUseConfig import createAlgorithm
#alg = createAlgorithm ( 'MyxAODAnalysis', 'AnalysisAlg' )
alg = CfgMgr.MyxAODAnalysis(
    'AnalysisAlg',
    TrigDecisionTool = ToolSvc.TrigDecisionTool, 
    TauTruthMatchingTool = ToolSvc.TauTruthMatchingTool
    )

# later on we'll add some configuration options for our algorithm that go here

# Add our algorithm to the main alg sequence
athAlgSeq += alg

# limit the number of events (for testing purposes)
#theApp.EvtMax = 500

# optional include for reducing printout from athena
include("AthAnalysisBaseComps/SuppressLogging.py")

