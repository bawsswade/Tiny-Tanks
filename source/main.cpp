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
	const int gWidth = 4;

	Graph myGraph(gWidth, gWidth);	//	create graph
	std::vector<GraphNode*>::iterator beg = myGraph.m_aNodes.begin();
	beg++;
	std::vector<GraphNode*>::iterator end = myGraph.m_aNodes.end();
	end--;
	cout << myGraph.SearchDFSrec((*beg), (*end)) << endl;

	GraphNode display;
	display = myGraph.FindNode(1, 1);
	cout << display.m_iNodeNumber;

	unsigned int spriteList[gWidth*gWidth];
	for (int i = 0; i < gWidth; i++)
	{
		for (int j = 0; j < gWidth; j++)
		{
			spriteList[gWidth * i + j] = CreateSprite("./square.png", wWidth / gWidth, wHeight / gWidth, true);
			MoveSprite(spriteList[gWidth * i + j], (wWidth / gWidth)*j + (wWidth / gWidth /2), (wHeight / gWidth)*i + (wHeight / gWidth/2));
		}
	}

    //***********************Game Loop************************
	do
	{
		ClearScreen();

		//DrawSprite(hello);

		for (int i = 0; i < 4; i++)
		{
			DrawSprite(spriteList[i]);
		}

	} while(FrameworkUpdate() == false);
	//*******************************************************
		

    Shutdown();

    return 0;
}

