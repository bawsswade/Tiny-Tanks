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
	/*! \brief struct edge: holds start and end node and exdge cost
	*/
	struct Edge
	{
		GraphNode* m_pStart;	/**< GraphNode pointer to start node */
		GraphNode* m_pEnd;		/**< GraphNode pointer to end node */
		float m_fCost;			/**< cost from start to end node */
	};

	typedef std::vector<Edge> EdgeList;

	//	constructors
	GraphNode(){};
	/**	\brief GraphNode constructor that creates a vector of graphnodes with edges connecting to all sides
	  * \param int: num by num graph
	*/
	GraphNode(int a_iNum);

	/// vector of edges
	EdgeList m_aEdges;
	/// bool if node is visited while searching 
	bool m_bVisited = false;

	/**	\brief adds edge to edgelist 
		\param endnode and the cost between each
	*/
	void AddEdge(GraphNode *endNode, float cost);
	/**	\brief remove an node and all nodes connecting to it
		\param which node to remove
	*/
	void RemoveEdges(GraphNode *n);
	/**	\prints all eges of one graphnode
		\param which graphnode to display edges
	*/
	void DisplayEdges();	//	all neighbors

	bool isPathNode = false;	///< marks final path of nodes
	bool isWalkable = true;		///< wall or not
	int m_iNodeNumber;			///< graphNode's node number
	float posX, posY;			///< location drawn
	float gScore = 0;		//	nodes gscore (how list is ordered)
	float fScore = 0;
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
	void SearchAStar(GraphNode* a_pStart, GraphNode* a_pEnd);


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