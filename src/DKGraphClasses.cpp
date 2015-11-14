/*
 * DKGraphClasses.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: dell
 */
#include "../hdr/DKGraphClasses.h"
#include "../hdr/DKGraphData.h"

using namespace std;
//**********************************************************************
//
//**********************************************************************
cls_Edge::cls_Edge(void)
	://pobj_VertexSource(NULL),
	pobj_VertexDestination(NULL),
	b_DirectionForward(false),
	b_DirectionCircular(false),
	b_DirectionBack(false),
	i_WeightForward(0),
	i_WeightCircular(0),
	i_WeightBack(0),
	i_Weight(0)
{
	//Nothing to do here
}

cls_Edge::~cls_Edge(void)
{
	//Nothing to do here
}

//**********************************************************************
//
//**********************************************************************
cls_Vertex::cls_Vertex(void):b_BreathFirstVisited(false),b_DepthFirstVisited(false)
{
	return;
}
//**********************************************************************
//
//**********************************************************************
cls_Vertex::cls_Vertex(string str_val):b_BreathFirstVisited(false),b_DepthFirstVisited(false)
{
	str_VertexData = str_val;

	return;
}
//**********************************************************************
//
//**********************************************************************
cls_Vertex::~cls_Vertex(void)
{
	b_DeleteTheDequeObjects();
	return;
}
//**********************************************************************
//
//**********************************************************************
bool cls_Vertex::b_AddEdge(cls_Edge* pobj_val)
{
	bool b_ret = false;
	if(pobj_val)
	{
		obj_EdgeDeque.push_back(pobj_val);
		b_ret = true;
	}
	return b_ret;
}
//************************************************************************
// Loop through all the allocated abjects and delete them
//************************************************************************
bool cls_Vertex::b_DeleteTheDequeObjects()
{
	cls_Edge *pobj_buf = NULL;

	int i_dequeSize = obj_EdgeDeque.size();
	if(i_dequeSize > 0)
	{
		for(int i_dequeCounter = i_dequeSize-1; i_dequeCounter >= 0; i_dequeCounter--)
		{
			pobj_buf = obj_EdgeDeque.at(i_dequeCounter);
			if(pobj_buf)
			{
				delete pobj_buf;
				pobj_buf = NULL;
			}
		}
		return true;
	}
	return false;
}
//**********************************************************************
//
//**********************************************************************
bool cls_Graph::b_AddVertex(cls_Vertex* pobj_val)
{
	bool b_ret = false;
	if(pobj_val)
	{
		obj_VertexDeque.push_back(pobj_val);
		b_ret = true;
	}
	return b_ret;
}

//**********************************************************************
//
//**********************************************************************
int cls_Graph::i_DisplayVertexValues(void)
{
	int i_displayedCount = 0;
	int i_dequeSize = obj_VertexDeque.size();

	if(i_dequeSize > 0)
	{
		cls_Vertex* pobj_buf = NULL;

		for(int i_dequeCounter = 0; i_dequeCounter < i_dequeSize; i_dequeCounter++)
		{
			pobj_buf = obj_VertexDeque.at(i_dequeCounter);

			if (pobj_buf)
			{
				cout << "Vertext Value = " << pobj_buf->str_GetVertexData().c_str() << "\n";
				i_displayedCount++;
			}
			pobj_buf = NULL;
		}
	}
	return i_displayedCount;
}

