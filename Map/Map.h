/*
 * Map.h
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#include "../STC/Node.h"
#include "lodepng.h"
#include <vector>
using namespace std;
typedef vector<vector<bool> > Grid;
class Map {
private:
	vector<unsigned char> image;
	//vector<unsigned char> Gridimage;
	Grid originalMap;
	Grid inflateMap;
	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned int coarseMapWidth;
	unsigned int coarseMapHeight;
	float mapResolution;
	float robotSize;
	//size of the robot in pixels
	int robotSizeInCells;
	//the inflation of the map
	unsigned int inflationRadius;
	Grid fineGrid; // each cell in the size of the robot
	Grid coarseGrid; // each cell in the size 2x2 of the fine grid cell

	bool checkIfCellIsOccupied(int i, int j);
	void inflate(int i , int j);

public:
	Map(float mapResolution, float robotSize);
	void loadMapFromFile(const char* filePath);
	void addPathToFile(char* filePath , vector<vector<Node *> > graph,int Width,int Hight);
	void inflateObstacles();
	void printInflateMap() const;
	void printGrid(const Grid &grid) const;
	vector<vector<bool> > getInflateMap();
	void writeinflateObstacles();
	void buildFineGrid();
	void buildCoarseGrid();
	virtual ~Map();
	const vector<unsigned char>& GetImage(){
		return image;
	}
	const Grid& getOriginalMap() const;
	const Grid& getFineGrid() const;
	const Grid& getCoarseGrid()const;

};

#endif /* MAP_H_ */
