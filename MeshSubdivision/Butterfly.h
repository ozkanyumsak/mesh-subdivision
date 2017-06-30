#pragma once

#include "BaseScheme.h"

class Butterfly : public BaseScheme
{
public:
	Mesh* run(Mesh* org);
	bool needsTriangulation() { return true; }
protected:
	Point getEdgePoint(Edge * e);
};

