/*
 * ConfigurationManager.cpp
 *
 *  Created on: May 29, 2015
 *      Author: user
 */

#include "ConfigurationManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
using namespace std;

using namespace std;
ConfigurationManager::ConfigurationManager(const char* configurationPath) {
	ReadConfigFile(configurationPath);
	//convertSizeToCM();

}
void ConfigurationManager::ReadConfigFile(const char* configPath)
{
	// variables
			string mapPath;
			string temp;
			double mapResolution;
			double gridResolution;
			double startLocationX;
			double startLocationY;
			double startLocationYAW;
			double targetPointX;
			double targetPointY;
			double robotSizeX;
			double robotSizeY;

			ifstream fin(configPath);
			string line;
			istringstream sin;

			// Getting the map path
			getline(fin, line);
			istringstream aa(line);
			aa >> temp >> mapPath;

			this->map_path = (char*)mapPath.c_str();

			// Getting the start location
			getline(fin, line);
			istringstream bb(line);
			bb >> temp >> startLocationX >> startLocationY >> startLocationYAW;
			this-> start_x = startLocationX;
			this-> start_y = startLocationY;
			this-> yaw = startLocationYAW;

			// Getting the goal
			getline(fin, line);
			istringstream cc(line);
			cc >> temp >> targetPointX >> targetPointY;
			this-> target_x = targetPointX;
			this-> target_y = targetPointY;

			// Getting the robot size
			getline(fin, line);
			istringstream dd(line);
			dd >> temp >> robotSizeX >> robotSizeY;
			this-> robot_width = robotSizeX;
			this-> robot_length = robotSizeY;

			// Getting the map resolution
			getline(fin, line);
			istringstream ee(line);
			ee >> temp >> mapResolution;
			this-> map_resolution = mapResolution;

			// Getting the grid resolution
			getline(fin, line);
			istringstream ff(line);
			ff >> temp >> gridResolution;
			this-> grid_resolution = gridResolution;

			fin.close();
}

void ConfigurationManager::ReadConfigurationData(const char* configurationPath) {
	 ifstream myReadFile;
	 int counter = 0;
	 char attribute_name[MAX_LINE_LENGTH];
	 myReadFile.open(configurationPath);
	 while (!myReadFile.eof() && (counter < NUM_OF_PROPERTIES)) {

		 myReadFile.getline(attribute_name, MAX_LINE_LENGTH, ' ');
		 myReadFile.getline(this->file_data[counter], MAX_LINE_LENGTH, '\n');
		 counter++;
	}

	this->map_path = this->file_data[0];
	this->start_x = atoi(this->file_data[1]);
	this->start_y = atoi(this->file_data[2]);
	this->yaw = atoi(this->file_data[3]);
	this->target_x = atoi(this->file_data[4]);
	this->target_y = atoi(this->file_data[5]);
	this->robot_length = atof(this->file_data[6]);
	this->robot_width = atof(this->file_data[7]);
	this->map_resolution = atof(this->file_data[8]);
	this->grid_resolution = atof(this->file_data[9]);
}

void ConfigurationManager::Read(const char* configurationPath){
	ifstream file(configurationPath);
	string str;
	for (int i=0; getline(file, str); i++) {
	string temp;
	vector<string> words;
	stringstream s(str);
	while (s >> temp)
	words.push_back(temp);
	switch (i) {
	case 0: // map file name
		this->map_path = (char*)words[1].c_str();
	break;
	case 1: // start coordinates
		this->start_x = atof(words[1].c_str());
		this->start_y = atof(words[2].c_str());
		this->yaw = atof(words[3].c_str());
	break;
	case 2: // goal coordinates
		this->target_x = atof(words[1].c_str());
		this->target_y = atof(words[2].c_str());
	break;
	case 3: // robot size
		this->robot_length = atof(words[1].c_str());
		this->robot_width = atof(words[1].c_str());
	break;
	case 4: // map resolution
		this->map_resolution = atof(words[1].c_str());
	break;
	case 5: // grid resolution
		this->grid_resolution = atof(words[1].c_str());
	break;
	}
	}
	file.close();
}

void ConfigurationManager::convertSizeToCM(){
	this->robot_length = this->robot_length / this->map_resolution;
	this->robot_width = this->robot_width / this->map_resolution;
}

ConfigurationManager::~ConfigurationManager() {
	// TODO Auto-generated destructor stub
}
