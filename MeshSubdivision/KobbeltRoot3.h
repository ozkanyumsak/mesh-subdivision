#pragma once

#include "BaseScheme.h"

class KobbeltRoot3 : public BaseScheme
{
public:
	KobbeltRoot3();
	Mesh* run(Mesh* org);
	bool needsTriangulation() { return true; }

protected:
	Point getVertexPoint(Vertex * v);

	float coeffs[10];
};

