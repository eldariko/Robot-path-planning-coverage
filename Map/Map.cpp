
/*
 * Map.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#include "Map.h"
#include <iostream>

Map::Map(float mapResolution, float robotSize) :
	mapResolution(mapResolution), robotSize(robotSize) {
	mapWidth=0;mapHeight=0;coarseMapHeight=0;coarseMapWidth=0;
	robotSizeInCells = robotSize / mapResolution;
	inflationRadius = 0.3 * robotSizeInCells;
	cout<<"inflation radius "<< inflationRadius<<endl;
	cout <<"robotSizeInCells: "<< robotSizeInCells<< ", robotSize: " << robotSize << ",mapResolution: " << mapResolution << endl;

}

void Map::loadMapFromFile(const char* filePath) {
	lodepng::decode(image, mapWidth, mapHeight, filePath);
	cout << "original map size: " << mapWidth << "," << mapHeight << endl;
	originalMap.resize(mapHeight);
	for (unsigned i = 0; i < mapHeight; i++)
		originalMap[i].resize(mapWidth);

	for (unsigned i = 0; i < mapHeight; i++) {
		for (unsigned j = 0; j < mapWidth; j++) {
			originalMap[i][j] = checkIfCellIsOccupied(i, j);

		}
	}
}

bool Map::checkIfCellIsOccupied(int i, int j) {
	int c = (i * mapWidth + j) * 4;
	int r = image[c];
	int g = image[c + 1];
	int b = image[c + 2];

	if (r == 0 && g == 0 && b == 0)
		return true;
	return false;
}

void Map::printInflateMap() const {
	for (unsigned i = 0; i < mapHeight; i++) {
		for (unsigned j = 0; j < mapWidth; j++) {
			cout << (inflateMap[i][j] ? "*" : " ");
		}
		cout << endl;
	}
}

void Map::printGrid(const Grid &grid) const {
	int rows = grid.size();
	int cols = grid[0].size();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << (grid[i][j] ? "*" : " ");
		}
		cout << endl;
	}


}

void Map::inflateObstacles(){
    cout<<"inflate obstacle func start"<<endl;
	inflateMap.resize(mapHeight);
	for (unsigned i = 0; i < mapHeight; i++){
		inflateMap[i].resize(mapWidth);
	}


	for (unsigned i = 0; i < mapHeight; i++) {
		for (unsigned j = 0; j < mapWidth; j++) {
			if(originalMap[i][j]){
				inflate(i,j);
			}
		}
	}
	cout<<"inflate obstacle func end"<<endl;
}

void Map::inflate(int i , int j){

	for (unsigned int k=i-inflationRadius;k<i+inflationRadius;k++){
		for(unsigned int m=j-inflationRadius;m<j+inflationRadius;m++){
			if(m < 0 || k < 0 || k >= mapHeight || m >= mapWidth ){
				continue;
			}else{
				// Mark this cell as occupied in inflateMap
				inflateMap[k][m]= true;
				// Draw black color in corresponding image

				int c = (k * mapWidth + m) * 4;
				image[c] = 0;
				image[c + 1] = 0;
				image[c + 2] = 0;

			}
		}
	}
}

vector<vector<bool> > Map::getInflateMap(){
	return inflateMap;
}

void Map::writeinflateObstacles(){

	lodepng::encode("inflateMap.png",image,mapWidth,mapHeight);

}

void Map::buildFineGrid(){
	cout<<"buildFineGrid func start"<<endl;
	int fineGridHeight = mapHeight/robotSizeInCells;
	int fineGridWidth = mapWidth/robotSizeInCells;
	fineGrid.resize(fineGridHeight);
	for (int i = 0; i < fineGridHeight; i++){
		fineGrid[i].resize(fineGridWidth);
	}

	int flag = false;


	for(int i = 0;i<fineGridHeight;i++){
		for(int j = 0 ;j<fineGridWidth;j++){
			flag = false;
			for(int m=i*robotSizeInCells;m < i * robotSizeInCells +robotSizeInCells;m++ ){
				for(int z=j *robotSizeInCells;z< j * robotSizeInCells +robotSizeInCells;z++ ){
					if(inflateMap[m][z] == true){
						flag = true;
						break;
					}
				}
			}
			fineGrid[i][j]= flag;
		}
	}
	cout<<"buildFineGrid func end"<<endl;

}

void Map::buildCoarseGrid(){
	cout<<"buildCoraseGrid func start"<<endl;
	int coarseMapHeight = mapHeight/(robotSizeInCells*2);
			this->coarseMapHeight = coarseMapHeight;
			int coarseMapWidth = mapWidth/(robotSizeInCells*2);
			this->coarseMapWidth= coarseMapWidth;
			coarseGrid.resize(coarseMapHeight);
			for (int i = 0; i < coarseMapHeight; i++){
				coarseGrid[i].resize(coarseMapWidth);
			}

		    int flag = false;


		    for(int i = 0;i<coarseMapHeight;i++){
		    	for(int j = 0 ;j<coarseMapWidth;j++){
		    		flag = false;
		    		for(int m=i*(robotSizeInCells*2);m < i * (robotSizeInCells*2) +(robotSizeInCells*2);m++ ){
		    			for(int z=j *(robotSizeInCells*2);z< j * (robotSizeInCells*2) +(robotSizeInCells*2);z++ ){
		    				if(inflateMap[m][z] == true){
		    					flag = true;
		    					break;
		    				}
		    			}
		    		}
		    		coarseGrid[i][j]= flag;
		    	}
		    }

	cout<<"buildCoraseGrid func end"<<endl;

}

void Map::addPathToFile(char* filePath , vector<vector<Node *> > graph,int Width,int Hight) {

	cout<<"file path " <<filePath<<endl;
	cout<<"Width(coarse with) " << Width << endl;
	cout<<"Height(coarse height) " << Hight <<endl;
	cout<<"Graph length " << graph.size()<<endl;

	for(int z = 0;z<Hight;z++){
				for(int l= 0;l<Width;l++){
					if (graph[z][l] != NULL) {
						for (int k=0;k<4;k++) {
							if (graph[z][l]->neighborsInSpanningTree[k] != NULL) {
							   	int row = graph[z][l]->getPosition().first;
								int column = graph[z][l]->getPosition().second;
								//convert the row to the original map row that was read from the image
								row  = ((row+0.5) * robotSizeInCells * 2);
								//convert the column to the original map column that was read from the image
								column = ((column+0.5) * robotSizeInCells * 2);

								int neighborRow = graph[z][l]->neighborsInSpanningTree[k]->getPosition().first ;
								int neighborColumn = graph[z][l]->neighborsInSpanningTree[k]->getPosition().second;
								////convert the row to the original map row that was read from the image
								neighborRow = ((neighborRow+0.5) * robotSizeInCells * 2);
								////convert the column to the original map column that was read from the image
								neighborColumn = ((neighborColumn+0.5) * robotSizeInCells * 2);
								//check how we need to move on row or column
								if(column<neighborColumn && row == neighborRow){
									for (int m = column; m < neighborColumn; m++) {//draw horizontal red line
										int c = (row * mapWidth + m) * 4;
									    image[c] = 255;
										image[c + 1] = 0;
										image[c + 2] = 0;


									}
								//check how we need to move on row or column
								}else if(column>neighborColumn && row == neighborRow){
									for (int m =neighborColumn ; m < column; m++) {//draw horizontal red line
										int c = (row * mapWidth + m) * 4;
										image[c] = 255;
										image[c + 1] = 0;
										image[c + 2] = 0;
										}
								//check how we need to move on row or column
								}else if(column == neighborColumn && row > neighborRow){
									for (int m =neighborRow ; m < row; m++) {//draw vertical red line
										int c = (m * mapWidth + column) * 4;
										image[c] = 255;
										image[c + 1] = 0;
										image[c + 2] = 0;
										}
								//check how we need to move on row or column
								}else if(column == neighborColumn && row < neighborRow){
									for (int m =row ; m < neighborRow; m++) {//draw vertical red line
										int c = (m * mapWidth + column) * 4;
										image[c] = 255;
										image[c + 1] = 0;
										image[c + 2] = 0;
										}
								}
//								cout << "(" << graph[z][l]->getPosition().first << "," << graph[z][l]->getPosition().second << ")";
//								cout << " -> ";
//								cout << "(" << graph[z][l]->neighborsInSpanningTree[k]->getPosition().first << "," << graph[z][l]->neighborsInSpanningTree[k]->getPosition().second << ")" << endl;
							}
						}

					}

				}
			}

	unsigned error = lodepng::encode(filePath, image, mapWidth, mapHeight);
	if (!error){
		std::cout << "encoder error " << error << ": "
		<< lodepng_error_text(error) << std::endl;
	}
}

const Grid& Map::getFineGrid() const {
	return this->fineGrid;
}

const Grid& Map::getCoarseGrid() const{
	return this->coarseGrid;
}
const Grid& Map::getOriginalMap() const{
	return this->originalMap;
}


Map::~Map() {
	// TODO Auto-generated destructor stub
}


