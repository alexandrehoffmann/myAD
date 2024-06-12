/*
 * VarGraph.hpp
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
 
#ifndef REV_VAR_GRAPH_HPP
#define REV_VAR_GRAPH_HPP

#include <vector>
#include <list>
#include <stdexcept>

namespace myAD
{
namespace rev
{

template<typename T> class Var;

/**
 * A graph that represents the evaluation of a function.
 * 
 * This class is a Singleton.
 * 
 * A node represents a variable. All variables are stored in the graph,
 * including temporary variables.
 * 
 * An edge represents a local gradient. More precisely, if there is an edge 
 * from variable A to variable B with value V, it means \f$ \frac{\partial A}{\partial B} = V \f$.
 * 
 */
template<typename T>
class VarGraph
{
public:
	friend class Var<T>;

	class Edge
	{
	public:
		Edge(const size_t childId, const T value) : m_childId(childId), m_value(value) {}

		size_t getChildId() const { return m_childId; }
		T      getValue()   const { return m_value;   }
	private:
		size_t m_childId;
		T      m_value;
	};

	static VarGraph<T>& getInstance();
	
	void reserveVars(const size_t nvars) { m_adjList.reserve(nvars); }
	void addEdge(const Var<T>& parent, const Var<T>& child, const T value);
	
	std::vector< T > gradient(const Var<T>& var, const T seed = 1);
	std::vector< T > gradient(const Var<T>& var, const Var<T>* x, const size_t x_size, const T seed = 1);
	
	size_t getNnodes() const { return m_adjList.size(); }
	size_t getNedges() const;
	
	void clear() { m_adjList.clear(); }
private:
	void addVar(Var<T>& var);

	VarGraph() {}
	
	void computeGrad(const size_t varId, const T& seed, T* grad);
	
	std::vector< std::list< Edge > > m_adjList;
};

}
}

#include <Reverse/VarGraph.tpp>

#endif // REV_VAR_GRAPH_HPP
