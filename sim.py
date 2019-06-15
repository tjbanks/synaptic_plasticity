from neuron import h
import matplotlib.pyplot as plt
import numpy as np

h.load_file('stdrun.hoc')

def plot_hh_stsp(syn_tauD1=130, syn_d1=0.7, 
                 syn_tauD2=400, syn_d2=0.92, 
                 syn_tauF=200,syn_f=1,
                 stim1_start= 100, stim1_frequency=20, stim1_duration=500):
    syn_reversal = 0
    netcon_weight=3
    stop_time=1000
    
    #Create the soma section and define the default parameters
    soma = h.Section(name='soma')
    soma.diam = 200 #micrometers
    soma.L = 100 #micrometers

    soma.cm = 1.4884e-4/6.2832e-4 #uF

    #Insert the Hodgkin-Huxley channels and define the conductances
    soma.insert('hh')
    soma.gnabar_hh = 0.12
    soma.gkbar_hh = 0.012
    soma.gl_hh = 2.0e-5
    soma.el_hh = -70

    v_init = h.v_init= -60

    # input

    soma = h.Section(name='soma')
    soma.insert('hh')
    syn = h.Exp2Syn1_STSP(0.5, sec=soma)
    syn.e = syn_reversal
    syn.tauD1 = syn_tauD1
    syn.d1 = syn_d1
    syn.tauD2 = syn_tauD2
    syn.d2 = syn_d2
    syn.tauF = syn_tauF
    syn.f = syn_f

    nc = h.NetStim(0.5)
    nc.start = stim1_start
    #nc.number = 5
    #nc.interval = 5
    nc.number = stim1_frequency * stim1_duration/1000
    nc.interval = 1000/stim1_frequency
    nc.noise = 0

    netCon = h.NetCon(nc, syn)
    netCon.weight[0] = netcon_weight

    
    spike_vec = h.Vector()
    netcon = h.NetCon(nc, None)
    netcon.record(spike_vec)

    tstop = h.tstop = stop_time   # how long to run the simulation in ms
    h.dt = 0.025 # time step (resolution) of the simulation in ms

    # define three vectors for recording variables
    v0_vec = h.Vector() 
    isyn0_vec = h.Vector()
    t_vec = h.Vector()

    # record the voltage (_ref_v) and time (_ref_t) into the vectors we just created
    v0_vec.record(soma(0.5)._ref_v)
    isyn0_vec.record(syn._ref_i)
    t_vec.record(h._ref_t)

    # run the simulation!
    h.run()
    
    def plot_facfactor(spike_vector, ax=None):
        F = 0
        D1 = 1
        D2 = 1
        t = 0
        tsyn = -1e30

        facfactor_arr = []
        D1_arr = []
        D2_arr = []
        F_arr = []

        for t in spike_vector:
            #For each spike time calculate the following and plot
            F  = 1 + (F-1)* np.exp(-(t - tsyn)/syn_tauF)
            D1 = 1 - (1-D1)*np.exp(-(t - tsyn)/syn_tauD1)
            D2 = 1 - (1-D2)*np.exp(-(t - tsyn)/syn_tauD2)
            
            tsyn = t
            
            facfactor = F * D1 * D2
            
            F = F * syn_f
            if F > 30:
                F = 30
            
            
            D1 = D1 * syn_d1
            D2 = D2 * syn_d2

            facfactor_arr.append(facfactor)
            D1_arr.append(D1)
            D2_arr.append(D2)
            F_arr.append(F)

        ax.plot(spike_vector, facfactor_arr,'b',marker="o")
        ax.plot(spike_vector, D1_arr,marker="o")
        ax.plot(spike_vector, D2_arr,marker="o")
        ax.plot(spike_vector, F_arr,marker="o")

        ax.set_xlim(0, tstop)
        ax.set_ylim(0,np.max([np.max(F_arr),np.max(facfactor)])+1)
        ax.set_xlabel('time (ms)')
        #ax.set_ylabel('mV')
        ax.legend(["Total Factor","D1 Factor", "D2 Factor", "F Factor"])
        ax.set_title('Facilitation/Depression Impact')


    f, ((ax2, ax3),(ax1, ax4)) = plt.subplots(2, 2, figsize=(10,10))
    
    #plt.figure(figsize=(5,5))
    ax1.plot(t_vec, v0_vec,'b')
    ax1.set_xlim(0, tstop)
    ax1.set_xlabel('time (ms)')
    ax1.set_ylabel('mV')
    ax1.set_title('Membrane Potential')

    #plt.figure(figsize=(5,5))
    ax2.plot(t_vec, np.abs(isyn0_vec),'b')
    ax2.set_xlim(0, tstop)
    ax2.set_xlabel('time (ms)')
    ax2.set_ylabel('nA')
    ax2.set_title('Synaptic Current')

    ax4.plot(spike_vec,np.ones(len(spike_vec)),linestyle="",marker="o")
    ax4.set_xlim(0, tstop)
    ax4.set_title('Spike Times')
    ax4.set_xlabel('time (ms)')

    plot_facfactor(spike_vec, ax3)

    plt.tight_layout()
    f.subplots_adjust(hspace=0.3) 

    plt.show()
