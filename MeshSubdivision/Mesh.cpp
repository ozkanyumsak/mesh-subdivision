#include "Mesh.h"

void Mesh::loadOff(const char* path, bool quadToTri)
{
	cout << "Mesh initializing (to " << path << ")..\n";

	ifstream file;
	file.open(path, std::ifstream::in);

	char heading[10];

	if (file >> heading)
	{
		size_t vertSize, faceSize, dummy;
		file >> vertSize >> faceSize >> dummy;

		for (size_t i = 0; i < vertSize; i++)
		{
			Point p;
			file >> p.x >> p.y >> p.z;
			addVertex(p);
		}

		size_t sideCount = 0;
		size_t* vIds = NULL;

		if (quadToTri)
		{
			vIds = new size_t[4];
			for (size_t i = 0; i < faceSize; i++)
			{
				file >> sideCount;

				if (sideCount != 4)
				{
					cout << path << " is not a quad mesh" << endl;
					int in; cin >> in; exit(0);
				}

				file >> vIds[0] >> vIds[1] >> vIds[2] >> vIds[3];

				addFace(new size_t[3]{ vIds[0], vIds[1], vIds[2] }, 3);
				addFace(new size_t[3]{ vIds[0], vIds[2], vIds[3] }, 3);
			}
		}
		else
		{
			for (size_t i = 0; i < faceSize; i++)
			{
				file >> sideCount;

				vIds = new size_t[sideCount];
				for (size_t i = 0; i < sideCount; i++)
					file >> vIds[i];

				addFace(vIds, sideCount);
			}
		}

		cout << "Mesh has " << faces.size() << " faces, " << verts.size()
			<< " verts, " << edges.size() << " edges\nInitialization done\n";
	}
	else
	{
		cout << "cannot read " << path << endl;
	}
}

void Mesh::addFace(size_t* vertices, size_t sideCount)
{
	Face* face = new Face(faces.size());
	//TO DO: this will result in null face neighbors
	//face->faces.resize(sideCount, NULL);
	faces.push_back(face);

	for (size_t i = 0; i < sideCount; i++)
	{
		Vertex* v = verts[vertices[i]];
		Vertex* vNext = verts[vertices[i < sideCount - 1 ? i + 1 : 0]];

		face->verts.push_back(v); //sorted
		v->faces.push_back(face); //not sorted

		Edge* edge = NULL;
		int vNextPos = v->getVertPos(vNext);

		if (vNextPos == -1)
			edge = addEdge(v, vNext);
		else
		{
			edge = v->edges[vNextPos];

			face->faces.push_back(edge->faces[0]); //sorted
			//TO DO: this will result in null face neighbors
			//edge->faces[0]->faces[edge->faces[0]->getEdgePos(edge)] = face; //sorted
			edge->faces[0]->faces.push_back(face); //not sorted
		}

		face->edges.push_back(edge); //sorted
		edge->faces.push_back(face); //sorted, left face is first

		if (i > 0) edge->edges.push_back(face->edges[i - 1]); //not sorted
		else face->edges[0]->edges.push_back(edge);
	}
}

void Mesh::addVertex(const Point& p)
{
	verts.push_back(new Vertex(verts.size(), p));
}

Edge* Mesh::addEdge(Vertex * v1, Vertex * v2)
{
	v1->verts.push_back(v2); // not sorted
	v2->verts.push_back(v1); // not sorted

	Edge* edge = new Edge(edges.size(),
		Point::distance(v1->coords, v2->coords));

	edges.push_back(edge);

	v1->edges.push_back(edge); //not sorted
	v2->edges.push_back(edge); //not sorted

	edge->verts.push_back(v1);
	edge->verts.push_back(v2);

	return edge;
}

// TO DO: sort edge neighbors of an edge
void Mesh::sortCounterClockwise()
{
	for each (Vertex* v in verts)
	{
		Face* f = v->faces[0];
		Edge* edge = NULL;
		size_t eItr = 0;
		int ePos = 0;

		do
		{
			Edge* e1 = NULL;
			Edge* e2 = NULL;

			for each (Edge* e in f->edges)
				if (e->getVertPos(v) != -1)
				{
					if (e1 == NULL) e1 = e;
					else e2 = e;
				}

			edge = (f->getNextEdge(e1) == e2) ? e1 : e2;
			ePos = v->getEdgePos(edge);

			if (ePos != eItr)
			{
				swap(v->edges[ePos], v->edges[eItr]);
				swap(v->verts[ePos], v->verts[eItr++]);
			}

			swap(v->faces[ePos], v->faces[v->getFacePos(f)]);

			if (edge->faces.size() == 2)
				f = edge->faces[(f == edge->faces[0]) ? 1 : 0];
			else
				f = v->faces[0];

		} while (f != v->faces[0]);
	}
}

