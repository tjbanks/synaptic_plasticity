from bmtk.utils.spike_trains import SpikesGenerator

def write_input_file(rate=50):
    sg = SpikesGenerator(nodes='network/input_nodes.h5', t_max=1.0)
    sg.set_rate(rate)
    sg.save_csv('./input/input_spikes.csv', in_ms=True)

if __name__ == '__main__':
    write_input_file()
