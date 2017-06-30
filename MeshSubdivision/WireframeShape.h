#pragma once

#ifndef HAVE_INT8_T
#define HAVE_INT8_T 1
#endif

#include "Point.h"
#include "Mesh.h"

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoDrawStyle.h>

class WireframeShape
{
public:
	SoSeparator* getShapeSep(Mesh* mesh, float r, float g, float b);
private:
};
