#include "Shape.h"
Shape::Shape(int amountVerts) : numVert(amountVerts)
{
	Verts = new VertexPosColour[amountVerts];

}

Shape::~Shape()
{
	delete[] Verts;
	Verts = nullptr;
}