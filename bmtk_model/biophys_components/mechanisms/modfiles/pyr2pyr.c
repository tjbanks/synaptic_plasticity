/* Created by Language version: 7.5.0 */
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
 
#define nrn_init _nrn_init__pyr2pyr
#define _nrn_initial _nrn_initial__pyr2pyr
#define nrn_cur _nrn_cur__pyr2pyr
#define _nrn_current _nrn_current__pyr2pyr
#define nrn_jacob _nrn_jacob__pyr2pyr
#define nrn_state _nrn_state__pyr2pyr
#define _net_receive _net_receive__pyr2pyr 
 
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
#define Cdur_nmda _p[1]
#define AlphaTmax_nmda _p[2]
#define Beta_nmda _p[3]
#define Erev_nmda _p[4]
#define gbar_nmda _p[5]
#define Cdur_ampa _p[6]
#define AlphaTmax_ampa _p[7]
#define Beta_ampa _p[8]
#define Erev_ampa _p[9]
#define gbar_ampa _p[10]
#define ECa _p[11]
#define Cainf _p[12]
#define pooldiam _p[13]
#define z _p[14]
#define tauCa _p[15]
#define P0 _p[16]
#define fCa _p[17]
#define lambda1 _p[18]
#define lambda2 _p[19]
#define threshold1 _p[20]
#define threshold2 _p[21]
#define fmax _p[22]
#define fmin _p[23]
#define facfactor _p[24]
#define f _p[25]
#define tauF _p[26]
#define d1 _p[27]
#define tauD1 _p[28]
#define d2 _p[29]
#define tauD2 _p[30]
#define aACH _p[31]
#define bACH _p[32]
#define wACH _p[33]
#define aDA _p[34]
#define bDA _p[35]
#define wDA _p[36]
#define i_nmda _p[37]
#define g_nmda _p[38]
#define on_nmda _p[39]
#define W_nmda _p[40]
#define i_ampa _p[41]
#define g_ampa _p[42]
#define on_ampa _p[43]
#define W_ampa _p[44]
#define ICa _p[45]
#define iCatotal _p[46]
#define Wmax _p[47]
#define Wmin _p[48]
#define maxChange _p[49]
#define normW _p[50]
#define scaleW _p[51]
#define pregid _p[52]
#define postgid _p[53]
#define calcium _p[54]
#define F _p[55]
#define D1 _p[56]
#define D2 _p[57]
#define r_nmda _p[58]
#define r_ampa _p[59]
#define Capoolcon _p[60]
#define t0 _p[61]
#define Afactor _p[62]
#define dW_ampa _p[63]
#define tsyn _p[64]
#define fa _p[65]
#define Dr_nmda _p[66]
#define Dr_ampa _p[67]
#define DCapoolcon _p[68]
#define v _p[69]
#define _g _p[70]
#define _tsav _p[71]
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
 static double _hoc_eta();
 static double _hoc_omega();
 static double _hoc_sfunc();
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
 "eta", _hoc_eta,
 "omega", _hoc_omega,
 "sfunc", _hoc_sfunc,
 0, 0
};
#define eta eta_pyr2pyr
#define omega omega_pyr2pyr
#define sfunc sfunc_pyr2pyr
 extern double eta( _threadargsprotocomma_ double );
 extern double omega( _threadargsprotocomma_ double , double , double );
 extern double sfunc( _threadargsprotocomma_ double );
 /* declare global and static user variables */
#define ACH ACH_pyr2pyr
 double ACH = 1;
#define DA DA_pyr2pyr
 double DA = 1;
