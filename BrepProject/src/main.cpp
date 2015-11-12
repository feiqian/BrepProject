//************************************
//This project is written to construct a simple brep-based model
//Author: feiqian  Email: feiqian@zju.edu.cn 
//´úÂëÍĞ¹ÜµØÖ·£ºhttps://github.com/feiqian/BrepProject
//************************************
#include <stdio.h>
#include<stdlib.h>
#include "BrepModel.h"
#include "GlutDisplay.h"

int main(int argc, char**argv)
{
	const char* modelPath;
	if(argc>=2) modelPath = argv[1];
	else modelPath = "cube.brp";

	BrepModel* brepModel = new BrepModel;
	brepModel->createSolid(modelPath);

	GlutDisplay::setSolid(brepModel->solid);
	GlutDisplay::display(argc,argv);
}