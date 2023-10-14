def pass_gn1(df,event,jet,tag ='gn170'):
    b_WP = { "dl1d40" : 6.957, "dl1d45" : 6.344, "dl1d50" : 5.730, "dl1d55" : 5.121, "dl1d60" : 4.512, "dl1d65" : 3.882, "dl1d70" : 3.251, "dl1d72" : 2.964, "dl1d75" : 2.489, "dl1d77" : 2.157, "dl1d80" : 1.626, "dl1d82" : 1.254, "dl1d85" : 0.634, "dl1d90" : -0.465, "dl1d95" : -1.616, "gn140": 7.370, "gn145": 6.748, "gn150": 6.094, "gn155": 5.425, "gn160": 4.757, "gn165": 4.095, "gn170": 3.423, "gn172": 3.141, "gn175": 2.703, "gn177": 2.392, "gn180": 1.884, "gn182": 1.510, "gn185": 0.881, "gn190": -0.351, "gn195": -1.794, "offperf" : -999}
    fc = 0.05
    pb = df['HLTJets_GN1b'][event][jet]
    pc = df['HLTJets_GN1c'][event][jet]
    pu = df['HLTJets_GN1u'][event][jet]
    
    if pb==1:
        Db = 50
    elif pb==0:
        Db = -10 
    else:
        Db = np.log(pb/((1-fc)*pu + (fc*pc)))    
        
    if Db > b_WP[tag]:
        return True
    else:
        return False
    

def pass_jetcond(df,event,pt1=75,pt2=50,pt3=25,pt4=20,j_vt=0.2,b_WP_tag='gn170'):
    pt1_flag = 0
    pt2_flag = 0
    pt3_flag = 0
    pt4_flag = 0
    bWP_flag = 0
    count = 0
    if len(df['HLTJets'][event])>=4:
        #Loop over all the jets
        for jet in range(len(df['HLTJets'][event])) :
            # All jets should have j_vt to be more than 0.2
            if df['HLTJets_Jvt'][event][jet]>j_vt:
                # Check if a jet pass the gn1 tag (Atleast one should)
                if pass_gn1(df,event,jet,tag=b_WP_tag) and df['HLTJets'][event][jet].Pt()>20:
                    bWP_flag = 1 

                # The jet with highest pT threshold  
                if df['HLTJets'][event][jet].Pt()>pt1 and pt1_flag==0:
                    pt1_flag=1
                    count+=1
                    if count==4 and bWP_flag:
                        break
                    continue
                        
                # The jet with second highest pT threshold
                if df['HLTJets'][event][jet].Pt()>pt2 and pt2_flag==0:
                    pt2_flag=1
                    count+=1
                    if count==4 and bWP_flag:
                        break
                    continue


                # The jet with the second lowest pT threshold
                if df['HLTJets'][event][jet].Pt()>pt3 and pt3_flag==0:
                    pt3_flag=1
                    count+=1
                    if count==4 and bWP_flag:
                        break
                    continue
                        
                # The jet with lowest pT threshold
                if df['HLTJets'][event][jet].Pt()>pt4 and pt4_flag==0:
                    pt4_flag=1
                    count+=1
                    if count==4 and bWP_flag:
                        break
                    continue

    if count==4 and bWP_flag==1:
        return True
    else:
        return False
    
    
                
    
def pass_RNNcond(df,event,index,m_RNN=280,no_RNN=440):
    '''This returns True or False for a particlular hltpt tau if it can be paired up 
    with the second tau and pass the medium RNN cut'''
    # For tau[index] RNN Medium(Loose) if pt < m_RNN(no_RNN) | no RNN ID if pt > no_RNN GeV
    RNN_cond = df['TrigTRM_TauIDm'][event][index] and (df['TrigTRM_Taus'][event][index].Pt() < m_RNN)
    RNN_cond |= (df['TrigTRM_TauIDl'][event][index]) and (df['TrigTRM_Taus'][event][index].Pt() > m_RNN) and (df['TrigTRM_Taus'][event][index].Pt() < no_RNN) 
    RNN_cond |= df['TrigMatched_Taus_HLTptfl'][event][index].Pt() > no_RNN
    return  RNN_cond


def RNN_cond(df,event,index,cond='medium'):
    if df['TrigTRM_TauIDm'][event][index]==1 and cond == 'medium':
        return True
    
    elif df['TrigTRM_TauIDl'][event][index]==1 and cond == 'loose':
        return True
    
    elif df['TrigTRM_TauIDt'][event][index]==1 and cond == 'tight':
        return True

    else:
        return False

def pass_3b1j(df,event,pt_tau=20, pt_j0=75, pt_j1=50, pt_j2=25, pt_j3=20, jvt=0.2, b_WP_tag = 'gn170',cond = 'medium'):
    # condition to pass tau
    tau_cond = False
    for tau in range(len(df['TrigTRM_Taus'][event])):
        if RNN_cond(df,event,tau,cond=cond) and df['TrigTRM_Taus'][event][tau].Pt()>pt_tau:
#         if pass_RNNcond(event,tau) and df['TrigTRM_Taus'][event][tau].Pt()>pt_tau:
            tau_cond=True
    
    b_cond = False
    if pass_jetcond(df,event,pt1=pt_j0,pt2=pt_j1,pt3=pt_j2,pt4=pt_j3,j_vt=jvt,b_WP_tag=b_WP_tag):
        b_cond=True
    
    return tau_cond and b_cond