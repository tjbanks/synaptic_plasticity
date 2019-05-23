/* Created by Language version: 6.2.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__inter2pyr
#define _nrn_initial _nrn_initial__inter2pyr
#define nrn_cur _nrn_cur__inter2pyr
#define _nrn_current _nrn_current__inter2pyr
#define nrn_jacob _nrn_jacob__inter2pyr
#define nrn_state _nrn_state__inter2pyr
#define _net_receive _net_receive__inter2pyr 
#define release release__inter2pyr 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define initW _p[0]
#define Cdur_gabaa _p[1]
#define AlphaTmax_gabaa _p[2]
#define Beta_gabaa _p[3]
#define Erev_gabaa _p[4]
#define gbar_gabaa _p[5]
#define Cdur_gabab _p[6]
#define AlphaTmax_gabab _p[7]
#define Beta_gabab _p[8]
#define Erev_gabab _p[9]
#define gbar_gabab _p[10]
#define K3_gabab _p[11]
#define K4_gabab _p[12]
#define n_gabab _p[13]
#define Kd_gabab _p[14]
#define ECa _p[15]
#define Cainf _p[16]
#define pooldiam _p[17]
#define z _p[18]
#define tauCa _p[19]
#define P0a _p[20]
#define P0b _p[21]
#define fCa _p[22]
#define lambda1 _p[23]
#define lambda2 _p[24]
#define threshold1 _p[25]
#define threshold2 _p[26]
#define facfactor _p[27]
#define f _p[28]
#define tauF _p[29]
#define d1 _p[30]
#define tauD1 _p[31]
#define d2 _p[32]
#define tauD2 _p[33]
#define aACH _p[34]
#define bACH _p[35]
#define wACH _p[36]
#define aDA _p[37]
#define bDA _p[38]
#define wDA _p[39]
#define i_gabab _p[40]
#define g_gabab _p[41]
#define on_gabab _p[42]
#define W_gabab _p[43]
#define rr_gabab _p[44]
#define i_gabaa _p[45]
#define g_gabaa _p[46]
#define on_gabaa _p[47]
#define W_gabaa _p[48]
#define ICa _p[49]
#define iCatotal _p[50]
#define Wmax _p[51]
#define Wmin _p[52]
#define maxChange _p[53]
#define normW _p[54]
#define scaleW _p[55]
#define pregid _p[56]
#define postgid _p[57]
#define F _p[58]
#define D1 _p[59]
#define D2 _p[60]
#define r_gabab _p[61]
#define s_gabab _p[62]
#define r_gabaa _p[63]
#define Capoolcon _p[64]
#define t0 _p[65]
#define Afactor _p[66]
#define dW_gabaa _p[67]
#define tsyn _p[68]
#define fa _p[69]
#define Dr_gabab _p[70]
#define Ds_gabab _p[71]
#define Dr_gabaa _p[72]
#define DCapoolcon _p[73]
#define v _p[74]
#define _g _p[75]
#define _tsav _p[76]
#define _nd_area  *_ppvar[0]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_VDCCm();
 static double _hoc_eta();
 static double _hoc_omega();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "VDCCm", _hoc_VDCCm,
 "eta", _hoc_eta,
 "omega", _hoc_omega,
 0, 0
};
#define VDCCm VDCCm_inter2pyr
#define eta eta_inter2pyr
#define omega omega_inter2pyr
 extern double VDCCm( _threadargsprotocomma_ double );
 extern double eta( _threadargsprotocomma_ double );
 extern double omega( _threadargsprotocomma_ double , double , double );
 /* declare global and static user variables */
#define ACH ACH_inter2pyr
 double ACH = 1;
#define LearningShutDown LearningShutDown_inter2pyr
 double LearningShutDown = 1;
