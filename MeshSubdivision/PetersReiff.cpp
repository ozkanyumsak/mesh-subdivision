#include "PetersReiff.h"

Mesh * PetersReiff::run(Mesh * org)
{
	Mesh* mesh = new Mesh();
	size_t orgVertSize = org->verts.size();

	//vertex ordering in the new mesh:
	//ids of the vertices are the same as the ids of the associated edges

	//adding vertices
	for each (Edge* e in org->edges) mesh->addVertex(
		(e->verts[0]->coords + e->verts[1]->coords) / 2.0f);

	size_t* vIds = NULL;
	size_t eSize = 0;

	//adding faces centered around original vertices
	for each (Vertex* v in org->verts)
	{
		eSize = v->edges.size();
		vIds = new size_t[eSize];
		Edge* eNext = v->edges[0];

		for (size_t i = 0; i < eSize; i++)
		{
			vIds[i] = eNext->id;
			eNext = v->getNextEdgeCC(eNext);
		}

		mesh->addFace(vIds, eSize);
	}

	//adding faces using edge midpoints
	for each (Face* f in org->faces)
	{
		eSize = f->edges.size();
		vIds = new size_t[eSize];

		for (size_t i = 0; i < eSize; i++)
			vIds[i] = f->edges[i]->id;

		mesh->addFace(vIds, eSize);
	}

	return mesh;
}


