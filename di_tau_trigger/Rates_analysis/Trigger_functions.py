#########################################################################################################################################################

def is_mRNN(df,event,tau,branch='TrigMatched_rnn_HLTptfl_perf',m0=0.35,m1=0.03,mm=0.105):
    ''' Checks if a tau in an event passes the medium RNN cut
        :param event: int
        :param tau: int
        :param branch: str (branch containing the trigger matched tau rnn value)
        :param m0: float (0 prong medium RNN working point)
        :param m1: float (1 prong medium RNN working point)
        :param mm: float (multi prong medium RNN working point)
        :return: bool
    '''    
    if branch == 'TrigMatched_rnn_HLTptfl_perf':

        if df['TrigMatched_prong_HLTptfl_perf'][event][tau]==0:
            return df[branch][event][tau]>m0
        if df['TrigMatched_prong_HLTptfl_perf'][event][tau]==1:
            return df[branch][event][tau]>m1
        if df['TrigMatched_prong_HLTptfl_perf'][event][tau]>=2:
            return df[branch][event][tau]>mm
        
    
    if branch == 'Off_Matched_TauRNN':
        
        if df['Off_Matched_TauProng'][event][tau]==0:
            return df[branch][event][tau]>m0
        if df['Off_Matched_TauProng'][event][tau]==1:
            return df[branch][event][tau]>m1
        if df['Off_Matched_TauProng'][event][tau]>=2:
            return df[branch][event][tau]>mm
        
    
    
    if branch == 'TrigMatched_rnn_HLTetafl_perf':
        
        if df['TrigMatched_prong_HLTetafl_perf'][event][tau]==0:
            return df[branch][event][tau]>m0
        if df['TrigMatched_prong_HLTetafl_perf'][event][tau]==1:
            return df[branch][event][tau]>m1
        if df['TrigMatched_prong_HLTetafl_perf'][event][tau]>=2:
            return df[branch][event][tau]>mm
         
#########################################################################################################################################################          

def is_lRNN(df,event,tau,branch='TrigMatched_rnn_HLTptfl_perf',l0=0.1,l1=0.01,lm=0.06):
    ''' Checks if a tau in an event passes the loose RNN cut
        :param event: int
        :param tau: int
        :param branch: str (branch containing the trigger matched tau rnn value)
        :param l0: float (0 prong loose RNN working point)
        :param l1: float (1 prong loose RNN working point)
        :param lm: float (multi prong loose RNN working point)
        :return: bool
    '''  

    if branch == 'TrigMatched_rnn_HLTptfl_perf':

        if df['TrigMatched_prong_HLTptfl_perf'][event][tau]==0:
            return df[branch][event][tau]>l0
        if df['TrigMatched_prong_HLTptfl_perf'][event][tau]==1:
            return df[branch][event][tau]>l1
        if df['TrigMatched_prong_HLTptfl_perf'][event][tau]>=2:
            return df[branch][event][tau]>lm
        
    
    if branch == 'Off_Matched_TauRNN':
        
        if df['Off_Matched_TauProng'][event][tau]==0:
            return df[branch][event][tau]>l0
        if df['Off_Matched_TauProng'][event][tau]==1:
            return df[branch][event][tau]>l1
        if df['Off_Matched_TauProng'][event][tau]>=2:
            return df[branch][event][tau]>lm
        
    
    if branch == 'TrigMatched_rnn_HLTetafl_perf':
        
        if df['TrigMatched_prong_HLTetafl_perf'][event][tau]==0:
            return df[branch][event][tau]>l0
        if df['TrigMatched_prong_HLTetafl_perf'][event][tau]==1:
            return df[branch][event][tau]>l1
        if df['TrigMatched_prong_HLTetafl_perf'][event][tau]>=2:
            return df[branch][event][tau]>lm
        
#########################################################################################################################################################         

def selection_cond(df,event):
    ''' Checks if an event passes the selection cut (a reasonable selection condition agreed by the bbtautau trigger analysis group)
        :param event: int
        :return: bool 
    '''    
    #atleast 2 offline taus
    if len(df['Offline_Matched_Taus'][event])>=2:
        #Must pass RNN loose
        if is_lRNN(event,0,branch='Off_Matched_TauRNN') and is_lRNN(event,1,branch='Off_Matched_TauRNN'):
            #Must have tau1_pt >20 and tau2_pt>12
            if df['Offline_Matched_Taus'][event][0].Pt()>20 and df['Offline_Matched_Taus'][event][1].Pt()>12:
                return True
    else:
        return False

