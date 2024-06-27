/*
 * VarGraph.tpp
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
 
#ifndef REV_VAR_GRAPH_TPP
#define REV_VAR_GRAPH_TPP

#include <myAD/Reverse/VarGraph.hpp>
#include <myAD/Reverse/Var.hpp>

namespace myAD
{
namespace rev
{

template<typename T>
VarGraph<T>& VarGraph<T>::getInstance()
{
	static VarGraph<T> INSTANCE;
	return INSTANCE;
}

template<typename T>
void VarGraph<T>::addVar(Var<T>& var)
{
	var.m_id = m_adjList.size();
	m_adjList.push_back(std::list< Edge >());
}

template<typename T>
void VarGraph<T>::addEdge(const Var<T>& parent, const Var<T>& child, const T value)
{
	if (parent.m_id >= m_adjList.size()) { throw std::invalid_argument("it seems the Graph has been cleared. This variable is no longer registered."); }
	if (child.m_id >= m_adjList.size())  { throw std::invalid_argument("it seems the Graph has been cleared. This variable is no longer registered."); }
	
	m_adjList[parent.getId()].push_back(Edge(child.getId(), value));
}

template<typename T>
size_t VarGraph<T>::getNedges() const
{
	size_t n = 0;
	for (size_t i=0;i<m_adjList.size();++i)
	{
		n += m_adjList[i].size();
	}
	
	return n;
}

template<typename T>
std::vector< T > VarGraph<T>::gradient(const Var<T>& var, const T seed)
{
	if (var.m_id >= m_adjList.size()) { throw std::invalid_argument("it seems the Graph has been cleared. This variable is no longer registered."); }

	std::vector<T> grad(m_adjList.size());
	
	grad[var.m_id] = seed;

	computeGrad(var.m_id, seed, grad.data());

	return grad;
}

template<typename T>
std::vector< T > VarGraph<T>::gradient(const Var<T>& var, const Var<T>* x, const size_t x_size, const T seed)
{
	std::vector<T> grad(x_size);
	gradient(var, x, x_size, grad.data(), seed);

	return grad;
}

template<typename T>
void VarGraph<T>::gradient(const Var<T>& var, const Var<T>* x, const size_t x_size, const T seed, T* __restrict__ grad)
{
	std::vector<T> fullGrad = gradient(var, seed);
	
	for (size_t i=0;i<x_size;++i)
	{
		grad[i] = fullGrad[x[i].getId()];
	}
}

template<typename T>
void VarGraph<T>::computeGrad(const size_t varId, const T& seed, T* grad)
{
	for (const Edge& e : m_adjList[varId])
	{
		const T&     localGrad = e.getValue();
		const size_t childId   = e.getChildId();

		const T childSeed = seed*localGrad;
		grad[childId] += childSeed;
		computeGrad(childId, childSeed, grad);
	}
}

}
}

#endif // REV_VAR_GRAPH_HPP
