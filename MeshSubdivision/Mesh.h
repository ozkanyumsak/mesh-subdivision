#pragma once

#include "MeshData.h"

#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

const float PI_2_FLOAT = 6.2831853f;
const float PI_FLOAT = 3.1415927f;

class Mesh
{
public:
	vector<Face*> faces;
	vector<Edge*> edges;
	vector<Vertex*> verts;

	void loadOff(const char* path, bool quadToTri);

	void addFace(size_t* vertices, size_t sideCount);
	void addVertex(const Point& p);

	void sortCounterClockwise();

protected:
	Edge* addEdge(Vertex* v1, Vertex* v2);
};