//**********************************************************************
//
//**********************************************************************
cls_Vertex* cls_Graph::pobj_GetVertex(string str_val)const
{
	int i_dequeSize = obj_VertexDeque.size();

	if(i_dequeSize > 0)
	{
		cls_Vertex* pobj_buf = NULL;

		for(int i_dequeCounter = 0; i_dequeCounter < i_dequeSize; i_dequeCounter++)
		{
			pobj_buf = obj_VertexDeque.at(i_dequeCounter);

			if (pobj_buf)
			{
				if(pobj_buf->str_GetVertexData().compare(str_val) == 0) return pobj_buf;

			}
			pobj_buf = NULL;
		}
	}
	return NULL;
}
//**********************************************************************
// Return the edge at the index
//**********************************************************************
cls_Edge* cls_Vertex::pobj_GetEdgeAt(int i_index)
{
	int i_size = obj_EdgeDeque.size();
	if(i_size <= i_index) return NULL;

	return obj_EdgeDeque.at(i_index);
}
//**********************************************************************
// This function will take the edges from the priority queue and
// add them to the deque in sorted order, sorted by forward weight
//**********************************************************************
void cls_Vertex::v_BuildASortedDeque()
{
	if(obj_priorityQue.size() > 0)
	{
		while(obj_priorityQue.size() >= 1)
		{
			cls_Edge *pobj_edge = obj_priorityQue.top();
			if(pobj_edge)//Make sure the pointer is valid
			{
				obj_priorityQue.pop();//Only pop one off if the edge pointer is valid
				b_AddEdge(pobj_edge);//Add the edge onto the queue
			}
		}
	}
}
//**********************************************************************
//
//**********************************************************************
cls_Vertex* cls_Graph::pobj_GetVertexAt(int i_index) const
{
	int i_count = i_GetVertexCount();
	if(i_index <= i_count)
	{
		return obj_VertexDeque.at(i_index);
	}
	return NULL;
}
//**********************************************************************
//
//**********************************************************************
bool cls_Vertex::b_AddEdgeToThePriorityQueue(cls_Edge* pobj_val)
{
	if(pobj_val)
	{
		obj_priorityQue.push(pobj_val);//Add them to a priority queue which will sort them
		return true;
	}
	return false;
}
//**********************************************************************
//
//**********************************************************************
const int cls_Graph::i_GetVertexCount()const
{
	return obj_VertexDeque.size();
}
//**********************************************************************
//
//**********************************************************************
bool cls_Graph::b_DisplayConnectedVerticesAt(int i_index)const
{
	if(i_GetVertexCount() <= i_index)
	{
		return b_DisplayConnectedVertices(pobj_GetVertexAt(i_index));
	}
	return false;
}
//**********************************************************************
//
// Do a depth first search starting at source and finishing at
// destination, str_sourceVal = "A", str_destinationVal = "F"
//
//**********************************************************************
bool cls_Graph::b_DepthFirstSearchAtoB(string str_sourceVal,string str_destinationVal)
{
	cls_Vertex * pobj_sourceVertext = pobj_GetVertex(str_sourceVal);
	cls_Vertex * pobj_destinationVertext = pobj_GetVertex(str_destinationVal);

	if(!pobj_sourceVertext || !pobj_destinationVertext) return false;

	str_DepthFirstResult = "";

	pobj_sourceVertext->v_SetDepthFirstVisited(true);
	obj_DepthFirstVisited.push_front(pobj_sourceVertext);

	str_DepthFirstResult = pobj_sourceVertext->str_GetVertexData().c_str();

	cls_Vertex * pobj_workingVertext = pobj_sourceVertext;
	bool b_keepSearching = true;
	while(b_keepSearching)
	{
		pobj_workingVertext = pobj_DepthFirstSearch(pobj_workingVertext);


		if(pobj_workingVertext)
		{
			str_DepthFirstResult += pobj_workingVertext->str_GetVertexData().c_str();
			obj_DepthFirstVisited.push_front(pobj_workingVertext);
			pobj_workingVertext->v_SetDepthFirstVisited(true);

			if(pobj_workingVertext->str_GetVertexData().compare(pobj_destinationVertext->str_GetVertexData()) == 0)
				b_keepSearching = false;
		}else{
			obj_BreathFirstVisited.pop();
			if(obj_BreathFirstVisited.size() > 0)
				pobj_workingVertext = obj_BreathFirstVisited.front();
		}
	}

	return true;
}

