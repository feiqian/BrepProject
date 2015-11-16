#include<stdio.h>
#include "EulerOperator.h"

void EulerOperator::insertEdge(Solid* solid,Edge* edge)
{
	Edge* head = solid->edge;
	if(head==NULL) solid->edge = edge;
	else
	{
		while(head->next!=NULL) head=head->next;
		edge->prev = head;
		head->next = edge;
	}
}

void EulerOperator::insertFace(Solid* solid,Face* face)
{
	face->solid = solid;
	Face* head = solid->face;
	if(head==NULL) solid->face = face;
	else
	{
		while(head->next!=NULL) head=head->next;
		face->prev = head;
		head->next = face;
	}
}

void EulerOperator::insertLoop(Face* face,Loop* loop)
{
	loop->face = face;
	Loop* head = face->loop;
	if(head==NULL) face->loop = loop;
	else
	{
		while(head->next!=NULL) head=head->next;
		loop->prev = head;
		head->next = loop;
	}
}

void EulerOperator::delEdge(Solid* solid,Edge* edge)
{
	Edge* head = solid->edge;
	while(head!=edge)
	{
		head = head->next;
	}

	if(head->prev==NULL)
	{
		solid->edge = head->next;
		head->next->prev = NULL;
	}
	else if(head->next==NULL)
	{
		head->prev->next = NULL;
		head->prev = NULL;
	}
	else
	{
		head->next->prev = head->prev;
		head->prev->next = head->next;
	}

	delete edge;
}

void EulerOperator::delFace(Solid* solid,Face* face)
{
	Face* head = solid->face;
	while(head!=face)
	{
		head = head->next;
	}

	if(head->prev==NULL)
	{
		solid->face = head->next;
		head->next->prev = NULL;
	}
	else if(head->next==NULL)
	{
		head->prev->next = NULL;
		head->prev = NULL;
	}
	else
	{
		head->next->prev = head->prev;
		head->prev->next = head->next;
	}

	delete face;
}

Edge* EulerOperator::makeEdge(Vertex* ve1,Vertex* ve2)
{
	Edge* edge = new Edge;
	Half_Edge* he1 = new Half_Edge;
	Half_Edge* he2 = new Half_Edge;
	he1->ve1=ve1;
	he1->ve2=ve2;
	he2->ve1=ve2;
	he2->ve2=ve1;
	he1->next = he2;
	he2->prev = he1;
	edge->he1 = he1;
	edge->he2 = he2;
	he1->edge = edge;
	he2->edge = edge;

	return edge;
}

void EulerOperator::insertSolid(Solid*& head,Solid* solid)
{
	if(head==NULL) head = solid;
	else
	{
		Solid* tail = head;
		while(tail->next!=NULL) tail = tail->next;
		tail->next = solid;
		solid->prev = solid;
	}
}

/*
 *����һ���壬�棬�⻷������
 *@param[in] point �¶����λ��
 *@param[out] solid �����ɵ���
 *@return �����ɵĶ���
 */
Vertex* EulerOperator::mvfs(Point point,Solid*& solid)
{
	Solid* solid2 = new Solid;
	Face* face = new Face;
	Loop* loop = new Loop;
	Vertex* vertex = new Vertex;

	vertex->point = point;
	loop->he = NULL;

	insertFace(solid2,face);
	insertLoop(face,loop);
	insertSolid(solid,solid2);

	return vertex;
}

/*
 *����һ��λ��Ϊpoint���µĶ��㣬������vertexָ���¶���ı�
 *@param[in] vertex ����
 *@param[in] point �����ɵĶ���λ��
 *@param[in] loop ��ǰ��
 *@return �����ɵİ��
 */
Half_Edge* EulerOperator::mev(Vertex* vertex,Point point,Loop* loop)
{
	Vertex* vertex2 = new Vertex;
	vertex2->point = point;

	Edge* edge  = makeEdge(vertex,vertex2);
	Half_Edge* he1 = edge->he1;
	Half_Edge* he2 = edge->he2;

	//����߲��뻷��
	he1->loop = loop;
	he2->loop = loop;

	if (loop->he==NULL)
	{
		loop->he = he1;
		he2->next = he1;
		he1->prev = he2;
	} 
	else
	{
		Half_Edge* he = loop->he;
		while(he->next->ve1!=vertex) he = he->next;

		he2->next = he->next;
		he1->prev = he;
		he->next->prev = he2;
		he->next = he1;
	}

	insertEdge(loop->face->solid,edge);

	return he1;
}

