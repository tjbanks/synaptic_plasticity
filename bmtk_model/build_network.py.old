from bmtk.builder.networks import NetworkBuilder
from bmtk.builder.auxi.node_params import positions_list
import math
import synapses
import numpy as np

def build_hippocampus():

    def pos_CA3e():
        # Create the possible x,y,z coordinates
        x_start, x_end, x_stride = 0.5,15,2.3
        y_start, y_end, y_stride = 0.5,3,1
        z_start, z_end, z_stride = 1,4,1
        x_grid = np.arange(x_start,x_end,x_stride)
        y_grid = np.arange(y_start,y_end,y_stride)
        z_grid = np.arange(z_start,z_end,z_stride)
        xx, yy, zz = np.meshgrid(x_grid, y_grid, z_grid)
        pos_list = np.vstack([xx.ravel(), yy.ravel(), zz.ravel()]).T
    
        return positions_list(pos_list)


    synapses.load()
    syn = synapses.syn_params_dicts()

    net = NetworkBuilder('CA3')
    net.add_nodes(N=2,
                pop_name='CA3e',
                positions=pos_CA3e()[:2],
                model_type = 'biophysical',
                model_template='hoc:IzhiCell_CA3',
                morphology='blank.swc'
                )
    def syn_connector_rule(source, target):
        
        if source['node_id'] != target['node_id']:
            return 1

        return 0


    def syn_dist_delay(source, target, base_delay, dist_delay=None):#, min_weight, max_weight):
        """
        Original Code:
        distDelay = 0.1* (0.5*dist + rC.normal(0,1.5)*(1-exp(-dist^2/3)) ) 
        """
        base_delay = float(base_delay)
        if dist_delay:
            dist_delay = float(dist_delay)

        if dist_delay: #An override of sorts
            return base_delay + dist_delay

        x_ind,y_ind,z_ind = 0,1,2
        
        dx = target['positions'][x_ind] - source['positions'][x_ind]
        dy = target['positions'][y_ind] - source['positions'][y_ind]
        dz = target['positions'][z_ind] - source['positions'][z_ind]

        dist = math.sqrt(dx**2 + dy**2 + dz**2)
        distDelay = 0.1* (0.5*dist + np.random.normal(0,1.5,1)[0]*(1-math.exp(-dist**2/3)) ) 
        return float(base_delay) + distDelay

    #Connect CA3e->CA3e Excitatory
    dynamics_file = 'CA3e2CA3e.exc.json'
    conn = net.add_edges(source={'pop_name': 'CA3e'}, target={'pop_name': 'CA3e'},
                connection_rule=syn_connector_rule,
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

    def hipp_external_connector(source,targets,min_syn=1, max_syn=1):
        total_targets = len(targets)
        syns = np.zeros(total_targets)
        syns[0] = 1 # Only connect to the first cell
        return syns


    inputnet = NetworkBuilder('input')
    inputnet.add_nodes(N=1, model_type='virtual',pat='pat1',pop_name='ec')
    conn = inputnet.add_edges(target=net.nodes(pop_name='CA3e'),
                    source={'pat':'pat1'},
                    iterator='one_to_all',
                    connection_rule=hipp_external_connector,
                    connection_params={},
                    dynamics_params='NetCon2EC.exc.json',
                    model_template='pyr2pyr',
                    delay=0,
                    syn_weight=1,
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
