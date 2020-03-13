#include "util.cpp"
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