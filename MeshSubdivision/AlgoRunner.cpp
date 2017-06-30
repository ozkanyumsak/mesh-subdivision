#include "AlgoRunner.h"

SoSeparator* AlgoRunner::run()
{
	SoSeparator* separator = new SoSeparator();

	FilledShape* schemeShape = new FilledShape();
	FilledShape* meshShape = new FilledShape();

	Mesh* mesh = new Mesh();
	BaseScheme* scheme = getSchemeInput();
	mesh->loadOff(getFilePathInput(), scheme->needsTriangulation());
	Mesh* schemeMesh = scheme->run(mesh);
	size_t iterations = getIterationInput() - 1;

	for (size_t i = 0; i < iterations; i++)
		schemeMesh = scheme->run(schemeMesh);

	// Adding scheme and original mesh to scene
	separator->addChild((new FilledShape())->getShapeSep(schemeMesh, 0.7f, 0.7f, 0.7f));
	separator->addChild((new WireframeShape())->getShapeSep(mesh, 0.1f, 1.0f, 0.8f));

	return separator;
}

const char * AlgoRunner::getFilePathInput()
{
	std::stringstream ss;
	int in;

	cout << "Enter a Mesh Category Number:\n1: Geometry\n2: Letters\n3: Numbers\n";
	cin >> in;
	ss << "Meshes/" << (in == 1 ? "Geometry" : (in == 2 ? "Letters" : "Numbers")) << "/";

	cout << "Enter a Mesh Number:\n";
	if (in == 1)
	{
		cout << "1: boxcube\n2: boxtorus\n3: cube\n4: helix2\n5: octtorus\n";
		cin >> in;

		if (in == 1) ss << "boxcube.off";
		else if (in == 2) ss << "boxtorus.off";
		else if (in == 3) ss << "cube.off";
		else if (in == 4) ss << "helix2.off";
		else if (in == 5) ss << "octtorus.off";
	}
	else if (in == 2)
	{
		cout << "1: D\n2: L\n3: M\n4: S\n5: T\n6: V\n7: W\n8: X\n";
		cin >> in;

		if (in == 1) ss << "D.off";
		else if (in == 2) ss << "L.off";
		else if (in == 3) ss << "M.off";
		else if (in == 4) ss << "S.off";
		else if (in == 5) ss << "T.off";
		else if (in == 6) ss << "V.off";
		else if (in == 7) ss << "W.off";
		else ss << "X.off";
	}
	else
	{
		cout << "1: 0\n2: 5\n3: 6\n4: 7\n5: 8\n6: 9\n";
		cin >> in;

		if (in == 1) ss << "0.off";
		else if (in == 2) ss << "5.off";
		else if (in == 3) ss << "6.off";
		else if (in == 4) ss << "7.off";
		else if (in == 5) ss << "8.off";
		else if (in == 5) ss << "9.off";
	}

	string s = ss.str();
	cout << "Opening: " << s << endl;
	return s.c_str();
}

BaseScheme* AlgoRunner::getSchemeInput()
{
	int in;
	cout << "Enter a Subdivision Scheme:\n"
		<<"1: Catmull-Clark\n2: Loop\n3: Butterfly\n4: Doo-Sabin\n5: Kobbelt Root3\n6: Peters-Reiff\n";
	cin >> in;

	if (in == 1) return new CatmullClark();
	else if (in == 2) return new Loop();
	else if (in == 3) return new Butterfly();
	else if (in == 4) return new DooSabin();
	else if (in == 5) return new KobbeltRoot3();
	else return new PetersReiff();
}

size_t AlgoRunner::getIterationInput()
{
	int in;
	cout << "Enter Scheme Iteration Count: ";
	cin >> in;
	return (size_t)in;
}
