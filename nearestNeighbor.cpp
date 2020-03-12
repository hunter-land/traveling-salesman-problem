#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits.h>

struct city {
	unsigned int id = 0;
	int x = 0;
	int y = 0;

	bool operator==(const city &right) {
		return x == right.x && y == right.y && id == right.id;
	}
};

struct tour {
	unsigned long long length = ULLONG_MAX;
	std::vector<city> cities;
};

unsigned int cityDistance(city a, city b) {
	return std::round(std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)));
}

tour nearestNeighbor(std::vector<city> cities, size_t maxTrys = 10) {
	// for every city
	// 	for unusedCities
	// 		for unusedCities
	// 			trackNearest
	// 		add nearest
	// 	trackBest
	// return best graph1

	std::vector<city> bestGraph = cities;
	unsigned long long bestLength = ULLONG_MAX;
	size_t stepSize = std::max((size_t)1, cities.size()/maxTrys);
	for(size_t i = 0, j = 0; i < cities.size() && j < maxTrys; i += stepSize) {
		city &startingCity = cities[i];
		//std::cout << "Starting from #" << startingCity.id;// << std::endl;
		std::vector<city> thisGraph = {startingCity};
		//thisGraph.push_back(startingCity);
		unsigned long long thisGraphLength = 0;

		std::vector<city> unusedCities = cities;
		unusedCities.erase(std::remove(unusedCities.begin(), unusedCities.end(), startingCity), unusedCities.end());

		//std::cout << "Starting with " << thisGraph.size() << ":" << unusedCities.size() << " cities..." << std::endl;
		while(unusedCities.size() > 0) {
			city nearest = unusedCities[0];
			unsigned long long distance = cityDistance(thisGraph[thisGraph.size()-1], nearest);
			for(size_t i = 1; i < unusedCities.size(); i++) {//for all unusedCities
				//find the closest one
				unsigned long long d = cityDistance(thisGraph[thisGraph.size()-1], unusedCities[i]);
				if(d < distance) {
					nearest = unusedCities[i];
					distance = d;
				}
			}
			//std::cout << " +" << distance << ">\t" << nearest.id; //std::cout << "\tNext node #" << nearest.id << std::endl;
			//add it to thisGraph
			thisGraph.push_back(nearest);
			thisGraphLength += distance;
			//remove it from unused cities
			unusedCities.erase(std::remove(unusedCities.begin(), unusedCities.end(), nearest), unusedCities.end());

			//std::cout << startingCity.id << "\t" << unusedCities.size() << "\t\t" << bestGraph[0].id << "\t" << bestLength << std::endl;

			if(thisGraphLength > bestLength) {
//				std::cout << "Broken: ";
				break;
			}
		}
//		std:: cout << thisGraph[0].id << ":\t" << thisGraphLength << " with " << thisGraph.size() << std::endl;
		// if(thisGraph.size() != cities.size()) {
		// 	std::cout << "Wrong size, missing ";
		// 	for(city uc : unusedCities) {
		// 		std::cout << uc.id << ", ";
		// 	}
		// 	std::cout << std::endl;
		// }
		if(thisGraphLength < bestLength) { // thisGraph.size() == cities.size()
			bestGraph = thisGraph;
			bestLength = thisGraphLength;
			//std::cout << "New best: " << thisGraph[0].id << std::endl;
		} else {
			//std::cout << "Not best distance: " << thisGraphLength << " vs current " << bestLength << std::endl;
		}
	}
	tour bestTour;
	bestTour.cities = bestGraph;
	bestTour.length = bestLength;
	return bestTour;
}

int main() {
	std::string line;
	std::vector<city> cities;
	while(std::getline(std::cin, line)) {
		city c;
		size_t s = 0;
		c.id = std::stod(line, &s);
		line = line.substr(s);
		c.x = std::stod(line, &s);
		line = line.substr(s);
		c.y = std::stod(line, &s);
		//std::cout << "Added city #" << c.id << "@(" << c.x << "," << c.y << ")" << std::endl;
		cities.push_back(c);
	}
	tour bestPath = nearestNeighbor(cities, 150);
	std::cout << "Tour(" << bestPath.cities[0].id << ") length of " << bestPath.length << " between " << bestPath.cities.size() << "/" << cities.size() << " cities." << std::endl;
}
