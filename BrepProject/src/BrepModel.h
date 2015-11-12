#ifndef _BREP_MODEL
#define _BREP_MODEL
#include "EulerOperator.h"

struct BrepModel;
struct BrepModel
{
	BrepModel():solid(NULL){};
	Solid* createSolid(const char* path);
	Solid* solid;
};
#endif

