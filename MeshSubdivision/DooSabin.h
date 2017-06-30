#pragma once

#include "BaseScheme.h"

struct DooSabinFace 
{
	vector<Vertex*> verts; //associated verts in the new mesh
};

class DooSabin : public BaseScheme
{
public:
	Mesh* run(Mesh* org);
	bool needsTriangulation() { return false; }

protected:
	Point getDsPoint(Vertex* v, Face* f);
};

