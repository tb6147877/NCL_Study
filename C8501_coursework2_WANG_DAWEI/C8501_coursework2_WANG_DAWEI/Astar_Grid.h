#pragma once

#include <iostream>
#include <vector>

#include "Unit.h"

namespace maze2 {
	//this class extend unit class and is used to A star path finding
	class Astar_Grid: public Unit//inheritance
	{
	private:
		Astar_Grid* m_parent;
		int m_f_value;
		int m_g_value;
		int m_h_value;
	public:

		Astar_Grid(const int x, const int y, const UnitType type, const MapType mapType);
		~Astar_Grid();

		int get_f_value() { return m_f_value; }
		void set_f_value(const int f) { m_f_value = f; }
		int get_g_value() { return m_g_value; }
		void set_g_value(const int g) { m_g_value = g; }
		int get_h_value() { return m_h_value; }
		void set_h_value(const int h) { m_h_value = h; }
		Astar_Grid* getParent() { return m_parent; }
		void setParent(Astar_Grid* p) { m_parent = p; }
		void print() { std::cout << "This is Derived class"; }
	};

}