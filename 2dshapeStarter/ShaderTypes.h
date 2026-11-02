#ifndef SHADERTYPES_H
#define SHADERTYPES_H

#include <d3d11.h>

#include "SimpleMath.h"

/*
This is what our vertex data will look like
*/
struct VertexPosColour
{
	DirectX::SimpleMath::Vector3 Pos;			//local space position of the vertex
	DirectX::SimpleMath::Vector4 Colour;		//colour red, green, blue, alpha

	static const D3D11_INPUT_ELEMENT_DESC sVertexDesc[2];
};



#endif
