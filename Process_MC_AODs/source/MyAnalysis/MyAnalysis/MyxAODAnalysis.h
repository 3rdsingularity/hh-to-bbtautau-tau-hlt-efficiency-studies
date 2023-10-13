#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <AsgTools/ToolHandle.h>

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
  /*
  unsigned long long m_eventNumber = 0; // Event number
  std::vector<float> *m_actualBC = nullptr; 
  std::vector<float> *m_aveBC =  nullptr;
  */
  
  //L1 
  bool L1_trig_pt; 
  bool L1_trig_eta;

  //HLT triggers
  bool HLT_trig_ptr22;
  bool HLT_trig_etar22;
  bool HLT_trig_ptTau0;
  bool HLT_trig_etaTau0;
  bool HLT_trig_ptidperf;
  bool HLT_trig_etaidperf;
  
  //Matched
  std::vector<int> *m_noff_mtaus = nullptr; 
  std::vector<TLorentzVector> *m_off_mtaus = nullptr;
  std::vector<bool> *m_off_mtauIDvl = nullptr; 
  std::vector<bool> *m_off_mtauIDl = nullptr; 
  std::vector<bool> *m_off_mtauIDm = nullptr; 
  std::vector<bool> *m_off_mtauIDt = nullptr;
  std::vector<size_t> *m_off_mprong = nullptr; 
  std::vector<float> *m_off_mrnn = nullptr;

  //TrigDefs::includeFailedDecisions
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

  //TrigDefs::includeFailedDecisions
  std::vector<int> *m_non_HLTptfl = nullptr; 
  std::vector<TLorentzVector> *m_on_HLTptfl = nullptr;
  std::vector<bool> *m_on_idvlHLTptfl = nullptr; 
  std::vector<bool> *m_on_idlHLTptfl = nullptr; 
  std::vector<bool> *m_on_idmHLTptfl = nullptr; 
  std::vector<bool> *m_on_idtHLTptfl = nullptr;
  std::vector<size_t> *m_on_prngHLTptfl = nullptr; 
  std::vector<float> *m_on_rnnHLTptfl = nullptr;
  std::vector<bool> *m_on_HLTptflag = nullptr;

  std::vector<int> *m_non_HLTetafl = nullptr; 
  std::vector<TLorentzVector> *m_on_HLTetafl = nullptr;
  std::vector<bool> *m_on_idvlHLTetafl = nullptr; 
  std::vector<bool> *m_on_idlHLTetafl = nullptr; 
  std::vector<bool> *m_on_idmHLTetafl = nullptr; 
  std::vector<bool> *m_on_idtHLTetafl = nullptr;
  std::vector<size_t> *m_on_prngHLTetafl = nullptr; 
  std::vector<float> *m_on_rnnHLTetafl = nullptr;
  std::vector<bool> *m_on_HLTetaflag = nullptr;

  //HLT container (loop directly) TrigTauRecMerged
  std::vector<int> *m_non_TrigTRM = nullptr; 
  std::vector<TLorentzVector> *m_on_TrigTRM = nullptr;
  std::vector<bool> *m_on_idvlTrigTRM = nullptr; 
  std::vector<bool> *m_on_idlTrigTRM = nullptr; 
  std::vector<bool> *m_on_idmTrigTRM = nullptr; 
  std::vector<bool> *m_on_idtTrigTRM = nullptr;
  std::vector<size_t> *m_on_prngTrigTRM = nullptr; 
  std::vector<float> *m_on_rnnTrigTRM = nullptr;

  // Add some truth jet to the NTuple
  std::vector<float> * m_on_truthmHH = nullptr;
  float m_truthmHH; 
  float m_nH;
  float m_status;
};

#endif
