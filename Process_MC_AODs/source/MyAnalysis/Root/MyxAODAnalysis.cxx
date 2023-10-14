//#include <AsgTools/MessageCheck.h> //include for r21
#include <AsgTools/MessageCheckAsgTools.h> //include for r22
#include <MyAnalysis/MyxAODAnalysis.h>

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
  //delete m_actualBC;
  //delete m_aveBC;
  
  delete m_non_hltJet;
  delete m_on_hltjet;
  delete m_on_hltjetjvtlist;
  delete m_on_hltjetdl1dblist;
  delete m_on_hltjetdl1dclist;
  delete m_on_hltjetdl1dulist;
  delete m_on_hltjetGN1blist;
  delete m_on_hltjetGN1clist;
  delete m_on_hltjetGN1ulist;

  delete m_noff_mtaus;
  delete m_off_mtaus;
  delete m_off_mtauIDvl;
  delete m_off_mtauIDl; 
  delete m_off_mtauIDm; 
  delete m_off_mtauIDt;
  delete m_off_mprong;
  delete m_off_mrnn;

  delete m_non_HLTptfl;
  delete m_on_HLTptfl;
  delete m_on_idvlHLTptfl;
  delete m_on_idlHLTptfl; 
  delete m_on_idmHLTptfl; 
  delete m_on_idtHLTptfl;
  delete m_on_prngHLTptfl;
  delete m_on_rnnHLTptfl;
  delete m_on_HLTptflag;

  delete m_non_HLTetafl;
  delete m_on_HLTetafl;
  delete m_on_idvlHLTetafl;
  delete m_on_idlHLTetafl; 
  delete m_on_idmHLTetafl; 
  delete m_on_idtHLTetafl;
  delete m_on_prngHLTetafl;
  delete m_on_rnnHLTetafl;
  delete m_on_HLTetaflag;

  delete m_non_TrigTRM;
  delete m_on_TrigTRM; 
  delete m_on_idvlTrigTRM;
  delete m_on_idlTrigTRM; 
  delete m_on_idmTrigTRM; 
  delete m_on_idtTrigTRM; 
  delete m_on_prngTrigTRM;
  delete m_on_rnnTrigTRM;
  
  delete m_on_truthmHH;

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
  //mytree->Branch ("EventNumber", &m_eventNumber);
  //m_actualBC = new std::vector<float>();
  //mytree->Branch ("ActualBC", &m_actualBC);
  //m_aveBC = new std::vector<float>();
  //mytree->Branch ("AveBC", &m_aveBC);

  //Triggers

  mytree->Branch("L1_J25", &L1_trig_pt);
  mytree->Branch("L1_ETA25", &L1_trig_eta);
  mytree->Branch("HLT_J25_r22", &HLT_trig_ptr22);
  mytree->Branch("HLT_ETA25_r22", &HLT_trig_etar22);
  mytree->Branch("HLT_J25_Tau0", &HLT_trig_ptTau0);
  mytree->Branch("HLT_ETA25_Tau0", &HLT_trig_etaTau0);
  mytree->Branch("HLT_J25_idperf", &HLT_trig_ptidperf);
  mytree->Branch("HLT_4J12_idperf", &HLT_trig_etaidperf);
  
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

  m_non_HLTptfl = new std::vector<int>(); 
  mytree->Branch("Num_TrigMatched_Taus_HLTptfl", &m_non_HLTptfl);
  m_on_HLTptfl = new std::vector<TLorentzVector>();
  mytree->Branch ("TrigMatched_Taus_HLTptfl", &m_on_HLTptfl);
  m_on_idvlHLTptfl = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDvl_HLTptfl", &m_on_idvlHLTptfl); 
  m_on_idlHLTptfl = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDl_HLTptfl", &m_on_idlHLTptfl);
  m_on_idmHLTptfl = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDm_HLTptfl", &m_on_idmHLTptfl);
  m_on_idtHLTptfl = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDt_HLTptfl", &m_on_idtHLTptfl);
  m_on_prngHLTptfl = new std::vector<size_t>();
  mytree->Branch ("TrigMatched_prong_HLTptfl", &m_on_prngHLTptfl);
  m_on_rnnHLTptfl = new std::vector<float>(); 
  mytree->Branch ("TrigMatched_rnn_HLTptfl", &m_on_rnnHLTptfl);
  m_on_HLTptflag = new std::vector<bool>();
  mytree->Branch ("TrigMatched_HLTptflag", &m_on_HLTptflag); 

  m_non_HLTetafl = new std::vector<int>(); 
  mytree->Branch("Num_TrigMatched_Taus_HLTetafl", &m_non_HLTetafl);
  m_on_HLTetafl = new std::vector<TLorentzVector>();
  mytree->Branch ("TrigMatched_Taus_HLTetafl", &m_on_HLTetafl);
  m_on_idvlHLTetafl = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDvl_HLTetafl", &m_on_idvlHLTetafl);
  m_on_idlHLTetafl = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDl_HLTetafl", &m_on_idlHLTetafl);
  m_on_idmHLTetafl = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDm_HLTetafl", &m_on_idmHLTetafl);
  m_on_idtHLTetafl = new std::vector<bool>();
  mytree->Branch ("TrigMatched_TauIDt_HLTetafl", &m_on_idtHLTetafl);
  m_on_prngHLTetafl = new std::vector<size_t>();
  mytree->Branch ("TrigMatched_prong_HLTetafl", &m_on_prngHLTetafl);
  m_on_rnnHLTetafl = new std::vector<float>(); 
  mytree->Branch ("TrigMatched_rnn_HLTetafl", &m_on_rnnHLTetafl);
  m_on_HLTetaflag = new std::vector<bool>();
  mytree->Branch ("TrigMatched_HLTetaflag", &m_on_HLTetaflag);


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


  //Initialize the mHH truth container
  m_on_truthmHH = new std::vector<float>();
  mytree->Branch ("Truth_mHH", &m_on_truthmHH);
  mytree->Branch ("truthmHH", &m_truthmHH);
  mytree->Branch ("nH", &m_nH);
  mytree->Branch ("status", &m_status);
  
  return StatusCode::SUCCESS;
}

