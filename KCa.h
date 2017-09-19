// Slow Calcium conductance
#ifndef KCA
#define KCA
#include "conductance.h"

//inherit conductance class spec
class KCa: public conductance {

public:

    // specify parameters + initial conditions 
    KCa(double g_, double E_, double m_, double h_)
    {
        gbar = g_;
        E = E_;
        m = m_;
        h = 1;
    }
    
    KCa(double g_, double E_, double m_)
    {
        gbar = g_;
        E = E_;
        m = m_;
        h = 1;
    }
    

    double getCurrent(void);
    void integrate(double V, double Ca, double dt);
    void connect(compartment *pcomp_);
    double m_inf(double V, double Ca);
    double tau_m(double V);

};

void KCa::connect(compartment *pcomp_) {container = pcomp_; }

void KCa::integrate(double V, double Ca, double dt)
{
    m = m_inf(V,Ca) + (m - m_inf(V,Ca))*exp(-dt/tau_m(V));
    g = gbar*m*m*m*m;
}

double KCa::m_inf(double V, double Ca) { return (Ca/(Ca+3.0))/(1.0+exp((V+28.3)/-12.6)); }
double KCa::tau_m(double V) {return 90.3 - 75.1/(1.0+exp((V+46.0)/-22.7));}


#endif
