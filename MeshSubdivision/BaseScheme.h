#pragma once

#include "Mesh.h"

class BaseScheme
{
public:
	virtual Mesh * run(Mesh * org) { return NULL; };
	virtual bool needsTriangulation() { return false; };
};

