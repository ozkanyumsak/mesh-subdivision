# mesh-subdivision
A collection of mesh subdivision algorithms.

Algorithms that are currently implemented:
  - Butterfly
  - Catmull-Clark
  - Doo–Sabin
  - Root-3 by Kobbelt
  - Peters-Reif
  - Loop
  
For now, only OFF mesh format is supported. Mesh examples including letters, numbers and common graphical objects (cube, torus, helix etc) can be found in Meshes folder.

Meshes are represented as a variation of Half-Edge data structure. See Mesh class for details.

Demo application is rather simple: You choose a subdivision algorithm and a mesh to apply it to from a console-based user interface. Most of it is implemented in AlgoRunner class.

Used Open Inventor for visualization of subdivision results, given a mesh object. To use another visualization framework, modify files under Inventor folder (FilledShape and WireframeShape classes), Algorunner and Main.

Example subdivision results for 1, 2 and 3 passes are given below for a closed mesh (X) and an open one (helix). Cyan wireframe is the original mesh.

Doo-Sabin

![Alt text](MeshSubdivision/Images/doosabinx.png?raw=true "Title")
![Alt text](MeshSubdivision/Images/doosabinhelix.png?raw=true "Title")

Catmull-Clark

![Alt text](MeshSubdivision/Images/catmulx.png?raw=true "Title")
![Alt text](MeshSubdivision/Images/catmulhelix.png?raw=true "Title")

Loop

![Alt text](MeshSubdivision/Images/loopx.png?raw=true "Title")
![Alt text](MeshSubdivision/Images/loophelix.png?raw=true "Title")

Butterfly

![Alt text](MeshSubdivision/Images/butterflyx.png?raw=true "Title")
![Alt text](MeshSubdivision/Images/butterflyhelix.png?raw=true "Title")

Root-3

![Alt text](MeshSubdivision/Images/rootx.png?raw=true "Title")
![Alt text](MeshSubdivision/Images/roothelix.png?raw=true "Title")

Peters-Reif

![Alt text](MeshSubdivision/Images/peterx.png?raw=true "Title")
![Alt text](MeshSubdivision/Images/peterhelix.png?raw=true "Title")