StatusCode MyxAODAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  //ANA_MSG_INFO ("in execute");
 
  // Try to include the truth container

  
  const xAOD::EventInfo * eventInfo = nullptr;
  ANA_CHECK(evtStore()->retrieve(eventInfo, "EventInfo"));

  // print out run and event number from retrieved object
  bool isMC = false;
  if(eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION)){ isMC = true; } // for truth containers 

  //================
  // Truth Container 
  //================
  // std::cout<<"SASASA Event output"<<std::endl;
  const xAOD::TruthParticleContainer* truthParticle = 0;
  const xAOD::TruthVertexContainer* truthVertices(nullptr);
  if (isMC) { ANA_CHECK(evtStore()->retrieve(truthParticle, "TruthParticles")); }
  if (isMC) { ANA_CHECK(evtStore()->retrieve(truthVertices, "TruthVertices")); }

  const xAOD::TruthParticle *h0 = nullptr;
  const xAOD::TruthParticle *h1 = nullptr;
  m_truthmHH = 0 ;
  m_nH = 0 ;

  // Add and fill truth containers
  if (isMC) {
    for (xAOD::TruthParticleContainer::const_iterator part=truthParticle->begin(); part!=truthParticle->end(); part++) {
      
      if ( TMath::Abs( (*part)->pdgId()) != 25) continue ;
      
      //std::cout<<std::to_string((*part)->status())<<std::endl;
 
      //if ( (*part)->status() != 1) continue; 
      //std::cout<<"stable";
      //std::cout<<std::to_string((*part)->status())<<std::endl;
      m_nH++;
      if (m_nH<5) continue;

      m_on_truthmHH->push_back((*part)->status());
      if (!h0) { 
        h0 = (*part);
      }
      else if ( !h1 ) { 
        h1 = (*part); 
      }
      else{
        //ANA_MSG_INFO ("More than 2 Higgs found"); 
        continue; 
      }
   
      if ( h0 != nullptr && h1 != nullptr ){
        m_truthmHH = (h0->p4() + h1->p4()).M() ;
      }
    }
  }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRIGGER DECISION //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //L1 
  L1_trig_pt = false; 
  L1_trig_eta = false; 

  //HLT
  HLT_trig_ptr22 = false;
  HLT_trig_etar22 = false;
  HLT_trig_ptTau0 = false;
  HLT_trig_etaTau0 = false;
 
  // L1 Trigger
  const std::string trigL1pT="L1_DR-TAU20ITAU12I-J25";
  const std::string trigL1eta="L1_TAU20IM_2TAU12IM_4J12.0ETA25";

  // HLT Trigger
  const std::string trigHLTptr22="HLT_tau35_mediumRNN_tracktwoMVA_tau25_mediumRNN_tracktwoMVA_03dRAB30_L1DR-TAU20ITAU12I-J25";
  const std::string trigHLTetar22="HLT_tau35_mediumRNN_tracktwoMVA_tau25_mediumRNN_tracktwoMVA_03dRAB_L1TAU20IM_2TAU12IM_4J12p0ETA25";
  const std::string trigHLTptTau0="HLT_tau0_mediumRNN_tracktwoMVA_tau0_mediumRNN_tracktwoMVA_03dRAB30_L1DR-TAU20ITAU12I-J25";
  const std::string trigHLTetaTau0="HLT_tau0_mediumRNN_tracktwoMVA_tau0_mediumRNN_tracktwoMVA_03dRAB_L1TAU20IM_2TAU12IM_4J12p0ETA25";
  const std::string trigHLTptidperf ="HLT_tau30_idperf_tracktwoMVA_tau20_idperf_tracktwoMVA_03dRAB30_L1DR-TAU20ITAU12I-J25";
  const std::string trigHLTetaidperf="HLT_tau30_idperf_tracktwoMVA_tau20_idperf_tracktwoMVA_03dRAB_L1TAU20IM_2TAU12IM_4J12p0ETA25";
  // L1 Trigger Decision
  auto cgL1pT = m_trigDecTool->isPassed(trigL1pT);
  auto cgL1eta = m_trigDecTool->isPassed(trigL1eta);

  // HLT Trigger Decision
  auto cgHLTpT = m_trigDecTool->isPassed(trigHLTptr22);
  auto cgHLTeta = m_trigDecTool->isPassed(trigHLTetar22);
  auto cgHLTpTtau0 = m_trigDecTool->isPassed(trigHLTptTau0);
  auto cgHLTetatau0 = m_trigDecTool->isPassed(trigHLTetaTau0);
  auto cgHLTpTidperf = m_trigDecTool->isPassed(trigHLTptidperf);
  auto cgHLTetaidperf = m_trigDecTool->isPassed(trigHLTetaidperf);

  if (!cgL1pT) {
    L1_trig_pt = false;
  } else {
    L1_trig_pt = true;
  }
  if (!cgL1eta) {
    L1_trig_eta = false;
  } else {
    L1_trig_eta = true; 
  }


  if (!cgHLTpT) {
    HLT_trig_ptr22 = false; 
  } else {
    HLT_trig_ptr22 = true; 
  }
  if (!cgHLTeta) {
    HLT_trig_etar22 = false; 
  } else {
    HLT_trig_etar22 = true; 
  }
  if (!cgHLTpTtau0) {
    HLT_trig_ptTau0 = false; 
  } else {
    HLT_trig_ptTau0 = true; 
  }
  if (!cgHLTetatau0) {
    HLT_trig_etaTau0 = false; 
  } else {
    HLT_trig_etaTau0 = true; 
  }
  
   if (!cgHLTpTidperf) {
    HLT_trig_ptidperf = false; 
  } else {
    HLT_trig_ptidperf = true; 
  }
  if (!cgHLTetaidperf) {
    HLT_trig_etaidperf = false; 
  } else {
    HLT_trig_etaidperf = true; 
  }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HLT jets and b tag info //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const xAOD::JetContainer* hltjets = nullptr;
