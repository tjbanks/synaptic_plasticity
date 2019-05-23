# -*- coding: utf-8 -*-

"""Simulates an example network of 14 cell receiving two kinds of exernal input as defined in configuration file"""

import os, sys
from bmtk.simulator import bionet
from bmtk.simulator.bionet.default_setters.cell_models import loadHOC

import synapses

synapses.load()

bionet.pyfunction_cache.add_cell_model(loadHOC, directive='hoc', model_type='biophysical')

def run(config_file):

    conf = bionet.Config.from_json(config_file, validate=True)
    conf.build_env()

    graph = bionet.BioNetwork.from_config(conf)
    sim = bionet.BioSimulator.from_config(conf, network=graph)
    sim.run()
    bionet.nrn.quit_execution()


if __name__ == '__main__':
    if __file__ != sys.argv[-1]:
        run(sys.argv[-1])
    else:
        run('simulation_config.json')
