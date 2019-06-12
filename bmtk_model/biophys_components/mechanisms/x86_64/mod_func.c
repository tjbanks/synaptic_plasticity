#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _exp2syn_stsp_reg(void);
extern void _izh_reg(void);
extern void _kdr_reg(void);
extern void _leak_reg(void);
extern void _na_reg(void);
extern void _pyr2pyr_reg(void);
extern void _synapse_inter2pyr_reg(void);
extern void _vecevent_reg(void);

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," modfiles//exp2syn_stsp.mod");
    fprintf(stderr," modfiles//izh.mod");
    fprintf(stderr," modfiles//kdr.mod");
    fprintf(stderr," modfiles//leak.mod");
    fprintf(stderr," modfiles//na.mod");
    fprintf(stderr," modfiles//pyr2pyr.mod");
    fprintf(stderr," modfiles//synapse_inter2pyr.mod");
    fprintf(stderr," modfiles//vecevent.mod");
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
