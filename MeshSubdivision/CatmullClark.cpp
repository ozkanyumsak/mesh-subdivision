#include "CatmullClark.h"

Mesh * CatmullClark::run(Mesh * org)
{
	Mesh* mesh = new Mesh();

	size_t fSize = org->faces.size();
	size_t eSize = org->edges.size();

	//vertex ordering in the new mesh:
	//ids of the face points are the same as ids of associated faces
	//ids of the edge points are face size + ids of the associated edges
	//ids of the vertex points are face size + edge size + ids of associated vertices

	//adding face, edge and vertex points
	for each (Face* f in org->faces) mesh->addVertex(getFacePoint(f));
	for each (Edge* e in org->edges) mesh->addVertex(getEdgePoint(mesh, e));
	for each (Vertex* v in org->verts) mesh->addVertex(getVertexPoint(mesh, v));

	//adding faces
	for (size_t i = 0; i < org->faces.size(); i++)
	{
		Face* f = org->faces[i];

		for (size_t j = 0; j < 4; j++)
		{
			mesh->addFace(new size_t[4]{
				fSize + eSize + f->verts[j]->id, //vertex point
				fSize + f->edges[j]->id, //edge point of the edge starting with vertex point		
				f->id, //face point
					   //edge point of the edge ending with vertex point	
				fSize + f->edges[(j == 0) ? 3 : j - 1]->id
			}, 4);
		}
	}

	return mesh;
}

Point CatmullClark::getFacePoint(Face * f)
{
	Point p;
	for each (Vertex* v in f->verts) p += v->coords;
	p /= (float)f->verts.size();

	return p;
}

Point CatmullClark::getEdgePoint(Mesh* m, Edge * e)
{
	Point p;
	//non-boundary
	if (e->faces.size() == 2)
		p = (e->verts[0]->coords + e->verts[1]->coords +
			m->verts[e->faces[0]->id]->coords +
			m->verts[e->faces[1]->id]->coords) / 4.0f;
	//boundary
	else
		p = (e->verts[0]->coords + e->verts[1]->coords) / 2.0f;

	return p;
}

Point CatmullClark::getVertexPoint(Mesh * m, Vertex * v)
{
	Point p;

	//non-boundary
	if (v->edges.size() == v->faces.size())
	{
		Point fVal, eVal, vVal;

		//face points
		for each (Face* f in v->faces) fVal += m->verts[f->id]->coords;
		fVal /= (float)v->faces.size();

		//midpoints of edges
		for each (Edge* e in v->edges) eVal += (e->verts[0]->coords + e->verts[1]->coords) / 2.0f;

		float n = (float)v->edges.size();
		eVal /= n;

		//original vertex
		vVal = v->coords * (n - 3.0f);

		p = (fVal + (eVal * 2.0f) + vVal) / n;
	}
	//boundary, only using border edges and the vertex
	else
	{
		for each (Edge* e in v->edges)
			if (e->faces.size() == 1)
				p += (e->verts[0]->coords + e->verts[1]->coords) / 2.0f;

		p += v->coords;
		p /= 3.0f;
	}

	return p;
}
