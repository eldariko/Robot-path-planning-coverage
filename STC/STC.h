
#include "../Map/Map.h"
#include "Node.h"

using namespace std;


class STC {
private:
	Map &map;
	vector<vector<Node *> > graph;
	int graphWidth;
    int graphHeight;
    vector<Node *> mPath;
    void buildGraph();
	void DFS(Node* n);
	void printGraph();
	void printMap();
	void printDFS();
public:
	STC(Map &map, Position startPos);
	vector<vector<Node *> > getGraph();
	vector<Node> convertVector2dTo1d(vector<vector<Node *> > graph);
	void buildSpanningTree(Node* node);
	void printPath() ;
	void drawSpanningTree();
	unsigned int getGraphWidth();
	unsigned int getGraphHeight();
	const vector<Node*>& getPath() const {
			return mPath;
 		}
	virtual ~STC();
};


