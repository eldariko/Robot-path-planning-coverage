/*
 * ConfigurationManager.h
 *
 *  Created on: May 29, 2015
 *      Author: user
 */

#include "../Defines.h"
#include <string>

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

//#define CONFIGURA?TION_PATH '/home/user/workspace/Robots/Configuration'

using namespace std;

class ConfigurationManager {
public:
	char file_data[NUM_OF_PROPERTIES][MAX_LINE_LENGTH];
	const char * map_path;
	int start_x;
	int start_y;
	int yaw;
	int target_x;
	int target_y;
	double robot_length;
	double robot_width;
	double map_resolution;
	double grid_resolution;
	char* configurationPath;

	ConfigurationManager(const char* configurationPath);
	virtual ~ConfigurationManager();

	void ReadConfigurationData(const char* configurationPath);
	void ReadConfigFile(const char* configPath);
	void Read(const char* configPath);
	void convertSizeToCM();
};

#endif /* CONFIGURATIONMANAGER_H_ */
