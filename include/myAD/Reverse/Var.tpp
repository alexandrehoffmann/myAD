/*
 * Var.tpp
 * 
 * Copyright 2024 Alexandre Hoffmann <alexandre.hoffmann.etu@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#ifndef REV_VAR_TPP
#define REV_VAR_TPP

#include <myAD/Reverse/Var.hpp>
#include <myAD/Reverse/VarGraph.hpp>

#include <cmath>

template<typename T> 
myAD::rev::Var<T>& myAD::rev::Var<T>::operator =(const myAD::rev::Var<T>& other) 
{ 
	m_value = other.m_value; 
	VarGraph<T>::getInstance().addVar(*this); 
	VarGraph<T>::getInstance().addEdge(*this, other, 1); 
	
	return *this; 
}

template<typename T> 
myAD::rev::Var<T> sin(const myAD::rev::Var<T>& u)
{
	// Z = sin(A); dZ/dA = cos(A)
	myAD::rev::Var<T> ret(cos(u.getValue()));
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, u, cos(u.getValue()));
	
	return ret;
}

template<typename T>
myAD::rev::Var<T> cos(const myAD::rev::Var<T>& u)
{
	// Z = cos(A); dZ/dA = -sin(A)
	myAD::rev::Var<T> ret(cos(u.getValue()));
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, u, -sin(u.getValue()));
	
	return ret;
}
 
template<typename T> 
myAD::rev::Var<T> exp(const myAD::rev::Var<T>& u)
{	
	// Z = exp(A); dZ/dA = exp(A)
	myAD::rev::Var<T> ret(exp(u.getValue()));
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, u, exp(u.getValue()));
	
	return ret;
}

template<typename T> 
myAD::rev::Var<T> log(const myAD::rev::Var<T>& u)
{
	// Z = log(A); dZ/dA = 1 / A
	myAD::rev::Var<T> ret(log(u.getValue()));
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, u, 1 / u.getValue());
	
	return ret;
}

template<typename T> 
myAD::rev::Var<T> operator-(const myAD::rev::Var<T>& a)
{
	// Z = -A; dZ/dA = -1
	myAD::rev::Var<T> ret(-a.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, a, -1);
	
	return ret;
}

template<typename T> 
myAD::rev::Var<T> operator+(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs) 
{
	// Z = A + B; dZ/dA = 1, dZ/dB = 1
	myAD::rev::Var<T> ret(lhs.getValue() + rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, lhs, 1);
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, rhs, 1);

	return ret;
}

template<typename T>
myAD::rev::Var<T> operator-(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs)
{
	// Z = A - B; dZ/dA = 1, dZ/dB = -1
	myAD::rev::Var<T> ret(lhs.getValue() - rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, lhs,  1);
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, rhs, -1);

	return ret;
}

template<typename T>
myAD::rev::Var<T> operator*(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs)
{
	// Z = A * B; dZ/dA = B, dZ/dB = A
	myAD::rev::Var<T> ret(lhs.getValue() * rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, lhs, rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, rhs, lhs.getValue());

	return ret;
}

template<typename T>
myAD::rev::Var<T> operator/(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs)
{
	// Z = A / B; dZ/dA = 1 / B, dZ/dB = -A / B^2
	myAD::rev::Var<T> ret(lhs.getValue() / rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, lhs,  1. / rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, rhs, -lhs.getValue() / (rhs.getValue()*rhs.getValue()));

	return ret;
}

template<typename T> 
myAD::rev::Var<T> operator+(const T& lhs, const myAD::rev::Var<T>& rhs)
{
	// Z = cst + B; dZ/dB = 1
	myAD::rev::Var<T> ret(lhs + rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, rhs, 1);

	return ret;
}


template<typename T> 
myAD::rev::Var<T> operator-(const T& lhs, const myAD::rev::Var<T>& rhs)
{
	// Z = cst - B; dZ/dB = -1
	myAD::rev::Var<T> ret(lhs - rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, rhs, -1);

	return ret;
}

template<typename T> 
myAD::rev::Var<T> operator*(const T& lhs, const myAD::rev::Var<T>& rhs)
{
	// Z = cst * B; dZ/dB = cst
	myAD::rev::Var<T> ret(lhs * rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, rhs, lhs);

	return ret;
}

template<typename T> 
myAD::rev::Var<T> operator/(const T& lhs, const myAD::rev::Var<T>& rhs)
{
	// Z = cst / B; dZ/dB = -cst / B^2
	myAD::rev::Var<T> ret(lhs / rhs.getValue());
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, rhs, -lhs / (rhs.getValue()*rhs.getValue()));

	return ret;
}

template<typename T> 
myAD::rev::Var<T> operator+(const myAD::rev::Var<T>& lhs, const T& rhs)
{
	// Z = A + cst; dZ/dA = 1
	myAD::rev::Var<T> ret(lhs.getValue() + rhs);
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, lhs, 1);

	return ret;
}


template<typename T> 
myAD::rev::Var<T> operator-(const myAD::rev::Var<T>& lhs, const T& rhs)
{
	// Z = A - cst; dZ/dA = 1
	myAD::rev::Var<T> ret(lhs.getValue() - rhs);
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, lhs, 1);

	return ret;
}

template<typename T> 
myAD::rev::Var<T> operator*(const myAD::rev::Var<T>& lhs, const T& rhs)
{
	// Z = A * cst; dZ/dA = cst
	myAD::rev::Var<T> ret(lhs.getValue() * rhs);
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, lhs, rhs);

	return ret;
}

template<typename T> 
myAD::rev::Var<T> operator/(const myAD::rev::Var<T>& lhs, const T& rhs)
{
	// Z = A / cst; dZ/dA = 1 / cst
	myAD::rev::Var<T> ret(lhs.getValue() / rhs);
	myAD::rev::VarGraph<T>::getInstance().addEdge(ret, lhs, 1 / rhs);

	return ret;
}

#endif // REV_VAR_TPP
