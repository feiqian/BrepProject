#include<stdio.h>
#include "HalfEdgeDS.h"

Half_Edge* Half_Edge::getAdjacent()
{
	return edge->he1==this?edge->he2:edge->he1;
}

void Point::multiple(double dir[3], double distance)
{
	for(int i=0;i<3;++i)
	{
		coords[i]+=dir[i]*distance;
	}
}

int Point::_index = 0;
int Point::indexIncrement()
{
	return _index++;
}