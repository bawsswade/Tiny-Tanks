#include "graph.h"

//#include <algorithm>

Graph::Graph(int a_x, int a_y)
{
	// create and set x&y of nodes
	for (int i = 0; i < a_y; i++)
	{
		for (int j = 0; j < a_x; j++)
		{
			GraphNode *ptr = new GraphNode;
			ptr->posX = j;
			ptr->posY = i;
			ptr->m_iNodeNumber = (i*a_x) + j;
			this->AddNode(ptr);
		}
	}

	//	add edges
	std::vector<GraphNode*>::iterator it = this->m_aNodes.begin();
	for (int i = 0; i < a_y; i++)
	{
		for (int j = 0; j < a_x; j++)
		{
			float node = (i*a_x) + j;
			//	edge above
			if (i < a_y - 1)
				this->m_aNodes[node]->AddEdge(this->m_aNodes[node + a_x], 1);
			// edge to the right
			if (j < a_x - 1)
				this->m_aNodes[node]->AddEdge(this->m_aNodes[node + 1], 1);
			//	edge down
			if (i > 0)
				this->m_aNodes[node]->AddEdge(this->m_aNodes[node - a_x], 1);
			//	edge to the left
			if (j > 0)
				this->m_aNodes[node]->AddEdge(this->m_aNodes[node - 1], 1);
			//	edge diagonal top right
			if (i < a_y - 1 && j < a_x - 1)
				this->m_aNodes[node]->AddEdge(this->m_aNodes[node + a_x + 1], 1);
			//	 edge diagonal top left
			if (i < a_y - 1 && j > 0)
				this->m_aNodes[node]->AddEdge(this->m_aNodes[node + a_x - 1], 1);
			//	edge diagonal bottom left
			if (i > 0 && j > 0)
				this->m_aNodes[node]->AddEdge(this->m_aNodes[node - a_x - 1], 1);
			//	edge diagonal bottom right
			if (i > 0 && j < a_x - 1)
				this->m_aNodes[node]->AddEdge(this->m_aNodes[node - a_x + 1], 1);
		}
	}
}

GraphNode::GraphNode(int a_iNum)
{
	this->m_iNodeNumber = a_iNum;
}

void GraphNode::DisplayEdges()
{
	std::vector<Edge>::iterator it;
	cout << "Node " << this->m_iNodeNumber << " connects to: ";
	for (it = this->m_aEdges.begin(); it != this->m_aEdges.end(); ++it) {
		cout << it->m_pEnd->m_iNodeNumber << ", "; /*<< ". cost = " << it->m_fCost << endl;*/
	}
	cout << endl;
}

void Graph::AddNode(GraphNode* a_pNode)
{
	m_aNodes.push_back(a_pNode);
}

void Graph::RemoveNode(GraphNode* a_pNode)
{
	std::vector<GraphNode*>::iterator pNode = this->m_aNodes.begin();
	for (pNode; pNode != m_aNodes.end(); pNode++)
	{
		(*pNode)->RemoveEdges(a_pNode);
	}
}

void GraphNode::RemoveEdges(GraphNode *n)
{
	std::vector<Edge>::iterator it = this->m_aEdges.begin();
	while (it != this->m_aEdges.end())
	{
		if (it->m_pEnd == n)
		{
			//	erase returns random iterator to next element (have to assign it to it)
			it = m_aEdges.erase(it);
		}
		else
		{
			if (it != this->m_aEdges.end())
				it++;
		}
	}
}

void GraphNode::AddEdge(GraphNode *endNode, float cost)
{
	Edge temp;
	temp.m_pEnd = endNode;
	temp.m_pStart = this;
	temp.m_fCost = cost;
	this->m_aEdges.push_back(temp);
}

void Graph::DisplayNodes()
{
	std::vector<GraphNode*>::iterator it;
	for (it = this->m_aNodes.begin(); it != this->m_aNodes.end(); ++it) {
		cout << "Node: " << (*it)->posX << ", " << (*it)->posY << endl;
	}
}

void Graph::ResetVisited()
{
	std::vector<GraphNode*>::iterator it;
	for (it = this->m_aNodes.begin(); it != this->m_aNodes.end(); ++it) {
		(*it)->m_bVisited = false;
	}
}

bool Graph::SearchDFS(GraphNode* a_pStart, GraphNode* a_pEnd)
{
	std::stack<GraphNode*> oNodeStack;
	oNodeStack.push(a_pStart);

	while (!oNodeStack.empty())
	{
		GraphNode* pCurrent = oNodeStack.top();
		oNodeStack.pop();

		//	error checking if visisted
		if (pCurrent->m_bVisited == true)
		{
			continue;
		}

		//	set visited 
		pCurrent->m_bVisited = true;

		//	exit when found end
		if (pCurrent == a_pEnd)
		{
			return true;
		}

		// add all the neighbours of the current node onto the stack
		for (int i = 0; i < pCurrent->m_aEdges.size(); ++i)
		{
			if (pCurrent->m_aEdges[i].m_pEnd->m_bVisited != true)
			{
				oNodeStack.push(pCurrent->m_aEdges[i].m_pEnd);
			}
		}
	}

	//return false if we didn't find a_pEnd
	return false;
}

bool Graph::SearchDFSrec(GraphNode* a_pStart, GraphNode* a_pEnd)
{
	if (a_pStart->m_iNodeNumber != a_pEnd->m_iNodeNumber)
	{
		for (int i = 0; i < a_pStart->m_aEdges.size(); i++)
		{
			if (SearchDFSrec(a_pStart->m_aEdges[i].m_pEnd, a_pEnd))
				return true;
		}
	}
	else
		return true;
	return false;
}

