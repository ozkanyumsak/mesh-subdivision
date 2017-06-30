# mesh-subdivision
A collection of common mesh subdivision algorithms.

Algorithms that are currently implemented:
  - ButterFly
  - Catmull-Clark
  - Doo–Sabin
  - Root-3 by Kobbelt
  - Peters-Reif
  - Loop
  
For now, only OFF mesh format is supported. Mesh examples including letters, numbers and common graphical objects (cube, torus, helix etc) can be found in Meshes folder.

Meshes are represented as a variation of Half-Edge data structure. See Mesh class for details.

Demo application is rather simple: You can choose a subdivision algorithm and a mesh to apply it to from a console-based user interface. Most of it is implemented in AlgoRunner class.

Used Open Inventor for visualization of subdivision results.
