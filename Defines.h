
#ifndef DEFINES_H_
#define DEFINES_H_

// Configuration Manager
#define NUM_OF_PROPERTIES 10
#define MAX_LINE_LENGTH 100
#define CONFIGURATION_PATH "Configuration"

#define ROBOT_SIZE = 0.3; //size of robot in meters
#define MAP_RESOLUTION = 0.025; //resolution of the map
#define MAP_WIDTH = 550; //map width in pixels
#define MAP_HEIGHT = 380; //map height in pixels

// Thickened map
#define THICKENED_MAP_NAME "ThickMap.png"


// Laser Proxy
#define FORWARD_LASER_PROXY_VALUE 332
#define RIGHT_LASER_PROXY_VALUE 50
#define LEFT_LASER_PROXY_VALUE 614
#define DISTANCE_TOLERANCE 0.3

// Movement
#define TURN_RIGHT_SPEED -0.3
#define TURN_LEFT_SPEED 0.3
#define MOVE_SPEED 0.1

#define TOLERANCE 10

// Behaviors
#define BEHAVIORS_COUNT 2
#define ONE_DEGREE_INDEXES 2.4667
#define LASER_SPEC 111
#define MAX_YAW_DIFF 2

#endif
