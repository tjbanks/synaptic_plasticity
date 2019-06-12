from bmtk.builder.networks import NetworkBuilder
from bmtk.builder.auxi.node_params import positions_list
import math
import numpy as np

def build_hippocampus():

    net = NetworkBuilder('CA3')
    net.add_nodes(N=1,
                pop_name='CA3e',
                model_type = 'biophysical',
                model_template='hoc:Spikingcell',
                morphology='blank.swc'
                )

    inputnet = NetworkBuilder('input')
    inputnet.add_nodes(N=1, model_type='virtual',pat='pat1',pop_name='virt')
    conn = inputnet.add_edges(target=net.nodes(pop_name='CA3e'),
                    source={'pat':'pat1'},
                    connection_rule=1,
                    dynamics_params='stsp.json',
                    model_template='Exp2Syn1_STSP',
                    delay=0,
                    syn_weight=.5,
                    target_sections=['soma'],  # target soma
                    distance_range=[0.0, 300]
                    )
    conn.add_properties(['sec_id','sec_x'],rule=(0, 0.9), dtypes=[np.int32,np.float])

    net.build()
    net.save_nodes(output_dir='network')
    net.save_edges(output_dir='network')

    inputnet.build()
    inputnet.save(output_dir='network')

if __name__ == "__main__":
    build_hippocampus()