/*
 *���춥��ve1��ve2��һ���ߣ�ͬʱ����һ������
 *ע�⵱ǰloop�������Ϊve1->ve2,����loop������Ϊve2->ve1
 *@param[in] ve1 ����1
 *@param[in] ve2 ����2
 *@param[in] loop ��ǰ��
 *@return �����ɵ���
 */
Face* EulerOperator::mef(Vertex* ve1,Vertex* ve2,Loop* loop)
{
	Edge* edge  = makeEdge(ve1,ve2);
	Half_Edge* he1 = edge->he1;
	Half_Edge* he2 = edge->he2;

	//�����»�
	Loop* loop2 = new Loop;
	Half_Edge *tmpHe1,*tmpHe2;
	Half_Edge* he = loop->he;

	while(he->ve1!=ve1) he=he->next;
	tmpHe1 = he;
	while(he->ve1!=ve2) he=he->next;
	tmpHe2 = he;

	tmpHe1->prev->next = he1;
	he1->prev = tmpHe1->prev;
	he2->next = tmpHe1;
	tmpHe1->prev = he2;

	tmpHe2->prev->next = he2;
	he2->prev = tmpHe2->prev;
	he1->next = tmpHe2;
	tmpHe2->prev = he1;

	loop->he = he1;
	he1->loop = loop;
	loop2->he = he2;
	he2->loop = loop2;

	//��������
	Face* face = new Face;
	Solid* solid = loop->face->solid;

	insertEdge(solid,edge);
	insertFace(solid,face);
	insertLoop(face,loop2);

	return face;
}

/*
 *ɾ������ve1->ve2��һ���ߣ�����һ���»�
 *@param[in] ve1 ����1
 *@param[in] ve2 ����2
 *@param[in] loop ��ǰ��
 *@return �����ɵĻ�
 */
Loop* EulerOperator::kemr(Vertex *ve1, Vertex *ve2, Loop *loop)
{
	Half_Edge *he1,*he2;
	Half_Edge *head = loop->he;
	while(head->ve1!=ve1 || head->ve2!=ve2) head = head->next;
	he1 = head;
	he2 = he1->getAdjacent();

	he2->prev->next = he1->next;
	he1->next->prev = he2->prev;

	he1->prev->next = he2->next;
	he2->next->prev = he1->prev;

	//�����»�
	Loop* loop2 = new Loop;
	loop2->he = he2->prev;
	he2->prev->loop = loop2;
	insertLoop(loop->face,loop2);
	loop->he = he1->prev;
	he1->prev->loop = loop;

	delEdge(loop->face->solid,he1->edge);
	return loop2;
}

/*
 *ɾ��innerLoopָ����棬������outerLoopָ������ڻ�
 *@param[in] outerLoop ����ɾ������⻷
 *@param[in] innerLoop Ҫɾ�������ڵ��⻷
 */
void EulerOperator::kfmrh(Loop* outerLoop,Loop* innerLoop)
{
	delFace(innerLoop->face->solid,innerLoop->face);
	insertLoop(outerLoop->face,innerLoop);
}

/*
 *ƽ��ɨ��
 *@param[in] face Ҫƽ�Ƶ���
 *@param[in] dir ƽ�Ʒ���
 *@param[in] distance ƽ�Ʒ����ϵ�λ��
 */
void EulerOperator::sweep(Face *face, double dir[3], double distance)
{
	Loop* outerLoop = NULL;
	for(Loop* loop = face->loop;loop!=NULL;loop=loop->next)
	{
		Loop* loop2 = loop->he->getAdjacent()->loop;
		Half_Edge* head = loop2->he;
		Half_Edge* he = head;
		Half_Edge* next = head->next;
		Vertex* end;
		Vertex *ve1=NULL,*ve2=NULL;

		do
		{
			Vertex *ve = he->ve1;
			Point pt1 = ve->point;
			pt1.multiple(dir,distance);
			pt1.index = Point::indexIncrement();

			if(ve1==NULL) 
			{
				ve1 = mev(ve,pt1,loop2)->ve2;
				end = ve1;
			}
			else ve2 = mev(ve,pt1,loop2)->ve2;

			if(ve1&&ve2)
			{
				mef(ve1,ve2,loop2);
				ve1 = ve2;
				ve2 = NULL;
			}
			he = next;
			next = next->next;
		}while(he->ve1!=head->ve1);

		mef(ve1,end,loop2);
		if(outerLoop!=NULL) kfmrh(outerLoop,loop2);
		else outerLoop = loop2;
	}
}