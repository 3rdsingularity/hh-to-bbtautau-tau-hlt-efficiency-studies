#See: https://twiki.cern.ch/twiki/bin/viewauth/AtlasComputing/SoftwareTutorialxAODAnalysisInCMake for more details about anything here
#Datapath='/afs/cern.ch/work/j/jguhit/quicktriggeranalysis/samples'
#testFile = os.path.join(Datapath, 'mc16_13TeV.600023.PhH7EG_PDF4LHC15_HHbbtautauHadHad_cHHH01d0.recon.AOD.e8269_e7400_s3126_r12406/AOD.25557808._001099.pool.root.1')

#testFile = os.getenv("ALRB_TutorialData") + '/mc16_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3126_r10201_p4172/DAOD_PHYS.21569875._001323.pool.root.1'
# import AthenaRootComps.ReadAthenaxAOD

# For kl=1 case
# Datapath='/eos/user/s/shhayash/HH4b/HH4b-RUN3-TRIGGER/AOD/valid1.600023.PhH7EG_PDF4LHC15_HHbbtautauHadHad_cHHH01d0.merge.AOD.e7954_e7400_s3775_r13561_r13491_tid28764607_00/'
# testFile = os.path.join(Datapath,'AOD.28764607._000001.pool.root.1')

# Datapath='/eos/user/s/shiwen/public/bbtautauHLT/mc21_13p6TeV.601477.PhPy8EG_HHbbttHadHad_cHHH01d0.merge.AOD.e8472_e8455_s3873_s3874_r13829_r13831_tid30221003_00/'
# testFile = os.path.join(Datapath,'AOD.30221003._000001.pool.root.1')

# Datapath='/eos/user/s/shiwen/public/bbtautauHLT/mc21_13p6TeV.601478.PhPy8EG_HHbbttHadHad_cHHH10d0.deriv.DAOD_PHYS.e8472_s3873_r13829_p5511/'
# testFile = os.path.join(Datapath,'DAOD_PHYS.32050035._000001.pool.root.1')

testFile0 = '/afs/cern.ch/user/a/asudhaka/eos_space/tau_trigger/mc23_13p6TeV.601477.PhPy8EG_HHbbttHadHad_cHHH01d0.recon.AOD.e8514_e8528_s4111_s4114_r14668/AOD.33514441._000001.pool.root.1'
testFile1 = '/afs/cern.ch/user/a/asudhaka/eos_space/tau_trigger/mc23_13p6TeV.601477.PhPy8EG_HHbbttHadHad_cHHH01d0.recon.AOD.e8514_e8528_s4111_s4114_r14668/AOD.33514441._000002.pool.root.1'

# For kl=10 case 
# Datapath='/eos/user/s/shiwen/data_bbtautau/valid1.600024.PhH7EG_PDF4LHC15_HHbbtautauHadHad_cHHH10d0.merge.AOD.e7954_e7400_s3775_r13561_r13491_tid28764613_00/'
# testFile0 = os.path.join(Datapath,'AOD.28764613._000001.pool.root.1')
# testFile1 = os.path.join(Datapath,'AOD.28764613._000002.pool.root.1')

# For New Sample by Jem 
#Datapath='/afs/cern.ch/work/j/jguhit/public/'
#testFile = os.path.join(Datapath, 'AOD.27382945._000067.pool.root.1') 

#AOD.28764607._000001.pool.root.1
#Datapath='/afs/cern.ch/work/j/jguhit/athanalysisr22/bbtautautriggeranalysis/samples'
#testFile = os.path.join(Datapath, 'valid1.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau.recon.AOD.e5112_s3214_d1738_r13391_tid28072335_00/AOD.28072335._000318.pool.root.1')
#testFile = os.path.join(Datapath, 'data18_13TeV.00360026.physics_EnhancedBias.merge.AOD.r13464_p5024_tid28328499_00/AOD.28328499._000115.pool.root.1')

#override next line on command line with: --filesInput=
jps.AthenaCommonFlags.FilesInput = [testFile0] #
# jps.AthenaCommonFlags.FilesInput = [testFile0, testFile1]
#Specify AccessMode (read mode) ... ClassAccess is good default for xAOD
jps.AthenaCommonFlags.AccessMode = "ClassAccess" 

jps.AthenaCommonFlags.HistOutputs = ["ANALYSIS:kl01_mc23.root"]
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

