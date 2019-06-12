import glob
import json
import os

from bmtk.simulator.bionet.pyfunction_cache import add_synapse_model
from neuron import h
import random

def Exp2Syn1_STSP(syn_params, sec_x, sec_id):
    """Create a Exp2Syn1_STSP synapse
    :param syn_params: parameters of a synapse
    :param sec_x: normalized distance along the section
    :param sec_id: target section
    :return: NEURON synapse object
    """

    lsyn = h.Exp2Syn1_STSP(sec_x, sec=sec_id)

    if syn_params.get('e'):
        lsyn.e = float(syn_params['e'])
    if syn_params.get('tauD1'):
        lsyn.tauD1 = float(syn_params['tauD1']) 
    if syn_params.get('d1'):
        lsyn.d1 = float(syn_params['d1']) 
    if syn_params.get('tauD2'):
        lsyn.tauD2 = float(syn_params['tauD2'])
    if syn_params.get('d2'):
        lsyn.d2 = float(syn_params['d2']) 
    if syn_params.get('tauF'):
        lsyn.tauF = float(syn_params['tauF'])
    if syn_params.get('f'):
        lsyn.f = float(syn_params['f']) 
    
    return lsyn


def exp2syn1_stsp(syn_params, xs, secs):
    """Create a list of Exp2Syn1_STSP synapses
    :param syn_params: parameters of a synapse
    :param xs: list of normalized distances along the section
    :param secs: target sections
    :return: list of NEURON synpase objects
    """
    syns = []
    for x, sec in zip(xs, secs):
        syn = Exp2Syn1_STSP(syn_params, x, sec)
        syns.append(syn)
    return syns

def load():
    add_synapse_model(Exp2Syn1_STSP, 'exp2syn1_stsp', overwrite=False)
    add_synapse_model(Exp2Syn1_STSP, overwrite=False)
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
