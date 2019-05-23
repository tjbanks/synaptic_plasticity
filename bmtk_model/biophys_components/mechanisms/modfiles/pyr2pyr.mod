NEURON {
	POINT_PROCESS pyr2pyr
	NONSPECIFIC_CURRENT i_nmda, i_ampa
	RANGE initW
	RANGE Cdur_nmda, AlphaTmax_nmda, Beta_nmda, Erev_nmda, gbar_nmda, W_nmda, on_nmda, g_nmda
	RANGE Cdur_ampa, AlphaTmax_ampa, Beta_ampa, Erev_ampa, gbar_ampa, W_ampa, on_ampa, g_ampa
	RANGE ECa, ICa, P0, fCa, tauCa, iCatotal
	RANGE Cainf, pooldiam, z
	RANGE lambda1, lambda2, threshold1, threshold2
	RANGE fmax, fmin, Wmax, Wmin, maxChange, normW, scaleW
	RANGE pregid,postgid
	
	:Added by Ali
	RANGE F, f, tauF, D1, d1, tauD1, D2, d2, tauD2
	RANGE facfactor
	RANGE aACH, bACH, aDA, bDA, wACH, wDA, calcium
}

UNITS {
	(mV) = (millivolt)
        (nA) = (nanoamp)
	(uS) = (microsiemens)
	FARADAY = 96485 (coul)
	pi = 3.141592 (1)
}

PARAMETER {
: parameters are vars assigned by user or changed by hoc. THey appear in nrnpointmenu
	initW = 5

	Cdur_nmda = 10 (ms)
	AlphaTmax_nmda = .088 (/ms)
	Beta_nmda = 0.0033 (/ms) :.008
	Erev_nmda = 0 (mV)
	gbar_nmda = 0.0017 (uS) :.6e-3

	Cdur_ampa = 2.4(ms) :5.31 
	AlphaTmax_ampa = 0.58 (/ms) :0.117 
	Beta_ampa = 0.091 (/ms)
	Erev_ampa = 0 (mV)
	gbar_ampa = 1.7e-3 (uS)

	ECa = 120

	Cainf = 50e-6 (mM)
	pooldiam =  1.8172 (micrometer)
	z = 2

	tauCa = 50 (ms)
	P0 = .015
	fCa = .024

	lambda1 = 2.5
	lambda2 = .01
	threshold1 = 0.2 (uM)
	threshold2 = 0.4 (uM)

	fmax = 3
	fmin = .8

	:Added by Ali
	ACH = 1
	DA = 1
	LearningShutDown = 1

	facfactor = 1
	: the (1) is needed for the range limits to be effective
        f = 1 (1) < 0, 1e9 >    : facilitation
        tauF = 1 (ms) < 1e-9, 1e9 >
        d1 = 1 (1) < 0, 1 >     : fast depression
        tauD1 = 1 (ms) < 1e-9, 1e9 >
        d2 = 1 (1) < 0, 1 >     : slow depression
        tauD2 = 1 (ms) < 1e-9, 1e9 >
		
	aACH = 1
	bACH = 0
	wACH = 0
	aDA = 1
	bDA = 0
	wDA = 0

}

ASSIGNED {
: These are vars calculated by Neuron hoc or by the mechanism mod itself
	v (mV)

	i_nmda (nA)
	g_nmda (uS)
	on_nmda
	W_nmda

	i_ampa (nA)
	g_ampa (uS)
	on_ampa
	W_ampa

	t0 (ms)

	ICa (mA)
	Afactor	(mM/ms/nA)
	iCatotal (mA)

	dW_ampa
	Wmax
	Wmin
	maxChange
	normW
	scaleW
	
	pregid
	postgid
	
	:Added by Ali
		calcium

		tsyn
	
		fa
		F
		D1
		D2
		
}

STATE { r_nmda r_ampa Capoolcon }

INITIAL {
	on_nmda = 0
	r_nmda = 0
	W_nmda = initW

	on_ampa = 0
	r_ampa = 0
	W_ampa = initW

	t0 = -1

	:Wmax = 2*initW
	:Wmin = 0.25*initW
	maxChange = (Wmax-Wmin)/10
	dW_ampa = 0

	Capoolcon = Cainf
	Afactor	= 1/(z*FARADAY*4/3*pi*(pooldiam/2)^3)*(1e6)
	
	:Added by Ali

		tsyn = -1e30

	fa =0
	F = 1
	D1 = 1
	D2 = 1

}

