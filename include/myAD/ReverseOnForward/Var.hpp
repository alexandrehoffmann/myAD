/*
 * Var.hpp
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
 
#ifndef REV_ON_FWD_VAR_HPP
#define REV_ON_FWD_VAR_HPP

#include <myAD/Forward/Var.hpp>
#include <myAD/Reverse/Var.hpp>

namespace myAD
{
namespace fwd
{

template<typename T>
class Var< rev::Var<T> >
{
public:
	Var(const T value=0, const T diff=0) : m_value(value), m_diff(diff) {}
	Var(const rev::Var<T>& value, const rev::Var<T>& diff) : m_value(value), m_diff(diff) {}

	const rev::Var<T>& getValue() const { return m_value; }
	const rev::Var<T>& getDiff()  const { return m_diff;  }
	
	//const T& getValue() const { return m_value.getValue(); }
	//const T& getDiff()  const { return m_diff.getValue();  }
	
	//const rev::Var<T>& getRevValue() const { return m_value; }
	//const rev::Var<T>& getRevDiff()  const { return m_diff;  }

	Var& operator= (const T& v);
	Var& operator+=(const T& v);
	Var& operator-=(const T& v);
	Var& operator*=(const T& v);
	Var& operator/=(const T& v);

	Var& operator+=(const Var& other);
	Var& operator-=(const Var& other);
	Var& operator*=(const Var& other);
	Var& operator/=(const Var& other);

	Var inverse() const { return Var( 1/m_value, m_diff / (m_value*m_value) ); }  
private:
	rev::Var<T> m_value;
	rev::Var<T> m_diff;
};
	
}
}

template<typename T> bool operator==(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs.getValue() == rhs.getValue(); }
template<typename T> bool operator!=(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs.getValue() != rhs.getValue(); }
template<typename T> bool operator< (const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs.getValue() <  rhs.getValue(); }
template<typename T> bool operator<=(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs.getValue() <= rhs.getValue(); }
template<typename T> bool operator> (const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs.getValue() >  rhs.getValue(); }
template<typename T> bool operator>=(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs.getValue() >= rhs.getValue(); }

template<typename T> bool operator==(const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs == rhs.getValue(); }
template<typename T> bool operator!=(const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs != rhs.getValue(); }
template<typename T> bool operator< (const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs <  rhs.getValue(); }
template<typename T> bool operator<=(const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs <= rhs.getValue(); }
template<typename T> bool operator> (const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs >  rhs.getValue(); }
template<typename T> bool operator>=(const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { return lhs >= rhs.getValue(); }

template<typename T> bool operator==(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { return lhs.getValue() == rhs; }
template<typename T> bool operator!=(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { return lhs.getValue() != rhs; }
template<typename T> bool operator< (const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { return lhs.getValue() <  rhs; }
template<typename T> bool operator<=(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { return lhs.getValue() <= rhs; }
template<typename T> bool operator> (const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { return lhs.getValue() >  rhs; }
template<typename T> bool operator>=(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { return lhs.getValue() >= rhs; }

template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > sin(const myAD::fwd::Var< myAD::rev::Var<T> >& u);
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > cos(const myAD::fwd::Var< myAD::rev::Var<T> >& u);
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > exp(const myAD::fwd::Var< myAD::rev::Var<T> >& u);
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > log(const myAD::fwd::Var< myAD::rev::Var<T> >& u);

template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator-(const myAD::fwd::Var< myAD::rev::Var<T> >& a) { return myAD::fwd::Var< myAD::rev::Var<T> >(-a.getValue(), -a.getDiff()); }

template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator+(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret += rhs; }
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator-(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret -= rhs; }
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator*(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret *= rhs; }
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator/(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret /= rhs; }

template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator+(const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret += rhs; }
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator-(const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret -= rhs; }
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator*(const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret *= rhs; }
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator/(const T& lhs, const myAD::fwd::Var< myAD::rev::Var<T> >& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret /= rhs; }

template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator+(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret += rhs; }
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator-(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret -= rhs; }
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator*(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret *= rhs; }
template<typename T> myAD::fwd::Var< myAD::rev::Var<T> > operator/(const myAD::fwd::Var< myAD::rev::Var<T> >& lhs, const T& rhs) { myAD::fwd::Var< myAD::rev::Var<T> > ret(lhs); return ret /= rhs; }

#include <myAD/ReverseOnForward/Var.tpp>

#endif // REV_ON_FWD_VAR_HPP