//**********************************************************************
//
//**********************************************************************
cls_Vertex* cls_Graph::pobj_DepthFirstSearch(string str_sourceVal)
{
	return pobj_DepthFirstSearch(pobj_GetVertex(str_sourceVal));
}
//**********************************************************************
//
//**********************************************************************
cls_Vertex* cls_Graph::pobj_DepthFirstSearch(cls_Vertex *pobj_sourceVertex)
{
	if(str_GraphType.compare(GRAPH_TYPE_NOT_SET) == 0) return NULL;

	if(!pobj_sourceVertex) return NULL;

	int i_edgeCount = pobj_sourceVertex->i_GetEdgeCount();

	if(i_edgeCount > 0)
	{
		for(int i_dequeCounter = 0; i_dequeCounter < i_edgeCount; i_dequeCounter++)
		{
			cls_Edge* pobj_edge = pobj_sourceVertex->pobj_GetEdgeAt(i_dequeCounter);

			if (pobj_edge)
			{
				if(!pobj_edge->pobj_GetVertexDestination()->b_GetDepthFirstVisited())
				{
					return pobj_edge->pobj_GetVertexDestination();
				}
			}
		}
	}
	return NULL;
}
//**********************************************************************
//
//**********************************************************************
bool cls_Graph::b_DepthFirstVisitAllVerticesFrom(string str_val)
{
	return b_DepthFirstVisitAllVerticesFrom(pobj_GetVertex(str_val));
}
//**********************************************************************
//
//**********************************************************************
bool cls_Graph::b_DepthFirstVisitAllVerticesFrom(cls_Vertex *pobj_vertex)
{
	if(str_GraphType.compare(GRAPH_TYPE_NOT_SET) == 0) return false;

	if(!pobj_vertex) return false;

	int i_edgeCount = pobj_vertex->i_GetEdgeCount();

	if(i_edgeCount > 0)
	{
		for(int i_dequeCounter = 0; i_dequeCounter < i_edgeCount; i_dequeCounter++)
		{
			cls_Edge* pobj_edge = pobj_vertex->pobj_GetEdgeAt(i_dequeCounter);

			if (pobj_edge)
			{
				if(!pobj_edge->pobj_GetVertexDestination()->b_GetDepthFirstVisited())
				{
					str_DepthFirstResult += pobj_edge->pobj_GetVertexDestination()->str_GetVertexData().c_str();
					obj_DepthFirstVisited.push_front(pobj_edge->pobj_GetVertexDestination());
					pobj_edge->pobj_GetVertexDestination()->v_SetDepthFirstVisited(true);
					return true;
				}
			}
		}
	}
	return false;
}

//**********************************************************************
//
// Do a breath first search starting at source and finishing at
// destination, str_sourceVal = "A", str_destinationVal = "F"
//
//**********************************************************************
bool cls_Graph::b_BreathFirstSearchAtoB(string str_sourceVal,string str_destinationVal)
{
	cls_Vertex * pobj_sourceVertext = pobj_GetVertex(str_sourceVal);
	cls_Vertex * pobj_destinationVertext = pobj_GetVertex(str_destinationVal);

	if(!pobj_sourceVertext || !pobj_destinationVertext) return false;

	bool b_keepSearching = true;

	pobj_sourceVertext->v_SetBreathFirstVisited(true);
	obj_BreathFirstVisited.push(pobj_sourceVertext);

	str_BreathFirstResult = pobj_sourceVertext->str_GetVertexData().c_str();

	cls_Vertex * pobj_workingVertext = pobj_sourceVertext;
	while(b_keepSearching)
	{
		cls_Vertex *pobj_result = pobj_BreathFirstSearch(pobj_workingVertext,pobj_destinationVertext);

		if(pobj_result)
			if(pobj_result->str_GetVertexData().compare(pobj_destinationVertext->str_GetVertexData()) == 0)
				b_keepSearching = false;

		obj_BreathFirstVisited.pop();
		if(obj_BreathFirstVisited.size() > 0)
			pobj_workingVertext = obj_BreathFirstVisited.front();

	}
	return true;
}


