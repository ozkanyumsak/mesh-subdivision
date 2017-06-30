#pragma once

#include "Point.h"
#include "Mesh.h"
#include "Loop.h"
#include "CatmullClark.h"
#include "DooSabin.h"
#include "PetersReiff.h"
#include "Butterfly.h"
#include "KobbeltRoot3.h"
#include "WireframeShape.h"
#include "FilledShape.h"

#include <sstream>
#include <string>

#include <Inventor/nodes/SoSeparator.h>

class AlgoRunner
{
public:
	SoSeparator* run();
	const char* getFilePathInput();
	BaseScheme* getSchemeInput();
	size_t getIterationInput();
};

