# The xfit class



This document describes the `xfit` class. `xfit` is a toolbox that helps you find neuron or network models satisfying arbitrary constraints. It is a bridge 
between the [Global Optimization Toolbox](https://www.mathworks.com/products/global-optimization.html) in MATLAB and the [xolotl](https://go.brandeis.edu/xolotl) neuron and network simulator 

The first step in using `xfit` is to create a `xfit` object using:

```matlab
xf = xfit('particleswarm');
```

## Properties

Every xfit object has the following properties.
To access a property, use dot notation, e.g.:

```matlab
xf.x
```

You can view all the properties of an xfit object
using the built-in `properties` command:

```matlab
properties(xf)
```

### `x`

| Default | Allowed values | Type |
| ------- | ----- | ----- |
| []  |    scalar values | xolotl | 

This property contains a xolotl object. Since xfit uses
xolotl to run actual simulations, this is necessary for all projects. 

### `sim_func`

| Default | Allowed values | Type |
| ------- | ----- | ----- |
| []  |    any | function_handle | 

A function handle to the simulation function used to evaluate the model cost.
The simulation function can be any MATLAB function,
provided that the following are true:

* The first output must be the cost, which is a positive, real-valued scalar.
* The function accepts two arguments, the first of which is a xolotl object.

The function thus has the (minimal) signature:

```
function [cost, ...] = functionName(xolotl_object, data)
```

When xfit performs a parameter optimization routine,
it calls the `sim_func` using the xolotl object stored in the `x` property, which has been set up with trial parameters.

### `parameter_names`

| Default | Allowed values | Type |
| ------- | ----- | ----- |
| []  |    any | cell | 

This cell array of character vectors contains the names of xolotl parameters to optimize over.
The `find` method of xolotl is the best way to populate this list.
`seed`, `lb`, and `ub` share one-to-one correspondence with `parameter_names`, so all should be the same dimensions.

### `seed`

| Default | Allowed values | Type |
| ------- | ----- | ----- |
| []  |    vector | double | 

The seed is an $n$ x 1 vector of numerical parameter values
for starting an optimization protocol,
where $n$ is the number of parameters to optimize over.

### `lb` & `ub`

| Default | Allowed values | Type |
| ------- | ----- | ----- |
| []  |    vectors | double | 

`lb` and `ub` are $n$ x 1 vectors of numerical lower bound and upper bound values. During optimization, parameters are bounded between their upper and lower bounds.

### `options`



This property is a struct that holds options for the selected optimization engine. It is automatically generated from MATLAB's built-in [optimoptions](https://www.mathworks.com/help/optim/ug/optimization-options-reference.html) function.


### `engine`

This option determines the optimization algorithm used.

| Engine Name | Engine Keyword |
| ----------- | -------------- |
| Pattern Search | `patternsearch` |
| Particle Swarm | `particleswarm` |
| Genetic Algorithm | `ga` |

### `timestamp`
This property keeps track of the duration of a simulation. This is a read-only property. 

### `best_cost`


The best cost holds the lowest value computed by the simulation function during an optimization procedure. This is a read-only property. 

### `data`

| Default | Allowed values | Type |
| ------- | ----- | ----- |
| []  |    any | any | 

The `data` property can hold any user-defined data. You may want to use this if your cost function required additional data to measure the cost. For example, if you want to fit a neuron to a specifiy voltage trace, you would store it here. 


## Methods

-------

### evaluate

**Syntax**

```matlab
c = evaluate(self,params);
```

**Description**

Updates parameters in the xolotl object using
`params` (a vector), evaluate the cost function,
and return a cost (a double).

It is assumed that you have the following things
configured in the xfit object:

- `x` (the xolotl object)
- `SimFcn`
- `parameter_names`



!!! info "See Also"
    * [xfit.fit](../xfit/#fit)



-------

### fit

**Syntax**

```matlab
best_fit_params = xf.fit;
```

**Description**

Assuming `xf` is a `xfit` object, runs the optimization 
algorithm in an effort to minimze the cost function using 
specified conditions. Returns a vector of the best-fit
parameters. Only the last (best-fit) value is returned. 

The best-fit value is also used to update the seed.



!!! info "See Also"
    * [xfit.evaluate](../xfit/#evaluate)
    * [How to fit a xolotl model](https://xolotl.readthedocs.io/en/master/how-to/fit-parameters/)