#########################################################################################################################################################    

def pt_cond(df,event,index,i,pt0,pt1,branch='TrigMatched_Taus_HLTptfl_perf'): #"index" is index of the tau of concern, i is the index of the tau pair
    ''' Checks for a particular tau if it can be paired up with the second tau and pass the pt cut
        :param event: int 
        :param index: int (index of the tau to be checked)
        :param i: int (index of the pair tau)
        :param pt0: float (leading tau pT threshold)
        :param pt1: float (pair tau pT threshold)
        :param branch: str (branch containing the trigger matched tau Lorentz four vector)
        :return: bool
    '''    
    # Check if both the taus are above pt2 and check if atleast one of them is above pt2
    condition = df[branch][event][index].Pt()>pt1
    condition &= df[branch][event][i].Pt()>pt1
    condition &= (df[branch][event][index].Pt()>pt0 or df[branch][event][i].Pt()>pt0)
    if i!=index and condition:
        return True
    return False

# def pt_cond2(event,index,i,pt1,pt2): #"index" is index of the tau of concern, i is the index of the tau pair
#     ''' This returns True or False for a particular hlteta tau if it can be paired up 
#     with the second tau and pass the pt cut'''
#     # Check if both the taus are above pt2 and check if atleast one of them is above pt2
#     condition1 = df['TrigMatched_Taus_HLTetafl_perf'][event][index].Pt()>pt2
#     condition1 &= df['TrigMatched_Taus_HLTetafl_perf'][event][i].Pt()>pt2
#     condition1 &= (df['TrigMatched_Taus_HLTetafl_perf'][event][index].Pt()>pt1 or df['TrigMatched_Taus_HLTetafl_perf'][event][i].Pt()>pt1)
#     if i!=index and condition1:
#         return True
#     return False

#########################################################################################################################################################    

def mRNN_L1Topo_cond(df,event,index,i, no_RNN = 440, m_RNN=280,m0=0.35,m1=0.03,mm=0.105,l0=0.1,l1=0.01,lm=0.06):
    ''' Checks for a particular tau if it can be paired up with the second tau and pass the medium RNN cut for the L1Topo Trigger
        :param event: int 
        :param index: int (index of the tau to be checked)
        :param i: int (index of the pair tau)
        :param no_RNN: pT threshold above which there is no RNN ID requirement
        :param mRNN: pT threshold below which there is medium RNN requirement
        :param m0: float (0 prong medium RNN working point)
        :param m1: float (1 prong medium RNN working point)
        :param mm: float (multi prong medium RNN working point)
        :param l0: float (0 prong loose RNN working point)
        :param l1: float (1 prong loose RNN working point)
        :param lm: float (multi prong loose RNN working point)
        :return: bool
    '''   
    # For tau[index] RNN Medium(Loose) if pt < m_RNN(no_RNN) | no RNN ID if pt > no_RNN GeV
    RNN1_cond = (is_mRNN(df,event,index,m0=m0,m1=m1,mm=mm)) and (df['TrigMatched_Taus_HLTptfl_perf'][event][index].Pt() < m_RNN)
    RNN1_cond |= (is_lRNN(df,event,index,l0=l0,l1=l1,lm=lm)) and (df['TrigMatched_Taus_HLTptfl_perf'][event][index].Pt() > m_RNN) and (df['TrigMatched_Taus_HLTptfl_perf'][event][index].Pt() < no_RNN) 
    RNN1_cond |= df['TrigMatched_Taus_HLTptfl_perf'][event][index].Pt() > no_RNN
    # For tau[i] RNN Medium(Loose) if pt < m_RNN(no_RNN) | no RNN ID if pt > no_RNN GeV
    RNN2_cond = (is_mRNN(df,event,i,m0=m0,m1=m1,mm=mm)) and (df['TrigMatched_Taus_HLTptfl_perf'][event][i].Pt() < m_RNN) 
    RNN2_cond |= (is_lRNN(df,event,i,l0=l0,l1=l1,lm=lm)) and (df['TrigMatched_Taus_HLTptfl_perf'][event][i].Pt() > m_RNN) and (df['TrigMatched_Taus_HLTptfl_perf'][event][i].Pt() < no_RNN)
    RNN2_cond |= df['TrigMatched_Taus_HLTptfl_perf'][event][i].Pt() > no_RNN
    if RNN1_cond and RNN2_cond:
        return  True
    else:
        return False