#define gbar_Ca gbar_Ca_inter2pyr
 double gbar_Ca = 0.018;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "d2", 0, 1,
 "d1", 0, 1,
 "f", 0, 1e+09,
 "tauD2", 1e-09, 1e+09,
 "tauD1", 1e-09, 1e+09,
 "tauF", 1e-09, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gbar_Ca_inter2pyr", "uS",
 "Cdur_gabaa", "ms",
 "AlphaTmax_gabaa", "/ms",
 "Beta_gabaa", "/ms",
 "Erev_gabaa", "mV",
 "gbar_gabaa", "uS",
 "Cdur_gabab", "ms",
 "AlphaTmax_gabab", "/ms",
 "Beta_gabab", "/ms",
 "Erev_gabab", "mV",
 "gbar_gabab", "uS",
 "K3_gabab", "/ms",
 "K4_gabab", "/ms",
 "Cainf", "mM",
 "pooldiam", "micrometer",
 "tauCa", "ms",
 "threshold1", "uM",
 "threshold2", "uM",
 "f", "1",
 "tauF", "ms",
 "d1", "1",
 "tauD1", "ms",
 "d2", "1",
 "tauD2", "ms",
 "i_gabab", "nA",
 "g_gabab", "uS",
 "i_gabaa", "nA",
 "g_gabaa", "uS",
 "ICa", "mA",
 "iCatotal", "mA",
 0,0
};
 static double Capoolcon0 = 0;
 static double delta_t = 0.01;
 static double r_gabaa0 = 0;
 static double r_gabab0 = 0;
 static double s_gabab0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "gbar_Ca_inter2pyr", &gbar_Ca_inter2pyr,
 "ACH_inter2pyr", &ACH_inter2pyr,
 "LearningShutDown_inter2pyr", &LearningShutDown_inter2pyr,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[2]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "6.2.0",
