Small automatic differentiation library that supports forward mode, reverse mode and reverse-on-fowrad mode.

# forward mode

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