//**********************************************************************
//
//**********************************************************************
cls_Vertex * cls_Graph::pobj_BreathFirstSearch(string str_sourceVal,string str_destinationVal)
{
	return pobj_BreathFirstSearch(pobj_GetVertex(str_sourceVal), pobj_GetVertex(str_destinationVal));
}
//**********************************************************************
//
//**********************************************************************
cls_Vertex * cls_Graph::pobj_BreathFirstSearch(cls_Vertex *pobj_sourceVertex,cls_Vertex *pobj_destinationVertex)
{
	if(str_GraphType.compare(GRAPH_TYPE_NOT_SET) == 0) return NULL;

	if(!pobj_sourceVertex || !pobj_destinationVertex) return NULL;

	int i_edgeCount = pobj_sourceVertex->i_GetEdgeCount();

	if(i_edgeCount > 0)
	{
		for(int i_dequeCounter = 0; i_dequeCounter < i_edgeCount; i_dequeCounter++)
		{
			cls_Edge* pobj_edge = pobj_sourceVertex->pobj_GetEdgeAt(i_dequeCounter);

			if (pobj_edge)
			{
				if(!pobj_edge->pobj_GetVertexDestination()->b_GetBreathFirstVisited())
				{
					str_BreathFirstResult += pobj_edge->pobj_GetVertexDestination()->str_GetVertexData().c_str();
					obj_BreathFirstVisited.push(pobj_edge->pobj_GetVertexDestination());
					pobj_edge->pobj_GetVertexDestination()->v_SetBreathFirstVisited(true);

					string str_curval = pobj_edge->pobj_GetVertexDestination()->str_GetVertexData();
					string str_dest = pobj_destinationVertex->str_GetVertexData();

					if(str_curval.compare(str_dest) == 0)//Match found
						return pobj_edge->pobj_GetVertexDestination();
				}
			}
		}
	}

	return NULL;
}
//**********************************************************************
//
//**********************************************************************
bool cls_Graph::b_BreathFirstVisitAllVerticesFrom(string str_val)
{
	return b_BreathFirstVisitAllVerticesFrom(pobj_GetVertex(str_val));
}
//**********************************************************************
//
//**********************************************************************
bool cls_Graph::b_BreathFirstVisitAllVerticesFrom(cls_Vertex *pobj_vertex)
{
	if(str_GraphType.compare(GRAPH_TYPE_NOT_SET) == 0) return false;

	if(!pobj_vertex) return false;

	int i_edgeCount = pobj_vertex->i_GetEdgeCount();

	if(i_edgeCount > 0)
	{
		for(int i_dequeCounter = 0; i_dequeCounter < i_edgeCount; i_dequeCounter++)
		{
			cls_Edge* pobj_edge = pobj_vertex->pobj_GetEdgeAt(i_dequeCounter);

			if (pobj_edge)
			{
				if(!pobj_edge->pobj_GetVertexDestination()->b_GetBreathFirstVisited())
				{
					str_BreathFirstResult += pobj_edge->pobj_GetVertexDestination()->str_GetVertexData().c_str();
					obj_BreathFirstVisited.push(pobj_edge->pobj_GetVertexDestination());
					pobj_edge->pobj_GetVertexDestination()->v_SetBreathFirstVisited(true);
				}
			}
		}
	}

	return true;
}

