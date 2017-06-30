#pragma once

#include "BaseScheme.h"

class Loop : public BaseScheme
{
public:
	Loop();
	Mesh* run(Mesh* org);
	bool needsTriangulation() { return true; }

protected:
	Point getVertexPoint(Vertex* v);
	Point getEdgePoint(Edge* e);

	float coeffs[10];
};


