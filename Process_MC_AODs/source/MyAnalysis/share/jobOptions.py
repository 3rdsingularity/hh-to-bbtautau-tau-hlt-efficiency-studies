

# For kl=1 case
Datapath='/eos/user/s/shhayash/HH4b/HH4b-RUN3-TRIGGER/AOD/valid1.600023.PhH7EG_PDF4LHC15_HHbbtautauHadHad_cHHH01d0.merge.AOD.e7954_e7400_s3775_r13561_r13491_tid28764607_00/'
testFile = os.path.join(Datapath,'AOD.28764607._000001.pool.root.1')

Datapath='/eos/user/s/shiwen/public/bbtautauHLT/mc21_13p6TeV.601477.PhPy8EG_HHbbttHadHad_cHHH01d0.merge.AOD.e8472_e8455_s3873_s3874_r13829_r13831_tid30221003_00/'
testFile = os.path.join(Datapath,'AOD.30221003._000001.pool.root.1')

jps.AthenaCommonFlags.FilesInput = [testFile] #
jps.AthenaCommonFlags.AccessMode = "ClassAccess" 
jps.AthenaCommonFlags.HistOutputs = ["ANALYSIS:kl01NewSample.root"]
svcMgr.THistSvc.MaxFileSize=-1 #speeds up jobs that output lots of histograms

# First create all the public tools to be used in the job
# from AthenaCommon.AppMgr import ToolSvc
# from TrigDecisionTool.TrigDecisionToolConf import Trig__TrigDecisionTool
import AthenaCommon.CfgMgr as CfgMgr

# ToolSvc += CfgMgr.TrigConf__xAODConfigTool("xAODConfigTool")
# ToolSvc += CfgMgr.Trig__TrigDecisionTool("TrigDecisionTool",
#         ConfigTool = ToolSvc.xAODConfigTool,
#         TrigDecisionKey = "xTrigDecision",
#         NavigationFormat = "TrigComposite") #NavigationFormat = "TrigComposite" 
# from TrigEDMConfig.TriggerEDM import EDMLibraries
# ToolSvc.TrigDecisionTool.Navigation.Dlls = [e for e in EDMLibraries if 'TPCnv' not in e]
# ToolSvc += CfgMgr.TauAnalysisTools__TauTruthMatchingTool("TauTruthMatchingTool")

from AnaAlgorithm.DualUseConfig import createAlgorithm
# #alg = createAlgorithm ( 'MyxAODAnalysis', 'AnalysisAlg' )
# alg = CfgMgr.MyxAODAnalysis(
#     'AnalysisAlg',
#     # TrigDecisionTool = ToolSvc.TrigDecisionTool, 
#     # TauTruthMatchingTool = ToolSvc.TauTruthMatchingTool
# )
# include("AthAnalysisBaseComps/SuppressLogging.py")

from AthenaCommon.Configurable import ConfigurableRun3Behavior
from AthenaConfiguration.ComponentAccumulator import appendCAtoAthena, conf2toConfigurable
from TrigDecisionTool.TrigDecisionToolConfig import TrigDecisionToolCfg
from AthenaConfiguration.AllConfigFlags import ConfigFlags
ConfigFlags.Input.Files = [testFile]
with ConfigurableRun3Behavior():
  tdtAcc = TrigDecisionToolCfg(ConfigFlags)
tdt = conf2toConfigurable(tdtAcc.getPrimary())
appendCAtoAthena( tdtAcc )

alg = createAlgorithm ( 'MyxAODAnalysis', 'AnalysisAlg' )
athAlgSeq += alg

# xAODConfTool = createPublicTool( 'TrigConf::xAODConfigTool', 'xAODConfigTool' )
# job.algsAdd (xAODConfTool)
# addPrivateTool( alg, 'trigDecisionTool', 'Trig::TrigDecisionTool' )

# alg.trigDecisionTool.ConfigTool = '%s/%s' % ( xAODConfTool.getType(), xAODConfTool.getName() )
# alg.trigDecisionTool.TrigDecisionKey = "xTrigDecision"