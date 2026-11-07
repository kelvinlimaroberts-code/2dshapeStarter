#pragma once
//system libraries
#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <vector>

//our libraries
#include "WindowUtils.h"
#include "D3D.h"
#include "Sprite.h"
#include "ShaderTypes.h"
#include "FX.h"
using namespace std;					//open the standard template library
using namespace DirectX;				//DirectX library
using namespace DirectX::SimpleMath;	//the maths part of the library

//verticis messing
class Shape
{
private:
	const int numVert;
	const int numIndicies;
	XMVECTORF32 clr = Colors::IndianRed;
public:
	VertexPosColour* Verts;

	Shape(int amountVerts, int amountIndicies);
	~Shape();
	void SetColour(XMVECTORF32 c);
};