CHECK( evtStore()->retrieve( hltjets , "HLT_AntiKt4EMPFlowJets_subresjesgscIS_ftf_bJets" ) );
SG::AuxElement::ConstAccessor<ElementLink<xAOD::BTaggingContainer>> acc_btag_link("btaggingLink");
SG::AuxElement::ConstAccessor<float> acc_hlt_pb("DL1d20211216_pb");
SG::AuxElement::ConstAccessor<float> acc_hlt_pc("DL1d20211216_pc");
SG::AuxElement::ConstAccessor<float> acc_hlt_pu("DL1d20211216_pu"); 
SG::AuxElement::ConstAccessor<float> acc_hlt_gn1_pb("GN120220813_pb");
SG::AuxElement::ConstAccessor<float> acc_hlt_gn1_pc("GN120220813_pc");
SG::AuxElement::ConstAccessor<float> acc_hlt_gn1_pu("GN120220813_pu");

//Here we work with Online HLT Jets
ATH_MSG_DEBUG ("HLT jets: " << hltjets->size() << "...");
m_non_hltJet->clear();
m_on_hltjet->clear();
m_on_hltjetjvtlist->clear();
m_on_hltjetdl1dblist->clear();
m_on_hltjetdl1dclist->clear();
m_on_hltjetdl1dulist->clear();
m_on_hltjetGN1blist->clear();
m_on_hltjetGN1clist->clear();
m_on_hltjetGN1ulist->clear();
int countonJet = 0;