#define LearningShutDown LearningShutDown_pyr2pyr
 double LearningShutDown = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "d2", 0, 1,
 "d1", 0, 1,
 "f", 0, 1e+009,
 "tauD2", 1e-009, 1e+009,
 "tauD1", 1e-009, 1e+009,
 "tauF", 1e-009, 1e+009,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "Cdur_nmda", "ms",
 "AlphaTmax_nmda", "/ms",
 "Beta_nmda", "/ms",
 "Erev_nmda", "mV",
 "gbar_nmda", "uS",
 "Cdur_ampa", "ms",
 "AlphaTmax_ampa", "/ms",
 "Beta_ampa", "/ms",
 "Erev_ampa", "mV",
 "gbar_ampa", "uS",
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
 "i_nmda", "nA",
 "g_nmda", "uS",
 "i_ampa", "nA",
 "g_ampa", "uS",
 "ICa", "mA",
 "iCatotal", "mA",
 0,0
};
 static double Capoolcon0 = 0;
 static double r_ampa0 = 0;
 static double r_nmda0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "ACH_pyr2pyr", &ACH_pyr2pyr,
 "DA_pyr2pyr", &DA_pyr2pyr,
 "LearningShutDown_pyr2pyr", &LearningShutDown_pyr2pyr,
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
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.5.0",
"pyr2pyr",
 "initW",
 "Cdur_nmda",
 "AlphaTmax_nmda",
 "Beta_nmda",
 "Erev_nmda",
 "gbar_nmda",
 "Cdur_ampa",
 "AlphaTmax_ampa",
 "Beta_ampa",
 "Erev_ampa",
 "gbar_ampa",
 "ECa",
 "Cainf",
 "pooldiam",
 "z",
 "tauCa",
 "P0",
 "fCa",
 "lambda1",
 "lambda2",
 "threshold1",
 "threshold2",
 "fmax",
 "fmin",
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
 "i_nmda",
 "g_nmda",
 "on_nmda",
 "W_nmda",
 "i_ampa",
 "g_ampa",
 "on_ampa",
 "W_ampa",
 "ICa",
 "iCatotal",
 "Wmax",
 "Wmin",
 "maxChange",
 "normW",
 "scaleW",
 "pregid",
 "postgid",
 "calcium",
 "F",
 "D1",
 "D2",
 0,
 "r_nmda",
 "r_ampa",
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
 	_p = nrn_prop_data_alloc(_mechtype, 72, _prop);
 	/*initialize range parameters*/
 	initW = 5;
 	Cdur_nmda = 10;
 	AlphaTmax_nmda = 0.088;
 	Beta_nmda = 0.0033;
 	Erev_nmda = 0;
 	gbar_nmda = 0.0017;
 	Cdur_ampa = 2.4;
 	AlphaTmax_ampa = 0.58;
 	Beta_ampa = 0.091;
 	Erev_ampa = 0;
 	gbar_ampa = 0.0017;
 	ECa = 120;
 	Cainf = 5e-005;
 	pooldiam = 1.8172;
 	z = 2;
 	tauCa = 50;
 	P0 = 0.015;
 	fCa = 0.024;
 	lambda1 = 2.5;
 	lambda2 = 0.01;
 	threshold1 = 0.2;
 	threshold2 = 0.4;
 	fmax = 3;
 	fmin = 0.8;
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
 	_prop->param_size = 72;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 2, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _pyr2pyr_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 1,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
  hoc_register_prop_size(_mechtype, 72, 2);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 pyr2pyr C:/Users/Tyler/Desktop/git_stage/synaptic_plasticity/bmtk_model/biophys_components/mechanisms/modfiles/pyr2pyr.mod\n");
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
 
static void _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{  double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _thread = (Datum*)0; _nt = (_NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t; {
   t0 = t ;
   F = 1.0 + ( F - 1.0 ) * exp ( - ( t - tsyn ) / tauF ) ;
   D1 = 1.0 - ( 1.0 - D1 ) * exp ( - ( t - tsyn ) / tauD1 ) ;
   D2 = 1.0 - ( 1.0 - D2 ) * exp ( - ( t - tsyn ) / tauD2 ) ;
   tsyn = t ;
   facfactor = F * D1 * D2 * _args[0] ;
   F = F * f ;
   if ( F > 30.0 ) {
     F = 30.0 ;
     }
   D1 = D1 * d1 ;
   D2 = D2 * d2 ;
   } }
 
double sfunc ( _threadargsprotocomma_ double _lv ) {
   double _lsfunc;
  _lsfunc = 1.0 / ( 1.0 + 0.33 * exp ( - 0.06 * _lv ) ) ;
    
return _lsfunc;
 }
 
static double _hoc_sfunc(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (_NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  sfunc ( _p, _ppvar, _thread, _nt, *getarg(1) );
 return(_r);
}
 
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

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  Capoolcon = Capoolcon0;
  r_ampa = r_ampa0;
  r_nmda = r_nmda0;
 {
   on_nmda = 0.0 ;
   r_nmda = 0.0 ;
   W_nmda = initW ;
   on_ampa = 0.0 ;
   r_ampa = 0.0 ;
   W_ampa = initW ;
   t0 = - 1.0 ;
   maxChange = ( Wmax - Wmin ) / 10.0 ;
   dW_ampa = 0.0 ;
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
   g_ampa = gbar_ampa * facfactor ;
   i_ampa = g_ampa * ( v - Erev_ampa ) ;
   }
 _current += i_nmda;
 _current += i_ampa;

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

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif
