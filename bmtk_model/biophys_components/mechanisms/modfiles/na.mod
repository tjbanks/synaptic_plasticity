: Fast spike generating Na current channel

NEURON {
	SUFFIX na
	USEION na READ ena WRITE ina
	RANGE gbar, g
	RANGE minf, hinf, mtau, htau
	RANGE ina
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
	ena (mV)
	ina (mA/cm2)
	minf
	hinf
	mtau (ms)
	htau (ms)
	g (siemens/cm2)
}

STATE {
	m h
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	g = gbar*m*m*m*h
	ina = g*(v-ena)
}

INITIAL {
	rate(v)
	m = minf
	h = hinf
}

DERIVATIVE states {
	rate(v)
	m' = (minf-m)/mtau
	h' = (hinf-h)/htau
}

PROCEDURE rate(v (mV)) {
	UNITSOFF
	minf = 1.0/(1.0+ (exp ((v+25.5)/(-5.29))))
	mtau = (2.64 - 2.52/(1.0+ (exp ((v+120)/(-25)))))    
	hinf = 1.0/(1.0+ (exp ((v+48.9)/(5.18))))  
	htau = (1.34/(1+ (exp ((v+62.9)/(-10)))))*(1.5 + 1.0/(1.0 + (exp ((v+34.9)/(3.6)))))
	UNITSON
}
