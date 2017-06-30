#include "FilledShape.h"

SoSeparator* FilledShape::getShapeSep(Mesh* mesh, float r, float g, float b)
{
	SoSeparator* sep = new SoSeparator();

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


	for (size_t t = 0, nt = 0; t < mesh->faces.size(); t++)
	{
		for (size_t i = 0; i < mesh->faces[t]->verts.size(); i++)
			faceSet->coordIndex.set1Value(nt++, mesh->faces[t]->verts[i]->id);

		faceSet->coordIndex.set1Value(nt++, SO_END_FACE_INDEX);
	}

	sep->addChild(faceSet);

	return sep;
}