//**********************************************************************
//
//**********************************************************************
bool cls_Graph::b_DisplayConnectedVertices(string str_val)const
{
	return b_DisplayConnectedVertices(pobj_GetVertex(str_val));
}
//**********************************************************************
//
//**********************************************************************
bool cls_Graph::b_DisplayConnectedVertices(cls_Vertex *pobj_vertex)const
{
	if(str_GraphType.compare(GRAPH_TYPE_NOT_SET) == 0) return false;

	if(pobj_vertex)
	{
		int i_edgeCount = pobj_vertex->i_GetEdgeCount();

		if(i_edgeCount > 0)
		{
			for(int i_dequeCounter = 0; i_dequeCounter < i_edgeCount; i_dequeCounter++)
			{
				cls_Edge* pobj_edge = pobj_vertex->pobj_GetEdgeAt(i_dequeCounter);

				if (pobj_edge)
				{
					cout << pobj_vertex->str_GetVertexData().c_str();

					if(str_GraphType.compare(GRAPH_TYPE_STANDARD) != 0)
					{
						if(str_GraphType.compare(GRAPH_TYPE_WEIGHTED_ONLY) == 0)
						{//This is a weighted only graph
							cout << " -" << pobj_edge->i_GetWeightForward() << "- ";

						}else if(str_GraphType.compare(GRAPH_TYPE_BOTH) == 0)
						{//Directed and weighted
							if(pobj_edge->b_GetDirectionBack())
								cout << " " << pobj_edge->i_GetWeightBack() << " <-";
							else
								cout << " " << pobj_edge->i_GetWeightBack() << "  -";

							if(pobj_edge->b_GetDirectionCircular())
								cout << "->" << pobj_edge->i_GetWeightCircular() << "<-";
							else
								cout << "- " << pobj_edge->i_GetWeightCircular() << " -";

							if(pobj_edge->b_GetDirectionForward())
								cout << "-> " << pobj_edge->i_GetWeightForward() << " ";
							else
								cout << "-  " << pobj_edge->i_GetWeightForward() << " ";

						}else if(str_GraphType.compare(GRAPH_TYPE_DIRECTED_ONLY) == 0)
						{//Directed only
							if(pobj_edge->b_GetDirectionBack())
								cout << " <-";
							else
								cout << " --";

							if(pobj_edge->b_GetDirectionCircular())
								cout << "><";
							else
								cout << "--";

							if(pobj_edge->b_GetDirectionForward())
								cout << "-> ";
							else
								cout << "-- ";
						}
					}
					else//Thie just a plain graph, no weights or directions
						cout << " is connected to ";

					cout << pobj_edge->pobj_GetVertexDestination()->str_GetVertexData().c_str() << "\n";
				}

				pobj_edge = NULL;
			}
		}else//The current vertex is not connected to any other vertex
			cout << pobj_vertex->str_GetVertexData().c_str() << " has no outward connected edges\n";

	}
	return true;
}
//************************************************************************
// Loop through all the allocated abjects and delete them
//************************************************************************
bool cls_Graph::b_DeleteTheDequeObjects()
{
	cls_Vertex *pobj_buf = NULL;

	int i_dequeSize = obj_VertexDeque.size();
	if(i_dequeSize > 0)
	{
		for(int i_dequeCounter = i_dequeSize-1; i_dequeCounter >= 0; i_dequeCounter--)
		{
			pobj_buf = obj_VertexDeque.at(i_dequeCounter);
			if(pobj_buf)
			{
				delete pobj_buf;
				pobj_buf = NULL;
			}
		}
		return true;
	}
	return false;
}

//************************************************************************
//
//************************************************************************
bool cls_Graph::b_DeleteVertex(string str_vertex)
{
	return b_DeleteVertex(pobj_GetVertex(str_vertex));
}
//************************************************************************
//
//************************************************************************
bool cls_Graph::b_DeleteVertex(cls_Vertex *pobj_vertex)
{
	if(!pobj_vertex) return false;

	obj_VertexDeque.at(1) = NULL;
	return true;
}

