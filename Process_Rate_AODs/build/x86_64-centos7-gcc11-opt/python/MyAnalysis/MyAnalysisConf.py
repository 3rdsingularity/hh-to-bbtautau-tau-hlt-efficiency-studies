#Thu Oct 12 16:14:34 2023"""Automatically generated. DO NOT EDIT please"""
import sys
if sys.version_info >= (3,):
    # Python 2 compatibility
    long = int
from GaudiKernel.GaudiHandles import *
from AthenaCommon.Configurable import *

class MyxAODAnalysis( ConfigurableAlgorithm ) :
  __slots__ = { 
    'ExtraInputs' : [], # list
    'ExtraOutputs' : [], # list
    'OutputLevel' : 0, # int
    'Enable' : True, # bool
    'ErrorMax' : 1, # int
    'AuditAlgorithms' : False, # bool
    'AuditInitialize' : False, # bool
    'AuditReinitialize' : False, # bool
    'AuditRestart' : False, # bool
    'AuditExecute' : False, # bool
    'AuditFinalize' : False, # bool
    'AuditStart' : False, # bool
    'AuditStop' : False, # bool
    'Timeline' : True, # bool
    'MonitorService' : 'MonitorSvc', # str
    'RegisterForContextService' : False, # bool
    'Cardinality' : 1, # int
    'NeededResources' : [  ], # list
    'Blocking' : False, # bool
    'FilterCircularDependencies' : True, # bool
    'EvtStore' : ServiceHandle('StoreGateSvc'), # GaudiHandle
    'DetStore' : ServiceHandle('StoreGateSvc/DetectorStore'), # GaudiHandle
    'THistSvc' : ServiceHandle('THistSvc/THistSvc'), # GaudiHandle
    'RootStreamName' : '/ANALYSIS', # str
    'RootDirName' : '', # str
    'HistNamePrefix' : '', # str
    'HistNamePostfix' : '', # str
    'HistTitlePrefix' : '', # str
    'HistTitlePostfix' : '', # str
    'TrigDecisionTool' : PublicToolHandle('Trig::TrigDecisionTool/TrigDecisionTool'), # GaudiHandle
    'TauTruthMatchingTool' : PublicToolHandle('TauAnalysisTools::TauTruthMatchingTool/TauTruthMatchingTool'), # GaudiHandle
  }
  _propertyDocDct = { 
    'ExtraInputs' : """  [DataHandleHolderBase<PropertyHolder<CommonMessaging<implements<IAlgorithm,IDataHandleHolder,IProperty,IStateful> > > >] """,
    'ExtraOutputs' : """  [DataHandleHolderBase<PropertyHolder<CommonMessaging<implements<IAlgorithm,IDataHandleHolder,IProperty,IStateful> > > >] """,
    'OutputLevel' : """ output level [Gaudi::Algorithm] """,
    'Enable' : """ should the algorithm be executed or not [Gaudi::Algorithm] """,
    'ErrorMax' : """ [[deprecated]] max number of errors [Gaudi::Algorithm] """,
    'AuditAlgorithms' : """ [[deprecated]] unused [Gaudi::Algorithm] """,
    'AuditInitialize' : """ trigger auditor on initialize() [Gaudi::Algorithm] """,
    'AuditReinitialize' : """ trigger auditor on reinitialize() [Gaudi::Algorithm] """,
    'AuditRestart' : """ trigger auditor on restart() [Gaudi::Algorithm] """,
    'AuditExecute' : """ trigger auditor on execute() [Gaudi::Algorithm] """,
    'AuditFinalize' : """ trigger auditor on finalize() [Gaudi::Algorithm] """,
    'AuditStart' : """ trigger auditor on start() [Gaudi::Algorithm] """,
    'AuditStop' : """ trigger auditor on stop() [Gaudi::Algorithm] """,
    'Timeline' : """ send events to TimelineSvc [Gaudi::Algorithm] """,
    'MonitorService' : """ name to use for Monitor Service [Gaudi::Algorithm] """,
    'RegisterForContextService' : """ flag to enforce the registration for Algorithm Context Service [Gaudi::Algorithm] """,
    'Cardinality' : """ how many clones to create - 0 means algo is reentrant [Gaudi::Algorithm] """,
    'NeededResources' : """ named resources needed during event looping [Gaudi::Algorithm] """,
    'Blocking' : """ if algorithm invokes CPU-blocking system calls (offloads computations to accelerators or quantum processors, performs disk or network I/O, is bound by resource synchronization, etc) [Gaudi::Algorithm] """,
    'FilterCircularDependencies' : """ filter out circular data dependencies [Gaudi::Algorithm] """,
    'EvtStore' : """ Handle to a StoreGateSvc instance: it will be used to retrieve data during the course of the job [unknown owner type] """,
    'DetStore' : """ Handle to a StoreGateSvc/DetectorStore instance: it will be used to retrieve data during the course of the job [unknown owner type] """,
    'THistSvc' : """ Handle to a THistSvc instance: it will be used to write ROOT objects to ROOT files [unknown owner type] """,
    'RootStreamName' : """ Name of the output ROOT stream (file) that the THistSvc uses [unknown owner type] """,
    'RootDirName' : """ Name of the ROOT directory inside the ROOT file where the histograms will go [unknown owner type] """,
    'HistNamePrefix' : """ The prefix for the histogram THx name [unknown owner type] """,
    'HistNamePostfix' : """ The postfix for the histogram THx name [unknown owner type] """,
    'HistTitlePrefix' : """ The prefix for the histogram THx title [unknown owner type] """,
    'HistTitlePostfix' : """ The postfix for the histogram THx title [unknown owner type] """,
  }
  __declaration_location__ = 'MyAnalysis_entries.cxx:3'
  def __init__(self, name = Configurable.DefaultName, **kwargs):
      super(MyxAODAnalysis, self).__init__(name)
      for n,v in kwargs.items():
         setattr(self, n, v)
  def getDlls( self ):
      return 'MyAnalysis'
  def getType( self ):
      return 'MyxAODAnalysis'
  pass # class MyxAODAnalysis
