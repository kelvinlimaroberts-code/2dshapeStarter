
#include "Shape.h"

using namespace std;					//open the standard template library
using namespace DirectX;				//DirectX library
using namespace DirectX::SimpleMath;	//the maths part of the library


ID3D11InputLayout* gInputLayout;				//vertex description D3D object
ID3D11Buffer* gBoxVB;							//vertex buffer D3D object for the sprite 
ID3D11Buffer* gBoxIB;							//index buffer D3D object for the sprite
ID3D11VertexShader* pVertexShader = nullptr;	//vertex buffer D3D object
ID3D11PixelShader* pPixelShader = nullptr;		//pixel shader D3D object


constexpr float offset1 = 0.5f;
constexpr float offset2 = 0.4f;
constexpr float offset3 = 0.1f;

constexpr int numVertShape1 = 4;
VertexPosColour shape1[] =
{
	{ Vector3(-0.5f, -0.5f, 0.f), Colors::White   },
	{ Vector3(-0.5f, +0.5f, 0.f), Colors::Black },
	{ Vector3(+0.5f, +0.5f, 0.f), Colors::Red },
	{ Vector3(+0.5f, -0.5f, 0.f), Colors::Green }
};

constexpr int numVertShape2 = 12;
VertexPosColour shape2[numVertShape2] =
{
	{ Vector3(-offset1, offset2 , 0.f), Colors::Purple   },					//0
	{ Vector3(-offset2, offset1, 0.f), Colors::DodgerBlue   },				//1
	{ Vector3(0.f, offset3, 0.f), Colors::LawnGreen },						//2
	{ Vector3(offset2, offset1, 0.f), Colors::LightGoldenrodYellow},		//3
	{ Vector3(offset1, offset2 , 0.f), Colors::Orange   },					//4
	{ Vector3(offset3, 0.f, 0.f), Colors::Red   },							//5
	{ Vector3(offset1, -offset2, 0.f), Colors::Red   },						//6
	{ Vector3(offset2, -offset1 , 0.f), Colors::Red   },					//7
	{ Vector3(0.f, -offset3 , 0.f), Colors::Red   },						//8
	{ Vector3(-offset2, -offset1, 0.f), Colors::Red   },					//9
	{ Vector3(-offset1, -offset2 , 0.f), Colors::PeachPuff},				//10
	{ Vector3(-offset3, 0.0f, 0.f), Colors::Red   },						//11
};






/*
* create the geometry needed for a sprite - a two trangle quad
*/
void BuildGeometryBuffers()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	// Create vertex buffer for a quad (two triangle square)
	

	CreateVertexBuffer(d3d.GetDevice(),sizeof(VertexPosColour) * numVertShape2, shape2, gBoxVB);
	// Create the index buffer




	//constexpr static int amountIndicies = 6;
	//UINT indices[amountIndicies] = {
	//	// front face
	//	0,1,2,
	//	0,2,3
	//};

	constexpr static int amountIndicies = 18;      //SHAPE 2
	UINT indices[amountIndicies] = {
		// front face
		1,2,11,
		1,11,0,
		3,9,10,
		3,4,9,
		5,7,8,
		5,6,7
	};

	CreateIndexBuffer(d3d.GetDevice(), sizeof(UINT) * amountIndicies, indices, gBoxIB);
}


/*
* Setup geometry and shaders, everything the gpu needs to render primtives
*/
bool BuildFX()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	CheckShaderModel5Supported(d3d.GetDevice());

	//load in a pre-compiled vertex shader
	char* pBuff = nullptr;
	unsigned int bytes = 0;
	pBuff = ReadAndAllocate("../bin/data/SimpleVS.cso", bytes);
	CreateVertexShader(d3d.GetDevice(),pBuff, bytes, pVertexShader);
	//create a link between our data and the vertex shader
	CreateInputLayout(d3d.GetDevice(),VertexPosColour::sVertexDesc, 2, pBuff, bytes, &gInputLayout);
	delete[] pBuff;

	//load in a pre-compiled pixel shader	
	pBuff = ReadAndAllocate("../bin/data/SimplePS.cso", bytes);
	CreatePixelShader(d3d.GetDevice(),pBuff, bytes, pPixelShader);
	delete[] pBuff;


	return true;

}


