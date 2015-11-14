/*
 * DKGraphClasses.h
 *
 *  Created on: 14 Nov 2015
 *      Author: dell
 */

#ifndef HDR_DKGRAPHCLASSES_H_
#define HDR_DKGRAPHCLASSES_H_

#include<iostream>
#include <deque>
#include <queue>
#include <iostream>
#include <map>
#include <fstream>
#include <istream>
#include <queue>
#include <stack>

using namespace std;

#define GRAPH_TYPE_NOT_SET "Not Set"
#define GRAPH_TYPE_STANDARD "Standard"
#define GRAPH_TYPE_WEIGHTED_ONLY "Weighted"
#define GRAPH_TYPE_DIRECTED_ONLY "Directed"
#define GRAPH_TYPE_BOTH "Directed and Weighted"

void v_Lab8();


class cls_Vertex;

//******************************************************************************
//
//******************************************************************************
class cls_Edge
{
private:

	cls_Vertex* pobj_VertexDestination;

	//These Directions determine if the graph is directed edge, if all false then it's not a directed edge
	bool b_DirectionForward;
	bool b_DirectionCircular;
	bool b_DirectionBack;

	//These next three int's determine if this is a weighted graph, if all 0 then it's not a weighted edge
	int i_WeightForward;
	int i_WeightCircular;
	int i_WeightBack;

	//Use when the graph is weighted but not directed
	int i_Weight;

public:
	cls_Edge(void);
	~cls_Edge(void);

	void v_SetVertexDestination(cls_Vertex* pobj_val){if(pobj_val) pobj_VertexDestination = pobj_val;};
	cls_Vertex* pobj_GetVertexDestination(){return pobj_VertexDestination;};

	//Direction gets and set
	void v_SetDirectionForward(bool b_val){b_DirectionForward = b_val;};
	bool b_GetDirectionForward()const {return b_DirectionForward;};

	//Direction gets and set
	void v_SetDirectionBack(bool b_val){b_DirectionBack = b_val;};
	bool b_GetDirectionBack()const {return b_DirectionBack;};

	//Direction gets and set
	void v_SetDirectionCircular(bool b_val){b_DirectionCircular = b_val;};
	bool b_GetDirectionCircular()const {return b_DirectionCircular;};

	//Weight for each direction
	void v_SetWeightForward(int i_val){i_WeightForward = i_val;};
	int i_GetWeightForward()const {return i_WeightForward;};

	//Weight for each direction
	void v_SetWeightBack(int i_val){i_WeightBack = i_val;};
	int i_GetWeightBack()const {return i_WeightBack;};

	//Weight for each direction
	void v_SetWeightCircular(int i_val){i_WeightCircular = i_val;};
	int i_GetWeightCircular()const {return i_WeightCircular;};

	//Weight for each direction
	void v_SetWeight(int i_val){i_Weight = i_val;};
	int i_GetWeight()const {return i_Weight;};
	friend class cls_Vertex;
};
//************************************************************************
//This is the function that is used for the compare in the priority queue
//************************************************************************
struct DereferenceCompareEdge: public std::binary_function<cls_Edge*, cls_Edge*, bool>
{
    bool operator()(const cls_Edge* lhs, const cls_Edge* rhs) const
    {
		bool b_ret = lhs->i_GetWeightForward() > rhs->i_GetWeightForward();
        return b_ret;
    }
};
//******************************************************************************
//
//******************************************************************************
class cls_Vertex
{
private:
	bool b_BreathFirstVisited;
	bool b_DepthFirstVisited;

	string str_VertexData;
	deque<cls_Edge*> obj_EdgeDeque;

	//Define the priority queue
	priority_queue<cls_Edge*,vector<cls_Edge*>, DereferenceCompareEdge> obj_priorityQue;
public:

	cls_Vertex(void);
	cls_Vertex(string str_val);
	~cls_Vertex(void);

	void v_BuildASortedDeque();

	string str_GetVertexData()const {return str_VertexData.c_str();};
	void v_SetVertexData(string str_val){str_VertexData = str_val;};

