
# Written by Tyler Banks

import numpy as np
import matplotlib.pyplot as plt
import math

#https://docs.scipy.org/doc/scipy/reference/generated/scipy.integrate.solve_ivp.html
from scipy.integrate import odeint,solve_ivp
from scipy.interpolate import interp1d

def alpha_m(v):
    return ((v+45)/10)/(1-np.exp(-(v+45)/10))
def beta_m(v):
    return 4*np.exp(-(v+70)/18)
    
def alpha_h(v):
    return 0.07*np.exp(-(v+70)/20)
def beta_h(v):
    return 1/(np.exp(-(v+40)/10)+1)
    
def alpha_n(v): 
    return 1/100 * (v+60)/(1-np.exp(-(v+60)/10))
def beta_n(v):
    return 1/8 * np.exp(-(v+70)/80)

v = np.linspace(-100,50)
def m_inf(v=0.0):
    return alpha_m(v)/(alpha_m(v)+beta_m(v))
    #return 1.0/(1.0+ (np.exp((v+25.5)/(-5.29))))
def m_tau(v=0.0):
    return 1/(alpha_m(v)+beta_m(v))
    #return (2.64 - 2.52/(1.0+ (np.exp((v+120)/(-25)))))

def h_inf(v=0.0):
    return alpha_h(v)/(alpha_h(v)+beta_h(v))
    #return 1.0/(1.0+ (np.exp((v+48.9)/(5.18))))  
def h_tau(v=0.0):
    return 1/(alpha_h(v)+beta_h(v))
    #return (1.34/(1+ (np.exp((v+62.9)/(-10)))))*(1.5 + 1.0/(1.0 + (np.exp((v+34.9)/(3.6)))))

def n_inf(v=0.0):
    return alpha_n(v)/(alpha_n(v)+beta_n(v))
    #return 1.0/(1.0 + (np.exp((v+12.3)/(-11.8))))
def n_tau(v=0.0):
    return 1/(alpha_n(v)+beta_n(v))
    #return 14.4 - 12.8/(1.0+(np.exp((v+28.3)/(-19.2))))

