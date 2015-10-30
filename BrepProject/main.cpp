//************************************
//This project is written to construct a simple brep-based model
//Author: feiqian  Email: feiqian@zju.edu.cn 
//The project is MIT licensed
//************************************
#include <stdio.h>
#include<stdlib.h>
#include "BrepModel.h"
#include "GlutDisplay.h"

int main(int argc, char**argv)
{
	const char* modelPath = "cube.brp";
	BrepModel* brepModel = new BrepModel;
	brepModel->createSolid(modelPath);

	GlutDisplay::setSolid(brepModel->solid);
	GlutDisplay::display(argc,argv);
}