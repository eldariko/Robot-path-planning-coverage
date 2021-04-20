/*
 * STC.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: colman
 */

#include "STC.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

STC::STC(Map &map, Position startPos):map(map) {
	buildGraph();
	printGraph();
	cout<<endl;
	cout<<endl;
	printMap();
	cout<<"start position: "<<startPos.first<< " "<< startPos.second<<endl;
	DFS(graph[startPos.first][startPos.second]);
	//buildSpanningTree(graph[startPos.first][startPos.second]);
//	printPath();
}
//build graph using inflate grid
void STC::buildGraph() {
	cout<<"build graph"<<endl;
	Grid coarseGrid = map.getCoarseGrid();
	this->graphHeight  = coarseGrid.size();
	this->graphWidth= coarseGrid[0].size();

	graph.resize(graphHeight);
	for (int i = 0; i < graphHeight; i++)
		graph[i].resize(graphWidth);

	for (int i=0;i<graphHeight;i++) {
		for (int j=0;j<graphWidth;j++) {
			// Node is not occupied in coarseGrid
			if (!coarseGrid[i][j]) {
				//Node* node = new Node(i, j);
				graph[i][j] = new Node(i, j);;
			}
		}
	}

	cout<<"build graph end"<<endl;

}
void STC::printMap() {
    cout<<"map:"<<endl;
    Grid fineGrid = map.getFineGrid();
	int rows = fineGrid.size();
	int cols = fineGrid[0].size();
		for (int i=0;i<rows;i++) {
			for (int j=0;j<cols;j++) {
				if (!fineGrid[i][j]) {
					cout << setw(2) << i << ":" << setw(2) <<  j << " ";
				} else {
					cout << "  :   ";
				}
			}
			cout << endl;
		}
}

void STC::printGraph() {
    cout<<"graph:"<<endl;
	int gridRows = graph.size();
	int gridCols = graph[0].size();
		for (int i=0;i<gridRows;i++) {
			for (int j=0;j<gridCols;j++) {
				if (graph[i][j]) {
					cout << setw(2) << i << ":" << setw(2) <<  j << " ";
				} else {
					cout << "  :   ";
				}
			}
			cout << endl;
		}
}



void STC::DFS(Node* n) {
		n->visited = true;
		unsigned int x = n->getPosition().first;
		unsigned int y = n->getPosition().second;
		cout << "visited: (" << n->row << ", " << n->col << ")" << endl;

		//add the point of path
		mPath.push_back(n);

		// right
		unsigned int row = x - 1;
		unsigned int col = y;
		if (row >= 0 && row < graph.size() && col >= 0 && col < graph[0].size()) {
			//check if exist node in this field
			if (graph[row][col] != NULL && !graph[row][col]->visited) {
				n->neighborsInSpanningTree[0] = graph[row][col];
				DFS(graph[row][col]);
				mPath.push_back(n);
			}
		}

		// down
		row = x;
		col = y - 1;
		if (row >= 0 && row < graph.size() && col >= 0 && col < graph[0].size()) {
			if (graph[row][col] != NULL && !graph[row][col]->visited) {
				n->neighborsInSpanningTree[3] = graph[row][col];
				DFS(graph[row][col]);
				mPath.push_back(n);
			}
		}

		// left
		row = x + 1;
		col = y;
		if (row >= 0 && row < graph.size() && col >= 0 && col < graph[0].size()) {
			if (graph[row][col] != NULL && !graph[row][col]->visited) {
				n->neighborsInSpanningTree[2] = graph[row][col];
				DFS(graph[row][col]);
				mPath.push_back(n);
			}
		}

		// up
		row = x;
		col = y + 1;
		if (row >= 0 && row < graph.size() && col >= 0 && col < graph[0].size()) {
			if (graph[row][col] != NULL && !graph[row][col]->visited) {
				n->neighborsInSpanningTree[1] = graph[row][col];
				DFS(graph[row][col]);
				mPath.push_back(n);
			}
		}

		//Path.push_back(n);

//		n->visited = true;
//		int x = n->getPosition().first;
//		int y = n->getPosition().second;
//
//		cout << "visited: (" << n->row << ", " << n->col << ")" << endl;
//
//		// down
//		unsigned row = x+1;
//		unsigned col = y;
//		if (row >= 0 && row < graph.size() && col >=0 && col < graph[0].size()) {
//			//check if exist node in this field and not visited yet
//			if (graph[row][col] != NULL && !graph[row][col]->visited) {
//				n->neighborsInSpanningTree[0] = graph[row][col];
//				DFS(graph[row][col]);
//			}
//		}
//		// left
//		row = x;
//		col = y-1;
//		if (row >= 0 && row < graph.size() && col >=0 && col < graph[0].size()) {
//			//check if exist node in this field and not visited yet
//			if (graph[row][col] != NULL && !graph[row][col]->visited) {
//				n->neighborsInSpanningTree[1] = graph[row][col];
//				DFS(graph[row][col]);
//			}
//		}
//
//		// up
//		row = x-1;
//		col = y;
//		if (row >= 0 && row < graph.size() && col >=0 && col < graph[0].size()) {
//			//check if exist node in this field and not visited yet
//			if (graph[row][col] != NULL && !graph[row][col]->visited) {
//				n->neighborsInSpanningTree[2] = graph[row][col];
//				DFS(graph[row][col]);
//			}
//		}
//
//		// right
//		row = x;
//		col = y+1;
//		if (row >= 0 && row < graph.size() && col >=0 && col < graph[0].size()) {
//			//check if exist node in this field and not visited yet
//			if (graph[row][col] != NULL && !graph[row][col]->visited) {
//				n->neighborsInSpanningTree[3] = graph[row][col];
//				DFS(graph[row][col]);
//			}
//		}
}