	int i_GetEdgeCount()const {return obj_EdgeDeque.size();};
	bool b_AddEdge(cls_Edge* pobj_val);
	cls_Edge* pobj_GetEdgeAt(int i_index);

	bool b_AddEdgeToThePriorityQueue(cls_Edge* pobj_val);

	bool b_DeleteTheDequeObjects();

	bool b_GetBreathFirstVisited()const {return b_BreathFirstVisited;};
	void v_SetBreathFirstVisited(bool b_val){b_BreathFirstVisited = b_val;};

	bool b_GetDepthFirstVisited()const {return b_DepthFirstVisited;};
	void v_SetDepthFirstVisited(bool b_val){b_DepthFirstVisited = b_val;};

};

//******************************************************************************
//
//******************************************************************************
class cls_Graph
{
private:
	deque<cls_Vertex*> obj_VertexDeque;
	string str_GraphType;

public:

	queue<cls_Vertex*> obj_BreathFirstVisited;
	deque<cls_Vertex*> obj_DepthFirstVisited;

	string str_BreathFirstResult;
	string str_DepthFirstResult;

	cls_Graph(void):str_GraphType(GRAPH_TYPE_NOT_SET){};
	cls_Graph(string str_type):str_GraphType(str_type){};
	~cls_Graph(void){b_DeleteTheDequeObjects();};

	bool b_AddVertex(cls_Vertex* pobj_val);
	cls_Vertex* pobj_GetVertex(string str_val)const;

	int i_DisplayVertexValues(void);

	const int i_GetVertexCount() const;
	cls_Vertex* pobj_GetVertexAt(int i_index) const;
	bool b_DeleteVertex(string str_vertex);
	bool b_DeleteVertex(cls_Vertex *pobj_vertex);


	bool b_DisplayConnectedVertices(cls_Vertex *pobj_buf)const;
	bool b_DisplayConnectedVertices(string str_val)const;
	bool b_DisplayConnectedVerticesAt(int i_index)const;

	bool b_DeleteTheDequeObjects();

	string str_GetGraphType(){return str_GraphType.c_str();};
	void v_SetGraphType(string str_val){str_GraphType = str_val;};

	bool b_BreathFirstSearchAtoB(string str_sourceVal,string str_destinationVal);
	cls_Vertex *pobj_BreathFirstSearch(cls_Vertex *pobj_sourceVertex, cls_Vertex *pobj_destinationVertex);
	cls_Vertex *pobj_BreathFirstSearch(string str_sourceVal,string str_destinationVal);

	bool b_DepthFirstSearchAtoB(string str_sourceVal,string str_destinationVal);
	cls_Vertex *pobj_DepthFirstSearch(cls_Vertex *pobj_sourceVertex);
	cls_Vertex *pobj_DepthFirstSearch(string str_sourceVal);


	bool b_BreathFirstVisitAllVerticesFrom(cls_Vertex *pobj_vertex);
	bool b_BreathFirstVisitAllVerticesFrom(string str_val);

	bool b_DepthFirstVisitAllVerticesFrom(cls_Vertex *pobj_vertex);
	bool b_DepthFirstVisitAllVerticesFrom(string str_val);

	void v_ResetTheVisitedFlags(bool b_resetBreathFirst=true,bool b_resetDepthFirst=true);

};
//******************************************************************************
//
//******************************************************************************
class cls_ShortestPathDataBlob
{
private:
	int i_TempWeight;
	int i_Weight;
	int i_Order;
public:
	cls_ShortestPathDataBlob(void):i_TempWeight(0),i_Weight(0),i_Order(0){};
	~cls_ShortestPathDataBlob(void);

	int i_GetTempWeight()const {return i_TempWeight;};
	void v_SetTempWeight(int i_val){i_TempWeight = i_val;};

	int i_GetWeight()const {return i_Weight;};
	void v_SetWeight(int i_val){i_Weight = i_val;};

	int i_GetOrder()const {return i_Order;};
	void v_SetOrder(int i_val){i_Order = i_val;};

};





#endif /* HDR_DKGRAPHCLASSES_H_ */
