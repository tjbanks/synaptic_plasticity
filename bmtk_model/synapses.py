import glob
import json
import os

from bmtk.simulator.bionet.pyfunction_cache import add_synapse_model
from neuron import h
import random

def Pyr2Pyr(syn_params, sec_x, sec_id):
    """Create a pyr2pyr synapse
    :param syn_params: parameters of a synapse
    :param sec_x: normalized distance along the section
    :param sec_id: target section
    :return: NEURON synapse object
    """

    lsyn = h.pyr2pyr(sec_x, sec=sec_id)

    if syn_params.get('AlphaTmax_ampa'):
        lsyn.AlphaTmax_ampa = float(syn_params['AlphaTmax_ampa']) # par.x(21)
    if syn_params.get('Beta_ampa'):
        lsyn.Beta_ampa = float(syn_params['Beta_ampa']) # par.x(22)
    if syn_params.get('Cdur_ampa'):
        lsyn.Cdur_ampa = float(syn_params['Cdur_ampa']) # par.x(23)
    if syn_params.get('gbar_ampa'):
        lsyn.gbar_ampa = float(syn_params['gbar_ampa']) # par.x(24)
    if syn_params.get('Erev_ampa'):
        lsyn.Erev_ampa = float(syn_params['Erev_ampa']) # par.x(16)

    if syn_params.get('AlphaTmax_nmda'):
        lsyn.AlphaTmax_nmda = float(syn_params['AlphaTmax_nmda']) # par.x(25)
    if syn_params.get('Beta_nmda'):
        lsyn.Beta_nmda = float(syn_params['Beta_nmda']) # par.x(26)
    if syn_params.get('Cdur_nmda'):
        lsyn.Cdur_nmda = float(syn_params['Cdur_nmda']) # par.x(27)
    if syn_params.get('gbar_nmda'):
        lsyn.gbar_nmda = float(syn_params['gbar_nmda']) # par.x(28)
    if syn_params.get('Erev_nmda'):
        lsyn.Erev_nmda = float(syn_params['Erev_nmda']) # par.x(16)
    
    if syn_params.get('initW'):
        lsyn.initW = float(syn_params['initW']) * random.uniform(0.5,1.0) # par.x(0) * rC.uniform(0.5,1.0)//rand.normal(0.5,1.5) //`rand.repick() 

    if syn_params.get('Wmax'):
        lsyn.Wmax = float(syn_params['Wmax']) * lsyn.initW # par.x(1) * lsyn.initW
    if syn_params.get('Wmin'):
        lsyn.Wmin = float(syn_params['Wmin']) * lsyn.initW # par.x(2) * lsyn.initW
    #delay = float(syn_params['initW']) # par.x(3) + delayDistance
    #lcon = new NetCon(&v(0.5), lsyn, 0, delay, 1)

    if syn_params.get('lambda1'):
        lsyn.lambda1 = float(syn_params['lambda1']) # par.x(6)
    if syn_params.get('lambda2'):
        lsyn.lambda2 = float(syn_params['lambda2']) # par.x(7)
    if syn_params.get('threshold1'):
        lsyn.threshold1 = float(syn_params['threshold1']) # par.x(8)
    if syn_params.get('threshold2'):
        lsyn.threshold2 = float(syn_params['threshold2']) # par.x(9)
    if syn_params.get('tauD1'):
        lsyn.tauD1 = float(syn_params['tauD1']) # par.x(10)
    if syn_params.get('d1'):
        lsyn.d1 = float(syn_params['d1']) # par.x(11)
    if syn_params.get('tauD2'):
        lsyn.tauD2 = float(syn_params['tauD2']) # par.x(12)
    if syn_params.get('d2'):
        lsyn.d2 = float(syn_params['d2']) # par.x(13)
    if syn_params.get('tauF'):
        lsyn.tauF = float(syn_params['tauF']) # par.x(14)
    if syn_params.get('f'):
        lsyn.f = float(syn_params['f']) # par.x(15)

    if syn_params.get('bACH'):
        lsyn.bACH = float(syn_params['bACH']) # par.x(17)
    if syn_params.get('aDA'):
        lsyn.aDA = float(syn_params['aDA']) # par.x(18)
    if syn_params.get('bDA'):
        lsyn.bDA = float(syn_params['bDA']) # par.x(19)
    if syn_params.get('wACH'):
        lsyn.wACH = float(syn_params['wACH']) # par.x(20)
    
    return lsyn


def pyr2pyr(syn_params, xs, secs):
    """Create a list of pyr2pyr synapses
    :param syn_params: parameters of a synapse
    :param xs: list of normalized distances along the section
    :param secs: target sections
    :return: list of NEURON synpase objects
    """
    syns = []
    for x, sec in zip(xs, secs):
        syn = Pyr2Pyr(syn_params, x, sec)
        syns.append(syn)
    return syns

