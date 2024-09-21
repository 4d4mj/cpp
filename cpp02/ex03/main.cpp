// main.cpp
#include "bsp.hpp"
#include <iostream>

int main()
{
	// Create three vertices of a triangle
	Point a(0.0f, 0.0f);
	Point b(5.0f, 0.0f);
	Point c(2.5f, 5.0f);

	// Create a point to test
	Point point(2.5f, 2.0f); // Inside the triangle

	// Call the bsp function
	if (bsp(a, b, c, point))
	{
		std::cout << "Point is inside the triangle." << std::endl;
	}
	else
	{
		std::cout << "Point is outside the triangle." << std::endl;
	}

	return 0;
}
