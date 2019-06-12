: Delayed rectifier K+ current channel

NEURON {
	SUFFIX kdr
	USEION k READ ek WRITE ik
	RANGE gbar, g
	RANGE inf, tau
	RANGE ik
}

UNITS {
	(mA) = (milliamp)
	(mV) = (millivolt)
}

PARAMETER {
	gbar (siemens/cm2)
}

ASSIGNED {
	v (mV)
	ek (mV)
	ik (mA/cm2)
	g (siemens/cm2)
	inf
	tau (ms)
}

STATE {
	n
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	g = gbar*n*n*n*n
	ik = g*(v-ek)
}

INITIAL {
	rate(v)
	n = inf
}

DERIVATIVE states {
	rate(v)
	n' = (inf-n)/tau
}
PROCEDURE rate(v (mV)) {
	UNITSOFF
	inf = 1.0/(1.0 + (exp ((v+12.3)/(-11.8))))         
	tau = 14.4 - 12.8/(1.0+(exp ((v+28.3)/(-19.2))))  
	UNITSON
}