def DR_L1Topo_cond(df,event,index,i,min_DR = 0.3, max_DR = 3):
    ''' Checks for a particular tau if it can be paired up with the second tau and pass the angular separation cut for the L1Topo trigger
        :param event: int 
        :param index: int (index of the tau to be checked)
        :param i: int (index of the pair tau)
        :param min_DR: float (Minimum angular separation condition)
        :param max_DR: float (Maximum angular separation condition)
        :return: bool
    '''
    #Delta R should be greater than 0.3 and less than 3
    hltptDR_cond = df['TrigMatched_Taus_HLTptfl_perf'][event][index].DeltaR(df['TrigMatched_Taus_HLTptfl_perf'][event][i]) > min_DR 
    hltptDR_cond &= df['TrigMatched_Taus_HLTptfl_perf'][event][index].DeltaR(df['TrigMatched_Taus_HLTptfl_perf'][event][i]) < max_DR
    if hltptDR_cond:
        return True
    else:
        return False

def HLT_L1Topo_cond(df,event,tau_i,pt0=30,pt1=20, no_RNN = 440, m_RNN =280,m0=0.35,m1=0.03,mm=0.105,l0=0.1,l1=0.01,lm=0.06, min_DR =0.3,max_DR =3):
    '''Checks if the L1Topo trigger condition is satisfied for a specific tau in an event 
        :param df: pandas_data_frame 
        :param event: int 
        :param tau_i: int (index of the tau to be checked)
        :param pt0: float (leading tau pT threshold)
        :param pt1: float (pair tau pT threshold)
        :param no_RNN: pT threshold above which there is no RNN ID requirement
        :param mRNN: pT threshold below which there is medium RNN requirement
        :param m0: float (0 prong medium RNN working point)
        :param m1: float (1 prong medium RNN working point)
        :param mm: float (multi prong medium RNN working point)
        :param l0: float (0 prong loose RNN working point)
        :param l1: float (1 prong loose RNN working point)
        :param lm: float (multi prong loose RNN working point)
        :param min_DR: float (Minimum angular separation condition)
        :param max_DR: float (Maximum angular separation condition)
        :param return: bool
    '''    
    if len(df['TrigMatched_Taus_HLTptfl_perf'][event])>=2:
        ptflag = 0
        RNN_flag = 0
        #Checking if tau_i has a pair that satidsfies the hltpt condition by looping over all taus 
        for i in range(len(df['TrigMatched_Taus_HLTptfl_perf'][event])):
            #Checking the pt condtion for tau_i and tau[i]  
            if pt_cond(df,event,tau_i,i,pt0,pt1,branch='TrigMatched_Taus_HLTptfl_perf'):
                if ptflag ==0:
                    ptflag =1
                #Checking the medium RNN condition for tau_i and tau[i]
                if mRNN_L1Topo_cond(df,event,tau_i,i,no_RNN,m_RNN,m0=m0,m1=m1,mm=mm,l0=l0,l1=l1,lm=lm):
                    if RNN_flag == 0:
                        RNN_flag =1
                    #Checking the DeltaR condtion for tau_i and tau[i]
                    if DR_L1Topo_cond(df,event,tau_i,i,min_DR,max_DR):
                        return True
                        break
        return False

#########################################################################################################################################################    



