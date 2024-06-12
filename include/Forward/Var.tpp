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
 
#ifndef FWD_VAR_TPP
#define FWD_VAR_TPP

#include <Forward/Var.hpp>

#include <cmath>

namespace myAD
{
namespace fwd
{

template<typename T>
Var<T>& Var<T>::operator= (const T& v) 
{ 
	m_value = v; 
	
	return *this; 
}

template<typename T>
Var<T>& Var<T>::operator+=(const T& v) 
{ 
	m_value += v; 
	
	return *this; 
}

template<typename T>
Var<T>& Var<T>::operator-=(const T& v) 
{ 
	m_value -= v;
	
	return *this; 
}

template<typename T>
Var<T>& Var<T>::operator*=(const T& v) 
{ 
	m_diff2 *= v; 
	m_diff *= v;
	m_value *= v;
	 
	return *this; 
}

template<typename T>
Var<T>& Var<T>::operator/=(const T& v) 
{ 
	m_diff2 /= v; 
	m_diff /= v;
	m_value /= v;
	
	return *this; 
}

template<typename T>
Var<T>& Var<T>::operator+=(const Var<T>& other) 
{ 
	m_diff2 += other.m_diff2; 
	m_diff += other.m_diff; 
	m_value += other.m_value; 
	
	return *this; 
}

template<typename T>
Var<T>& Var<T>::operator-=(const Var<T>& other) 
{ 
	m_diff2 -= other.m_diff2; 
	m_diff -= other.m_diff; 
	m_value -= other.m_value; 
	
	return *this; 
}

template<typename T>
Var<T>& Var<T>::operator*=(const Var<T>& other) 
{
	m_diff2  = m_value*other.m_diff2 + 2*m_diff*other.m_diff + m_diff2*m_value;
	m_diff   = m_value*other.m_diff + m_diff*other.m_value;
	m_value *= other.m_value;
	
	return *this; 
}

template<typename T>
Var<T>& Var<T>::operator/=(const Var<T>& other) 
{ 
	return *this *= other.inverse(); 
}

}
}

template<typename T>
myAD::fwd::Var<T> sin(const myAD::fwd::Var<T>& u) 
{ 
	return myAD::fwd::Var<T>(sin(u.getValue()), u.getDiff()*cos(u.getValue()), cos(u.getValue())*u.getDiff2() - sin(u.getValue())*u.getDiff()*u.getDiff()); 
}

template<typename T>
myAD::fwd::Var<T> cos(const myAD::fwd::Var<T>& u) 
{ 
	return myAD::fwd::Var<T>(cos(u.getValue()), -u.getDiff()*sin(u.getValue()), -sin(u.getValue())*u.getDiff2() - cos(u.getValue())*u.getDiff()*u.getDiff());
}

template<typename T>
myAD::fwd::Var<T> exp(const myAD::fwd::Var<T>& u) 
{ 
	return myAD::fwd::Var<T>(exp(u.getValue()), u.getDiff()*exp(u.getValue()), exp(u.getValue())*(u.getDiff()*u.getDiff() + u.getDiff2())); 
}

template<typename T>
myAD::fwd::Var<T> log(const myAD::fwd::Var<T>& u) 
{ 
	return myAD::fwd::Var<T>(log(u.getValue()), u.getDiff() / u.getValue(), (u.getDiff2()*u.getValue() - u.getDiff()*u.getDiff()) / (u.getValue()*u.getValue())); 
}

#endif // FWD_VAR_TPP