def plot_hh(C = 1, vNa = 45, vK = -82, vL = -59,
            gNa = 120, gK = 36, gL = 0.3, v_init = -70, gsyn=.20,
            inj_amp = 10, inj_start = 50, inj_dur = 20,
            syn_rev=0, syn_tau=0.1, syn_weight=0.4, syn_times = [50.0],
            f=1, d1=1, d2=1, tauF=1,tauD1=1,tauD2=1,
            tmin=0, tmax=100, stsp=True):

    def I(t,amp,start,dur):
        return np.piecewise(t, [t<start, t>=start, t>=start+dur], [0,amp,0])
    
    #tsyn = -10000
    #F = 0
    #D1 = 1
    #D2 = 1
    #facfactor = 1
    #on_syn = 0
    

    def hh_eq(t,y):
        dy = np.zeros((17,))
        
        #nonlocal tsyn,F,D1,D2,facfactor,on_syn
        
        Vm = y[0]
        m = y[1]
        h = y[2]
        n = y[3]
        
        t_last = y[7]
        #current_g_syn = y[8]
        
        r_syn = y[10]
        
        tsyn = y[11]
        F = y[12]
        D1 = y[13]
        D2 = y[14]
        facfactor = y[15]
        on_syn = y[16]

        alpha_t_max_syn = .088
        beta_syn = 0.0033
        c_dur_syn = 10
        current_g_syn = 0
        
        if tsyn>0:
            if t-tsyn < c_dur_syn:
                on_syn = 1
            else:
                on_syn = 0

        if True in [i >= t_last and i < t for i in syn_times]:
                        
            F  = 1 + (F-1)* np.exp(-(t - tsyn)/tauF)
            D1 = 1 - (1-D1)*np.exp(-(t - tsyn)/tauD1)
            D2 = 1 - (1-D2)*np.exp(-(t - tsyn)/tauD2)
            
            tsyn = t
            
            facfactor = F * D1 * D2
            
            F = F * f 
            if F > 30:
                F = 30     
            D1 = D1 * d1
            D2 = D2 * d2
            
            current_g_syn = gsyn + syn_weight
            
            if stsp:
                current_g_syn = gsyn + syn_weight* facfactor
            
            #print(facfactor)

        i_Na = gNa*np.power(m,3)*h*(vNa - Vm)
        i_K =  gK*np.power(n,4)*(vK - Vm)
        i_L =  gL*(vL - Vm)
        i_Syn = current_g_syn*r_syn*(syn_rev - Vm)
                
        dy[0] = (i_Na + i_K + i_L + i_Syn + I(t,inj_amp,inj_start,inj_dur))/C
        dy[1] = (alpha_m(Vm) * (1.0 - m)) - (beta_m(Vm) * m)
        dy[2] = (alpha_h(Vm) * (1.0 - h)) - (beta_h(Vm) * h)
        dy[3] = (alpha_n(Vm) * (1.0 - n)) - (beta_n(Vm) * n)
                
        delta_r_syn = alpha_t_max_syn*on_syn*(1-r_syn) -beta_syn*r_syn

        # Convienient way of saving conductances
        dy[4] = i_Na - y[4]
        dy[5] = i_K - y[5]
        dy[6] = i_L - y[6]
        # Save the timestamps
        dy[7] = t - y[7]

        dy[8] = 0#-current_g_syn/syn_tau

        dy[9] = i_Syn - y[9]
        dy[10] = delta_r_syn
        
        dy[11] = tsyn - y[11]
        dy[12] = F - y[12]
        dy[13] = D1 - y[13]
        dy[14] = D2 - y[14]
        dy[15] = facfactor - y[15]
        dy[16] = on_syn - y[16]
        
        return dy

    
    Y = np.array([v_init, m_inf(), h_inf(), n_inf(), 0, 0, 0, 0, gsyn, 0, 0,-10000,0,1,1,1,0])
    sol = solve_ivp(hh_eq,[tmin,tmax],Y,max_step=.1)
    v = sol.y
    t = sol.t
            
    f, ((ax1, ax2),(ax3, ax4)) = plt.subplots(2, 2, figsize=(12,12))
    ax1.plot(t,v[0,:])
    ax1.set(ylabel='v [mv]',xlabel='time [ms]')
    ax1.set_title('Cell Potential')
    
    ax2.plot(t,v[1,:])
    ax2.plot(t,v[2,:])
    ax2.plot(t,v[3,:])
    ax2.set(ylabel='Probability',xlabel='time [ms]')
    ax2.legend(["m","h","n"])
    ax2.set_title('Gate Activation/Inactivation')
    
    ax3.plot(t,v[4,:])
    ax3.plot(t,v[5,:])
    ax3.plot(t,v[6,:])
    ax3.set(ylabel='Conductance [mS/cm2]',xlabel='time [ms]')
    ax3.legend(["Na","K","Leak"])
    ax3.set_title('Channel Conductance')
    
    ax4.plot(t,I(t,inj_amp,inj_start,inj_dur))
    ax4.set(ylabel='Current [nA]',xlabel='time [ms]')
    ax4.set_title('Current Injection')
    
    plt.tight_layout()
    f.subplots_adjust(hspace=0.3)  
    
    # limit cycles
    fig, ax = plt.subplots(figsize=(6, 6))
    ax.plot(v[0,:], v[1,:], label='Vm - m')
    ax.plot(v[0,:], v[3,:], label='Vm - n')
    ax.set_title('Limit cycles')
    ax.legend()
    plt.grid()

    fig, axsyn = plt.subplots(figsize=(20, 20))
    axsyn.plot(t, v[9,:], label='Synapse 1')
    axsyn.set_title('Synaptic Current')
    axsyn.legend()
    plt.grid()