BREAKPOINT {
	SOLVE release METHOD cnexp
}

DERIVATIVE release {
	if (t0>0) {
		if (t-t0 < Cdur_nmda) {
			on_nmda = 1
		} else {
			on_nmda = 0
		}
		if (t-t0 < Cdur_ampa) {
			on_ampa = 1
		} else {
			on_ampa = 0
		}
	}
	r_nmda' = AlphaTmax_nmda*on_nmda*(1-r_nmda) -Beta_nmda*r_nmda
	r_ampa' = AlphaTmax_ampa*on_ampa*(1-r_ampa) -Beta_ampa*r_ampa

	dW_ampa = eta(Capoolcon)*(lambda1*omega(Capoolcon, threshold1, threshold2)-lambda2*W_ampa)*dt

	: Limit for extreme large weight changes
	if (fabs(dW_ampa) > maxChange) {
		if (dW_ampa < 0) {
			dW_ampa = -1*maxChange
		} else {
			dW_ampa = maxChange
		}
	}

	:Normalize the weight change
	normW = (W_ampa-Wmin)/(Wmax-Wmin)
	if (dW_ampa < 0) {
		scaleW = sqrt(fabs(normW))
	} else {
		scaleW = sqrt(fabs(1.0-normW))
	}

	W_ampa = W_ampa + dW_ampa*scaleW *(1+ (wACH * (ACH - 1))) * LearningShutDown
	
	:Weight value limits
	if (W_ampa > Wmax) { 
		W_ampa = Wmax
	} else if (W_ampa < Wmin) {
 		W_ampa = Wmin
	}

	g_nmda = gbar_nmda*r_nmda * facfactor
	i_nmda = W_nmda*g_nmda*(v - Erev_nmda)*sfunc(v)

	g_ampa = gbar_ampa*r_ampa * facfactor
	i_ampa = W_ampa*g_ampa*(v - Erev_ampa)  * (1 + (bACH * (ACH-1)))*(aDA + (bDA * (DA-1))) 

	ICa = P0*g_nmda*(v - ECa)*sfunc(v)
	Capoolcon'= -fCa*Afactor*ICa + (Cainf-Capoolcon)/tauCa
}

NET_RECEIVE(dummy_weight) {
	t0 = t :spike time for conductance opening
	
	:Added by Ali, Synaptic facilitation
	F  = 1 + (F-1)* exp(-(t - tsyn)/tauF)
	D1 = 1 - (1-D1)*exp(-(t - tsyn)/tauD1)
	D2 = 1 - (1-D2)*exp(-(t - tsyn)/tauD2)
 :printf("%g\t%g\t%g\t%g\t%g\t%g\n", t, t-tsyn, F, D1, D2, facfactor)
	tsyn = t
	
	facfactor = F * D1 * D2

	F = F * f
	
	if (F > 30) { 
	F=30
	}
	D1 = D1 * d1
	D2 = D2 * d2
:printf("\t%g\t%g\t%g\n", F, D1, D2)
	


}

:::::::::::: FUNCTIONs and PROCEDUREs ::::::::::::

FUNCTION sfunc (v (mV)) {
	UNITSOFF
	sfunc = 1/(1+0.33*exp(-0.06*v))
	UNITSON
}

FUNCTION eta(Cani (mM)) {
	LOCAL taulearn, P1, P2, P4, Cacon
	P1 = 0.1
	P2 = P1*1e-4
	P4 = 1
	Cacon = Cani*1e3
	taulearn = P1/(P2+Cacon*Cacon*Cacon)+P4
	eta = 1/taulearn*0.001
}

FUNCTION omega(Cani (mM), threshold1 (uM), threshold2 (uM)) {
	LOCAL r, mid, Cacon
	Cacon = Cani*1e3
	r = (threshold2-threshold1)/2
	mid = (threshold1+threshold2)/2
	if (Cacon <= threshold1) { omega = 0}
	else if (Cacon >= threshold2) {	omega = 1/(1+50*exp(-50*(Cacon-threshold2)))}
	else {omega = -sqrt(r*r-(Cacon-mid)*(Cacon-mid))}
}
