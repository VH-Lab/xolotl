// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// inward rectifying potassium conductance
// component source [P. Miller](https://mitpress.mit.edu/books/introductory-course-computational-neuroscience)
// 
#ifndef KD
#define KD
#include "conductance.hpp"

//inherit conductance class spec
class Kd: public conductance {

public:

    //specify both gbar and erev and initial conditions
    Kd(double gbar_, double E_, double m_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;

        // defaults 
        if (isnan(gbar)) { gbar = 0; }
        if (isnan (E)) { E = -82; }
        
        p = 4;
    }

    double m_inf(double, double);
    double tau_m(double, double);
    string getClass(void);

    double Alpha(double);
    double Beta(double);

};

string Kd::getClass(){
    return "Kd";
}

double Kd::Alpha(double V) {
    if (V==-060) {
            return 100.0; // return 100*1e-3; // ms
    }
    else {
        return (1e4*(-V/1000.0-0.060))/(exp(100*(-V/1000.0-0.060))-1); //ms
    }
}

double Kd::Beta(double V) {
    return 125*exp((-V/1000.0-0.070)/0.08);
}

double Kd::m_inf(double V, double Ca) {return Alpha(V)/(Alpha(V)+Beta(V)); }
double Kd::tau_m(double V, double Ca) {return 1000.0/(Alpha(V)+Beta(V));}


#endif