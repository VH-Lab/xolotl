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
        n=n_;

        // defaults 
        if (isnan(gbar)) { gbar = 12e-6; }
        
        
        if (isnan (E)) { E = 0.045; }

        unitary_conductance = 20e-6; // uS

        p = 3;
        q = 1;

    }

    double m_inf(double, double);
    double h_inf(double, double);
//     double n_inf(double,double);
    double tau_m(double, double);
    double tau_h(double, double);


    double AlphaM(double);
    double AlphaH(double);
//     double AlphaN(double);
    double BetaM(double);
    double BetaH(double);
//     double BetaN(double);

    string getClass(void);
};

string NaV::getClass(){return "NaV";}


double NaV::AlphaM(double V) {
    if V==-0.045
    return 1e3;
    else
    return (1e5*(-V-0.045))/(exp(100*(-V-0.045))-1);
}

double NaV::AlphaH(double V) {
    return 70*exp(50*(-V-0.070));
}

// double NaV::AlphaN(double V) {
//     if V==-0.06
//     return 100
//     else
//     return 1e4*(-V-0.060))/(exp((100*(-V-0.060))-1)
// }

double NaV::BetaM(double V) {
    return 4*exp(-V/18);
}

double NaV::BetaH(double V) {
    return 1/(exp((30-V)/10)+1);
}

// double NaV::BetaN(double V) {
//     return 125*exp((-V-0.070)/0.08);
// }

// problematic -- this doesn't really work
double NaV::m_inf(double V, double Ca) {return AlphaM(V)/(AlphaM(V)+BetaM(V));}

double NaV::tau_m(double V, double Ca) {return 1.0/(AlphaM(V)+BetaM(V));}
double NaV::m(double V, double Ca, double m_inf, double tau_m) {return m_inf-m*dt/tau_m;}
double NaV::h_inf(double V, double Ca) {return AlphaH(V)/(AlphaH(V)+BetaH(V));}
double NaV::tau_h(double V, double Ca) {return 1.0/(AlphaH(V)+BetaH(V));}
double NaV::h(double V, double Ca, double h_inf, double tau_h) {return (h_inf-h)*dt/tau_h;}

// double NaV::n_inf(double V, double Ca) {return AlphaN(V)/(AlphaN(V)+BetaN(V));}
// double NaV::tau_n(double V, double Ca) {return 1/(AlphaN(V)+BetaN(V));}x

double NaV::g_bar(double V, double Ca,double g_bar, double E) {return g_bar*m*m*h*(E-V);}

#endif