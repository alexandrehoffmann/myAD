Small automatic differentiation library that supports forward mode, reverse mode and reverse-on-fowrad mode.

# Forward mode

Define a templated function :

```
template<typename T>
T Rosenbrock(const T* x, const size_t dim)
{	
	T y(0);
	for (size_t i=0;i<dim-1;++i)
	{
		y += 100.*(x[i+1] - x[i]*x[i])*(x[i+1] - x[i]*x[i]) + (1. - x[i])*(1. - x[i]);
	}
	
	return y;
}
```

Compute first and second order derivative with respect to x[2] : 
```
std::vector< myAD::fwd::Var<double> > x(10, 0.0);
myAD::fwd::Var<double> eps(0,1);
	
x[2] += eps; // differentiate with respect to x[2]
	 
myAD::fwd::Var<double> y = Rosenbrock(x.data(), x.size());
	
std::cout << "f(x) = " << y.getValue() << std::endl;
std::cout << "∂z/∂x[2](x) = " << y.getDiff() << std::endl;
std::cout << "∂^2 z/∂x[2]^2(x) = " << y.getDiff2() << std::endl;
```
# Reverse mode

Reverse mode works by constructing a weighted directional graph.
A node represents a variable, an edge (a, b, v) indicates that ∂a/∂b = v.

The Graph is a singleton and is automatically filled when declaring and manipulating variables. 
It should be cleared when the function has been evaluated. Each variable and temporary has a unique id that corresponds to the node it is associated to.

With the graph, we can compute the derivatives of a variable with respect to all the variables and temporaries used uppon the computation.
The gradient with respect to a given variable can be accessed by using the variable id.
```
myAD::rev::VarGraph<double>::getInstance().clear(); 
	
std::vector< myAD::rev::Var<double> > x(10, 0.0);
	 
myAD::rev::Var<double> y = Rosenbrock(x.data(), x.size());
	
std::vector< double > grad = myAD::rev::VarGraph<double>::getInstance().gradient(y);
	
std::cout << "f(x) = " << y.getValue() << std::endl;
for (size_t i=0;i<x.size();++i)
{
	std::cout << "∂z/∂x[" << i << "](x) = " << grad[x[i].getId()] << std::endl;
}
	
myAD::rev::VarGraph<double>::getInstance().clear();
```
Alternatively, one can specify the variable with respect to wich the gradient should be computed : 
```
std::vector< double > grad = myAD::rev::VarGraph<double>::getInstance().gradient(y, x.data(), x.size());

for (size_t i=0;i<x.size();++i)
{
	std::cout << "∂z/∂x[" << i << "](x) = " << grad[i] << std::endl;
}
```
# Reverse-on-forward mode

Reverse on forward aims at computing $\nabla^2 f(x)d$ for a given direction $d$.
First, we compute $g(x) = \nabla f(x)^T d$ with forward mode automatic differentiation.
Second, we use reverse mode automatic differentiation to compute $\nabla g(x) = \nabla^2 f(x)d$.

This is done via a spetialization of the forward variable :
```
using adouble = myAD::fwd::Var< myAD::rev::Var<double> >;
	
myAD::rev::VarGraph<double>::getInstance().clear();
	
adouble eps(0,1);
	
std::vector< adouble > x(10, 1.0);
for (size_t i=0;i<x.size();++i)
{
	x[i] = 1;
}
x[2] += eps; // computing \nabla f(x)^T e_3
	
adouble y = Rosenbrock(x.data(), x.size());
myAD::rev::Var<double> gradDotEps = y.getDiff();
std::vector< double > Hd = myAD::rev::VarGraph<double>::getInstance().gradient(gradDotEps);
	
for (size_t i=0;i<x.size();++i)
{
	std::cout << Hd[x[i].getValue().getId()] << std::endl;
}
	
myAD::rev::VarGraph<double>::getInstance().clear();
```
