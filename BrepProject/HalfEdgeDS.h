#ifndef _HALF_EDGE_DS
#define _HALF_EDGE_DS

struct Solid;
struct Face;
struct Loop;
struct Edge;
struct Half_Edge;
struct Point;
struct Vertex;

struct Solid
{
	Solid():face(NULL),edge(NULL),next(NULL),prev(NULL){};
	Face* face;
	Edge* edge;
	Solid* next;
	Solid* prev;
};

struct Face
{
	Face():solid(NULL),loop(NULL),next(NULL),prev(NULL){};
	Solid* solid;
	Loop* loop;
	Face* next;
	Face* prev;
};

struct Loop
{
	Loop():face(NULL),he(NULL),prev(NULL),next(NULL){};
	Face* face;
	Half_Edge* he;
	Loop* prev;
	Loop* next;
};

struct Edge
{
	Edge():he1(NULL),he2(NULL),prev(NULL),next(NULL){};
	Half_Edge* he1;
	Half_Edge* he2;
	Edge* prev;
	Edge* next;
};

struct Half_Edge
{
	Half_Edge():ve1(NULL),ve2(NULL),loop(NULL),edge(NULL),next(NULL),prev(NULL){};
	Vertex* ve1;
	Vertex* ve2;
	Loop* loop;
	Edge* edge;
	Half_Edge* next;
	Half_Edge* prev;
	Half_Edge* getAdjacent();
};

struct Point
{
	double coords[3];
	void multiple(double dir[3], double distance);
	int index;//·½±ãµ÷ÊÔ
	static int _index;
	static int indexIncrement();
};

struct Vertex
{
	Vertex():next(NULL),prev(NULL){};
	Point point;
	Vertex* next;
	Vertex* prev;
};

#endif

