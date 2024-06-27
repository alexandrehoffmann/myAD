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
 
#ifndef REV_VAR_HPP
#define REV_VAR_HPP

#include <cstdlib>

namespace myAD
{
namespace rev
{

template<typename T> class VarGraph;

template<typename T>
class Var
{
public:
	friend class VarGraph<T>;

	Var(const T value = 0) : m_value(value) { VarGraph<T>::getInstance().addVar(*this); }
	Var(const Var<T>& other) : m_value(other.m_value) { VarGraph<T>::getInstance().addVar(*this); VarGraph<T>::getInstance().addEdge(*this, other, 1); }

	const T& getValue() const { return m_value; }
	int      getId()    const { return m_id;    }
	
	Var& operator= (const T& v) { m_value = v;       return *this; }
	Var& operator+=(const T& v) { *this = *this + v; return *this; }
	Var& operator-=(const T& v) { *this = *this - v; return *this; }
	Var& operator*=(const T& v) { *this = *this * v; return *this; }
	Var& operator/=(const T& v) { *this = *this / v; return *this; }

	Var& operator =(const Var& other);
	Var& operator+=(const Var& other) { *this = *this + other; return *this; }
	Var& operator-=(const Var& other) { *this = *this - other; return *this; }
	Var& operator*=(const Var& other) { *this = *this * other; return *this; }
	Var& operator/=(const Var& other) { *this = *this / other; return *this; }
private:
	T      m_value;
	size_t m_id;
};

}
}

template<typename T> bool operator==(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs) { return lhs.getValue() == rhs.getValue(); }
template<typename T> bool operator!=(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs) { return lhs.getValue() != rhs.getValue(); }
template<typename T> bool operator< (const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs) { return lhs.getValue() <  rhs.getValue(); }
template<typename T> bool operator<=(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs) { return lhs.getValue() <= rhs.getValue(); }
template<typename T> bool operator> (const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs) { return lhs.getValue() >  rhs.getValue(); }
template<typename T> bool operator>=(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs) { return lhs.getValue() >= rhs.getValue(); }

template<typename T> bool operator==(const T& lhs, const myAD::rev::Var<T>& rhs) { return lhs == rhs.getValue(); }
template<typename T> bool operator!=(const T& lhs, const myAD::rev::Var<T>& rhs) { return lhs != rhs.getValue(); }
template<typename T> bool operator< (const T& lhs, const myAD::rev::Var<T>& rhs) { return lhs <  rhs.getValue(); }
template<typename T> bool operator<=(const T& lhs, const myAD::rev::Var<T>& rhs) { return lhs <= rhs.getValue(); }
template<typename T> bool operator> (const T& lhs, const myAD::rev::Var<T>& rhs) { return lhs >  rhs.getValue(); }
template<typename T> bool operator>=(const T& lhs, const myAD::rev::Var<T>& rhs) { return lhs >= rhs.getValue(); }

template<typename T> bool operator==(const myAD::rev::Var<T>& lhs, const T& rhs) { return lhs.getValue() == rhs; }
template<typename T> bool operator!=(const myAD::rev::Var<T>& lhs, const T& rhs) { return lhs.getValue() != rhs; }
template<typename T> bool operator< (const myAD::rev::Var<T>& lhs, const T& rhs) { return lhs.getValue() <  rhs; }
template<typename T> bool operator<=(const myAD::rev::Var<T>& lhs, const T& rhs) { return lhs.getValue() <= rhs; }
template<typename T> bool operator> (const myAD::rev::Var<T>& lhs, const T& rhs) { return lhs.getValue() >  rhs; }
template<typename T> bool operator>=(const myAD::rev::Var<T>& lhs, const T& rhs) { return lhs.getValue() >= rhs; }

template<typename T> myAD::rev::Var<T> sin(const myAD::rev::Var<T>& u);
template<typename T> myAD::rev::Var<T> cos(const myAD::rev::Var<T>& u);
template<typename T> myAD::rev::Var<T> exp(const myAD::rev::Var<T>& u);
template<typename T> myAD::rev::Var<T> log(const myAD::rev::Var<T>& u);

template<typename T> myAD::rev::Var<T> operator-(const myAD::rev::Var<T>& a);

template<typename T> myAD::rev::Var<T> operator+(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs);
template<typename T> myAD::rev::Var<T> operator-(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs);
template<typename T> myAD::rev::Var<T> operator*(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs);
template<typename T> myAD::rev::Var<T> operator/(const myAD::rev::Var<T>& lhs, const myAD::rev::Var<T>& rhs);

template<typename T> myAD::rev::Var<T> operator+(const T& lhs, const myAD::rev::Var<T>& rhs);
template<typename T> myAD::rev::Var<T> operator-(const T& lhs, const myAD::rev::Var<T>& rhs);
template<typename T> myAD::rev::Var<T> operator*(const T& lhs, const myAD::rev::Var<T>& rhs);
template<typename T> myAD::rev::Var<T> operator/(const T& lhs, const myAD::rev::Var<T>& rhs);

template<typename T> myAD::rev::Var<T> operator+(const myAD::rev::Var<T>& lhs, const T& rhs);
template<typename T> myAD::rev::Var<T> operator-(const myAD::rev::Var<T>& lhs, const T& rhs);
template<typename T> myAD::rev::Var<T> operator*(const myAD::rev::Var<T>& lhs, const T& rhs);
template<typename T> myAD::rev::Var<T> operator/(const myAD::rev::Var<T>& lhs, const T& rhs);

#include <myAD/Reverse/Var.tpp>

#endif // REV_VAR_HPP
