#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include "AIE.h"

using namespace std;



class GraphNode
{
public:
	struct Edge
	{
		GraphNode* m_pStart;
		GraphNode* m_pEnd;
		float m_fCost;
	};
	typedef std::vector<Edge> EdgeList;

	//	constructors
	GraphNode(){};
	GraphNode(int a_iNum);

	EdgeList m_aEdges;
	bool m_bVisited = false;

	//	functions
	void AddEdge(GraphNode *endNode, float cost);
	void RemoveEdges(GraphNode *n);

	void DisplayEdges();	//	all neighbors

	bool isPathNode = false;
	bool isWalkable = true;
	int m_iNodeNumber;	
	float posX, posY;		//	location drawn
	float gScore = 0;		//	nodes gscore (how list is ordered)
	GraphNode *prevNode = NULL;	//	holds parent Node

	~GraphNode(){};
};

class Graph
{
	typedef std::vector<GraphNode*> NodeList;
public:
	//Creates an empty graph
	Graph(){};
	Graph(int x, int y);
	//Creates a graph with the given number of nodes the contents and links of the nodes are randomized
	Graph(unsigned int a_uiNodeCount);

	void AddNode(GraphNode* a_pNode);
	void RemoveNode(GraphNode* a_pNode);

	//	Depth first
	bool SearchBFS(GraphNode* a_pStart, GraphNode* a_pEnd);
	bool SearchDFS(GraphNode* a_pStart, GraphNode* a_pEnd);
	bool SearchDFSrec(GraphNode* a_pStart, GraphNode* a_pEnd);
	void SearchDijkstra(GraphNode* a_pStart, GraphNode* a_pEnd);


	//	traverses graph from end and sets bool pathNode
	void BuildPath(GraphNode* a_pStart, GraphNode *a_pEnd);
	void SetWalls();

	void DisplayNodes();
	void ResetVisited();
	GraphNode FindNode(float x, float y);

	NodeList m_aNodes;
	

	~Graph(){};
};

bool NodeCompare(const GraphNode* left, const GraphNode* right);

#endif //_GRAPH_H_