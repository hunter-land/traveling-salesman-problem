#include <limits.h>
#include <cmath>
#include <vector>

// A city (node) in a graph
struct city {
	unsigned int id = 0; // Unique identifier
	int x = 0; // X-coordinate
	int y = 0; // Y-coordinate

	bool operator==(const city &right) {
		return x == right.x && y == right.y && id == right.id;
	}
};

// A solution to the TSP
struct tour {
	unsigned long long length = ULLONG_MAX;
	std::vector<city> cities;
};

/*
	Calculates the distance between two cities

	@param a first city
	@param b second city

	@return distance between cities, rounded to nearest integer
*/
unsigned int cityDistance(city a, city b) {
	return std::round(std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)));
}