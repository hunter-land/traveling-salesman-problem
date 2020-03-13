#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits.h>

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

//Approximate TSP, with a max number of attempts
tour nearestNeighbor(std::vector<city> cities, size_t maxTrys = 10) {
	// for every city
	// 	for unusedCities
	// 		for unusedCities
	// 			trackNearest
	// 		add nearest
	// 	trackBest
	// return best graph1

	// std::vector<city> bestGraph = cities;
	// unsigned long long bestLength = ULLONG_MAX;
	tour bestTour;
	size_t stepSize = std::max((size_t)1, cities.size()/maxTrys);
	for(size_t i = 0, j = 0; i < cities.size() && j < maxTrys; i += stepSize) {
		city &startingCity = cities[i];
		//std::cout << "Starting from #" << startingCity.id;// << std::endl;
		std::vector<city> thisGraph = {startingCity};
		unsigned long long thisGraphLength = 0;

		std::vector<city> unusedCities = cities;
		unusedCities.erase(std::remove(unusedCities.begin(), unusedCities.end(), startingCity), unusedCities.end());

		while(unusedCities.size() > 0) {
			city nearest = unusedCities[0];
			unsigned long long distance = cityDistance(thisGraph[thisGraph.size()-1], nearest);
			for(size_t i = 1; i < unusedCities.size(); i++) {//for all unusedCities
				//find the closest city
				unsigned long long d = cityDistance(thisGraph[thisGraph.size()-1], unusedCities[i]);
				if(d < distance) {
					nearest = unusedCities[i];
					distance = d;
				}
			}

			//add nearest city to thisGraph
			thisGraph.push_back(nearest);
			thisGraphLength += distance;
			//remove it from unused cities
			unusedCities.erase(std::remove(unusedCities.begin(), unusedCities.end(), nearest), unusedCities.end());

			if(thisGraphLength > bestTour.length) {
				break;
			}
		}

		if(thisGraphLength < bestTour.length) {
			bestTour.cities = thisGraph;
			bestTour.length = thisGraphLength;
			//std::cout << "New best: " << thisGraph[0].id << std::endl;
		} else {
			//std::cout << "Not best distance: " << thisGraphLength << " vs current " << bestLength << std::endl;
		}
	}
	bestTour.length += cityDistance(bestTour.cities[0], bestTour.cities[bestTour.cities.size()-1]);
	return bestTour;
}

int main() {
	std::string line;
	std::vector<city> cities;
	while(std::getline(std::cin, line)) { //For each city entry (line)
		city c;
		size_t s = 0;
		c.id = std::stod(line, &s); //Get city id
		line = line.substr(s);
		c.x = std::stod(line, &s); //Get x coord
		line = line.substr(s);
		c.y = std::stod(line, &s); //Get y coord
		//std::cout << "Added city #" << c.id << "@(" << c.x << "," << c.y << ")" << std::endl;
		cities.push_back(c);
	}
	tour bestPath = nearestNeighbor(cities, 150); //Solve best tsp path for given list of cities, with a maximum of 150 runs
	
	//Output results to file/prompt
	std::cout << bestPath.length << std::endl;
	for(city c : bestPath.cities) {
		std::cout << c.id << std::endl;
	}
	
	//std::cout << "Tour(" << bestPath.cities[0].id << ") length of " << bestPath.length << " between " << bestPath.cities.size() << "/" << cities.size() << " cities." << std::endl;
}
