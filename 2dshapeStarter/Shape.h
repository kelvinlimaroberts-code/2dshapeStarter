#pragma once
#include "ShaderTypes.h"

//verticis messing
class Shape
{
private:
	const int numVert;
public:
	VertexPosColour* Verts;
	Shape() = delete;
	Shape(int amountVerts);
	~Shape();
};