for (auto hltjet : *hltjets) {
  if (hltjet->pt() * 0.001 < 10.) continue; 

  TLorentzVector onjetHLT; 
  onjetHLT.SetPtEtaPhiM(hltjet->pt() * 0.001, hltjet->eta(), hltjet->phi(), 0);
  m_on_hltjet->push_back(onjetHLT); //it contains the kinematic of the jet
  m_on_hltjetjvtlist->push_back(hltjet->auxdata<float>("Jvt"));
  ElementLink<xAOD::BTaggingContainer> btag = acc_btag_link(*hltjet);
  m_on_hltjetdl1dblist->push_back(acc_hlt_pb(**btag));
  m_on_hltjetdl1dclist->push_back(acc_hlt_pc(**btag));
  m_on_hltjetdl1dulist->push_back(acc_hlt_pu(**btag));
  m_on_hltjetGN1blist->push_back(acc_hlt_gn1_pb(**btag));
  m_on_hltjetGN1clist->push_back(acc_hlt_gn1_pc(**btag));
  m_on_hltjetGN1ulist->push_back(acc_hlt_gn1_pu(**btag));
  countonJet ++;
}

//Outside Jet for loop do sorting (without truth matching)
TLorentzVector on_hltjet;
float on_jvt, on_dl1db, on_dl1dc, on_dl1du, on_gn1b, on_gn1c, on_gn1u;
for ( int i =0 ; i < (int)m_on_hltjet->size() - 1; i++){
  for (int j = i + 1; j < (int)m_on_hltjet->size(); j++){
    if (m_on_hltjet->at(i).Pt()<m_on_hltjet->at(j).Pt()){
      on_hltjet = m_on_hltjet->at(i);
      m_on_hltjet->at(i) = m_on_hltjet->at(j);
      m_on_hltjet->at(j) = on_hltjet; 

      on_jvt = m_on_hltjetjvtlist->at(i);
      m_on_hltjetjvtlist->at(i) = m_on_hltjetjvtlist->at(j);
      m_on_hltjetjvtlist->at(j) = on_jvt;

      on_dl1db = m_on_hltjetdl1dblist->at(i);
      m_on_hltjetdl1dblist->at(i) = m_on_hltjetdl1dblist->at(j);
      m_on_hltjetdl1dblist->at(j) = on_dl1db;

      on_dl1dc = m_on_hltjetdl1dclist->at(i);
      m_on_hltjetdl1dclist->at(i) = m_on_hltjetdl1dclist->at(j);
      m_on_hltjetdl1dclist->at(j) = on_dl1dc;

      on_dl1du = m_on_hltjetdl1dulist->at(i);
      m_on_hltjetdl1dulist->at(i) = m_on_hltjetdl1dulist->at(j);
      m_on_hltjetdl1dulist->at(j) = on_dl1du;

      on_gn1b = m_on_hltjetGN1blist->at(i);
      m_on_hltjetGN1blist->at(i) = m_on_hltjetGN1blist->at(j);
      m_on_hltjetGN1blist->at(j) = on_gn1b;

      on_gn1c = m_on_hltjetGN1clist->at(i);
      m_on_hltjetGN1clist->at(i) = m_on_hltjetGN1clist->at(j);
      m_on_hltjetGN1clist->at(j) = on_gn1c;

      on_gn1u = m_on_hltjetGN1ulist->at(i);
      m_on_hltjetGN1ulist->at(i) = m_on_hltjetGN1ulist->at(j);
      m_on_hltjetGN1ulist->at(j) = on_gn1u;
    }
  }
}
m_non_hltJet->push_back(countonJet); 



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// L1Topo trigger matched taus //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  //TrigDefs::includeFailedDecisions pT trigger
  std::string tauContainerName = "HLT_TrigTauRecMerged_MVA";
  auto vec = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTptidperf, TrigDefs::includeFailedDecisions ,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto vec = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTptTau0, TrigDefs::Physics,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto vec = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTptr22, TrigDefs::includeFailedDecisions ,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto vec = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTptr22, TrigDefs::Physics,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  m_on_HLTptfl->clear();
  m_on_idvlHLTptfl->clear();
  m_on_idlHLTptfl->clear();
  m_on_idmHLTptfl->clear();
  m_on_idtHLTptfl->clear();
  m_on_prngHLTptfl->clear();
  m_on_rnnHLTptfl->clear();
  m_non_HLTptfl->clear();
  m_on_HLTptflag->clear();
  int countonhltptfl = 0;
  //ANA_MSG_INFO("Before loop");
  for (auto& featLinkInfo : vec){
    const auto *feat = *(featLinkInfo.link);
    if(!feat) continue; 
    //ANA_MSG_INFO("Inside Loop");
    //ANA_MSG_INFO("Tau feat pT: "<< feat->pt() * 0.001);
    if (feat->pt() * 0.001 < 10.) continue;
    TLorentzVector ontauhltptfl; 
    ontauhltptfl.SetPtEtaPhiM(feat->pt() * 0.001, feat->eta(), feat->phi(), 0);
    m_on_HLTptfl->push_back(ontauhltptfl);
    // m_on_rnnHLTptfl->push_back(feat->discriminant(xAOD::TauJetParameters::TauID::RNNJetScoreSig));    // !!!!!!!!!!!!!!!!!!
    m_on_rnnHLTptfl->push_back(feat->discriminant(xAOD::TauJetParameters::TauID::RNNJetScoreSigTrans)); 
    m_on_prngHLTptfl->push_back(feat->nTracks());
    m_on_idvlHLTptfl->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigVeryLoose));
    m_on_idlHLTptfl->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
    m_on_idmHLTptfl->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
    m_on_idtHLTptfl->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigTight));
  
    if (feat->pt() * 0.001 < 280.) {
      m_on_HLTptflag->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
    } else if ( feat->pt() * 0.001 >= 280.  &&  feat->pt() * 0.001 < 440.) {
      m_on_HLTptflag->push_back(feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
    } else if (feat->pt() * 0.001 >= 440){
      m_on_HLTptflag->push_back(1);
    }
    countonhltptfl ++;
    //ANA_MSG_INFO("Online Taus Count: " << countonhltptfl);
    //ANA_MSG_INFO("m_on_HLTptfl" << feat->pt() * 0.001);
    //ANA_MSG_INFO("m_on_rnnHLTptfl" << feat->discriminant(xAOD::TauJetParameters::TauID::RNNJetScoreSigTrans));
    //ANA_MSG_INFO("m_on_prngHLTptfl" << feat->nTracks());
    //ANA_MSG_INFO("m_on_idmHLTptfl" << feat->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));

  }
  //Sorting 
  TLorentzVector ontmpmtau_hltptfl;
  bool ontmpmtauIDvl_hltptfl, ontmpmtauIDl_hltptfl, ontmpmtauIDm_hltptfl, ontmpmtauIDt_hltptfl, ontmp_hltptflag; 
  size_t ontmp_mprong_hltptfl; 
  float ontmp_mrnn_hltptfl;
  for ( int i =0 ; i < (int)m_on_HLTptfl->size() - 1; i++){
    for (int j = i + 1; j < (int)m_on_HLTptfl->size(); j++){
      if (m_on_HLTptfl->at(i).Pt()<m_on_HLTptfl->at(j).Pt()){
        ontmpmtau_hltptfl = m_on_HLTptfl->at(i);
        m_on_HLTptfl->at(i) = m_on_HLTptfl->at(j);
        m_on_HLTptfl->at(j) = ontmpmtau_hltptfl; 

        ontmpmtauIDvl_hltptfl = m_on_idvlHLTptfl->at(i);
        m_on_idvlHLTptfl->at(i) = m_on_idvlHLTptfl->at(j);
        m_on_idvlHLTptfl->at(j) = ontmpmtauIDvl_hltptfl;

        ontmpmtauIDl_hltptfl = m_on_idlHLTptfl->at(i);
        m_on_idlHLTptfl->at(i) = m_on_idlHLTptfl->at(j);
        m_on_idlHLTptfl->at(j) = ontmpmtauIDl_hltptfl;

        ontmpmtauIDm_hltptfl = m_on_idmHLTptfl->at(i);
        m_on_idmHLTptfl->at(i) = m_on_idmHLTptfl->at(j);
        m_on_idmHLTptfl->at(j) = ontmpmtauIDm_hltptfl;

        ontmpmtauIDt_hltptfl = m_on_idtHLTptfl->at(i);
        m_on_idtHLTptfl->at(i) = m_on_idtHLTptfl->at(j);
        m_on_idtHLTptfl->at(j) = ontmpmtauIDt_hltptfl;

        ontmp_mprong_hltptfl = m_on_prngHLTptfl->at(i);
        m_on_prngHLTptfl->at(i) = m_on_prngHLTptfl->at(j);
        m_on_prngHLTptfl->at(j) = ontmp_mprong_hltptfl;

        ontmp_mrnn_hltptfl = m_on_rnnHLTptfl->at(i);
        m_on_rnnHLTptfl->at(i) = m_on_rnnHLTptfl->at(j);
        m_on_rnnHLTptfl->at(j) = ontmp_mrnn_hltptfl;

        ontmp_hltptflag = m_on_HLTptflag->at(i);
        m_on_HLTptflag->at(i) = m_on_HLTptflag->at(j);
        m_on_HLTptflag->at(j) = ontmp_hltptflag;

      }
    }
  }
  
  m_non_HLTptfl->push_back(countonhltptfl);
  


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 4J12 trigger matched taus //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //TrigDefs::includeFailedDecisions eta trigger
  auto veceta = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTetaidperf, TrigDefs::includeFailedDecisions ,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto veceta = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTetaTau0, TrigDefs::Physics,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto veceta = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTetar22, TrigDefs::includeFailedDecisions,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  //auto veceta = m_trigDecTool->features<xAOD::TauJetContainer>(trigHLTetar22, TrigDefs::Physics,tauContainerName); //TrigDefs::includeFailedDecisions TrigDefs::Physics
  m_on_HLTetafl->clear();
  m_on_idvlHLTetafl->clear();
  m_on_idlHLTetafl->clear();
  m_on_idmHLTetafl->clear();
  m_on_idtHLTetafl->clear();
  m_on_prngHLTetafl->clear();
  m_on_rnnHLTetafl->clear();
  m_non_HLTetafl->clear();
  m_on_HLTetaflag->clear();
  int countonhltetafl = 0;
  //ANA_MSG_INFO("Before loop");
  for (auto& featLinkInfo_eta : veceta){
    const auto *feat_eta = *(featLinkInfo_eta.link);
    if(!feat_eta) continue; 
    //ANA_MSG_INFO("Inside Loop");
    //ANA_MSG_INFO("Tau feat pT: "<< feat_eta->pt() * 0.001);
    if (feat_eta->pt() * 0.001 < 10.) continue;
    TLorentzVector ontauhltetafl; 
    ontauhltetafl.SetPtEtaPhiM(feat_eta->pt() * 0.001, feat_eta->eta(), feat_eta->phi(), 0);
    m_on_HLTetafl->push_back(ontauhltetafl);
    m_on_prngHLTetafl->push_back(feat_eta->nTracks());
    // m_on_rnnHLTetafl->push_back(feat_eta->discriminant(xAOD::TauJetParameters::TauID::RNNJetScoreSig)); // !!!!!!!!!!!!!!!!!!!!!!!!!!
    m_on_rnnHLTetafl->push_back(feat_eta->discriminant(xAOD::TauJetParameters::TauID::RNNJetScoreSigTrans)); 
    m_on_idvlHLTetafl->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigVeryLoose));
    m_on_idlHLTetafl->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
    m_on_idmHLTetafl->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
    m_on_idtHLTetafl->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigTight));
    if (feat_eta->pt() * 0.001 < 280.) {
      m_on_HLTetaflag->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigMedium));
    } else if ( feat_eta->pt() * 0.001 >= 280.  &&  feat_eta->pt() * 0.001 < 440.) {
      m_on_HLTetaflag->push_back(feat_eta->isTau(xAOD::TauJetParameters::IsTauFlag::JetRNNSigLoose));
    } else if (feat_eta->pt() * 0.001 >= 440){
      m_on_HLTetaflag->push_back(1);
    }
    countonhltetafl ++;
  }
  //Sorting 
  TLorentzVector ontmpmtau_hltetafl;
  bool ontmpmtauIDvl_hltetafl, ontmpmtauIDl_hltetafl, ontmpmtauIDm_hltetafl, ontmpmtauIDt_hltetafl, ontmp_hltetaflag;
  size_t ontmp_mprong_hltetafl; 
  float ontmp_mrnn_hltetafl;
  for ( int i =0 ; i < (int)m_on_HLTetafl->size() - 1; i++){
    for (int j = i + 1; j < (int)m_on_HLTetafl->size(); j++){
      if (m_on_HLTetafl->at(i).Pt()<m_on_HLTetafl->at(j).Pt()){
        ontmpmtau_hltetafl = m_on_HLTetafl->at(i);
        m_on_HLTetafl->at(i) = m_on_HLTetafl->at(j);
        m_on_HLTetafl->at(j) = ontmpmtau_hltetafl; 

        ontmpmtauIDvl_hltetafl = m_on_idvlHLTetafl->at(i);
        m_on_idvlHLTetafl->at(i) = m_on_idvlHLTetafl->at(j);
        m_on_idvlHLTetafl->at(j) = ontmpmtauIDvl_hltetafl;

        ontmpmtauIDl_hltetafl = m_on_idlHLTetafl->at(i);
        m_on_idlHLTetafl->at(i) = m_on_idlHLTetafl->at(j);
        m_on_idlHLTetafl->at(j) = ontmpmtauIDl_hltetafl;

        ontmpmtauIDm_hltetafl = m_on_idmHLTetafl->at(i);
        m_on_idmHLTetafl->at(i) = m_on_idmHLTetafl->at(j);
        m_on_idmHLTetafl->at(j) = ontmpmtauIDm_hltetafl;

        ontmpmtauIDt_hltetafl = m_on_idtHLTetafl->at(i);
        m_on_idtHLTetafl->at(i) = m_on_idtHLTetafl->at(j);
        m_on_idtHLTetafl->at(j) = ontmpmtauIDt_hltetafl;

        ontmp_mprong_hltetafl = m_on_prngHLTetafl->at(i);
        m_on_prngHLTetafl->at(i) = m_on_prngHLTetafl->at(j);
        m_on_prngHLTetafl->at(j) = ontmp_mprong_hltetafl;

        ontmp_mrnn_hltetafl = m_on_rnnHLTetafl->at(i);
        m_on_rnnHLTetafl->at(i) = m_on_rnnHLTetafl->at(j);
        m_on_rnnHLTetafl->at(j) = ontmp_mrnn_hltetafl;

        ontmp_hltetaflag = m_on_HLTetaflag->at(i);
        m_on_HLTetaflag->at(i) = m_on_HLTetaflag->at(j);
        m_on_HLTetaflag->at(j) = ontmp_hltetaflag;
      }
    }
  }
  m_non_HLTetafl->push_back(countonhltetafl);
  

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
    if (ontau->pt() * 0.001 < 10.) continue; 

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

  m_non_TrigTRM->push_back(countonTRM); 
  


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Offline matched taus //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //Offline Taus
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
  
  // Fill the event into the tree:
  tree ("analysis")->Fill ();
  m_on_truthmHH->clear();

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
  //ANA_MSG_INFO ("in finalize");
  return StatusCode::SUCCESS;
}
