#include "AIE.h"
#include "Graph.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int wWidth = 720;
const int wHeight = 720;

int main( int argc, char* argv[] )
{	
	//initialize screen settings
	Initialise(wWidth, wHeight, false, "Tanks");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	
	float sWidth, sHeight;
	const int gWidth = 20;

	Graph myGraph(gWidth, gWidth);	//	create graph
	std::vector<GraphNode*>::iterator beg = myGraph.m_aNodes.begin();
	beg++;
	std::vector<GraphNode*>::iterator end = myGraph.m_aNodes.end();
	end--;
	

	/*GraphNode display;
	display = myGraph.FindNode(1, 1);
	cout << display.m_iNodeNumber;*/

	unsigned int spriteList[gWidth*gWidth];
	sWidth = wWidth / gWidth;
	sHeight = wHeight / gWidth;
	for (int i = 0; i < gWidth; i++)
	{
		for (int j = 0; j < gWidth; j++)
		{
			spriteList[gWidth * i + j] = CreateSprite("./square.png", sWidth, sHeight, true);
			MoveSprite(spriteList[gWidth * i + j], (sWidth)*j + (sWidth /2), (sHeight)*i + (sHeight/2));
		}
	}

    //***********************Game Loop************************
	do
	{
		ClearScreen();

		cout << myGraph.SearchDFS((*beg), (*end)) << endl;	//	return true if beg connect to end

		for (int i = 0; i < gWidth*gWidth; i++)+
		{
			if ((*beg)->m_bVisited)
			{
				spriteList[beg-myGraph.m_aNodes.begin()] = CreateSprite("./traversed.png", sWidth, sHeight, true);	//	this is fucked up: moves when sprite switch
			}
			DrawSprite(spriteList[i]);
		}

	} while(FrameworkUpdate() == false);
	//*******************************************************
		

    Shutdown();

    return 0;
}

