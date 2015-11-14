#pragma once
#ifndef GRAPH_DATA_GLOBALS_H
#define GRAPH_DATA_GLOBALS_H

using namespace std;
//--------------------------------------------------------------------------
//Add variables and arrays contaning data to add to the graph
// This will avoid the need to type in the data at the command prompt
const int i_numberOfVertices = 8;
const int i_numberOfDirections = 3;
const int i_maxEdges = i_numberOfVertices;
string strarr_vertexValues[i_numberOfVertices] = {"A","B","C","D","E","F","G","H"};

//------------------------------------------------------------------------
//Connected Vertex's, this if for use non directed, weighted and non weighted graph
string strarr_ConnectedStandard[i_numberOfVertices][i_maxEdges]
	= { {"B","C","","","","","",""},//Connected to A
		{"A","C","D","","","","",""},//Connected to B
		{"A","B","E","","","","",""},//Connected to C
		{"B","E","F","","","","",""},//Connected to D
		{"C","D","F","","","","",""},//Connected to E
		{"D","E","","","","","",""},//Connected to F
		{"A","C","H","I","","","",""},//Connected to G
		{"A","C","H","I","","","",""}//Connected to H
		};
//------------------------------------------------------------------------
//Connected Vertex's, this if for use non directed, weighted and non weighted graph
string strarr_ConnectedWeightedOnly[i_numberOfVertices][i_maxEdges]
	= { {"B","C","","","","","",""},//Connected to A
		{"A","C","D","","","","",""},//Connected to B
		{"A","B","E","","","","",""},//Connected to C
		{"B","E","F","","","","",""},//Connected to D
		{"C","D","F","","","","",""},//Connected to E
		{"D","E","","","","","",""},//Connected to F
		{"","","","","","","",""},//Connected to G
		{"","","","","","","",""}//Connected to H
		};

// This array stores the data for the weights of the edges
int iarr_weightsWeightedOnly[i_numberOfVertices][i_numberOfVertices][i_numberOfDirections]
= { {{6,0,0},{4,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to A
	{{6,0,0},{5,0,0},{2,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to B
	{{4,0,0},{5,0,0},{6,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to C
	{{2,0,0},{4,0,0},{3,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to D
	{{6,0,0},{4,0,0},{7,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to E
	{{3,0,0},{7,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to F
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to H
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to I
};

//------------------------------------------------------------------------
//Connected Vertex's, this is for use on a directed, non weighted graph
string strarr_ConnectedDirectionsOnly[i_numberOfVertices][i_maxEdges]
	= { {"A","B","C","","","","",""},//Connected to A
		{"A","C","D","","","","",""},//Connected to B
		{"A","B","E","","","","",""},//Connected to C
		{"B","E","F","","","","",""},//Connected to D
		{"C","D","F","","","","",""},//Connected to E
		{"D","E","","","","","",""},//Connected to F
		{"","","","","","","",""},//Connected to G
		{"","","","","","","",""}//Connected to H
		};
// This array stores the data for use on a directed, non weighted graph
bool barr_directionsDirectionsOnly[i_numberOfVertices][i_numberOfVertices][i_numberOfDirections]
= { {{0,1,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to A
	{{0,0,0},{1,0,1},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to B
	{{0,0,0},{1,0,1},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to C
	{{0,0,0},{1,0,1},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to D
	{{0,0,0},{1,0,1},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to E
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to F
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to G
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to H
};
//------------------------------------------------------------------------
//Connected Vertex's, this would be enough to use for a non directed, non weighted graph
string strarr_ConnectedWeightedAndDirected[i_numberOfVertices][i_maxEdges]
	= { {"B","C","D","","","","",""},//Connected to A, This one has a curcular path A->A
		{"C","D","E","F","","","",""},//Connected to B
		{"B","E","","","","","",""},//Connected to C
		{"E","F","","","","","",""},//Connected to D
		{"D","F","","","","","",""},//Connected to E
		{"A","H","","","","","",""},//Connected to F
		{"D","","","","","","",""},//Connected to G
		{"G","","","","","","",""}//Connected to H
		};

// This array stores the data for the weights of the edges
int iarr_weightsWeightedAndDirected[i_numberOfVertices][i_numberOfVertices][i_numberOfDirections]
= { {{6,0,0},{4,0,0},{9,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to A
	{{4,0,5},{2,0,0},{2,0,0},{3,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to B
	{{5,0,4},{6,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to C
	{{4,0,6},{3,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to D
	{{6,0,4},{7,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to E
	{{8,0,0},{3,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to F
	{{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to G
	{{3,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to H
};

// This array stores the data for the directions of the edges
bool barr_directionsWeightedAndDirected[i_numberOfVertices][i_numberOfVertices][i_numberOfDirections]
= { {{1,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to A
	{{1,0,1},{1,0,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to B
	{{1,0,1},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to C
	{{1,0,1},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to D
	{{1,0,1},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to E
	{{1,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to F
	{{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to G
	{{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},//Connected to F
};
//--------------------------------------------------------------------------


#endif