"inter2pyr",
 "initW",
 "Cdur_gabaa",
 "AlphaTmax_gabaa",
 "Beta_gabaa",
 "Erev_gabaa",
 "gbar_gabaa",
 "Cdur_gabab",
 "AlphaTmax_gabab",
 "Beta_gabab",
 "Erev_gabab",
 "gbar_gabab",
 "K3_gabab",
 "K4_gabab",
 "n_gabab",
 "Kd_gabab",
 "ECa",
 "Cainf",
 "pooldiam",
 "z",
 "tauCa",
 "P0a",
 "P0b",
 "fCa",
 "lambda1",
 "lambda2",
 "threshold1",
 "threshold2",
 "facfactor",
 "f",
 "tauF",
 "d1",
 "tauD1",
 "d2",
 "tauD2",
 "aACH",
 "bACH",
 "wACH",
 "aDA",
 "bDA",
 "wDA",
 0,
 "i_gabab",
 "g_gabab",
 "on_gabab",
 "W_gabab",
 "rr_gabab",
 "i_gabaa",
 "g_gabaa",
 "on_gabaa",
 "W_gabaa",
 "ICa",
 "iCatotal",
 "Wmax",
 "Wmin",
 "maxChange",
 "normW",
 "scaleW",
 "pregid",
 "postgid",
 "F",
 "D1",
 "D2",
 0,
 "r_gabab",
 "s_gabab",
 "r_gabaa",
 "Capoolcon",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 77, _prop);
 	/*initialize range parameters*/
 	initW = 5;
 	Cdur_gabaa = 5.31;
 	AlphaTmax_gabaa = 5000;
 	Beta_gabaa = 0.18;
 	Erev_gabaa = -75;
 	gbar_gabaa = 0.0017;
 	Cdur_gabab = 6;
 	AlphaTmax_gabab = 0.09;
 	Beta_gabab = 0.008;
 	Erev_gabab = -75;
 	gbar_gabab = 0.001;
 	K3_gabab = 0.18;
 	K4_gabab = 0.034;
 	n_gabab = 4;
 	Kd_gabab = 100;
 	ECa = 120;
 	Cainf = 5e-05;
 	pooldiam = 1.8172;
 	z = 2;
 	tauCa = 50;
 	P0a = 0.0035;
 	P0b = 0.0015;
 	fCa = 0.024;
 	lambda1 = 2.5;
 	lambda2 = 0.01;
 	threshold1 = 0.2;
 	threshold2 = 0.4;
 	facfactor = 1;
 	f = 1;
 	tauF = 1;
 	d1 = 1;
 	tauD1 = 1;
 	d2 = 1;
 	tauD2 = 1;
 	aACH = 1;
 	bACH = 0;
 	wACH = 0;
 	aDA = 1;
 	bDA = 0;
 	wDA = 0;
  }
 	_prop->param = _p;
 	_prop->param_size = 77;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _synapse_inter2pyr_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 1,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_prop_size(_mechtype, 77, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 inter2pyr /home/tbg28/git_stage/synaptic_plasticity/bmtk_model/biophys_components/mechanisms/x86_64/synapse_inter2pyr.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.0;
 static double pi = 3.141592;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[4], _dlist1[4];
 static int release(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   if ( t0 > 0.0 ) {
     if ( t - t0 < Cdur_gabab ) {
       on_gabab = 1.0 ;
       }
     else {
       on_gabab = 0.0 ;
       }
     if ( t - t0 < Cdur_gabaa ) {
       on_gabaa = 1.0 ;
       }
     else {
       on_gabaa = 0.0 ;
       }
     }
   Dr_gabab = AlphaTmax_gabab * on_gabab * ( 1.0 - r_gabab ) - Beta_gabab * r_gabab ;
   Ds_gabab = K3_gabab * r_gabab - K4_gabab * s_gabab ;
   Dr_gabaa = AlphaTmax_gabaa * on_gabaa * ( 1.0 - r_gabaa ) - Beta_gabaa * r_gabaa ;
   dW_gabaa = eta ( _threadargscomma_ Capoolcon ) * ( lambda1 * omega ( _threadargscomma_ Capoolcon , threshold1 , threshold2 ) - lambda2 * W_gabaa ) * dt ;
   if ( fabs ( dW_gabaa ) > maxChange ) {
     if ( dW_gabaa < 0.0 ) {
       dW_gabaa = - 1.0 * maxChange ;
       }
     else {
       dW_gabaa = maxChange ;
       }
     }
   normW = ( W_gabaa - Wmin ) / ( Wmax - Wmin ) ;
   if ( dW_gabaa < 0.0 ) {
     scaleW = sqrt ( fabs ( normW ) ) ;
     }
   else {
     scaleW = sqrt ( fabs ( 1.0 - normW ) ) ;
     }
   W_gabaa = W_gabaa + dW_gabaa * scaleW * ( 1.0 + ( wACH * ( ACH - 1.0 ) ) ) * LearningShutDown ;
   if ( W_gabaa > Wmax ) {
     W_gabaa = Wmax ;
     }
   else if ( W_gabaa < Wmin ) {
     W_gabaa = Wmin ;
     }
   rr_gabab = pow( s_gabab , n_gabab ) / ( pow( s_gabab , n_gabab ) + Kd_gabab ) ;
   g_gabab = gbar_gabab * rr_gabab * facfactor ;
   i_gabab = W_gabab * g_gabab * ( v - Erev_gabab ) ;
   g_gabaa = gbar_gabaa * r_gabaa * facfactor ;
   i_gabaa = W_gabaa * g_gabaa * ( v - Erev_gabaa ) * ( 1.0 + ( bACH * ( ACH - 1.0 ) ) ) ;
   ICa = P0b * g_gabab * ( v - ECa ) + P0a * gbar_Ca * VDCCm ( _threadargscomma_ v ) * ( v - ECa ) ;
   DCapoolcon = - fCa * Afactor * ICa + ( Cainf - Capoolcon ) / tauCa ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 if ( t0 > 0.0 ) {
   if ( t - t0 < Cdur_gabab ) {
     on_gabab = 1.0 ;
     }
   else {
     on_gabab = 0.0 ;
     }
   if ( t - t0 < Cdur_gabaa ) {
     on_gabaa = 1.0 ;
     }
   else {
     on_gabaa = 0.0 ;
     }
   }
 Dr_gabab = Dr_gabab  / (1. - dt*( ( AlphaTmax_gabab * on_gabab )*( ( ( - 1.0 ) ) ) - ( Beta_gabab )*( 1.0 ) )) ;
 Ds_gabab = Ds_gabab  / (1. - dt*( ( - ( K4_gabab )*( 1.0 ) ) )) ;
 Dr_gabaa = Dr_gabaa  / (1. - dt*( ( AlphaTmax_gabaa * on_gabaa )*( ( ( - 1.0 ) ) ) - ( Beta_gabaa )*( 1.0 ) )) ;
 dW_gabaa = eta ( _threadargscomma_ Capoolcon ) * ( lambda1 * omega ( _threadargscomma_ Capoolcon , threshold1 , threshold2 ) - lambda2 * W_gabaa ) * dt ;
 if ( fabs ( dW_gabaa ) > maxChange ) {
   if ( dW_gabaa < 0.0 ) {
     dW_gabaa = - 1.0 * maxChange ;
     }
   else {
     dW_gabaa = maxChange ;
     }
   }
 normW = ( W_gabaa - Wmin ) / ( Wmax - Wmin ) ;
 if ( dW_gabaa < 0.0 ) {
   scaleW = sqrt ( fabs ( normW ) ) ;
   }
 else {
   scaleW = sqrt ( fabs ( 1.0 - normW ) ) ;
   }
 W_gabaa = W_gabaa + dW_gabaa * scaleW * ( 1.0 + ( wACH * ( ACH - 1.0 ) ) ) * LearningShutDown ;
 if ( W_gabaa > Wmax ) {
   W_gabaa = Wmax ;
   }
 else if ( W_gabaa < Wmin ) {
   W_gabaa = Wmin ;
   }
 rr_gabab = pow( s_gabab , n_gabab ) / ( pow( s_gabab , n_gabab ) + Kd_gabab ) ;
 g_gabab = gbar_gabab * rr_gabab * facfactor ;
 i_gabab = W_gabab * g_gabab * ( v - Erev_gabab ) ;
 g_gabaa = gbar_gabaa * r_gabaa * facfactor ;
 i_gabaa = W_gabaa * g_gabaa * ( v - Erev_gabaa ) * ( 1.0 + ( bACH * ( ACH - 1.0 ) ) ) ;
 ICa = P0b * g_gabab * ( v - ECa ) + P0a * gbar_Ca * VDCCm ( _threadargscomma_ v ) * ( v - ECa ) ;
 DCapoolcon = DCapoolcon  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tauCa )) ;
 return 0;
}
 /*END CVODE*/
 static int release (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   if ( t0 > 0.0 ) {
     if ( t - t0 < Cdur_gabab ) {
       on_gabab = 1.0 ;
       }
     else {
       on_gabab = 0.0 ;
       }
     if ( t - t0 < Cdur_gabaa ) {
       on_gabaa = 1.0 ;
       }
     else {
       on_gabaa = 0.0 ;
       }
     }
    r_gabab = r_gabab + (1. - exp(dt*(( AlphaTmax_gabab * on_gabab )*( ( ( - 1.0 ) ) ) - ( Beta_gabab )*( 1.0 ))))*(- ( ( ( AlphaTmax_gabab )*( on_gabab ) )*( ( 1.0 ) ) ) / ( ( ( AlphaTmax_gabab )*( on_gabab ) )*( ( ( - 1.0 ) ) ) - ( Beta_gabab )*( 1.0 ) ) - r_gabab) ;
    s_gabab = s_gabab + (1. - exp(dt*(( - ( K4_gabab )*( 1.0 ) ))))*(- ( ( K3_gabab )*( r_gabab ) ) / ( ( - ( K4_gabab )*( 1.0 ) ) ) - s_gabab) ;
    r_gabaa = r_gabaa + (1. - exp(dt*(( AlphaTmax_gabaa * on_gabaa )*( ( ( - 1.0 ) ) ) - ( Beta_gabaa )*( 1.0 ))))*(- ( ( ( AlphaTmax_gabaa )*( on_gabaa ) )*( ( 1.0 ) ) ) / ( ( ( AlphaTmax_gabaa )*( on_gabaa ) )*( ( ( - 1.0 ) ) ) - ( Beta_gabaa )*( 1.0 ) ) - r_gabaa) ;
   dW_gabaa = eta ( _threadargscomma_ Capoolcon ) * ( lambda1 * omega ( _threadargscomma_ Capoolcon , threshold1 , threshold2 ) - lambda2 * W_gabaa ) * dt ;
   if ( fabs ( dW_gabaa ) > maxChange ) {
     if ( dW_gabaa < 0.0 ) {
       dW_gabaa = - 1.0 * maxChange ;
       }
     else {
       dW_gabaa = maxChange ;
       }
     }
   normW = ( W_gabaa - Wmin ) / ( Wmax - Wmin ) ;
   if ( dW_gabaa < 0.0 ) {
     scaleW = sqrt ( fabs ( normW ) ) ;
     }
   else {
     scaleW = sqrt ( fabs ( 1.0 - normW ) ) ;
     }
   W_gabaa = W_gabaa + dW_gabaa * scaleW * ( 1.0 + ( wACH * ( ACH - 1.0 ) ) ) * LearningShutDown ;
   if ( W_gabaa > Wmax ) {
     W_gabaa = Wmax ;
     }
   else if ( W_gabaa < Wmin ) {
     W_gabaa = Wmin ;
     }
   rr_gabab = pow( s_gabab , n_gabab ) / ( pow( s_gabab , n_gabab ) + Kd_gabab ) ;
   g_gabab = gbar_gabab * rr_gabab * facfactor ;
   i_gabab = W_gabab * g_gabab * ( v - Erev_gabab ) ;
   g_gabaa = gbar_gabaa * r_gabaa * facfactor ;
   i_gabaa = W_gabaa * g_gabaa * ( v - Erev_gabaa ) * ( 1.0 + ( bACH * ( ACH - 1.0 ) ) ) ;
   ICa = P0b * g_gabab * ( v - ECa ) + P0a * gbar_Ca * VDCCm ( _threadargscomma_ v ) * ( v - ECa ) ;
    Capoolcon = Capoolcon + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tauCa)))*(- ( ( ( - fCa )*( Afactor ) )*( ICa ) + ( ( Cainf ) ) / tauCa ) / ( ( ( ( - 1.0 ) ) ) / tauCa ) - Capoolcon) ;
   }
  return 0;
}
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{  double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _thread = (Datum*)0; _nt = (_NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t; {
   F = 1.0 + ( F - 1.0 ) * exp ( - ( t - tsyn ) / tauF ) ;
   D1 = 1.0 - ( 1.0 - D1 ) * exp ( - ( t - tsyn ) / tauD1 ) ;
   D2 = 1.0 - ( 1.0 - D2 ) * exp ( - ( t - tsyn ) / tauD2 ) ;
   tsyn = t ;
   facfactor = F * D1 * D2 ;
   F = F * f ;
   D1 = D1 * d1 ;
   D2 = D2 * d2 ;
   t0 = t ;
   } }
 
double eta ( _threadargsprotocomma_ double _lCani ) {
   double _leta;
 double _ltaulearn , _lP1 , _lP2 , _lP4 , _lCacon ;
 _lP1 = 0.1 ;
   _lP2 = _lP1 * 1e-4 ;
   _lP4 = 1.0 ;
   _lCacon = _lCani * 1e3 ;
   _ltaulearn = _lP1 / ( _lP2 + _lCacon * _lCacon * _lCacon ) + _lP4 ;
   _leta = 1.0 / _ltaulearn * 0.001 ;
   
return _leta;
 }
 
static double _hoc_eta(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  eta ( _p, _ppvar, _thread, _nt, *getarg(1) );
 return(_r);
}
 
double VDCCm ( _threadargsprotocomma_ double _lv ) {
   double _lVDCCm;
  _lVDCCm = 1.0 / ( 1.0 + exp ( ( - 4.0 - _lv ) / 6.3 ) ) ;
    
return _lVDCCm;
 }
 
static double _hoc_VDCCm(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  VDCCm ( _p, _ppvar, _thread, _nt, *getarg(1) );
 return(_r);
}
 
double omega ( _threadargsprotocomma_ double _lCani , double _lthreshold1 , double _lthreshold2 ) {
   double _lomega;
 double _lr , _lmid , _lCacon ;
 _lCacon = _lCani * 1e3 ;
   _lr = ( _lthreshold2 - _lthreshold1 ) / 2.0 ;
   _lmid = ( _lthreshold1 + _lthreshold2 ) / 2.0 ;
   if ( _lCacon <= _lthreshold1 ) {
     _lomega = 0.0 ;
     }
   else if ( _lCacon >= _lthreshold2 ) {
     _lomega = 1.0 / ( 1.0 + 50.0 * exp ( - 50.0 * ( _lCacon - _lthreshold2 ) ) ) ;
     }
   else {
     _lomega = - sqrt ( _lr * _lr - ( _lCacon - _lmid ) * ( _lCacon - _lmid ) ) ;
     }
   
return _lomega;
 }
 
static double _hoc_omega(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  omega ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) );
 return(_r);
}
 
