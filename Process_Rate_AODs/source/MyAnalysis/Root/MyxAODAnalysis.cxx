//#include <AsgTools/MessageCheck.h> //include for r21
#include <AsgTools/MessageCheckAsgTools.h> //include for r22
#include <MyAnalysis/MyxAODAnalysis.h>
#include "AthenaKernel/getMessageSvc.h"


//xAODs include(s)
#include <xAODEventInfo/EventInfo.h>
#include <xAODTau/TauJetContainer.h>
#include <xAODMuon/MuonContainer.h>
#include "xAODBase/IParticleContainer.h"
#include "xAODTrigger/TrigPassBits.h" 
#include "TrigConfHLTData/HLTTriggerElement.h"
#include <xAODJet/JetContainer.h>
#include "TrigDecisionTool/TrigDecisionTool.h"
#include "TrigDecisionTool/ChainGroup.h"
#include "TrigDecisionTool/FeatureContainer.h"
#include "TrigDecisionTool/Feature.h"
#include "TrigDecisionTool/Conditions.h"
#include "TrigDecisionTool/DecisionAccess.h"
#include "TrigDecisionTool/ConfigurationAccess.h"
#include "TrigDecisionTool/Combination.h"
#include "TrigDecisionTool/TDTUtilities.h"



MyxAODAnalysis :: MyxAODAnalysis (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm (name, pSvcLocator),
    m_trigDecTool( "Trig::TrigDecisionTool/TrigDecisionTool" ),
    m_T2MT( "TauAnalysisTools::TauTruthMatchingTool/TauTruthMatchingTool")
    //m_trigConfTool(new TrigConf::xAODConfigTool("xAODConfigTool")), 
    //m_trigDecTool(new Trig::TrigDecisionTool("TrigDecisionTool"))
{
  declareProperty("TrigDecisionTool", m_trigDecTool);
  declareProperty("TauTruthMatchingTool", m_T2MT);
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  This is also where you
  // declare all properties for your algorithm.  Note that things like
  // resetting statistics variables or booking histograms should
  // rather go into the initialize() function.
}

MyxAODAnalysis :: ~MyxAODAnalysis (){
  delete m_noff_mtaus;
  delete m_off_mtaus;
  delete m_off_mtauIDvl;
  delete m_off_mtauIDl; 
  delete m_off_mtauIDm; 
  delete m_off_mtauIDt;
  delete m_off_mprong;
  delete m_off_mrnn;

  delete m_non_hltJet;
  delete m_on_hltjet;
  delete m_on_hltjetjvtlist;
  delete m_on_hltjetdl1dblist;
  delete m_on_hltjetdl1dclist;
  delete m_on_hltjetdl1dulist;
  delete m_on_hltjetGN1blist;
  delete m_on_hltjetGN1clist;
  delete m_on_hltjetGN1ulist;

  delete m_non_HLTptfl_perf;
  delete m_on_HLTptfl_perf;
  delete m_on_idvlHLTptfl_perf;
  delete m_on_idlHLTptfl_perf; 
  delete m_on_idmHLTptfl_perf; 
  delete m_on_idtHLTptfl_perf;
  delete m_on_prngHLTptfl_perf;
  delete m_on_rnnHLTptfl_perf;
  delete m_on_HLTptflag_perf;

  delete m_non_HLTetafl_perf;
  delete m_on_HLTetafl_perf;
  delete m_on_idvlHLTetafl_perf;
  delete m_on_idlHLTetafl_perf; 
  delete m_on_idmHLTetafl_perf; 
  delete m_on_idtHLTetafl_perf;
  delete m_on_prngHLTetafl_perf;
  delete m_on_rnnHLTetafl_perf;
  delete m_on_HLTetaflag_perf;

  delete m_non_TrigTRM;
  delete m_on_TrigTRM; 
  delete m_on_idvlTrigTRM;
  delete m_on_idlTrigTRM; 
  delete m_on_idmTrigTRM; 
  delete m_on_idtTrigTRM; 
  delete m_on_prngTrigTRM;
  delete m_on_rnnTrigTRM;

}

StatusCode MyxAODAnalysis :: initialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  //ANA_MSG_INFO ("in initialize");

  ANA_CHECK( m_trigDecTool.retrieve() );
  ANA_CHECK( m_T2MT.retrieve() );

  //Tree Setup
  ANA_CHECK (book (TTree ("analysis", "My analysis ntuple")));
  TTree* mytree = tree ("analysis");
  //EventInfo
  mytree->Branch ("EventNumber", &m_eventNumber);

  //Triggers

  mytree->Branch("HLT_tau0_J25", &HLT_tau0_J25);
  mytree->Branch("HLT_tau0_4J12", &HLT_tau0_4J12);
  mytree->Branch("HLT_J25_idperf", &HLT_J25_idperf);
  mytree->Branch("HLT_4J12_idperf", &HLT_4J12_idperf);
  mytree->Branch("L1_RD0_filled", &L1_RD0_filled);
  mytree->Branch("L1_4b_3j1j", &L1_4b_3j1j);


  //Other Branches
  m_noff_mtaus = new std::vector<int>(); 
  mytree->Branch("Noffline_Matched_Taus", &m_noff_mtaus);
  m_off_mtaus = new std::vector<TLorentzVector>();
  mytree->Branch ("Offline_Matched_Taus", &m_off_mtaus);
  m_off_mtauIDvl = new std::vector<bool>();
  mytree->Branch ("Off_Matched_TauIDvl", &m_off_mtauIDvl);
  m_off_mtauIDl = new std::vector<bool>();
  mytree->Branch ("Off_Matched_TauIDl", &m_off_mtauIDl);
  m_off_mtauIDm = new std::vector<bool>();
  mytree->Branch ("Off_Matched_TauIDm", &m_off_mtauIDm);
  m_off_mtauIDt = new std::vector<bool>();
  mytree->Branch ("Off_Matched_TauIDt", &m_off_mtauIDt);
  m_off_mprong = new std::vector<size_t>();
  mytree->Branch ("Off_Matched_TauProng", &m_off_mprong);
  m_off_mrnn = new std::vector<float>(); 
  mytree->Branch ("Off_Matched_TauRNN", &m_off_mrnn);

  m_non_hltJet = new std::vector<int>();
  mytree->Branch("NHLTJets", &m_non_hltJet);
  m_on_hltjet = new std::vector<TLorentzVector>();
  mytree->Branch ("HLTJets", &m_on_hltjet);
  m_on_hltjetjvtlist = new std::vector<float>();
  mytree->Branch("HLTJets_Jvt", &m_on_hltjetjvtlist);
  m_on_hltjetdl1dblist = new std::vector<float>();
  mytree->Branch("HLTJets_DL1d20211216_pb", &m_on_hltjetdl1dblist);
  m_on_hltjetdl1dclist = new std::vector<float>();
  mytree->Branch("HLTJets_DL1d20211216_pc", &m_on_hltjetdl1dclist);
  m_on_hltjetdl1dulist = new std::vector<float>();
  mytree->Branch("HLTJets_DL1d20211216_pu", &m_on_hltjetdl1dulist);
  m_on_hltjetGN1blist = new std::vector<float>();
  mytree->Branch("HLTJets_GN1b", &m_on_hltjetGN1blist);
  m_on_hltjetGN1clist = new std::vector<float>();
  mytree->Branch("HLTJets_GN1c", &m_on_hltjetGN1clist);
  m_on_hltjetGN1ulist = new std::vector<float>();
  mytree->Branch("HLTJets_GN1u", &m_on_hltjetGN1ulist);
  

  // idperf
  m_non_HLTptfl_perf = new std::vector<int>(); 
  mytree->Branch("Num_TrigMatched_Taus_HLTptfl_perf", &m_non_HLTptfl_perf);
  m_on_HLTptfl_perf = new std::vector<TLorentzVector>();
  mytree->Branch ("TrigMatched_Taus_HLTptfl_perf", &m_on_HLTptfl_perf);
  m_on_idvlHLTptfl_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDvl_HLTptfl_perf", &m_on_idvlHLTptfl_perf); 
  m_on_idlHLTptfl_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDl_HLTptfl_perf", &m_on_idlHLTptfl_perf);
  m_on_idmHLTptfl_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDm_HLTptfl_perf", &m_on_idmHLTptfl_perf);
  m_on_idtHLTptfl_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDt_HLTptfl_perf", &m_on_idtHLTptfl_perf);
  m_on_prngHLTptfl_perf = new std::vector<size_t>();
  mytree->Branch ("TrigMatched_prong_HLTptfl_perf", &m_on_prngHLTptfl_perf);
  m_on_rnnHLTptfl_perf = new std::vector<float>(); 
  mytree->Branch ("TrigMatched_rnn_HLTptfl_perf", &m_on_rnnHLTptfl_perf);
  m_on_HLTptflag_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_HLTptflag_perf", &m_on_HLTptflag_perf); 

  m_non_HLTetafl_perf = new std::vector<int>(); 
  mytree->Branch("Num_TrigMatched_Taus_HLTetafl_perf", &m_non_HLTetafl_perf);
  m_on_HLTetafl_perf = new std::vector<TLorentzVector>();
  mytree->Branch ("TrigMatched_Taus_HLTetafl_perf", &m_on_HLTetafl_perf);
  m_on_idvlHLTetafl_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDvl_HLTetafl_perf", &m_on_idvlHLTetafl_perf);
  m_on_idlHLTetafl_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDl_HLTetafl_perf", &m_on_idlHLTetafl_perf);
  m_on_idmHLTetafl_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDm_HLTetafl_perf", &m_on_idmHLTetafl_perf);
  m_on_idtHLTetafl_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDt_HLTetafl_perf", &m_on_idtHLTetafl_perf);
  m_on_prngHLTetafl_perf = new std::vector<size_t>();
  mytree->Branch ("TrigMatched_prong_HLTetafl_perf", &m_on_prngHLTetafl_perf);
  m_on_rnnHLTetafl_perf = new std::vector<float>(); 
  mytree->Branch ("TrigMatched_rnn_HLTetafl_perf", &m_on_rnnHLTetafl_perf);
  m_on_HLTetaflag_perf = new std::vector<bool>();
  mytree->Branch ("TrigMatched_HLTetaflag_perf", &m_on_HLTetaflag_perf);


  //HLT Container directly 
  m_non_TrigTRM = new std::vector<int>(); 
  mytree->Branch("Num_TrigTRM_Taus", &m_non_TrigTRM);
  m_on_TrigTRM = new std::vector<TLorentzVector>();
  mytree->Branch ("TrigTRM_Taus", &m_on_TrigTRM);
  m_on_idvlTrigTRM = new std::vector<bool>();
  mytree->Branch ("TrigTRM_TauIDvl", &m_on_idvlTrigTRM);
  m_on_idlTrigTRM = new std::vector<bool>();
  mytree->Branch ("TrigTRM_TauIDl", &m_on_idlTrigTRM);
  m_on_idmTrigTRM = new std::vector<bool>();
  mytree->Branch ("TrigTRM_TauIDm", &m_on_idmTrigTRM);
  m_on_idtTrigTRM = new std::vector<bool>();
  mytree->Branch ("TrigTRM_TauIDt", &m_on_idtTrigTRM);
  m_on_prngTrigTRM = new std::vector<size_t>();
  mytree->Branch ("TrigTRM_prong", &m_on_prngTrigTRM);
  m_on_rnnTrigTRM = new std::vector<float>(); 
  mytree->Branch ("TrigTRM_rnn", &m_on_rnnTrigTRM);


  ANA_MSG_INFO("initialization done");
  return StatusCode::SUCCESS;
}

