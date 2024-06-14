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
 
#ifndef REV_ON_FWD_VAR_TPP
#define REV_ON_FWD_VAR_TPP

#include <ReverseOnForward/Var.hpp>

namespace myAD
{
namespace fwd
{

template<typename T>
Var< rev::Var<T> >& Var< rev::Var<T> >::operator= (const T& v) 
{ 
	m_value = v; 
	
	return *this; 
}

template<typename T>
Var< rev::Var<T> >& Var< rev::Var<T> >::operator+=(const T& v) 
{ 
	m_value += v; 
	
	return *this; 
}

template<typename T>
Var< rev::Var<T> >& Var< rev::Var<T> >::operator-=(const T& v) 
{ 
	m_value -= v;
	
	return *this; 
}

template<typename T>
Var< rev::Var<T> >& Var< rev::Var<T> >::operator*=(const T& v) 
{ 
	m_diff *= v;
	m_value *= v;
	 
	return *this; 
}

template<typename T>
Var< rev::Var<T> >& Var< rev::Var<T> >::operator/=(const T& v) 
{ 
	m_diff /= v;
	m_value /= v;
	
	return *this; 
}

template<typename T>
Var< rev::Var<T> >& Var< rev::Var<T> >::operator+=(const Var< rev::Var<T> >& other) 
{ 
	m_diff += other.m_diff; 
	m_value += other.m_value; 
	
	return *this; 
}

template<typename T>
Var< rev::Var<T> >& Var< rev::Var<T> >::operator-=(const Var< rev::Var<T> >& other) 
{ 
	m_diff -= other.m_diff; 
	m_value -= other.m_value; 
	
	return *this; 
}

template<typename T>
Var< rev::Var<T> >& Var< rev::Var<T> >::operator*=(const Var< rev::Var<T> >& other) 
{
	m_diff   = m_value*other.m_diff + m_diff*other.m_value;
	m_value *= other.m_value;
	
	return *this; 
}

template<typename T>
Var< rev::Var<T> >& Var< rev::Var<T> >::operator/=(const Var< rev::Var<T> >& other) 
{ 
	return *this *= other.inverse(); 
}

}
}

template<typename T>
myAD::fwd::Var< myAD::rev::Var<T> > sin(const myAD::fwd::Var< myAD::rev::Var<T> >& u) 
{ 
	return myAD::fwd::Var< myAD::rev::Var<T> >( sin(u.getValue()), u.getDiff()*cos(u.getValue()) ); 
}

template<typename T>
myAD::fwd::Var< myAD::rev::Var<T> > cos(const myAD::fwd::Var< myAD::rev::Var<T> >& u) 
{ 
	return myAD::fwd::Var< myAD::rev::Var<T> >( cos(u.getValue()), -u.getDiff()*sin(u.getValue()) );
}

template<typename T>
myAD::fwd::Var< myAD::rev::Var<T> > exp(const myAD::fwd::Var< myAD::rev::Var<T> >& u) 
{ 
	return myAD::fwd::Var< myAD::rev::Var<T> >( exp(u.getValue()), u.getDiff()*exp(u.getValue()) ); 
}

template<typename T>
myAD::fwd::Var< myAD::rev::Var<T> > log(const myAD::fwd::Var< myAD::rev::Var<T> >& u) 
{ 
	return myAD::fwd::Var< myAD::rev::Var<T> >( log(u.getValue()), u.getDiff() / u.getValue() ); 
}

#endif // REV_ON_FWD_VAR_TPP