def mRNN_4J12_cond(df,event,index,i, no_RNN = 440, m_RNN=280,m0=0.35,m1=0.03,mm=0.105,l0=0.1,l1=0.01,lm=0.06 ):
    ''' Checks for a particular tau if it can be paired up with the second tau and pass the medium RNN cut for the 4J12 trigger
        :param event: int 
        :param index: int (index of the tau to be checked)
        :param i: int (index of the pair tau)
        :param no_RNN: pT threshold above which there is no RNN ID requirement
        :param mRNN: pT threshold below which there is medium RNN requirement
        :param m0: float (0 prong medium RNN working point)
        :param m1: float (1 prong medium RNN working point)
        :param mm: float (multi prong medium RNN working point)
        :param l0: float (0 prong loose RNN working point)
        :param l1: float (1 prong loose RNN working point)
        :param lm: float (multi prong loose RNN working point)
        :return: bool
    '''
    # For tau[index] RNN Medium(Loose) if pt < m_RNN(no_RNN) | no RNN ID if pt > no_RNN GeV
    RNN1_cond = (is_mRNN(df,event,index,branch ='TrigMatched_rnn_HLTetafl_perf',m0=m0,m1=m1,mm=mm)) and (df['TrigMatched_Taus_HLTetafl_perf'][event][index].Pt() < m_RNN)
    RNN1_cond |= (is_lRNN(df,event,index,branch ='TrigMatched_rnn_HLTetafl_perf',l0=l0,l1=l1,lm=lm)) and (df['TrigMatched_Taus_HLTetafl_perf'][event][index].Pt() > m_RNN) and (df['TrigMatched_Taus_HLTetafl_perf'][event][index].Pt() < no_RNN) 
    RNN1_cond |= df['TrigMatched_Taus_HLTetafl_perf'][event][index].Pt() > no_RNN
    # For tau[i] RNN Medium(Loose) if pt < m_RNN(no_RNN) | no RNN ID if pt > no_RNN GeV
    RNN2_cond = (is_mRNN(df,event,i,branch ='TrigMatched_rnn_HLTetafl_perf',m0=m0,m1=m1,mm=mm)) and (df['TrigMatched_Taus_HLTetafl_perf'][event][i].Pt() < m_RNN) 
    RNN2_cond |= (is_lRNN(df,event,i,branch ='TrigMatched_rnn_HLTetafl_perf',l0=l0,l1=l1,lm=lm)) and (df['TrigMatched_Taus_HLTetafl_perf'][event][i].Pt() > m_RNN) and (df['TrigMatched_Taus_HLTetafl_perf'][event][i].Pt() < no_RNN)
    RNN2_cond |= df['TrigMatched_Taus_HLTetafl_perf'][event][i].Pt() > no_RNN
    if RNN1_cond and RNN2_cond:
        return  True
    else:
        return False

    
def DR_4J12_cond(df,event,index,i,min_DR = 0.3):
    ''' Checks for a particular tau if it can be paired up with the second tau and pass the angular separation cut for the 4J12 trigger
        :param event: int 
        :param index: int (index of the tau to be checked)
        :param i: int (index of the pair tau)
        :param min_DR: float (Minimum angular separation condition)
        :return: bool
    '''
    #Delta R should be greater than 0.3 and less than 3
    hltptDR_cond = df['TrigMatched_Taus_HLTetafl_perf'][event][index].DeltaR(df['TrigMatched_Taus_HLTetafl_perf'][event][i]) > min_DR
    if hltptDR_cond:
        return True
    else:
        return False
    
    

    
def HLT_4J12_cond(df,event,tau_i,pt0=30,pt1=20, no_RNN = 440, m_RNN =280,m0=0.35,m1=0.03,mm=0.105,l0=0.1,l1=0.01,lm=0.06, min_DR =0.3):
    '''Checks if the 4J12 trigger condition is satisfied for a specific tau in an event 
        :param event: int 
        :param tau_i: int (index of the tau to be checked)
        :param pt0: float (leading tau pT threshold)
        :param pt1: float (pair tau pT threshold)
        :param no_RNN: pT threshold above which there is no RNN ID requirement
        :param mRNN: pT threshold below which there is medium RNN requirement
        :param m0: float (0 prong medium RNN working point)
        :param m1: float (1 prong medium RNN working point)
        :param mm: float (multi prong medium RNN working point)
        :param l0: float (0 prong loose RNN working point)
        :param l1: float (1 prong loose RNN working point)
        :param lm: float (multi prong loose RNN working point)
        :param min_DR: float (Minimum angular separation condition)
        :param df: pandas_data_frame 
        :return: bool
    '''    
    if len(df['TrigMatched_Taus_HLTetafl_perf'][event])>=2:
        ptflag = 0
        RNN_flag = 0
        #Checking if tau_i has a pair that satidsfies the hltpt condition by looping over all taus 
        for i in range(len(df['TrigMatched_Taus_HLTetafl_perf'][event])):
            #Checking the pt condtion for tau_i and tau[i]  
            if pt_cond(df,event,tau_i,i,pt0,pt1,branch='TrigMatched_Taus_HLTetafl_perf'):
                if ptflag ==0:
                    ptflag =1
                #Checking the medium RNN condition for tau_i and tau[i]
                if mRNN_4J12_cond(df,event,tau_i,i,no_RNN,m_RNN,m0=m0,m1=m1,mm=mm,l0=l0,l1=l1,lm=lm):
                    if RNN_flag == 0:
                        RNN_flag =1
                    #Checking the DeltaR condtion for tau_i and tau[i]
                    if DR_4J12_cond(df,event,tau_i,i,min_DR):
                        return True
                        break
        return False

#########################################################################################################################################################
