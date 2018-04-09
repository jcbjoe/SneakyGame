#ifndef GEOMETRYBUILDER_H
#define GEOMETRYBUILDER_H

class MeshManager;
class Model;
class Mesh;

Mesh& BuildQuad(MeshManager& mgr); //Default Build Quad

Mesh& BuildPyramid(MeshManager& mgr);

Mesh& BuildQuadPyramid(MeshManager& mgr);

Mesh& BuildCube(MeshManager& mgr); //Default Build Cube

Mesh& BuildSphere(MeshManager& mgr, int LatLines, int LongLines); // Default build sphere

Mesh& BuildWall(MeshManager& mgr); // for Wall

Mesh& BuildDoor(MeshManager& mgr); // for door & Half Wall

Mesh& BuildFloor(MeshManager& mgr); // for Floor

Mesh& BuildLoot(MeshManager& mgr, int LatLines, int LongLines); // for Loot

#endif
