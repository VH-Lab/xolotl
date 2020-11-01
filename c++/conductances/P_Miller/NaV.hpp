// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// Sodium CONDUCTANCE
// component source [P. Miller](https://mitpress.mit.edu/books/introductory-course-computational-neuroscience)
// 
#ifndef NAV
#define NAV
#include "conductance.hpp"

//inherit conductance class spec
class NaV: public conductance {

public:

    // specify parameters + initial conditions
    NaV(double gbar_, double E_, double m_, double h_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;
        h = h_;

        // defaults 
        if (isnan(gbar)) { gbar = 0; }
        
        if (isnan (E)) { E = 45; }
        
        p = 3;
        q = 1;
    }

    double m_inf(double, double);
    double h_inf(double, double);
    double tau_m(double, double);
    double tau_h(double, double);


    double AlphaM(double);
    double AlphaH(double);
    double BetaM(double);
    double BetaH(double);

    string getClass(void);
};

string NaV::getClass(){return "NaV";}

double NaV::AlphaM(double V) {
    if (V==-0.045) {
        return 1e3;
    } else {
        return (1e5*(-V/1000-0.045))/(exp(100*(-V/1000-0.045))-1);
    }
}

double NaV::AlphaH(double V) {
    return 70*exp(50*(-V/1000-0.070));
}

// double NaV::AlphaN(double V) {
//     if V==-0.06
//     return 100
//     else
//     return 1e4*(-V-0.060))/(exp((100*(-V-0.060))-1)
// }

double NaV::BetaM(double V) {
    return 4000*exp((-V/1000-0.070)/0.018);
}

double NaV::BetaH(double V) {
    return 1000/(1+exp(100*(-V/1000-0.040)));
}

// double NaV::BetaN(double V) {
//     return 125*exp((-V-0.070)/0.08);
// }

// problematic -- this doesn't really work
double NaV::m_inf(double V, double Ca) {return AlphaM(V)/(AlphaM(V)+BetaM(V));}

double NaV::tau_m(double V, double Ca) {return 1000.0/(AlphaM(V)+BetaM(V));}
double NaV::h_inf(double V, double Ca) {return AlphaH(V)/(AlphaH(V)+BetaH(V));}
double NaV::tau_h(double V, double Ca) {return 1000.0/(AlphaH(V)+BetaH(V));}

#endif