//************************************************************************
//Loop trough all the vertices and reset the visited flag
//************************************************************************
void cls_Graph::v_ResetTheVisitedFlags(bool b_resetBreathFirst, bool b_resetDepthFirst)
{
	for(int i_counter = 0; i_counter < i_GetVertexCount();i_counter++)
	{
		if(b_resetBreathFirst) pobj_GetVertexAt(i_counter)->v_SetBreathFirstVisited(false);
		if(b_resetDepthFirst) pobj_GetVertexAt(i_counter)->v_SetDepthFirstVisited(false);
	}
}
//**********************************************************************
// The data used to create the graph is declared on GraphDataGlobals
//**********************************************************************
void v_Lab8()
{

	cls_Graph obj_graph(GRAPH_TYPE_BOTH);//The main graph object

	string (*ptrstrarr_connected)[i_numberOfVertices];
	bool (*ptrbarr_directions)[i_numberOfVertices][i_numberOfDirections];
	int (*ptriarr_weights)[i_numberOfVertices][i_numberOfDirections];

	if(obj_graph.str_GetGraphType().compare(GRAPH_TYPE_WEIGHTED_ONLY) == 0)
	{
		ptrstrarr_connected = strarr_ConnectedWeightedOnly;
		ptriarr_weights = iarr_weightsWeightedOnly;

	}else if(obj_graph.str_GetGraphType().compare(GRAPH_TYPE_BOTH) == 0)
	{
		ptrstrarr_connected = strarr_ConnectedWeightedAndDirected;
		ptrbarr_directions = barr_directionsWeightedAndDirected;
		ptriarr_weights = iarr_weightsWeightedAndDirected;

	}else if(obj_graph.str_GetGraphType().compare(GRAPH_TYPE_DIRECTED_ONLY) == 0)
	{
		ptrstrarr_connected = strarr_ConnectedDirectionsOnly;
		ptrbarr_directions = barr_directionsDirectionsOnly;


	}else if(obj_graph.str_GetGraphType().compare(GRAPH_TYPE_STANDARD) == 0)
	{
		ptrstrarr_connected = strarr_ConnectedStandard;
	}

	cls_Vertex* pobj_vertex = NULL;
	//Add all the Vertices to the graph
	for(int i_count = 0; i_count < i_numberOfVertices; i_count++)
	{
		pobj_vertex = new cls_Vertex(strarr_vertexValues[i_count]);
		if(pobj_vertex)
		{
			//Add the unconnected vertex's to the graph
			obj_graph.b_AddVertex(pobj_vertex);
		}
	}

	//Connect the vertices to make the graph ie A->B, A->C, B->A, B->C, B->D etc.etc.
	for(int i_count = 0; i_count < i_numberOfVertices; i_count++)
	{
		//Loop through the vertices one at a time and build the connections
		cls_Vertex* pobj_source = obj_graph.pobj_GetVertex(strarr_vertexValues[i_count]);
		if(pobj_source)
		{
			int i_edgeCount = 0;
			string str_vertextValue = ptrstrarr_connected[i_count][i_edgeCount];
			while(str_vertextValue.length() > 0)
			{
				cls_Edge* pobj_edge = new cls_Edge;

				//Set the destination vertex
				cls_Vertex* pobj_dest = obj_graph.pobj_GetVertex(ptrstrarr_connected[i_count][i_edgeCount]);
				pobj_edge->v_SetVertexDestination(pobj_dest);

				if(obj_graph.str_GetGraphType().compare(GRAPH_TYPE_STANDARD) != 0)
				{
					if(obj_graph.str_GetGraphType().compare(GRAPH_TYPE_WEIGHTED_ONLY) == 0)
					{
						pobj_edge->v_SetWeightForward(ptriarr_weights[i_count][i_edgeCount][0]);

					}else if(obj_graph.str_GetGraphType().compare(GRAPH_TYPE_DIRECTED_ONLY) == 0)
					{
						pobj_edge->v_SetDirectionForward(ptrbarr_directions[i_count][i_edgeCount][0]);
						pobj_edge->v_SetDirectionCircular(ptrbarr_directions[i_count][i_edgeCount][1]);
						pobj_edge->v_SetDirectionBack(ptrbarr_directions[i_count][i_edgeCount][2]);

					}else if(obj_graph.str_GetGraphType().compare(GRAPH_TYPE_BOTH) == 0)
					{
						//Add what ever weights are in the array
						pobj_edge->v_SetWeightForward(ptriarr_weights[i_count][i_edgeCount][0]);
						pobj_edge->v_SetWeightCircular(ptriarr_weights[i_count][i_edgeCount][1]);
						pobj_edge->v_SetWeightBack(ptriarr_weights[i_count][i_edgeCount][2]);

						//Add what ever directions are in the array
						pobj_edge->v_SetDirectionForward(ptrbarr_directions[i_count][i_edgeCount][0]);
						pobj_edge->v_SetDirectionCircular(ptrbarr_directions[i_count][i_edgeCount][1]);
						pobj_edge->v_SetDirectionBack(ptrbarr_directions[i_count][i_edgeCount][2]);
					}
				}
				pobj_source->b_AddEdgeToThePriorityQueue(pobj_edge);//Add them to a priority queue which will sort them
				i_edgeCount++;
				str_vertextValue = ptrstrarr_connected[i_count][i_edgeCount];
			}
		}
		pobj_source->v_BuildASortedDeque();//Take the edges from the priority queue and move them into the deque

	}

	obj_graph.i_DisplayVertexValues();

	//obj_graph.b_DeleteVertex("B");

	cout << "\n\n";

	cout << "Graph type : " << obj_graph.str_GetGraphType().c_str() << "\n\n";

	//Loop trough all the vertices and display the connected edges
	for(int i_counter = 0; i_counter < obj_graph.i_GetVertexCount();i_counter++)
	{
		obj_graph.b_DisplayConnectedVertices(obj_graph.pobj_GetVertexAt(i_counter));
		cout << "\n";
	}

	string str_sourceVertex("A");
	string str_destinationVertex("G");

// Do a breath first search from one vertex to another vertex
	if(obj_graph.b_BreathFirstSearchAtoB(str_sourceVertex,str_destinationVertex))
		cout << "Breath first from : " << str_sourceVertex.c_str() << " to " << str_destinationVertex.c_str() << " --> " << obj_graph.str_BreathFirstResult.c_str() << "\n\n";
	else
		cout << "Breath first result : FAILED\n\n";

// Do a depth first search from one vertex to another vertex

	if(obj_graph.b_DepthFirstSearchAtoB(str_sourceVertex,str_destinationVertex))
		cout << "Depth first from : " << str_sourceVertex.c_str() << " to " << str_destinationVertex.c_str() << " --> " << obj_graph.str_DepthFirstResult.c_str() << "\n\n";
	else
		cout << "Depth first result : FAILED\n\n";

	obj_graph.v_ResetTheVisitedFlags();

//---------------------------------------------------------------------------
// Do a breath first traversal of all vertices

	cls_Vertex * pobj_vertext = obj_graph.pobj_GetVertex(str_sourceVertex);
	bool b_keepSearching = true;

	pobj_vertext->v_SetBreathFirstVisited(true);
	obj_graph.obj_BreathFirstVisited.push(pobj_vertext);

	obj_graph.str_BreathFirstResult = pobj_vertext->str_GetVertexData().c_str();

	while(b_keepSearching)
	{
		obj_graph.b_BreathFirstVisitAllVerticesFrom(pobj_vertext);
		obj_graph.obj_BreathFirstVisited.pop();
		if(obj_graph.obj_BreathFirstVisited.size() > 0)
			pobj_vertext = obj_graph.obj_BreathFirstVisited.front();
		else
			b_keepSearching = false;

	}

	cout << "Breath first traverse all starting at : " << str_sourceVertex.c_str() << " --> " << obj_graph.str_BreathFirstResult.c_str() << "\n\n";

//---------------------------------------------------------------------------
// Do a depth first traversal of all vertices
	obj_graph.str_DepthFirstResult = "";

	pobj_vertext = obj_graph.pobj_GetVertex(str_sourceVertex);
	pobj_vertext->v_SetDepthFirstVisited(true);
	obj_graph.obj_DepthFirstVisited.push_front(pobj_vertext);

	obj_graph.str_DepthFirstResult = pobj_vertext->str_GetVertexData().c_str();

	b_keepSearching = true;
	while(b_keepSearching)
	{
		if(!obj_graph.b_DepthFirstVisitAllVerticesFrom(pobj_vertext)) obj_graph.obj_DepthFirstVisited.pop_front();
		if(obj_graph.obj_DepthFirstVisited.size() > 0)
		{
			pobj_vertext = obj_graph.obj_DepthFirstVisited.front();
		}
		else
			b_keepSearching = false;
	}

	cout << "Depth first traverse all starting at : " << str_sourceVertex.c_str() << " --> " << obj_graph.str_DepthFirstResult.c_str() << "\n\n";

	obj_graph.v_ResetTheVisitedFlags();

//---------------------------------------------------------------------------

	return;
}




