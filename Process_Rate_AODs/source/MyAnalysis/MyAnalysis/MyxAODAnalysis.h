#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h> // Was there before
#include <AsgTools/ToolHandle.h>  // Was there before

//ROOT include(s)
#include <TH1.h>
#include <TTree.h>
#include <vector>
#include <TSortedList.h>
#include <TObject.h>
#include <TLorentzVector.h>

//Tool include(s)
#include "TrigConfxAOD/xAODConfigTool.h"
#include "TrigDecisionTool/TrigDecisionTool.h"
#include "TrigDecisionTool/ChainGroup.h"
#include "TrigDecisionTool/FeatureContainer.h"
#include "TrigDecisionTool/Feature.h"
#include "TrigDecisionTool/Conditions.h"
#include "TrigDecisionTool/DecisionAccess.h"
#include "TrigDecisionTool/ConfigurationAccess.h"
#include "TrigDecisionTool/Combination.h"
#include "TrigDecisionTool/TDTUtilities.h"
#include "TauAnalysisTools/TauTruthMatchingTool.h"

//#include "FTagAnalysisInterfaces/IBTaggingSelectionTool.h"
#include "xAODBTagging/BTagging.h"
#include "xAODBTagging/BTaggingContainer.h"
#include "xAODBTagging/BTaggingUtilities.h"


class MyxAODAnalysis : public EL::AnaAlgorithm
{
public:
  // this is a standard algorithm constructor
  MyxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);
  ~MyxAODAnalysis();
  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;

private:
  // Tool Configuration
  ToolHandle< Trig::TrigDecisionTool > m_trigDecTool;
  ToolHandle< TauAnalysisTools::TauTruthMatchingTool > m_T2MT;
  
  
  // Flavor tagger
  // asg::AnaToolHandle<IBTaggingSelectionTool> m_btag_tool_HLT{"BTaggingSelectionTool"};
  // asg::AnaToolHandle<IBTaggingSelectionTool> m_btag_tool_offline{"BTaggingSelectionTool_offline"};


  unsigned long long m_eventNumber = 0; // Event number
  
  // L1 triggers

  bool L1_4b_3j1j;  // Asymmetric Trigger
  bool L1_RD0_filled; // L1_RD0_FILLED

  // HLT triggers
  bool HLT_tau0_J25;    // HLT_tau0_mediumRNN_tracktwoMVA_tau0_mediumRNN_tracktwoMVA_03dRAB30_L1DR-TAU20ITAU12I-J25
  bool HLT_tau0_4J12;   // HLT_tau0_mediumRNN_tracktwoMVA_tau0_mediumRNN_tracktwoMVA_03dRAB_L1TAU20IM_2TAU12IM_4J12p0ETA25
  bool HLT_J25_idperf;  // HLT_tau30_idperf_tracktwoMVA_tau20_idperf_tracktwoMVA_03dRAB30_L1DR-TAU20ITAU12I-J25
  bool HLT_4J12_idperf; // HLT_tau30_idperf_tracktwoMVA_tau20_idperf_tracktwoMVA_03dRAB_L1TAU20IM_2TAU12IM_4J12p0ETA25

  
  //Matched
  std::vector<int> *m_noff_mtaus = nullptr; 
  std::vector<TLorentzVector> *m_off_mtaus = nullptr;
  std::vector<bool> *m_off_mtauIDvl = nullptr; 
  std::vector<bool> *m_off_mtauIDl = nullptr; 
  std::vector<bool> *m_off_mtauIDm = nullptr; 
  std::vector<bool> *m_off_mtauIDt = nullptr;
  std::vector<size_t> *m_off_mprong = nullptr; 
  std::vector<float> *m_off_mrnn = nullptr;

  //Online HLT Jets
  std::vector<int> *m_non_hltJet = nullptr;
  std::vector<TLorentzVector> *m_on_hltjet = nullptr; //HLT_xAOD__JetContainer
  std::vector<float> *m_on_hltjetjvtlist = nullptr;
  std::vector<float> *m_on_hltjetdl1dblist = nullptr;
  std::vector<float> *m_on_hltjetdl1dclist = nullptr;
  std::vector<float> *m_on_hltjetdl1dulist = nullptr;
  std::vector<float> *m_on_hltjetGN1blist = nullptr;
  std::vector<float> *m_on_hltjetGN1clist = nullptr;
  std::vector<float> *m_on_hltjetGN1ulist = nullptr;

  //Tau_jets
  std::vector<int> *m_ntau_jets = nullptr; 
  std::vector<TLorentzVector> *m_tau_jets = nullptr;
  std::vector<bool> *m_tau_jetIDvl = nullptr; 
  std::vector<bool> *m_tau_jetIDl = nullptr; 
  std::vector<bool> *m_tau_jetIDm = nullptr; 
  std::vector<bool> *m_tau_jetIDt = nullptr;
  std::vector<size_t> *m_tau_jetprong = nullptr; 
  std::vector<float> *m_tau_jetrnn = nullptr;



  //TrigDefs::includeFailedDecisions_perf
  std::vector<int> *m_non_HLTptfl_perf = nullptr; 
  std::vector<TLorentzVector> *m_on_HLTptfl_perf = nullptr;
  std::vector<bool> *m_on_idvlHLTptfl_perf = nullptr; 
  std::vector<bool> *m_on_idlHLTptfl_perf = nullptr; 
  std::vector<bool> *m_on_idmHLTptfl_perf = nullptr; 
  std::vector<bool> *m_on_idtHLTptfl_perf = nullptr;
  std::vector<size_t> *m_on_prngHLTptfl_perf = nullptr; 
  std::vector<float> *m_on_rnnHLTptfl_perf = nullptr;
  std::vector<bool> *m_on_HLTptflag_perf = nullptr;

  std::vector<int> *m_non_HLTetafl_perf = nullptr; 
  std::vector<TLorentzVector> *m_on_HLTetafl_perf = nullptr;
  std::vector<bool> *m_on_idvlHLTetafl_perf = nullptr; 
  std::vector<bool> *m_on_idlHLTetafl_perf = nullptr; 
  std::vector<bool> *m_on_idmHLTetafl_perf = nullptr; 
  std::vector<bool> *m_on_idtHLTetafl_perf = nullptr;
  std::vector<size_t> *m_on_prngHLTetafl_perf = nullptr; 
  std::vector<float> *m_on_rnnHLTetafl_perf = nullptr;
  std::vector<bool> *m_on_HLTetaflag_perf = nullptr;


  //HLT container (loop directly) TrigTauRecMerged
  std::vector<int> *m_non_TrigTRM = nullptr; 
  std::vector<TLorentzVector> *m_on_TrigTRM = nullptr;
  std::vector<bool> *m_on_idvlTrigTRM = nullptr; 
  std::vector<bool> *m_on_idlTrigTRM = nullptr; 
  std::vector<bool> *m_on_idmTrigTRM = nullptr; 
  std::vector<bool> *m_on_idtTrigTRM = nullptr;
  std::vector<size_t> *m_on_prngTrigTRM = nullptr; 
  std::vector<float> *m_on_rnnTrigTRM = nullptr;
};

#endif