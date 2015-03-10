#include "Graph.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int wWidth = 720;
const int wHeight = 720;

struct spriteData
{
	unsigned int id;
	float xPos, yPos;
};



int main( int argc, char* argv[] )
{	
	//initialize screen settings
	Initialise(wWidth, wHeight, false, "Tanks");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	
	float sWidth, sHeight;
	const int gWidth = 20;

	Graph myGraph(gWidth, gWidth);	//	create graph: ACTUAL DATA
	std::vector<GraphNode*>::iterator beg = myGraph.m_aNodes.begin();
	std::vector<GraphNode*>::iterator end = myGraph.m_aNodes.end()-1;
	std::vector<GraphNode*>::iterator iter = beg;
	

	/*GraphNode display;
	display = myGraph.FindNode(1, 1);
	cout << display.m_iNodeNumber;*/

	spriteData spriteList[gWidth*gWidth];		//	array of sprites for graph
	sWidth = wWidth / gWidth;
	sHeight = wHeight / gWidth;

	//	for drawing grid: FOR VISUALIZING
	for (int i = 0; i < gWidth; i++)
	{
		for (int j = 0; j < gWidth; j++)
		{
			spriteList[gWidth * i + j].id = CreateSprite("./square.png", sWidth, sHeight, true);
			spriteList[gWidth * i + j].xPos = (sWidth)*j + (sWidth / 2);
			spriteList[gWidth * i + j].yPos = (sHeight)*i + (sHeight / 2);
			MoveSprite(spriteList[gWidth * i + j].id, spriteList[gWidth * i + j].xPos, spriteList[gWidth * i + j].yPos);
		}
	}

	myGraph.SetWalls();

	//cout << myGraph.SearchDFS((*beg), (*end)) << endl;	//	return true if beg connect to end
	myGraph.SearchDijkstra((*beg), (*end));
	
	DestroySprite(spriteList[(*beg)->m_iNodeNumber].id);
	DestroySprite(spriteList[(*end)->m_iNodeNumber].id);

	myGraph.BuildPath((*beg), (*end));

	//	check&change graphnode if traversed (draws numerically, NOT by search func)
	for (iter; iter != myGraph.m_aNodes.end(); iter++)
	{
		if ((*iter)->m_bVisited && iter != beg && iter != end)
		{
			spriteList[iter - beg].id = CreateSprite("./traversed.png", sWidth, sHeight, true);
			MoveSprite(spriteList[iter - beg].id, spriteList[iter - beg].xPos, spriteList[iter - beg].yPos);
		}
		if ((*iter)->isPathNode && iter != end)
		{
			spriteList[iter - beg].id = CreateSprite("./path.png", sWidth, sHeight, true);
			MoveSprite(spriteList[iter - beg].id, spriteList[iter - beg].xPos, spriteList[iter - beg].yPos);
		}
		if (!(*iter)->isWalkable && iter != end)
		{
			spriteList[iter - beg].id = CreateSprite("./wall.png", sWidth, sHeight, true);
			MoveSprite(spriteList[iter - beg].id, spriteList[iter - beg].xPos, spriteList[iter - beg].yPos);
		}
	}

    //***********************Game Loop************************
	do
	{
		ClearScreen();

		//	draw all graphnodes
		for (int i = 0; i < gWidth*gWidth; i++)
		{
			DrawSprite(spriteList[i].id);
		}

		
		
	} while(FrameworkUpdate() == false);
	//*******************************************************
		

    Shutdown();

    return 0;
}

