#include "Loop.h"

Loop::Loop()
{
	//pre-calculating coeffs for different sizes of vert neighbors to remove
	//cos calculation etc in the construction loop
	for (size_t i = 1; i < 10; i++)
	{
		//warren, for valence = 3
		if (i == 3)
			coeffs[i] = 3.0f / 16.0f;
		else
		{
			coeffs[i] = (3.0f / 8.0f) + (cosf(PI_2_FLOAT / (float)i) / 4.0f);
			coeffs[i] *= coeffs[i];
			coeffs[i] = (1.0f / (float)i) * ((5.0f / 8.0f) - coeffs[i]);
		}
	}
}

Mesh* Loop::run(Mesh * org)
{
	Mesh* mesh = new Mesh();

	//vertex ordering in the new mesh:
	//ids of the vertex points are the same as the original ones
	//ids of the edge points are vertex size + ids of the associated edges

	//adding vertex and face points
	for each (Vertex* v in org->verts) mesh->addVertex(getVertexPoint(v));
	for each (Edge* e in org->edges) mesh->addVertex(getEdgePoint(e));

	size_t vSize = org->verts.size();

	//adding faces
	for each (Face* f in org->faces)
	{
		mesh->addFace(new size_t[3]{
			f->verts[0]->id, vSize + f->edges[0]->id, vSize + f->edges[2]->id }, 3);
		mesh->addFace(new size_t[3]{
			vSize + f->edges[0]->id, f->verts[1]->id, vSize + f->edges[1]->id }, 3);
		mesh->addFace(new size_t[3]{
			vSize + f->edges[2]->id, vSize + f->edges[1]->id, f->verts[2]->id }, 3);
		mesh->addFace(new size_t[3]{
			vSize + f->edges[0]->id, vSize + f->edges[1]->id, vSize + f->edges[2]->id }, 3);
	}

	return mesh;
}

Point Loop::getVertexPoint(Vertex * v)
{
	Point p;
	size_t vSize = v->verts.size();
	p = v->coords * (1.0f - (float(vSize) * coeffs[vSize]));

	//non-boundary
	//if (vSize == v->faces.size())
		for each (Vertex* vn in v->verts) p += vn->coords * coeffs[vSize];
	//boundary
	//else

	return p;
}

Point Loop::getEdgePoint(Edge* e)
{
	Point p;

	Vertex* v1 = e->verts[0];
	Vertex* v2 = e->verts[1];

	//non-boundary
	if (e->faces.size() == 2)
	{
		p = (v1->coords + v2->coords) * (3.0f / 8.0f);

		Vertex* vn1 = e->faces[0]->getNextVert(v2);
		Vertex* vn2 = e->faces[1]->getNextVert(v1);

		p += (vn1->coords + vn2->coords) / 8.0f;
	}
	//boundary
	else
		p = (v1->coords + v2->coords) / 2.0f;

	return p;
}