void TranslateInRunTime(Vector3 moveVec, float elapsed)
{
	for (size_t i = 0; i < numVertShape1; i++)
	{
		shape1[i].Pos.x += moveVec.x * elapsed;
		shape1[i].Pos.y += moveVec.y * elapsed;
		shape1[i].Pos.z += moveVec.z * elapsed;


	}
}
void Scale()
{
	for (size_t i = 0; i < numVertShape1; i++)
	{
		shape1[i].Pos = Vector3(shape1[i].Pos.x * 1.0001, shape1[i].Pos.y * 1.0001, 0);
	}
}

//one time initialisation
void InitGame()
{
	BuildGeometryBuffers();
	BuildFX();
}

//one time release of all D3D objects
void ReleaseGame()
{
	ReleaseCOM(pVertexShader);
	ReleaseCOM(pPixelShader);
	ReleaseCOM(gBoxVB);
	ReleaseCOM(gBoxIB);
	ReleaseCOM(gInputLayout);
}

/*
* run once per update as fast as possible, do all logical updates
* dTime - elapsed time since last call to Update
*/
void Update(float dTime)
{
	//TranslateInRunTime({ 1,1,0 }, dTime);
	//Scale();
	BuildGeometryBuffers();  //should really be doin this but whatever

}

/*
* Take the logical representation, updated previously, render it on the screen
*/
void Render()
{
	MyD3D& d3d = WinUtil::Get().GetD3D();
	d3d.BeginRender(Vector4(0, 0, 0, 1));	//clear the back buffer for rendering

	d3d.InitInputAssembler(gInputLayout, gBoxVB, sizeof(VertexPosColour), gBoxIB);	//activate a vertex description, index+vertex buffer loaded previously
	d3d.GetDeviceCtx().VSSetShader(pVertexShader, nullptr, 0);	//activate a vertex shader
	d3d.GetDeviceCtx().PSSetShader(pPixelShader, nullptr, 0);	//activate a pixel shader
	d3d.GetDeviceCtx().DrawIndexed(6, 0, 0);	//draw 6 indices, each triplet refers to one triangle


	d3d.EndRender();	//swap front and back buffers when gpu is ready
}


//if ALT+ENTER or resize or drag window we might want do
//something like pause the game perhaps, but we definitely
//need to let D3D know what's happened (OnResize_Default).
void OnResize(int screenWidth, int screenHeight, MyD3D& d3d)
{
	d3d.OnResize_Default(screenWidth, screenHeight);	
}

//messages come from windows all the time, should we respond to any specific ones?
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 27:
		case 'q':
		case 'Q':
			PostQuitMessage(0); //exit request
			break;
		}
	case WM_INPUT:
		break;
	}

	//default message handling (resize window, full screen, etc)
	return WinUtil::DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

//main entry point for the game
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	//start a new window using the operating system
	int w(512), h(256);
	//int defaults[] = { 640,480, 800,600, 1024,768, 1280,1024 }; //clue to a more sophisticated way to choose resolution at a specific aspect ratio
		//WinUtil::ChooseRes(w, h, defaults, 4);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Fezzy", MainWndProc, true))
		assert(false);

	//setup D3D
	MyD3D d3d;
	if (!d3d.InitDirect3D(OnResize))
		assert(false);
	WinUtil::Get().SetD3D(d3d);
	d3d.GetCache().SetAssetPath("data/");

	//initialise any game related memory
	InitGame();

	//call update+render as fast as you can 
	bool canUpdateRender;
	float dTime = 0;
	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender && dTime>0)
		{
			Update(dTime);
			Render();
		}
		//time how long one loop takes
		dTime = WinUtil::Get().EndLoop(canUpdateRender);
	}

	//game over
	d3d.ReleaseD3D(true);	
	return 0;
}

