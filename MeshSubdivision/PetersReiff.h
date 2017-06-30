#pragma once

#include "BaseScheme.h"

class PetersReiff : public BaseScheme
{
public:
	Mesh* run(Mesh* org);
	bool needsTriangulation() { return false; }
};

