#include "WireframeShape.h"

SoSeparator* WireframeShape::getShapeSep(Mesh* mesh, float r, float g, float b)
{
	SoSeparator* sep = new SoSeparator();

	SoDrawStyle* drawStyle = new SoDrawStyle();
	drawStyle->style = SoDrawStyle::Style::LINES;
	sep->addChild(drawStyle);

	SoMaterial* mat = new SoMaterial();
	mat->diffuseColor.setValue(r, g, b);
	sep->addChild(mat);

	SoCoordinate3* coords = new SoCoordinate3();

	for each (Vertex* v in mesh->verts)
		coords->point.set1Value(v->id, v->coords.x,
			v->coords.y, v->coords.z);

	sep->addChild(coords);

	SoIndexedFaceSet* faceSet = new SoIndexedFaceSet();

	size_t nt = 0;

	for each (Face* f in mesh->faces)
	{
		for each (Vertex* v in f->verts)
			faceSet->coordIndex.set1Value(nt++, v->id);

		faceSet->coordIndex.set1Value(nt++, SO_END_FACE_INDEX);
	}

	sep->addChild(faceSet);

	return sep;
}