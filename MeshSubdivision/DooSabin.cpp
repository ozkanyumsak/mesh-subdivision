#include "DooSabin.h"

Mesh * DooSabin::run(Mesh * org)
{
	Mesh* mesh = new Mesh();
	vector<DooSabinFace> dsFaces;

	//vertex ordering in the new mesh:
	//not relatable to original mesh ordering

	//adding vertices
	for each (Face* f in org->faces)
	{
		DooSabinFace dsFace;

		for each (Vertex* v in f->verts)
		{
			mesh->addVertex(getDsPoint(v, f));
			dsFace.verts.push_back(mesh->verts.back());
		}

		dsFaces.push_back(dsFace);
	}

	//adding F faces
	for each (DooSabinFace f in dsFaces)
	{
		size_t vSize = f.verts.size();
		size_t* vIds = new size_t[vSize];

		for (size_t i = 0; i < vSize; i++)
			vIds[i] = f.verts[i]->id;

		mesh->addFace(vIds, vSize);
	}

	//adding E faces
	for each (Edge* e in org->edges)
	{
		//non-boundary
		if (e->faces.size() == 2)
		{
			DooSabinFace* dsf1 = &(dsFaces[e->faces[0]->id]);
			DooSabinFace* dsf2 = &(dsFaces[e->faces[1]->id]);

			mesh->addFace(new size_t[4]{
				dsf1->verts[e->faces[0]->getVertPos(e->verts[1])]->id,
				dsf1->verts[e->faces[0]->getVertPos(e->verts[0])]->id,
				dsf2->verts[e->faces[1]->getVertPos(e->verts[0])]->id,
				dsf2->verts[e->faces[1]->getVertPos(e->verts[1])]->id
			}, 4);
		}
	}

	//adding V faces
	for each (Vertex* v in org->verts)
	{
		size_t fSize = v->faces.size();
		//non-boundary
		if (v->edges.size() == fSize)
		{
			size_t* vIdx = new size_t[fSize];
			size_t vItr = 0;

			Face* f = v->faces[0];

			do
			{
				vIdx[vItr++] = dsFaces[f->id].verts[f->getVertPos(v)]->id;
				f = v->getNextFaceCC(f);
			} while (f != v->faces[0]);

			mesh->addFace(vIdx, fSize);
		}
	}

	return mesh;
}

Point DooSabin::getDsPoint(Vertex * v, Face * f)
{
	Point p;

	float coeff = 0.0f;
	int vSize = (int)f->verts.size();
	float vfSize = (float)vSize;
	int vIdx = (int)f->getVertPos(v);

	for (int i = 0; i < vSize; i++)
	{
		if (i == vIdx)
			coeff = (5.0f + vfSize) / (4.0f * vfSize);
		else
			coeff = (3.0f + (2.0f * cosf(PI_2_FLOAT *
				((float)(vIdx - i)) / vfSize))) / (4.0f * vfSize);

		p += f->verts[i]->coords * coeff;
	}

	return p;
}
