// One way Axial synapse
// meant to be used for multi-compartment models
#ifndef AXIAL
#define AXIAL
#include "synapse.hpp"

class Axial: public synapse {

public:

    double resistivity;

    // specify parameters + initial conditions 
    Axial(double resistivity_, double gbar_)
    {
        resistivity = resistivity_;
        gbar = gbar_;

        if (isnan(resistivity)) {resistivity = 1e-3;}
    }
    
    void integrate(double dt);
    void connect(compartment *pcomp1_, compartment *pcomp2_);
    double getCurrent(double V_post);
};

void Axial::integrate(double dt)
{       
    // set E to V_pre
    E = (pre_syn->V);
}

double Axial::getCurrent(double V_post)
{   
    return 0;

}

void Axial::connect(compartment *pcomp1_, compartment *pcomp2_) 
{
    pre_syn = pcomp1_; 
    post_syn = pcomp2_; 

    // connect to the compartment 
    post_syn->addAxial(this);

    // calculate the gbar from the areas
    // of the two compartments using 
    // equation 6.30 (Dayan and Abbott)

    double Lmu_ = post_syn->len;
    double amu_ = post_syn->radius;

    double amu = pre_syn->radius;
    double Lmu = pre_syn->len;

    gbar = (amu*amu_*amu_)/((resistivity*Lmu)*(Lmu*amu_*amu_ + Lmu_*amu*amu));
}

#endif