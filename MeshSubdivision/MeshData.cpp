#include "MeshData.h"

int MeshData::getFacePos(const Face* f)
{
	for (size_t i = 0; i < faces.size(); i++)
		if (f == faces[i])
			return (int)i;
	return -1;
}

int MeshData::getEdgePos(const Edge* e)
{
	for (size_t i = 0; i < edges.size(); i++)
		if (e == edges[i])
			return (int)i;
	return -1;
}

int MeshData::getVertPos(const Vertex* v)
{
	for (size_t i = 0; i < verts.size(); i++)
		if (v == verts[i])
			return (int)i;
	return -1;
}

Face * MeshData::getNextFace(const Face * f)
{
	int pos = getFacePos(f);
	return faces[pos < (int)faces.size() - 1 ? pos + 1 : 0];
}

Edge * MeshData::getNextEdge(const Edge * e)
{
	int pos = getEdgePos(e);
	return edges[pos < (int)edges.size() - 1 ? pos + 1 : 0];
}

Vertex * MeshData::getNextVert(const Vertex * v)
{
	int pos = getVertPos(v);
	return verts[pos < (int)verts.size() - 1 ? pos + 1 : 0];
}


Face * MeshData::getPrevFace(const Face * f)
{
	int pos = getFacePos(f);
	return faces[pos == 0 ? (int)faces.size() - 1 : pos - 1];
}

Edge * MeshData::getPrevEdge(const Edge * e)
{
	int pos = getEdgePos(e);
	return edges[pos == 0 ? (int)edges.size() - 1 : pos - 1];
}

Vertex * MeshData::getPrevVert(const Vertex * v)
{
	int pos = getVertPos(v);
	return verts[pos == 0 ? (int)verts.size() - 1 : pos - 1];
}

Vertex * Vertex::getNextVertCC(const Vertex * v)
{
	//normal iteration
	for each (Face* f in faces)
		if (f->getNextVert(this) == v)
			return f->getPrevVert(this);

	//arrived at boundary
	for each (Face* f in faces)
	{
		Vertex* vn = f->getNextVert(this);
		if (vn->verts.size() != vn->faces.size())
			return vn;
	}

	return NULL;
}

Edge * Vertex::getNextEdgeCC(const Edge * e)
{
	//normal operation
	for each (Face* f in e->faces)
	{
		Edge* ePrev = f->getPrevEdge(e);
		if (ePrev->getVertPos(this) != -1)
			return ePrev;
	}

	//arrived at boundary
	for each (Edge* en in edges)
		if (en->faces.size() != 2 && en != e)
			return en;
	return NULL;
}

Face * Vertex::getNextFaceCC(Face * f)
{
	//normal operation
	for each (Edge* e in edges)
		if (e->faces.size() == 2)
		{
			if ((e->verts[0] == this && e->faces[1] == f) ||
				(e->verts[1] == this && e->faces[0] == f))
				return e->faces[0] == f ? e->faces[1] : e->faces[0];
		}

	//arrived at boundary
	for each (Edge* e in edges)
		if (e->faces.size() != 2 && f->getEdgePos(e) == -1)
			return e->faces[0];

	return NULL;
}


