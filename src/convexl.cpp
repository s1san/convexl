#include "convexl.h"

#include "geometrycentral/surface/manifold_surface_mesh.h"
#include "geometrycentral/surface/meshio.h"
#include "geometrycentral/surface/surface_mesh.h"

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"

using namespace geometrycentral;
using namespace geometrycentral::surface;

int main()
{
	//std::unique_ptr<SurfaceMesh> mesh;
	//std::unique_ptr<VertexPositionGeometry> geometry;
	//std::tie(mesh, geometry) = readSurfaceMesh("./spot.ply");

	//for (Vertex v : mesh->vertices()) {
	//	std::cout << "Vertex " << v << " has degree " << v.degree() << "\n";
	//	for (Face fn : v.adjacentFaces())
	//		std::cout << "	incident on face " << fn << "\n";
	//}

	polyscope::init();

	//polyscope::registerSurfaceMesh("my mesh", geometry->vertexPositions, 
	//	mesh->getFaceVertexList());

	polyscope::show();
	return 0;
}
