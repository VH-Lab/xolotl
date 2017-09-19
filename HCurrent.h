// H current. again, for mysterious reasons, the compiler
// won't let me call this class "H"
#ifndef HCURRENT
#define HCURRENT
#include "conductance.h"

//inherit conductance class spec
class HCurrent: public conductance {
    
public:

    //specify both gbar and erev and initial conditions
    HCurrent(double g_, double E_, double m_)
    {
        gbar = g_;
        E = E_;
        m = m_;
        h = 1;
    }

    HCurrent(double g_, double E_, double m_, double h_)
    {
        gbar = g_;
        E = E_;
        m = m_;
        h = 1;
    }
    
    double getCurrent(void);
    void integrate(double V, double Ca, double dt);
    void connect(compartment *pcomp_);
    double m_inf(double V);
    double tau_m(double V);

};

void HCurrent::connect(compartment *pcomp_) {container = pcomp_;}

void HCurrent::integrate(double V, double Ca, double dt)
{
    m = m_inf(V) + (m - m_inf(V))*exp(-dt/tau_m(V));
    g = gbar*m;
}


double HCurrent::m_inf(double V) {return 1.0/(1.0+exp((V+70.0)/6.0));}
double HCurrent::tau_m(double V) {return (272.0 + 1499.0/(1.0+exp((V+42.2)/-8.73)));}


#endif
