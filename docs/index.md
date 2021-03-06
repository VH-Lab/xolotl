
# xolotl: a fast and flexible neuronal simulator 

![](https://user-images.githubusercontent.com/6005346/41205222-30b6f3d4-6cbd-11e8-983b-9125585d629a.png)

`xolotl` is a fast single-compartment and 
multi-compartment simulator  written in `C++` with 
a [MATLAB](https://www.mathworks.com/products/matlab.html) interface that you'll actually enjoy using.

Why use xolotl? This is why:

-----------------

# xolotl is *FAST*

xolotl is written in C++, and it's **fast**. In our testing, it's 
more than **3 times** faster than NEURON for single
compartment neurons. 

![](https://user-images.githubusercontent.com/6005346/50499683-9c0bf400-0a19-11e9-9375-92a1fdefa2fc.png)

----------------
# xolotl is *easy to use*

Want to set up a Hodgkin-Huxley model, inject current, 
integrate it and plot the voltage trace? This is all you need:

```matlab
x = xolotl;
x.add('compartment', 'HH','A', 0.01);
x.HH.add('liu/NaV', 'gbar', 1000);
x.HH.add('liu/Kd', 'gbar', 300);
x.HH.add('Leak', 'gbar', 1);
x.I_ext = .2;
x.plot;
```


----------------

# xolotl has *documentation*

Unlike certain widely used NEURON simulators that 
shall remain nameless, xolotl has documentation that actually...
exists. 

This is what it looks like:

![](https://user-images.githubusercontent.com/6005346/50499847-e3df4b00-0a1a-11e9-8aba-b3be57c3e784.png)

----------------

# xolotl lets you do **this**

<video width="100%" autoplay loop muted>
  <source src="https://xolotl.readthedocs.io/en/master/images/manipulate-neuron.mp4" type="video/mp4">
  <source src="https://xolotl.readthedocs.io/en/master/images/manipulate-neuron.webm" type="video/webm">
Your browser does not support the video tag.
</video>

xolotl lets you manipulate *any* parameter in *any* model and 
view the effects of changing that parameter **in real time**


----------------
# xolotl is fully *programmable*

xolotl is designed to be used from **within MATLAB**. It 
gives you the best of both worlds: the high performance 
of C++ compiled code with the rich power of all the toolboxes
MATLAB has to offer. You can:

* write functions that pass models as arguments
* optimize parameters of neuron models using the [Global Optimization Toolbox](https://www.mathworks.com/products/global-optimization.html)
* run simulations in parallel across multiple computers
* have a single script to run the simulation and analyze results

--------------------

Hooked? Check out the [quickstart](./tutorials/start-here.md) to see how easy it is to use. 