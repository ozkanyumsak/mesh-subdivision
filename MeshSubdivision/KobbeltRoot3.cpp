#include "KobbeltRoot3.h"

KobbeltRoot3::KobbeltRoot3()
{
	//pre-calculating coeffs for different sizes of vert neighbors to remove
	//cos calculation etc in the construction loop
	for (size_t i = 1; i < 10; i++)
		coeffs[i] = (4.0f - (2.0f * cosf(PI_2_FLOAT / float(i)))) / 9.0f;
}

Mesh * KobbeltRoot3::run(Mesh * org)
{
	Mesh* mesh = new Mesh();

	//vertex ordering in the new mesh:
	//ids of the vertex points are the same as the original ones
	//ids of the face points are vertex size + original face ids

	//adding vertex and face points

	for each (Vertex* v in org->verts) mesh->addVertex(getVertexPoint(v));

	for each (Face* f in org->faces)
		mesh->addVertex((f->verts[0]->coords + 
			f->verts[1]->coords + f->verts[2]->coords) / 3.0f);

	//adding faces with the ordering:
	//original vertex -> face point on neightbor face -> face point on next neighbor face

	size_t vSize = org->verts.size();

	for each (Vertex* v in org->verts)
	{
		Face* f = v->faces[0];
		Face * fNext = NULL;
		do
		{
			fNext = v->getNextFaceCC(f);

			//non-boundary or last face of a boundary vertex
			if (fNext != NULL && (v->verts.size() == v->faces.size() || fNext != v->faces[0]))
			{
				size_t* vIdx = new size_t[3];
				vIdx[0] = v->id;
				vIdx[1] = mesh->verts[vSize + f->id]->id;
				vIdx[2] = mesh->verts[vSize + fNext->id]->id;
				mesh->addFace(vIdx, 3);
			}

			f = fNext;

		} while (f != v->faces[0] && f != NULL);
	}

	return mesh;
}

Point KobbeltRoot3::getVertexPoint(Vertex * v)
{
	Point p;
	size_t vSize = v->verts.size();

	for each (Vertex* v in v->verts) p += v->coords;
	p *= coeffs[vSize] / (float)vSize;
	p += v->coords * (1.0f - coeffs[vSize]);

	return p;
}
