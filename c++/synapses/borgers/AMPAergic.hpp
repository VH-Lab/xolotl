// nearly-instantaneous rise synaptic conductance for AMPAergic receptors
// based on C. Borgers "An Introduction to Modeling Neuronal Dynamics" Ch. 20
#ifndef AMPA
#define AMPA
#include "synapse.hpp"
// #include "math.hpp"

class AMPAergic: public synapse {

public:

    double tau_r;
    double tau_d;

      // specify parameters + initial conditions
      AMPAergic(double g_, double s_, double E_, double tau_r_, double tau_d_)
      {
          gbar = g_;
          E = E_;
          s = s_;
          tau_r = tau_r_;
          tau_d = tau_d_;

          // defaults
          if (isnan (s)) { s = 0; }
          if (isnan (gbar)) { gbar = 0; }
          if (isnan (E)) { E = 0; }
          if (isnan (tau_r)) { tau_r = 1; }
          if (isnan (tau_d)) { tau_d = 1; }
          is_electrical = false;
      }

    void integrate(void);
    int getFullStateSize(void);
    void connect(compartment *pcomp1_, compartment *pcomp2_);
    double getCurrent(double V_post);
    int getFullState(double*, int);
};

int AMPAergic::getFullStateSize()
{
    return 2;
}

void AMPAergic::integrate(void)
{
    // figure out the voltage of the pre-synaptic neuron
    double V_pre = pre_syn->V;

    // find s_inf
    double s_inf = ((1.0 + tanh(V_pre/10.0))/2.0) / ( ((1.0 + tanh(V_pre/10.0))/2.0) + tau_r / tau_d );

    // integrate using exponential Euler
    double tau_s = tau_r / ( ((1.0 + tanh(V_pre/10.0))/2.0) + tau_r / tau_d );

    s = s_inf + (s - s_inf)*exp(-dt/tau_s);

}


int AMPAergic::getFullState(double *syn_state, int idx)
{
    // give it the current synapse variable
    syn_state[idx] = s;

    idx++;

    // also return the current from this synapse
    syn_state[idx] = gbar*s*(post_syn->V - E);
    idx++;
    return idx;
}

void AMPAergic::connect(compartment *pcomp1_, compartment *pcomp2_)
{
    pre_syn = pcomp1_;
    post_syn = pcomp2_;

    // tell the post-synaptic cell that we're connecting to it
    post_syn->addSynapse(this);
}




#endif
