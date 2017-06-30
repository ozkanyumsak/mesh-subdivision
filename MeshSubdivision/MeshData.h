#pragma once

#include "Point.h"
#include <vector>
using namespace std;

struct Face;
struct Edge;
struct Vertex;

struct MeshData
{
	size_t id;
	vector<Face*> faces;
	vector<Edge*> edges;
	vector<Vertex*> verts;

	MeshData(size_t id) : id(id) {}

	int getFacePos(const Face* f);
	int getEdgePos(const Edge* e);
	int getVertPos(const Vertex* v);

	Face * getNextFace(const Face* f);
	Edge * getNextEdge(const Edge* e);
	Vertex * getNextVert(const Vertex* v);

	Face * getPrevFace(const Face* f);
	Edge * getPrevEdge(const Edge* e);
	Vertex * getPrevVert(const Vertex* v);
};

struct Face : public MeshData
{
	Face(size_t id) : MeshData(id) {}
};

struct Edge : public MeshData
{
	float length;
	Edge(size_t id, float length) 
		: MeshData(id), length(length) {};
};

struct Vertex : public MeshData
{
	Point coords;

	Vertex(size_t id, const Point& coords)
		: MeshData(id), coords(coords) {};

	Vertex * getNextVertCC(const Vertex* v);
	Edge * getNextEdgeCC(const Edge* e);
	Face * getNextFaceCC(Face* f);
};

