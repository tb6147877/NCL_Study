#include <iostream>
#include <cmath>
#include <string>

//Problem1================================================


int CalculateSqrt(int x) {
	int l = 0, r = x, mid;
	while (l + 1 < r)
	{
		mid = l + (r - l) / 2;
		if (x / mid >= mid)
		{
			l = mid;
		}
		else
		{
			r = mid;
		}
	}
	return r == 1 ? r : l;
}

//Problem2==================================================

#define MAP_ROW 100
#define MAP_COLUMN 100
#define MAP_RADIUS 5
#define RESET "\033[0m"
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */


class Unit {
private:
	int m_x;
	int m_y;
	int m_distance;

	int calculateDistanceToCenter() {
		int offset_x{ abs(m_x - 50) }, offset_y{abs(m_y-50)};
		//We do not need to calculate square root, because we just use this value to compare.
		return offset_x * offset_x + offset_y * offset_y;
	}
public:
	Unit() = default;
	Unit(const int x, const int y) :m_x{ x }, m_y{ y } {m_distance = calculateDistanceToCenter(); }
	Unit(const int flag) :m_x{ flag }, m_y{ flag }, m_distance{flag} {}
	Unit(const Unit& unit) { m_x = unit.m_x; m_y = unit.m_y; m_distance = unit.m_distance; }
	int getX() { return m_x; }
	int getY() { return m_y; }
	int getDistance() { return m_distance; }
	void draw(const bool flag) { 
		if (flag)
		{
			std::cout << YELLOW << "¡ñ" << RESET;
		}
		else {
			std::cout << BLUE << "¡ñ" << RESET;
		}
	}
	void find_reverse_unit(int& x, int& y) {
		x = m_x;
		y = MAP_ROW - m_y;
	}

	friend std::ostream& operator<<(std::ostream& out, const Unit& u);
};

std::ostream& operator<<(std::ostream& out, const Unit& a) {
	out << '('<<a.m_x << "/" << a.m_y<<')';
	return out;
}

class Map {
private:
	Unit m_units[MAP_ROW][MAP_COLUMN];

public:
	Map() {
		for (int i = 0; i < MAP_ROW; i++)
		{
			for (int j = 0; j < MAP_COLUMN; j++)
			{
				m_units[i][j] = Unit{ i,j };
				//std::cout << m_units[i][j]<<"  ";
			}
			//std::cout << "\n";
		}
	}

	void draw() {
		for (int i = 0; i < MAP_ROW ; i++)
		{
			for (int j = 0; j < MAP_COLUMN; j++)
			{
				if (m_units[i][j].getDistance()<MAP_RADIUS*MAP_RADIUS)
				{
					m_units[i][j].draw(true);
				}
				else {
					m_units[i][j].draw(false);
				}
			}
			std::cout << "\n";
		}
	}
};

int main() {
	Map map{};
	map.draw();
}