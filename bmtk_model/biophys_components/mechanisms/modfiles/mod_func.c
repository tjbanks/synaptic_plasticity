#include <stdio.h>
#include "hocdec.h"
#define IMPORT extern __declspec(dllimport)
IMPORT int nrnmpi_myid, nrn_nobanner_;

extern void _exp2syn_stsp_reg();
extern void _izh_reg();
extern void _kdr_reg();
extern void _leak_reg();
extern void _na_reg();
extern void _pyr2pyr_reg();
extern void _synapse_inter2pyr_reg();
extern void _vecevent_reg();

void modl_reg(){
	//nrn_mswindll_stdio(stdin, stdout, stderr);
    if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
	fprintf(stderr, "Additional mechanisms from files\n");

fprintf(stderr," exp2syn_stsp.mod");
fprintf(stderr," izh.mod");
fprintf(stderr," kdr.mod");
fprintf(stderr," leak.mod");
fprintf(stderr," na.mod");
fprintf(stderr," pyr2pyr.mod");
fprintf(stderr," synapse_inter2pyr.mod");
fprintf(stderr," vecevent.mod");
fprintf(stderr, "\n");
    }
_exp2syn_stsp_reg();
_izh_reg();
_kdr_reg();
_leak_reg();
_na_reg();
_pyr2pyr_reg();
_synapse_inter2pyr_reg();
_vecevent_reg();
}
