/*
 * Node.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#include "Node.h"

Node::Node()
{
	visited=false;
	row = 0;
	col = 0;
}
Node::Node(int row, int col) : row(row), col(col), visited(false) {
	neighborsInSpanningTree.resize(4);
}

Position Node::getPosition() {
	Position position;
	position.first = row;
	position.second = col;
	return position;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