static int _ode_count(int _type){ return 4;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 4; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  Capoolcon = Capoolcon0;
  r_gabaa = r_gabaa0;
  r_gabab = r_gabab0;
  s_gabab = s_gabab0;
 {
   on_gabab = 0.0 ;
   r_gabab = 0.0 ;
   s_gabab = 0.0 ;
   W_gabab = initW ;
   on_gabaa = 0.0 ;
   r_gabaa = 0.0 ;
   W_gabaa = initW ;
   t0 = - 1.0 ;
   maxChange = ( Wmax - Wmin ) / 10.0 ;
   dW_gabaa = 0.0 ;
   Capoolcon = Cainf ;
   Afactor = 1.0 / ( z * FARADAY * 4.0 / 3.0 * pi * pow( ( pooldiam / 2.0 ) , 3.0 ) ) * ( 1e6 ) ;
   tsyn = - 1e30 ;
   fa = 0.0 ;
   F = 1.0 ;
   D1 = 1.0 ;
   D2 = 1.0 ;
   }
 
}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _tsav = -1e20;
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   }
 _current += i_gabab;
 _current += i_gabaa;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 {   release(_p, _ppvar, _thread, _nt);
  }}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(r_gabab) - _p;  _dlist1[0] = &(Dr_gabab) - _p;
 _slist1[1] = &(s_gabab) - _p;  _dlist1[1] = &(Ds_gabab) - _p;
 _slist1[2] = &(r_gabaa) - _p;  _dlist1[2] = &(Dr_gabaa) - _p;
 _slist1[3] = &(Capoolcon) - _p;  _dlist1[3] = &(DCapoolcon) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif
