// bsp.cpp
#include "Point.hpp"

// Helper function to calculate the area of a triangle
Fixed triangleArea(const Point &a, const Point &b, const Point &c)
{
	// Area of a triangle using vertices (x1, y1), (x2, y2), (x3, y3)
	return Fixed(std::abs((a.getX().toFloat() * (b.getY().toFloat() - c.getY().toFloat()) +
						   b.getX().toFloat() * (c.getY().toFloat() - a.getY().toFloat()) +
						   c.getX().toFloat() * (a.getY().toFloat() - b.getY().toFloat())) /
						  2.0f));
}

bool bsp(const Point a, const Point b, const Point c, const Point point)
{
	// Area of the triangle ABC
	Fixed areaABC = triangleArea(a, b, c);

	// Area of the triangles PAB, PBC, and PCA
	Fixed areaPAB = triangleArea(point, a, b);
	Fixed areaPBC = triangleArea(point, b, c);
	Fixed areaPCA = triangleArea(point, c, a);

	// If the sum of the areas of PAB, PBC, and PCA is equal to the area of ABC, the point is inside
	return (areaABC == (areaPAB + areaPBC + areaPCA));
}
