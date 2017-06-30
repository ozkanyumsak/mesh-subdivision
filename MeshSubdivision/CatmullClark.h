#pragma once

#include "BaseScheme.h"

class CatmullClark : public BaseScheme
{
public:
	Mesh* run(Mesh* org);
	bool needsTriangulation() { return false; }

protected:
	Point getFacePoint(Face* f);
	Point getEdgePoint(Mesh* m, Edge* e);
	Point getVertexPoint(Mesh* m, Vertex* v);
};
