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
 
#ifndef FWD_VAR_HPP
#define FWD_VAR_HPP

namespace myAD
{
namespace fwd
{

template<typename T>
class Var
{
public:
	Var(const T value=0, const T diff=0, const T diff2=0) : m_value(value), m_diff(diff), m_diff2(diff2) {}

	const T& getValue() const { return m_value; }
	const T& getDiff()  const { return m_diff;  }
	const T& getDiff2() const { return m_diff2; }

	Var& operator= (const T& v);
	Var& operator+=(const T& v);
	Var& operator-=(const T& v);
	Var& operator*=(const T& v);
	Var& operator/=(const T& v);

	Var& operator+=(const Var& other);
	Var& operator-=(const Var& other);
	Var& operator*=(const Var& other);
	Var& operator/=(const Var& other);

	Var inverse() const { return Var(1/m_value, m_diff / (m_value*m_value), (2*m_diff*m_diff - m_diff2*m_value) / (m_value*m_value*m_value) ); }  
private:
	T m_value;
	T m_diff;
	T m_diff2;
};
	
}
}

template<typename T> bool operator==(const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { return lhs.getValue() == rhs.getValue(); }
template<typename T> bool operator!=(const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { return lhs.getValue() != rhs.getValue(); }
template<typename T> bool operator< (const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { return lhs.getValue() <  rhs.getValue(); }
template<typename T> bool operator<=(const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { return lhs.getValue() <= rhs.getValue(); }
template<typename T> bool operator> (const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { return lhs.getValue() >  rhs.getValue(); }
template<typename T> bool operator>=(const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { return lhs.getValue() >= rhs.getValue(); }

template<typename T> bool operator==(const T& lhs, const myAD::fwd::Var<T>& rhs) { return lhs == rhs.getValue(); }
template<typename T> bool operator!=(const T& lhs, const myAD::fwd::Var<T>& rhs) { return lhs != rhs.getValue(); }
template<typename T> bool operator< (const T& lhs, const myAD::fwd::Var<T>& rhs) { return lhs <  rhs.getValue(); }
template<typename T> bool operator<=(const T& lhs, const myAD::fwd::Var<T>& rhs) { return lhs <= rhs.getValue(); }
template<typename T> bool operator> (const T& lhs, const myAD::fwd::Var<T>& rhs) { return lhs >  rhs.getValue(); }
template<typename T> bool operator>=(const T& lhs, const myAD::fwd::Var<T>& rhs) { return lhs >= rhs.getValue(); }

template<typename T> bool operator==(const myAD::fwd::Var<T>& lhs, const T& rhs) { return lhs.getValue() == rhs; }
template<typename T> bool operator!=(const myAD::fwd::Var<T>& lhs, const T& rhs) { return lhs.getValue() != rhs; }
template<typename T> bool operator< (const myAD::fwd::Var<T>& lhs, const T& rhs) { return lhs.getValue() <  rhs; }
template<typename T> bool operator<=(const myAD::fwd::Var<T>& lhs, const T& rhs) { return lhs.getValue() <= rhs; }
template<typename T> bool operator> (const myAD::fwd::Var<T>& lhs, const T& rhs) { return lhs.getValue() >  rhs; }
template<typename T> bool operator>=(const myAD::fwd::Var<T>& lhs, const T& rhs) { return lhs.getValue() >= rhs; }

template<typename T> myAD::fwd::Var<T> sin(const myAD::fwd::Var<T>& u);
template<typename T> myAD::fwd::Var<T> cos(const myAD::fwd::Var<T>& u);
template<typename T> myAD::fwd::Var<T> exp(const myAD::fwd::Var<T>& u);
template<typename T> myAD::fwd::Var<T> log(const myAD::fwd::Var<T>& u);

template<typename T> myAD::fwd::Var<T> operator-(const myAD::fwd::Var<T>& a) { return myAD::fwd::Var<T>(-a.getValue(), -a.getDiff(), -a.getDiff2()); }

template<typename T> myAD::fwd::Var<T> operator+(const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { myAD::fwd::Var<T> ret(lhs); return ret += rhs; }
template<typename T> myAD::fwd::Var<T> operator-(const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { myAD::fwd::Var<T> ret(lhs); return ret -= rhs; }
template<typename T> myAD::fwd::Var<T> operator*(const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { myAD::fwd::Var<T> ret(lhs); return ret *= rhs; }
template<typename T> myAD::fwd::Var<T> operator/(const myAD::fwd::Var<T>& lhs, const myAD::fwd::Var<T>& rhs) { myAD::fwd::Var<T> ret(lhs); return ret /= rhs; }

template<typename T> myAD::fwd::Var<T> operator+(const T& lhs, const myAD::fwd::Var<T>& rhs) { myAD::fwd::Var<T> ret(lhs); return ret += rhs; }
template<typename T> myAD::fwd::Var<T> operator-(const T& lhs, const myAD::fwd::Var<T>& rhs) { myAD::fwd::Var<T> ret(lhs); return ret -= rhs; }
template<typename T> myAD::fwd::Var<T> operator*(const T& lhs, const myAD::fwd::Var<T>& rhs) { myAD::fwd::Var<T> ret(lhs); return ret *= rhs; }
template<typename T> myAD::fwd::Var<T> operator/(const T& lhs, const myAD::fwd::Var<T>& rhs) { myAD::fwd::Var<T> ret(lhs); return ret /= rhs; }

template<typename T> myAD::fwd::Var<T> operator+(const myAD::fwd::Var<T>& lhs, const T& rhs) { myAD::fwd::Var<T> ret(lhs); return ret += rhs; }
template<typename T> myAD::fwd::Var<T> operator-(const myAD::fwd::Var<T>& lhs, const T& rhs) { myAD::fwd::Var<T> ret(lhs); return ret -= rhs; }
template<typename T> myAD::fwd::Var<T> operator*(const myAD::fwd::Var<T>& lhs, const T& rhs) { myAD::fwd::Var<T> ret(lhs); return ret *= rhs; }
template<typename T> myAD::fwd::Var<T> operator/(const myAD::fwd::Var<T>& lhs, const T& rhs) { myAD::fwd::Var<T> ret(lhs); return ret /= rhs; }

#include <Forward/Var.tpp>

#include <ReverseOnForward/Var.hpp>

#endif // FWD_VAR_HPP
