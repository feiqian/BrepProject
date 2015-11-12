#include<iostream>
#include<vector>
#include "BrepModel.h"
using namespace std;

Solid* BrepModel::createSolid(const char* path)
{
	FILE *file = fopen(path,"r");
	if(file==NULL) 
	{
		printf("%s","open file error!");
		return NULL;
	}

	int numOfVertex,numOfOperator;
	fscanf(file,"%d",&numOfVertex);
	fscanf(file,"%d\n",&numOfOperator);

	vector<Point> ptList(numOfVertex);
	Point pt;
	for(int i=0;i<numOfVertex;++i)
	{
		fscanf(file,"%lf",&pt.coords[0]);
		fscanf(file,"%lf",&pt.coords[1]);
		fscanf(file,"%lf\n",&pt.coords[2]);
		pt.index = Point::indexIncrement();
		ptList[i] = pt;
	}

	vector<Vertex*> veList(numOfVertex);
	vector<Loop*> loopList;
	int type;
	int index1,index2;
	Loop *loop;

	for(int i=0;i<numOfOperator;++i)
	{
		fscanf(file,"%d",&type);
		printf("now processing %d\n",i);
		switch(type)
		{
			case 0:
			{
				//mvfs
				fscanf(file,"%d",&index1);
				veList[index1] = EulerOperator::mvfs(ptList[index1],solid);
				loop = solid->face->loop;
				loopList.push_back(loop);
				break;
			}
			case 1:
			{
				//mev
				fscanf(file,"%d",&index1);
				fscanf(file,"%d",&index2);
				veList[index2] = EulerOperator::mev(veList[index1],ptList[index2],loop)->ve2;
				break;
			}

			case 2:
			{
				//mef
				fscanf(file,"%d",&index1);
				fscanf(file,"%d",&index2);
				Face* face = EulerOperator::mef(veList[index1],veList[index2],loop);
				loopList.push_back(face->loop);
				break;
			}
			case 3:
			{
				//kemr
				fscanf(file,"%d",&index1);
				fscanf(file,"%d",&index2);
				Loop* newLoop = EulerOperator::kemr(veList[index1],veList[index2],loop);
				loopList.push_back(newLoop);
				break;
			}
			case 4:
			{
				//kfmrh
				fscanf(file,"%d",&index1);
				fscanf(file,"%d",&index2);
				EulerOperator::kfmrh(loopList[index1],loopList[index2]);
				break;
			}
			case 5:
			{
				//select loop
				fscanf(file,"%d",&index1);
				loop = loopList[index1];
				break;
			}
			case 6:
			{
				//sweep
				double dir[3],distance;
				for(int i=0;i<3;++i)
				{
					fscanf(file,"%lf",&dir[i]);
				}
				fscanf(file,"%lf",&distance);
				EulerOperator::sweep(solid->face,dir,distance);
				break;
			}
			default:
			printf("%s","unrecognized operator type!");
			getchar();
		}
	}

	fclose(file);
	return solid;
}