bool Graph::SearchBFS(GraphNode* a_pStart, GraphNode* a_pEnd)
{
	std::queue<GraphNode*> oNodeQueue;
	oNodeQueue.push(a_pStart);

	while (!oNodeQueue.empty())
	{
		GraphNode* pCurrent = oNodeQueue.front();
		oNodeQueue.pop();

		//	error checking if visisted
		if (pCurrent->m_bVisited == true)
		{
			continue;
		}

		//	set visited 
		pCurrent->m_bVisited = true;

		//	exit when found end
		if (pCurrent == a_pEnd)
		{
			return true;
		}

		// add all the neighbours of the current node onto the queue
		for (int i = 0; i < pCurrent->m_aEdges.size(); ++i)
		{
			if (pCurrent->m_aEdges[i].m_pEnd->m_bVisited != true)
			{
				oNodeQueue.push(pCurrent->m_aEdges[i].m_pEnd);
			}
		}
	}

	//return false if we didn't find a_pEnd
	return false;
}

GraphNode Graph::FindNode(float a_x, float a_y)
{
	unsigned int closestX = INFINITY, closestY = INFINITY;
	std::vector<GraphNode*>::iterator it = this->m_aNodes.begin();
	GraphNode* returnNode = NULL;
	for (it; it != this->m_aNodes.end(); it++)
	{
		//	return the exact position: FIX if needed
		unsigned int tempX = (*it)->posX - a_x;
		unsigned int tempY = (*it)->posY - a_y;
		if (tempX == 0 && tempY == 0)
			returnNode = *it;
	}
	return (*returnNode);
}

bool NodeCompare(const GraphNode* left, const GraphNode* right)
{
	return (left->gScore < right->gScore);
}

void Graph::SearchDijkstra(GraphNode* a_pStart, GraphNode* a_pEnd)
{
	std::list<GraphNode*> q;	//	to run shortest path
	q.push_front(a_pStart);

	//GraphNode *pathNode;
	//a_pStart->gScore = 0;	//	set gscore

	while (!q.empty())
	{
		GraphNode* pCurrent = q.front();

		q.pop_front();
		cout << pCurrent->m_iNodeNumber << endl;

		//	error checking if visisted
		if (pCurrent->m_bVisited || !pCurrent->isWalkable)
		{
			continue;
		}
		//	set visited 
		else
		{
			pCurrent->m_bVisited = true;
		}

		// add all the neighbours of the current node onto the queue
		for (int i = 0; i < pCurrent->m_aEdges.size(); ++i)
		{
			if (pCurrent->m_aEdges[i].m_pEnd->m_bVisited != true)
			{
				//	assign all edge.prevNode to current node
				pCurrent->m_aEdges[i].m_pEnd->prevNode = pCurrent;	

				//	add edge cost to next node	
				pCurrent->m_aEdges[i].m_pEnd->gScore = pCurrent->m_aEdges[i].m_fCost + pCurrent->gScore;		
				//	push edge
				q.push_front(pCurrent->m_aEdges[i].m_pEnd);
				//	sort so that lowest g score is on top
				q.sort(NodeCompare);
			}
			///*sort using priority queue, go through least gscore, push everything else
			//push all nodes less than least gscore
			//set first edge to shortest path*/
			//if (i == 0)
			//{
			//	pathNode = pCurrent->m_aEdges[i].m_pEnd;	
			//}
			////	compare shortest path to rest and change if not shortest path
			////	need to fix: you're pushing all edges ends (double the work) pretty sure not getting shortest path
			//else
			//{
			//	//pathNode = q.front();
			//	if (pathNode->gScore < pCurrent->m_aEdges[i].m_pEnd->gScore)
			//	{
			//		q.push(pCurrent->m_aEdges[i].m_pEnd);
			//		q.push(pathNode);
			//	}
			//	else if (pathNode->gScore > pCurrent->m_aEdges[i].m_pEnd->gScore)
			//	{
			//		q.push(pathNode);
			//		pathNode = pCurrent->m_aEdges[i].m_pEnd;
			//		q.push(pCurrent->m_aEdges[i].m_pEnd);
			//	}
			//	else
			//	{
			//		q.push(pathNode);
			//		pathNode = pCurrent->m_aEdges[i].m_pEnd;
			//		q.push(pCurrent->m_aEdges[i].m_pEnd);
			//	}
			//}
			//q.front()->prevNode = pCurrent;	//	this is why it jumps
		}
		
		if (q.front() == a_pEnd)	//	change this so that it checks every instance
		{
			cout << "hi";
		}
		
	}
}

void Graph::BuildPath(GraphNode* a_pStart, GraphNode *a_pEnd)
{
	GraphNode *p = a_pEnd;
	while (p != a_pStart)
	{
		p->isPathNode = true;
		p = p->prevNode;
	}
}

void Graph::SetWalls()
{
	/*for (int i = 0; i < 19; i++)
	{
		this->m_aNodes[2 + i*20]->isWalkable = false;
	}*/
	this->m_aNodes[21]->isWalkable = false;
	this->m_aNodes[42]->isWalkable = false;
	this->m_aNodes[12]->isWalkable = false;
	this->m_aNodes[17]->isWalkable = false;
	this->m_aNodes[23]->isWalkable = false;
}