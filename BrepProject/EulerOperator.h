#ifndef _EULER_OPERATOR
#define _EULER_OPERATOR
#include "HalfEdgeDS.h"

class EulerOperator
{
public:
	static Vertex* mvfs(Point point,Solid*& solid);
	static Half_Edge* mev(Vertex* vertex,Point point,Loop* loop);
	static Face* mef(Vertex* ve1,Vertex* ve2,Loop* loop);
	static Loop* kemr(Vertex *ve1, Vertex *ve2, Loop *loop);
	static void kfmrh(Loop* outerLoop,Loop* innerLoop);
	static void sweep(Face *face, double dir[3], double distance);
private:
	static void insertEdge(Solid* solid,Edge* edge);
	static void insertFace(Solid* solid,Face* face);
	static void insertLoop(Face* face,Loop* loop);
	static void insertSolid(Solid*& head,Solid* solid);
	static void delEdge(Solid* solid,Edge* edge);
	static void delFace(Solid* solid,Face* face);
	static Edge* makeEdge(Vertex* ve1,Vertex* ve2);
};
#endif