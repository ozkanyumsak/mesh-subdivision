#include "Butterfly.h"

Mesh * Butterfly::run(Mesh * org)
{
	Mesh* mesh = new Mesh();

	//vertex ordering in the new mesh:
	//original vertex indices remain the same
	//edge points have the vertex size + id of the associated edges

	//adding original vertices and edge points
	for each (Vertex* v in org->verts) mesh->addVertex(v->coords);
	for each (Edge* e in org->edges) mesh->addVertex(getEdgePoint(e));

	size_t vSize = org->verts.size();

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

Point Butterfly::getEdgePoint(Edge * e)
{
	Point p = (e->verts[0]->coords + e->verts[1]->coords) / 2.0f;

	// non - boundary
	if (e->faces.size() == 2)
	{
		for each (Face* f in e->faces)
			//non-boundary
			if (f->faces.size() == 3)
			{
				for each (Vertex* v in f->verts)
					if (v != e->verts[0] && v != e->verts[1])
						p += v->coords / 8.0f;

				for each (Face* fn in f->faces)
					if (fn->getEdgePos(e) == -1)
						for each (Vertex* vn in fn->verts)
							if (f->getVertPos(vn) == -1)
								p -= vn->coords / 16.0f;
			}
	}

	return p;
}
