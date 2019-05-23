from bmtk.builder.networks import NetworkBuilder
import synapses

def build_hippocampus():

    synapses.load()
    syn = synapses.syn_params_dicts()

    net = NetworkBuilder('CA3')
    net.add_nodes(N=2,
                pop_name='CA3e',
                model_type = 'biophysical',
                model_template='hoc:IzhiCell_CA3',
                morphology='blank.swc'
                )

    #Connect CA3e->CA3e Excitatory
    dynamics_file = 'CA3e2CA3e.exc.json'
    conn = net.add_edges(source={'pop_name': 'CA3e'}, target={'pop_name': 'CA3e'},
                connection_rule=1,
                #connection_params={'con_pattern':syn[dynamics_file]['con_pattern'],
                #                'ratio':syn[dynamics_file]['ratio'],
                #                'gaussa':syn[dynamics_file]['gaussa']},
                syn_weight=1,
                dynamics_params=dynamics_file,
                model_template=syn[dynamics_file]['level_of_detail'],
                distance_range=[0.0, 300.0],
                target_sections=['soma'],
                delay=0.0)
    conn.add_properties(['sec_id','sec_x'],rule=(0, 0.9), dtypes=[np.int32,np.float])
    conn.add_properties('delay', 
                rule=syn_dist_delay,
                rule_params={'base_delay':syn[dynamics_file]['delay']},
                dtypes=np.float)

    net.build()
    net.save_nodes(output_dir='network')
    net.save_edges(output_dir='network')


if __name__ == "__main__":
    build_hippocampus()