NEURON {
  POINT_PROCESS IZH
  NONSPECIFIC_CURRENT vv
  RANGE a,b,c,d,e,f,I,vv,thresh, vr, vt, vpeak, aACH, cACH, dACH,alphaShutdown, bACH, ACHshutdown, aMin, aMax, g, vrACH, k, Cap, uinit
}
UNITS {
	(mV) = (millivolt)
    (nA) = (nanoamp)
	(pA) = (picoamp)
	(uS) = (microsiemens)
	(nS) = (nanosiemens)
}

INITIAL {
u = uinit
net_send(0,1)
}

PARAMETER {  
: these are default parameters, if parameters were not set up by the user. 
  k = 0.0011 (nA/mV2) :(1/mV*megaohm) 
  a = 0.01 (1/ms)
  b = 0.0002 (uS)
  c = -65 (mV)
  d = .001 (nA)

 
  vpeak= 30 (mV)
  vv = 0 (mV)
  vr = - 70 (mV)
  vt = - 45 (mV)

  a_OLM = 0.002
  ACH = 1 	 		: Baseline levels of ACh
  dACH = 0 (nA)		: Determines the direction of the magnitude of ACh effects on the Izhikevitch parameter 'd' 
  cACH = 0 (mV)		: Determines the direction of the magnitude of ACh effects on the Izhikevitch parameter 'c' 
  vrACH = 0 (mV)	: Determines the direction of the magnitude of ACh effects on Cell's resting membrane potential  
  bACH = 1.25
  
  ACHshutdown = 0	: Takes the value of 1 only for OLM cells to allow the calculation of parameter 'a' 
  
  uinit = 0 (nA)
  
}

STATE { u }

ASSIGNED {
  }

BREAKPOINT {
  SOLVE states METHOD derivimplicit
  vv = -(k*(v - (vr + vrACH * (-1+ ACH) ))*(v - vt) - u)
  
  a_OLM = 0.023*ACH^2 - 0.022*ACH + 0.002 : The parameter 'a' for OLM cells was fit to the polynomial function of ACh of second degree to reproduce the effects described in the paper 
}

DERIVATIVE states {
    u' = (a_OLM * ACHshutdown + a )*(b*(v - (vr + vrACH * (-1+ ACH) ))-u)
}

NET_RECEIVE (w) {
  if (flag == 1) {
    WATCH (v>vpeak) 2
  } else if (flag == 2) {
    net_event(t)
    v = c + cACH * (-1+ACH) 
    u = u+d + dACH * (1-ACH)
  }
}


