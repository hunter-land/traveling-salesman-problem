#include <limits.h>
#include <cmath>
#include <vector>

//A city, its id, and coords
struct city {
	unsigned int id = 0;
	int x = 0;
	int y = 0;

	bool operator==(const city &right) {
		return x == right.x && y == right.y && id == right.id;
	}
};

//A tour of cities
struct tour {
	unsigned long long length = ULLONG_MAX;
	std::vector<city> cities;
};

//Get distance between cities
unsigned int cityDistance(city a, city b) {
	return std::round(std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)));
}