StatusCode MyxAODAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  

  //L1 flags
  L1_4b_3j1j = false;  // Asymmetric Trigger
  L1_RD0_filled = false; // L1_RD0_FILLED

  //HLT flags

  HLT_tau0_J25 = false;
  HLT_tau0_4J12 = false;
  HLT_4J12_idperf = false;
  HLT_J25_idperf = false;

  const std::string trigL1_4b_3j1j="L1_J45p0ETA21_3J15p0ETA25"; //b+3j
  const std::string trigL1_RD0_filled="L1_RD0_FILLED";

  const std::string tau0_J25="HLT_tau0_mediumRNN_tracktwoMVA_tau0_mediumRNN_tracktwoMVA_03dRAB30_L1DR-TAU20ITAU12I-J25";
  const std::string tau0_4J12="HLT_tau0_mediumRNN_tracktwoMVA_tau0_mediumRNN_tracktwoMVA_03dRAB_L1TAU20IM_2TAU12IM_4J12p0ETA25";
  const std::string idperf_J25="HLT_tau30_idperf_tracktwoMVA_tau20_idperf_tracktwoMVA_03dRAB30_L1DR-TAU20ITAU12I-J25";
  const std::string idperf_4J12 ="HLT_tau30_idperf_tracktwoMVA_tau20_idperf_tracktwoMVA_03dRAB_L1TAU20IM_2TAU12IM_4J12p0ETA25";

  auto cgL1_4b_3j1j = m_trigDecTool->isPassed(trigL1_4b_3j1j);
  auto cgL1_RD0_filled = m_trigDecTool->isPassed(trigL1_RD0_filled);
  auto cHLT_tau0_J25 = m_trigDecTool->isPassed(tau0_J25);
  auto cHLT_tau0_4J12 = m_trigDecTool->isPassed(tau0_4J12);
  auto cHLT_4J12_idperf = m_trigDecTool->isPassed(idperf_4J12);
  auto cHLT_J25_idperf = m_trigDecTool->isPassed(idperf_J25);


  if (!cgL1_4b_3j1j){L1_4b_3j1j = false;} 
  else {L1_4b_3j1j = true;}
  if (!cgL1_RD0_filled){L1_RD0_filled = false;} 
  else {L1_RD0_filled = true;}

  if (!cHLT_tau0_J25) {HLT_tau0_J25 = false;} 
  else {HLT_tau0_J25 = true;}
  if (!cHLT_tau0_4J12) {HLT_tau0_4J12 = false;} 
  else {HLT_tau0_4J12 = true;}
  if (!cHLT_4J12_idperf) {HLT_4J12_idperf = false;} 
  else {HLT_4J12_idperf = true;}
  if (!cHLT_J25_idperf) {HLT_J25_idperf = false;} 
  else {HLT_J25_idperf = true;}


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //b jets

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // const xAOD::JetContainer* hltjets = nullptr;
  // CHECK( evtStore()->retrieve( hltjets , "HLT_AntiKt4EMPFlowJets_subresjesgscIS_ftf_bJets" ) );


  // // SG::AuxElement::ConstAccessor<ElementLink<xAOD::BTaggingContainer>> acc_btag_link("btaggingLink");
  // // SG::AuxElement::ConstAccessor<float> acc_reco_pb("DL1dv01_pb");
  // // SG::AuxElement::ConstAccessor<float> acc_reco_pc("DL1dv01_pc");
  // // SG::AuxElement::ConstAccessor<float> acc_reco_pu("DL1dv01_pu");
 
  // //Here we work with Online HLT Jets
  // ATH_MSG_DEBUG ("HLT jets: " << hltjets->size() << "...");
  // m_non_hltJet->clear();
  // m_on_hltjet->clear();
  // m_on_hltjetjvtlist->clear();
  // m_on_hltjetdl1dblist->clear();
  // m_on_hltjetdl1dclist->clear();
  // m_on_hltjetdl1dulist->clear();
  // m_on_hltjetGN1blist->clear();
  // m_on_hltjetGN1clist->clear();
  // m_on_hltjetGN1ulist->clear();
  // int countonJet = 0;

  // // // using DL1d20211216 from https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/Trigger/TrigHypothesis/TrigBjetHypo/python/TrigBjetBtagHypoTool.py#0108
  // // SG::AuxElement::ConstAccessor<float> acc_hlt_pb("DL1d20211216_pb");
  // // SG::AuxElement::ConstAccessor<float> acc_hlt_pc("DL1d20211216_pc");
  // // SG::AuxElement::ConstAccessor<float> acc_hlt_pu("DL1d20211216_pu"); 
  // // SG::AuxElement::ConstAccessor<float> acc_hlt_gn1_pb("GN120220813_pb");
  // // SG::AuxElement::ConstAccessor<float> acc_hlt_gn1_pc("GN120220813_pc");
  // // SG::AuxElement::ConstAccessor<float> acc_hlt_gn1_pu("GN120220813_pu");

  // for (auto hltjet : *hltjets) {
  //   if (hltjet->pt() * 0.001 < 10.) continue; 

  //   TLorentzVector onjetHLT; 
  //   onjetHLT.SetPtEtaPhiM(hltjet->pt() * 0.001, hltjet->eta(), hltjet->phi(), 0);
  //   m_on_hltjet->push_back(onjetHLT); //it contains the kinematic of the jet
  //   m_on_hltjetjvtlist->push_back(hltjet->auxdata<float>("Jvt"));
  //   // ElementLink<xAOD::BTaggingContainer> btag = acc_btag_link(*hltjet);
  //   // m_on_hltjetdl1dblist->push_back(acc_hlt_pb(**btag));
  //   // m_on_hltjetdl1dclist->push_back(acc_hlt_pc(**btag));
  //   // m_on_hltjetdl1dulist->push_back(acc_hlt_pu(**btag));
  //   // m_on_hltjetGN1blist->push_back(acc_hlt_gn1_pb(**btag));
  //   // m_on_hltjetGN1clist->push_back(acc_hlt_gn1_pc(**btag));
  //   // m_on_hltjetGN1ulist->push_back(acc_hlt_gn1_pu(**btag));
  //   countonJet ++;
  // }

  // //Outside Jet for loop do sorting (without truth matching)
  // TLorentzVector on_hltjet;
  // float on_jvt, on_dl1db, on_dl1dc, on_dl1du, on_gn1b, on_gn1c, on_gn1u;
  // for ( int i =0 ; i < (int)m_on_hltjet->size() - 1; i++){
  //   for (int j = i + 1; j < (int)m_on_hltjet->size(); j++){
  //     if (m_on_hltjet->at(i).Pt()<m_on_hltjet->at(j).Pt()){
  //       on_hltjet = m_on_hltjet->at(i);
  //       m_on_hltjet->at(i) = m_on_hltjet->at(j);
  //       m_on_hltjet->at(j) = on_hltjet; 

  //       on_jvt = m_on_hltjetjvtlist->at(i);
  //       m_on_hltjetjvtlist->at(i) = m_on_hltjetjvtlist->at(j);
  //       m_on_hltjetjvtlist->at(j) = on_jvt;

  //       on_dl1db = m_on_hltjetdl1dblist->at(i);
  //       m_on_hltjetdl1dblist->at(i) = m_on_hltjetdl1dblist->at(j);
  //       m_on_hltjetdl1dblist->at(j) = on_dl1db;

  //       on_dl1dc = m_on_hltjetdl1dclist->at(i);
  //       m_on_hltjetdl1dclist->at(i) = m_on_hltjetdl1dclist->at(j);
  //       m_on_hltjetdl1dclist->at(j) = on_dl1dc;

  //       on_dl1du = m_on_hltjetdl1dulist->at(i);
  //       m_on_hltjetdl1dulist->at(i) = m_on_hltjetdl1dulist->at(j);
  //       m_on_hltjetdl1dulist->at(j) = on_dl1du;

  //       on_gn1b = m_on_hltjetGN1blist->at(i);
  //       m_on_hltjetGN1blist->at(i) = m_on_hltjetGN1blist->at(j);
  //       m_on_hltjetGN1blist->at(j) = on_gn1b;

  //       on_gn1c = m_on_hltjetGN1clist->at(i);
  //       m_on_hltjetGN1clist->at(i) = m_on_hltjetGN1clist->at(j);
  //       m_on_hltjetGN1clist->at(j) = on_gn1c;

  //       on_gn1u = m_on_hltjetGN1ulist->at(i);
  //       m_on_hltjetGN1ulist->at(i) = m_on_hltjetGN1ulist->at(j);
  //       m_on_hltjetGN1ulist->at(j) = on_gn1u;
  //     }
  //   }
  // }
  // m_non_hltJet->push_back(countonJet); 





  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //TrigDefs::includeFailedDecisions pT trigger

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
  std::string tauContainerName = "HLT_TrigTauRecMerged_MVA";
 

  //TrigDefs::includeFailedDecisions pT trigger
    
  auto vec_idperf = m_trigDecTool->features<xAOD::TauJetContainer>(idperf_J25, TrigDefs::includeFailedDecisions ,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto vec = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTptTau0, TrigDefs::Physics,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  // auto vec = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTptr22, TrigDefs::includeFailedDecisions ,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto vec = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTptr22, TrigDefs::Physics,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
 
  m_on_HLTptfl_perf->clear();
  m_on_idvlHLTptfl_perf->clear();
  m_on_idlHLTptfl_perf->clear();
  m_on_idmHLTptfl_perf->clear();
  m_on_idtHLTptfl_perf->clear();
  m_on_prngHLTptfl_perf->clear();
  m_on_rnnHLTptfl_perf->clear();
  m_non_HLTptfl_perf->clear();
  m_on_HLTptflag_perf->clear();
  int countonhltptfl_perf = 0;
  
  for (auto& featLinkInfo : vec_idperf){
    const auto *feat = *(featLinkInfo.link);
    if(!feat) continue; 
    if (feat->pt() * 0.001 < 10.) continue;
    TLorentzVector ontauhltptfl_perf; 
    ontauhltptfl_perf.SetPtEtaPhiM(feat->pt() * 0.001, feat->eta(), feat->phi(), 0);
    m_on_HLTptfl_perf->push_back(ontauhltptfl_perf);
    m_on_rnnHLTptfl_perf->push_back(feat->discriminant(xAOD::TauJetParameters::TauID::RNNJetScoreSigTrans));
    m_on_prngHLTptfl_perf->push_back(feat->nTracks());
    m_on_idvlHLTptfl_perf->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigVeryLoose));
    m_on_idlHLTptfl_perf->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
    m_on_idmHLTptfl_perf->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
    m_on_idtHLTptfl_perf->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigTight));
  
    if (feat->pt() * 0.001 < 280.) {
      m_on_HLTptflag_perf->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
    } else if ( feat->pt() * 0.001 >= 280.  &&  feat->pt() * 0.001 < 440.) {
      m_on_HLTptflag_perf->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
    } else if (feat->pt() * 0.001 >= 440){
      m_on_HLTptflag_perf->push_back(1);
    }
    countonhltptfl_perf ++;
  }
  // ANA_MSG_INFO("After pt loop. Now sorting...");

  //Sorting 
  TLorentzVector ontmpmtau_hltptfl_perf;
  bool ontmpmtauIDvl_hltptfl_perf, ontmpmtauIDl_hltptfl_perf, ontmpmtauIDm_hltptfl_perf, ontmpmtauIDt_hltptfl_perf, ontmp_hltptflag_perf; 
  size_t ontmp_mprong_hltptfl_perf; 
  float ontmp_mrnn_hltptfl_perf;
  for ( int i =0 ; i < (int)m_on_HLTptfl_perf->size() - 1; i++){
    for (int j = i + 1; j < (int)m_on_HLTptfl_perf->size(); j++){
      if (m_on_HLTptfl_perf->at(i).Pt()<m_on_HLTptfl_perf->at(j).Pt()){
        ontmpmtau_hltptfl_perf = m_on_HLTptfl_perf->at(i);
        m_on_HLTptfl_perf->at(i) = m_on_HLTptfl_perf->at(j);
        m_on_HLTptfl_perf->at(j) = ontmpmtau_hltptfl_perf; 

        ontmpmtauIDvl_hltptfl_perf = m_on_idvlHLTptfl_perf->at(i);
        m_on_idvlHLTptfl_perf->at(i) = m_on_idvlHLTptfl_perf->at(j);
        m_on_idvlHLTptfl_perf->at(j) = ontmpmtauIDvl_hltptfl_perf;

        ontmpmtauIDl_hltptfl_perf = m_on_idlHLTptfl_perf->at(i);
        m_on_idlHLTptfl_perf->at(i) = m_on_idlHLTptfl_perf->at(j);
        m_on_idlHLTptfl_perf->at(j) = ontmpmtauIDl_hltptfl_perf;

        ontmpmtauIDm_hltptfl_perf = m_on_idmHLTptfl_perf->at(i);
        m_on_idmHLTptfl_perf->at(i) = m_on_idmHLTptfl_perf->at(j);
        m_on_idmHLTptfl_perf->at(j) = ontmpmtauIDm_hltptfl_perf;

        ontmpmtauIDt_hltptfl_perf = m_on_idtHLTptfl_perf->at(i);
        m_on_idtHLTptfl_perf->at(i) = m_on_idtHLTptfl_perf->at(j);
        m_on_idtHLTptfl_perf->at(j) = ontmpmtauIDt_hltptfl_perf;

        ontmp_mprong_hltptfl_perf = m_on_prngHLTptfl_perf->at(i);
        m_on_prngHLTptfl_perf->at(i) = m_on_prngHLTptfl_perf->at(j);
        m_on_prngHLTptfl_perf->at(j) = ontmp_mprong_hltptfl_perf;

        ontmp_mrnn_hltptfl_perf = m_on_rnnHLTptfl_perf->at(i);
        m_on_rnnHLTptfl_perf->at(i) = m_on_rnnHLTptfl_perf->at(j);
        m_on_rnnHLTptfl_perf->at(j) = ontmp_mrnn_hltptfl_perf;

        ontmp_hltptflag_perf = m_on_HLTptflag_perf->at(i);
        m_on_HLTptflag_perf->at(i) = m_on_HLTptflag_perf->at(j);
        m_on_HLTptflag_perf->at(j) = ontmp_hltptflag_perf;

      }
    }
  }
  m_non_HLTptfl_perf->push_back(countonhltptfl_perf);

  
   
  //TrigDefs::includeFailedDecisions eta trigger
  auto veceta_idperf = m_trigDecTool->features<xAOD::TauJetContainer>(idperf_4J12, TrigDefs::includeFailedDecisions ,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto veceta = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTetaTau0, TrigDefs::Physics,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  // auto veceta = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTetar22, TrigDefs::includeFailedDecisions,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto veceta = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTetar22, TrigDefs::Physics,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  m_on_HLTetafl_perf->clear();
  m_on_idvlHLTetafl_perf->clear();
  m_on_idlHLTetafl_perf->clear();
  m_on_idmHLTetafl_perf->clear();
  m_on_idtHLTetafl_perf->clear();
  m_on_prngHLTetafl_perf->clear();
  m_on_rnnHLTetafl_perf->clear();
  m_non_HLTetafl_perf->clear();
  m_on_HLTetaflag_perf->clear();
  int countonhltetafl_perf = 0;
  // ANA_MSG_INFO("Before eta loop");
  for (auto& featLinkInfo_eta : veceta_idperf){
    const auto *feat_eta = *(featLinkInfo_eta.link);
    if(!feat_eta) continue; 
    //ANA_MSG_INFO("Inside Loop");
    //ANA_MSG_INFO("Tau feat pT: "<< feat_eta->pt() * 0.001);
    if (feat_eta->pt() * 0.001 < 10.) continue;
    TLorentzVector ontauhltetafl_perf; 
    ontauhltetafl_perf.SetPtEtaPhiM(feat_eta->pt() * 0.001, feat_eta->eta(), feat_eta->phi(), 0);
    m_on_HLTetafl_perf->push_back(ontauhltetafl_perf);
    m_on_prngHLTetafl_perf->push_back(feat_eta->nTracks());
    m_on_rnnHLTetafl_perf->push_back(feat_eta->discriminant(xAOD::TauJetParameters::TauID::RNNJetScoreSigTrans)); 
    m_on_idvlHLTetafl_perf->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigVeryLoose));
    m_on_idlHLTetafl_perf->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
    m_on_idmHLTetafl_perf->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
    m_on_idtHLTetafl_perf->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigTight));
    if (feat_eta->pt() * 0.001 < 280.) {
      m_on_HLTetaflag_perf->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
    } else if ( feat_eta->pt() * 0.001 >= 280.  &&  feat_eta->pt() * 0.001 < 440.) {
      m_on_HLTetaflag_perf->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
    } else if (feat_eta->pt() * 0.001 >= 440){
      m_on_HLTetaflag_perf->push_back(1);
    }
    countonhltetafl_perf ++;
  }
  // ANA_MSG_INFO("After eta loop. Now sorting...");
  //Sorting 
  TLorentzVector ontmpmtau_hltetafl_perf;
  bool ontmpmtauIDvl_hltetafl_perf, ontmpmtauIDl_hltetafl_perf, ontmpmtauIDm_hltetafl_perf, ontmpmtauIDt_hltetafl_perf, ontmp_hltetaflag_perf;
  size_t ontmp_mprong_hltetafl_perf; 
  float ontmp_mrnn_hltetafl_perf;
  for ( int i =0 ; i < (int)m_on_HLTetafl_perf->size() - 1; i++){
    for (int j = i + 1; j < (int)m_on_HLTetafl_perf->size(); j++){
      if (m_on_HLTetafl_perf->at(i).Pt()<m_on_HLTetafl_perf->at(j).Pt()){
        ontmpmtau_hltetafl_perf = m_on_HLTetafl_perf->at(i);
        m_on_HLTetafl_perf->at(i) = m_on_HLTetafl_perf->at(j);
        m_on_HLTetafl_perf->at(j) = ontmpmtau_hltetafl_perf; 

        ontmpmtauIDvl_hltetafl_perf = m_on_idvlHLTetafl_perf->at(i);
        m_on_idvlHLTetafl_perf->at(i) = m_on_idvlHLTetafl_perf->at(j);
        m_on_idvlHLTetafl_perf->at(j) = ontmpmtauIDvl_hltetafl_perf;

        ontmpmtauIDl_hltetafl_perf = m_on_idlHLTetafl_perf->at(i);
        m_on_idlHLTetafl_perf->at(i) = m_on_idlHLTetafl_perf->at(j);
        m_on_idlHLTetafl_perf->at(j) = ontmpmtauIDl_hltetafl_perf;

        ontmpmtauIDm_hltetafl_perf = m_on_idmHLTetafl_perf->at(i);
        m_on_idmHLTetafl_perf->at(i) = m_on_idmHLTetafl_perf->at(j);
        m_on_idmHLTetafl_perf->at(j) = ontmpmtauIDm_hltetafl_perf;

        ontmpmtauIDt_hltetafl_perf = m_on_idtHLTetafl_perf->at(i);
        m_on_idtHLTetafl_perf->at(i) = m_on_idtHLTetafl_perf->at(j);
        m_on_idtHLTetafl_perf->at(j) = ontmpmtauIDt_hltetafl_perf;

        ontmp_mprong_hltetafl_perf = m_on_prngHLTetafl_perf->at(i);
        m_on_prngHLTetafl_perf->at(i) = m_on_prngHLTetafl_perf->at(j);
        m_on_prngHLTetafl_perf->at(j) = ontmp_mprong_hltetafl_perf;

        ontmp_mrnn_hltetafl_perf = m_on_rnnHLTetafl_perf->at(i);
        m_on_rnnHLTetafl_perf->at(i) = m_on_rnnHLTetafl_perf->at(j);
        m_on_rnnHLTetafl_perf->at(j) = ontmp_mrnn_hltetafl_perf;

        ontmp_hltetaflag_perf = m_on_HLTetaflag_perf->at(i);
        m_on_HLTetaflag_perf->at(i) = m_on_HLTetaflag_perf->at(j);
        m_on_HLTetaflag_perf->at(j) = ontmp_hltetaflag_perf;
      }
    }
  }
  m_non_HLTetafl_perf->push_back(countonhltetafl_perf);




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //Online Taus
  const xAOD::TauJetContainer* ontaus = nullptr; 
  ANA_CHECK (evtStore()->retrieve (ontaus, "HLT_TrigTauRecMerged_MVA")); //r22: HLT_TrigTauRecMerged_MVA, r21: HLT_xAOD__TauJetContainer_TrigTauRecMerged
  //ANA_CHECK (evtStore()->retrieve (ontaus, "HLT_tau35_perf_tracktwo_tau25_perf_tracktwo"));
  //Clear Vectors
  m_non_TrigTRM->clear();
  m_on_TrigTRM->clear();
  m_on_idvlTrigTRM->clear();
  m_on_idlTrigTRM->clear();
  m_on_idmTrigTRM->clear();
  m_on_idtTrigTRM->clear();
  m_on_prngTrigTRM->clear();
  m_on_rnnTrigTRM->clear();

  int countonTRM = 0;

  for (auto ontau : *ontaus){
    if (ontau->pt() * 0.001 < 0) continue; 

    TLorentzVector ontauTRM; 
    ontauTRM.SetPtEtaPhiM(ontau->pt() * 0.001, ontau->eta(), ontau->phi(), 0);
    m_on_TrigTRM->push_back(ontauTRM);
    m_on_idvlTrigTRM->push_back(ontau->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigVeryLoose));
    m_on_idlTrigTRM->push_back(ontau->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
    m_on_idmTrigTRM->push_back(ontau->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
    m_on_idtTrigTRM->push_back(ontau->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigTight));
    m_on_prngTrigTRM->push_back(ontau->nTracks());
    m_on_rnnTrigTRM->push_back(ontau->discriminant(xAOD::TauJetParameters::TauID::RNNJetScoreSigTrans));
    countonTRM++;
  }

  // Outside Tau for loop do sorting (without truth matching)
  TLorentzVector ontrmtau;
  bool ontrmtauIDvl, ontrmtauIDl, ontrmtauIDm, ontrmtauIDt; 
  size_t ontrm_prong; 
  float ontrm_rnn;
  for ( int i =0 ; i < (int)m_on_TrigTRM->size() - 1; i++){
    for (int j = i + 1; j < (int)m_on_TrigTRM->size(); j++){
      if (m_on_TrigTRM->at(i).Pt()<m_on_TrigTRM->at(j).Pt()){
        ontrmtau = m_on_TrigTRM->at(i);
        m_on_TrigTRM->at(i) = m_on_TrigTRM->at(j);
        m_on_TrigTRM->at(j) = ontrmtau; 

        ontrmtauIDvl = m_on_idvlTrigTRM->at(i);
        m_on_idvlTrigTRM->at(i) = m_on_idvlTrigTRM->at(j);
        m_on_idvlTrigTRM->at(j) = ontrmtauIDvl;

        ontrmtauIDl = m_on_idlTrigTRM->at(i);
        m_on_idlTrigTRM->at(i) = m_on_idlTrigTRM->at(j);
        m_on_idlTrigTRM->at(j) = ontrmtauIDl;

        ontrmtauIDm = m_on_idmTrigTRM->at(i);
        m_on_idmTrigTRM->at(i) = m_on_idmTrigTRM->at(j);
        m_on_idmTrigTRM->at(j) = ontrmtauIDm;

        ontrmtauIDt = m_on_idtTrigTRM->at(i);
        m_on_idtTrigTRM->at(i) = m_on_idtTrigTRM->at(j);
        m_on_idtTrigTRM->at(j) = ontrmtauIDt;

        ontrm_prong = m_on_prngTrigTRM->at(i);
        m_on_prngTrigTRM->at(i) = m_on_prngTrigTRM->at(j);
        m_on_prngTrigTRM->at(j) = ontrm_prong;

        ontrm_rnn = m_on_rnnTrigTRM->at(i);
        m_on_rnnTrigTRM->at(i) = m_on_rnnTrigTRM->at(j);
        m_on_rnnTrigTRM->at(j) = ontrm_rnn;
      }
    }
  }
  // ANA_MSG_INFO("Online taus added. Now adding offline taus (requires truthmatching)");

  m_non_TrigTRM->push_back(countonTRM); 

  
  const xAOD::EventInfo * eventInfo = nullptr;
  ANA_CHECK (evtStore()->retrieve(eventInfo, "EventInfo"));


  bool isMC = false;
  if(eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION)){ isMC = true; } // for truth containers 
  
  if (isMC) {
  const xAOD::TauJetContainer* taus = nullptr; 
  ANA_CHECK (evtStore()->retrieve (taus, "TauJets"));
  
  //Clear the vectors 
  //Taus with matching
  m_noff_mtaus->clear();
  m_off_mtaus->clear();
  m_off_mtaus->clear();
  m_off_mtauIDvl->clear();
  m_off_mtauIDl->clear();
  m_off_mtauIDm->clear();
  m_off_mtauIDt->clear();
  m_off_mprong->clear();
  m_off_mrnn->clear();

  int countmoff = 0;
  for (auto tau : *taus){ //replaced const xAOD::TauJet* with auto 
      if (tau->pt() * 0.001 < 10.) continue; 
      //ANA_MSG_INFO ("in execute, tau pT = " << tau->pt() * 0.001 ); 
      //push back vectors
      TLorentzVector offtau; 
      offtau.SetPtEtaPhiM(tau->pt() * 0.001, tau->eta(), tau->phi(), 0);

      auto TruthTau = m_T2MT->getTruth(*tau);
      if (TruthTau){
        TLorentzVector offmatchtau;
        offmatchtau.SetPtEtaPhiM(tau->pt() * 0.001, tau->eta(), tau->phi(), 0);
        m_off_mtaus->push_back(offmatchtau);
        m_off_mtauIDvl->push_back(tau->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigVeryLoose));
        m_off_mtauIDl->push_back(tau->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
        m_off_mtauIDm->push_back(tau->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
        m_off_mtauIDt->push_back(tau->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigTight));
        m_off_mprong->push_back(tau->nTracks());
        m_off_mrnn->push_back(tau->discriminant(xAOD::TauJetParameters::TauID::RNNJetScoreSigTrans));
        countmoff++;
      }
  }
  // Outside Tau for loop do sorting (WITH matching)
  TLorentzVector tmpmtau;
  bool tmpmtauIDvl, tmpmtauIDl, tmpmtauIDm, tmpmtauIDt; 
  size_t tmp_mprong; 
  float tmp_mrnn;
  for ( int i =0 ; i < (int)m_off_mtaus->size() - 1; i++){
    for (int j = i + 1; j < (int)m_off_mtaus->size(); j++){
      if (m_off_mtaus->at(i).Pt()<m_off_mtaus->at(j).Pt()){
        tmpmtau = m_off_mtaus->at(i);
        m_off_mtaus->at(i) = m_off_mtaus->at(j);
        m_off_mtaus->at(j) = tmpmtau; 

        tmpmtauIDvl = m_off_mtauIDvl->at(i);
        m_off_mtauIDvl->at(i) = m_off_mtauIDvl->at(j);
        m_off_mtauIDvl->at(j) = tmpmtauIDvl;

        tmpmtauIDl = m_off_mtauIDl->at(i);
        m_off_mtauIDl->at(i) = m_off_mtauIDl->at(j);
        m_off_mtauIDl->at(j) = tmpmtauIDl;

        tmpmtauIDm = m_off_mtauIDm->at(i);
        m_off_mtauIDm->at(i) = m_off_mtauIDm->at(j);
        m_off_mtauIDm->at(j) = tmpmtauIDm;

        tmpmtauIDt = m_off_mtauIDt->at(i);
        m_off_mtauIDt->at(i) = m_off_mtauIDt->at(j);
        m_off_mtauIDt->at(j) = tmpmtauIDt;

        tmp_mprong = m_off_mprong->at(i);
        m_off_mprong->at(i) = m_off_mprong->at(j);
        m_off_mprong->at(j) = tmp_mprong;

        tmp_mrnn = m_off_mrnn->at(i);
        m_off_mrnn->at(i) = m_off_mrnn->at(j);
        m_off_mrnn->at(j) = tmp_mrnn;
      }
    }
  }
  
  m_noff_mtaus->push_back(countmoff);

}



  ANA_CHECK (evtStore()->retrieve(eventInfo, "EventInfo"));
  m_eventNumber = eventInfo->eventNumber();
  
  // Fill the event into the tree:

 
  
  tree ("analysis")->Fill();
  return StatusCode::SUCCESS;

}



StatusCode MyxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.
  //ANA_MSG_INFO ("in fin/alize");
  return StatusCode::SUCCESS;
}