void STC::buildSpanningTree(Node* node) {

	//cout << "(" << node->row << ", " << node->col << ")" << endl;
	mPath.push_back(node);
	if (node->neighborsInSpanningTree.size() != 0) {
		for (unsigned i = 0; i < node->neighborsInSpanningTree.size(); i++) {
			if(node->neighborsInSpanningTree[i])
			buildSpanningTree(node->neighborsInSpanningTree[i]);
		}
	}
}

void STC::printPath() {
	cout << "PATH" << endl;
	Node lastNode(9,7);
	for (unsigned i = 0; i < mPath.size(); ++i) {
		cout << "(" << mPath[i]->row << ", " << mPath[i]->col << ")";
		cout << "( Dx: " << lastNode.row - mPath[i]->row << ", Dy: "<<
				lastNode.col - mPath[i]->col << ")" << endl;

		lastNode = *mPath[i];
	}
}

vector<Node > STC::convertVector2dTo1d(vector<vector<Node *> > graph){
	unsigned k=0;
	vector<Node> v;
	v.resize(graph.size()*graph[0].size());
	for(unsigned i = 0; i < graph.size(); i++){
	        for(unsigned j = 0; j < graph[i].size(); j++){
	        	if(graph[i][j]){
					//cout << "(" << graph[i][j]->getPosition().first << "," << graph[i][j]->getPosition().second << ") ";
	        		v[k]=*graph[i][j];
	        	    k++;
	        	}
	        }
        	//cout<<k<<endl;

	}

	v.resize(k);


return v;

}

void STC::printDFS() {
	cout<<"print DFS:"<<endl;
	int gridRows = graph.size();
	int gridCols = graph[0].size();
    cout<<"gridRows:"<<gridRows<<"gridCols:"<<gridCols<<endl;
	for (int i=0;i<gridRows;i++) {
		for (int j=0;j<gridCols;j++) {
			if (graph[i][j] != NULL) {
				//int b=0;
				for (int k=0;k<4;k++) {
					if (graph[i][j]->neighborsInSpanningTree[k] != NULL) {
                       // b++;
						cout << "(" << graph[i][j]->getPosition().first << "," << graph[i][j]->getPosition().second << ")";
						cout << " -> ";
						cout << "(" << graph[i][j]->neighborsInSpanningTree[k]->getPosition().first << "," << graph[i][j]->neighborsInSpanningTree[k]->getPosition().second << ")" << endl;
					}
				}
              //cout<<"b="<<b<<endl;
			}
		}
	}
}

vector<vector<Node *> > STC::getGraph(){
	//convertVector2dTo1d(graph)
	return graph;
	//return convertVector2dTo1d(graph);
}

unsigned int STC::getGraphWidth(){
return this->graphWidth;
}
unsigned int STC::getGraphHeight(){
	return this->graphHeight;
}

STC::~STC() {
	// TODO Auto-generated destructor stub
}