def Inter2Pyr(syn_params, sec_x, sec_id):
    lsyn = h.inter2pyr(sec_x, sec=sec_id)

    #target.soma lsyn = new inter2pyr(0.9)
    if syn_params.get('AlphaTmax_gabaa'):
        lsyn.AlphaTmax_gabaa = float(syn_params['AlphaTmax_gabaa']) # par.x(21)
    if syn_params.get('Beta_gabaa'):
        lsyn.Beta_gabaa = float(syn_params['Beta_gabaa']) # par.x(22)
    if syn_params.get('Cdur_gabaa'):
        lsyn.Cdur_gabaa = float(syn_params['Cdur_gabaa']) # par.x(23)
    if syn_params.get('gbar_gabaa'):
        lsyn.gbar_gabaa = float(syn_params['gbar_gabaa']) # par.x(24)
    if syn_params.get('Erev_gabaa'):
        lsyn.Erev_gabaa = float(syn_params['Erev_gabaa']) # par.x(16)

    if syn_params.get('AlphaTmax_gabab'):
        lsyn.AlphaTmax_gabab = float(syn_params['AlphaTmax_gabab']) # par.x(25)
    if syn_params.get('Beta_gabab'):
        lsyn.Beta_gabab = float(syn_params['Beta_gabab']) # par.x(26)
    if syn_params.get('Cdur_gabab'):
        lsyn.Cdur_gabab = float(syn_params['Cdur_gabab']) # par.x(27)
    if syn_params.get('gbar_gabab'):
        lsyn.gbar_gabab = float(syn_params['gbar_gabab']) # par.x(28)
    if syn_params.get('Erev_gabab'):
        lsyn.Erev_gabab = float(syn_params['Erev_gabab']) # par.x(16)
    

    if syn_params.get('initW'):
        lsyn.initW = float(syn_params['initW']) * random.random() # par.x(0) * rC.uniform(0.5,1.0)//rand.normal(0.5,1.5) //`rand.repick() 

    if syn_params.get('Wmax'):
        lsyn.Wmax = float(syn_params['Wmax']) * lsyn.initW # par.x(1) * lsyn.initW
    if syn_params.get('Wmin'):
        lsyn.Wmin = float(syn_params['Wmin']) * lsyn.initW # par.x(2) * lsyn.initW
    #delay = float(syn_params['initW']) # par.x(3) + delayDistance
    #lcon = new NetCon(&v(0.5), lsyn, 0, delay, 1)

    if syn_params.get('lambda1'):
        lsyn.lambda1 = float(syn_params['lambda1']) # par.x(6)
    if syn_params.get('lambda2'):
        lsyn.lambda2 = float(syn_params['lambda2']) # par.x(7)
    if syn_params.get('threshold1'):
        lsyn.threshold1 = float(syn_params['threshold1']) # par.x(8)
    if syn_params.get('threshold2'):
        lsyn.threshold2 = float(syn_params['threshold2']) # par.x(9)
    if syn_params.get('tauD1'):
        lsyn.tauD1 = float(syn_params['tauD1']) # par.x(10)
    if syn_params.get('d1'):
        lsyn.d1 = float(syn_params['d1']) # par.x(11)
    if syn_params.get('tauD2'):
        lsyn.tauD2 = float(syn_params['tauD2']) # par.x(12)
    if syn_params.get('d2'):
        lsyn.d2 = float(syn_params['d2']) # par.x(13)
    if syn_params.get('tauF'):
        lsyn.tauF = float(syn_params['tauF']) # par.x(14)
    if syn_params.get('f'):
        lsyn.f = float(syn_params['f']) # par.x(15)

    if syn_params.get('bACH'):
        lsyn.bACH = float(syn_params['bACH']) # par.x(17)
    if syn_params.get('aDA'):
        lsyn.aDA = float(syn_params['aDA']) # par.x(18)
    if syn_params.get('bDA'):
        lsyn.bDA = float(syn_params['bDA']) # par.x(19)
    if syn_params.get('wACH'):
        lsyn.wACH = float(syn_params['wACH']) # par.x(20)

    return lsyn

def inter2pyr(syn_params, xs, secs):
    """Create a list of pyr2pyr synapses
    :param syn_params: parameters of a synapse
    :param xs: list of normalized distances along the section
    :param secs: target sections
    :return: list of NEURON synpase objects
    """
    syns = []
    for x, sec in zip(xs, secs):
        syn = Inter2Pyr(syn_params, x, sec)
        syns.append(syn)
    return syns

def load():
    add_synapse_model(Pyr2Pyr, 'pyr2pyr', overwrite=False)
    add_synapse_model(Pyr2Pyr, overwrite=False)
    add_synapse_model(Inter2Pyr, 'inter2pyr', overwrite=False)
    add_synapse_model(Inter2Pyr, overwrite=False)
    return

def syn_params_dicts(syn_dir='biophys_components/synaptic_models'):
    """
    returns: A dictionary of dictionaries containing all
    properties in the synapse json files
    """
    files = glob.glob(os.path.join(syn_dir,'*.json'))
    data = {}
    for fh in files:
        with open(fh) as f:
            data[os.path.basename(fh)] = json.load(f) #data["filename.json"] = {"prop1":"val1",...}
    return data
