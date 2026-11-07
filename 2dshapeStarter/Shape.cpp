#include "Shape.h"
Shape::Shape(int amountVerts, int amountIndicies) : numVert(amountVerts), numIndicies(amountIndicies)
{
	Verts = new VertexPosColour[amountVerts];

}

Shape::~Shape()
{
	delete[] Verts;
	Verts = nullptr;
}

void Shape::SetColour(XMVECTORF32 c)
{
	clr = c;
}
