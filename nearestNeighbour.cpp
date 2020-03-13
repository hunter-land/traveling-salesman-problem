#include <vector>
#include <algorithm>
#include "util.cpp"

//Approximate TSP, with a max number of attempts
tour nearestNeighbor(std::vector<city> cities, size_t maxTrys = 10) {
	// for every city
	// 	for unusedCities
	// 		for unusedCities
	// 			trackNearest
	// 		add nearest
	// 	trackBest
	// return best graph1

	tour bestTour;
	size_t stepSize = std::max((size_t)1, cities.size()/maxTrys);
	for(size_t i = 0, j = 0; i < cities.size() && j < maxTrys; i += stepSize) { //Pick maxTrys cities and solve using each as starting city
		city &startingCity = cities[i];
		//std::cout << "Starting from #" << startingCity.id;// << std::endl;
		std::vector<city> thisGraph = {startingCity};
		unsigned long long thisGraphLength = 0;

		std::vector<city> unusedCities = cities;
		unusedCities.erase(std::remove(unusedCities.begin(), unusedCities.end(), startingCity), unusedCities.end());

		while(unusedCities.size() > 0) { //While we have not gone to all cities
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

		//If we have found a new best, save it
		if(thisGraphLength < bestTour.length) {
			bestTour.cities = thisGraph;
			bestTour.length = thisGraphLength;
			//std::cout << "New best: " << thisGraph[0].id << std::endl;
		} else {
			//std::cout << "Not best distance: " << thisGraphLength << " vs current " << bestLength << std::endl;
		}
	}
	bestTour.length += cityDistance(bestTour.cities[0], bestTour.cities[bestTour.cities.size()-1]); //Add last connection
	return bestTour;
}