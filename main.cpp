#include "nearestNeighbour.cpp"
#include <iostream>

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
		cities.push_back(c);
	}

	//Solve best tsp path for given list of cities, with a maximum of 150 iterations
	tour bestPath = nearestNeighbor(cities, 150); 
	
	//Output results to file
	std::cout << bestPath.length << std::endl;
	for(city c : bestPath.cities) {
		std::cout << c.id << std::endl;
	}
}