#include "SceneStadium.h"
#include "GL\glew.h"
#include <cmath>
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LapCounter.h"
#include <string>

SceneText::SceneText()
{
	initialspeedZ = 1.f;
	finalspeedZ = 1.f;
}

SceneText::~SceneText()
{

}

void SceneText::Init()
{
	//Ryan's stuff
	ElapsedTime = 0.0;

	Score = 0;
	Fire = true;
	BallMove = false;
	CamIndex = 0;
	SwitchField = 0;
	Buffer = 0.0;
	LightOn = true;
	ballRY = 0.f;
	ballT = 0.f;
	
	Generator.Init("Track//RaceTrack1.txt");
	BestTime.Print();

	CameraOBJ[0].Set(-19.414f, 3.f, 25.14f, 0.f, -240.f, 0.f);
	CameraOBJ[1].Set(-20.791f, 3.f, 3.573f, 0.f, -270.f, 0.f);
	CameraOBJ[2].Set(-20.791f, 3.f, -15.872f, 0.f, -300.f, 0.f);
	CameraOBJ[3].Set(8.649f, 0.4f, 27.543f, 0.f, -135.f, 0.f);
	CameraOBJ[4].Set(10.409f, 0.4f, -24.331f, 0.f, -45, 0.f);
	CameraOBJ[5].Set(20.566f, 3.f, -16.985f, 0.f, -60.f, 0.f);
	CameraOBJ[6].Set(20.566f, 3.f, 15.974f, 0.f, -105.f, 0.f);
	// Init VBO here
	// Set background color to darkblue
	glClearColor(0.0f, 0.7f, 0.93f, 0.0f);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
											   //m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
											   // Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Use our shader
	//m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Blending.fragmentshader");
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	//m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Texture.fragmentshader");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	//m_programID = LoadShaders("Shader//Shading.vertexshader","Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 5);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// New to Scene3
	// Initialize the camera
	camera.Init(Vector3(0, 2, -10), Vector3(0, 2, 0), Vector3(0, 1, 0));
	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", Color(1, 0, 0), 1000, 1000, 1000);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Light", Color(0, 0, 0), 1, 36, 18);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Ground", /*Color(0.23f, 0.33f, 0.14f)*/Color(0, 0, 0), 1, 1);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//arrow.tga");
	meshList[GEO_QUAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_QUAD]->material.kShininess = 0.3f;
	
	// TGA files

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(0, 0, 0), 1, 1);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(0, 0, 0), 1, 1);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(0, 0, 0), 1, 1);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(0, 0, 0), 1, 1);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(0, 0, 0), 1, 1);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(0, 0, 0), 1, 1);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	// Obj files

	//meshList[GEO_TRACK] = MeshBuilder::GenerateOBJ("track", "OBJ//RaceTrack2.obj");
	//meshList[GEO_TRACK]->textureID = LoadTGA("Image//RaceTrack1.tga");
	meshList[GEO_TRACK_B_0] = MeshBuilder::GenerateOBJ("Track_B_0", "OBJ//RaceTrack_B_0.obj");
	meshList[GEO_TRACK_B_0]->textureID = LoadTGA("Image//RaceTrack1.tga");
	meshList[GEO_TRACK_B_1] = MeshBuilder::GenerateOBJ("Track_B_1", "OBJ//RaceTrack_B_1.obj");
	meshList[GEO_TRACK_B_1]->textureID = LoadTGA("Image//RaceTrack1.tga");
	meshList[GEO_TRACK_B_2] = MeshBuilder::GenerateOBJ("Track_B_2", "OBJ//RaceTrack_B_2.obj");
	meshList[GEO_TRACK_B_2]->textureID = LoadTGA("Image//RaceTrack1.tga");
	meshList[GEO_TRACK_B_3] = MeshBuilder::GenerateOBJ("Track_B_3", "OBJ//RaceTrack_B_3.obj");
	meshList[GEO_TRACK_B_3]->textureID = LoadTGA("Image//RaceTrack1.tga");
	meshList[GEO_TRACK_S_0] = MeshBuilder::GenerateOBJ("Track_S_0", "OBJ//RaceTrack_S_0.obj");
	meshList[GEO_TRACK_S_0]->textureID = LoadTGA("Image//RaceTrack1.tga");
	meshList[GEO_TRACK_S_1] = MeshBuilder::GenerateOBJ("Track_S_1", "OBJ//RaceTrack_S_1.obj");
	meshList[GEO_TRACK_S_1]->textureID = LoadTGA("Image//RaceTrack1.tga");
	meshList[GEO_TRACK_S_2] = MeshBuilder::GenerateOBJ("Track_S_2", "OBJ//RaceTrack_S_2.obj");
	meshList[GEO_TRACK_S_2]->textureID = LoadTGA("Image//RaceTrack1.tga");
	meshList[GEO_TRACK_S_3] = MeshBuilder::GenerateOBJ("Track_S_3", "OBJ//RaceTrack_S_3.obj");
	meshList[GEO_TRACK_S_3]->textureID = LoadTGA("Image//RaceTrack1.tga");
	meshList[GEO_KART] = MeshBuilder::GenerateOBJ("Kart", "OBJ//Kart1.obj");
	meshList[GEO_KART]->textureID = LoadTGA("Image//Kart1.tga");
	meshList[GEO_KART2] = MeshBuilder::GenerateOBJ("Kart2", "OBJ//Kart2.obj");
	meshList[GEO_KART2]->textureID = LoadTGA("Image//Kart2.tga");
	meshList[GEO_KART3] = MeshBuilder::GenerateOBJ("Kart3", "OBJ//Kart3.obj");
	meshList[GEO_KART3]->textureID = LoadTGA("Image//Kart3.tga");
	meshList[GEO_KART4] = MeshBuilder::GenerateOBJ("Kart4", "OBJ//Kart4.obj");
	meshList[GEO_KART4]->textureID = LoadTGA("Image//Kart4.tga");
	meshList[GEO_BARRICADE] = MeshBuilder::GenerateOBJ("Barricade", "OBJ//SP2_Barricade.obj");
	meshList[GEO_BARRICADE]->textureID = LoadTGA("Image//SP2_Barricade_Texture_Color.tga");/*
	meshList[GEO_ITEM] = MeshBuilder::GenerateOBJ("Item", "OBJ//item.obj");
	meshList[GEO_ITEM]->textureID = LoadTGA("Image//item.tga");*/

	Car.Init(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0), 0.f);
	Car.setHitBox(meshList[GEO_KART]->XCoord, meshList[GEO_KART]->YCoord, meshList[GEO_KART]->ZCoord);
	Seat.Init(Vector3(10, 0, 0));
	Seat.setHitBox(meshList[GEO_KART2]->XCoord, meshList[GEO_KART2]->YCoord, meshList[GEO_KART2]->ZCoord);
	Kart3.Init(Vector3(0, 0, -200), Vector3(0, 0, -199), Vector3(0, 1, 0), 0.5f);
	Kart3.setHitBox(meshList[GEO_KART3]->XCoord, meshList[GEO_KART3]->YCoord, meshList[GEO_KART3]->ZCoord);
	Kart4.Init(Vector3(0, 0, 10), Vector3(0, 0, 11), Vector3(0, 1, 0), 0.f);
	Kart4.setHitBox(meshList[GEO_KART4]->XCoord, meshList[GEO_KART4]->YCoord, meshList[GEO_KART4]->ZCoord);
	Barricade.Init(Vector3(2.864, 0, 34.103));
	Barricade.setHitBox(meshList[GEO_BARRICADE]->XCoord, meshList[GEO_BARRICADE]->YCoord, meshList[GEO_BARRICADE]->ZCoord);
	Barricade2.Init(Vector3(-2.88, 0, 36.9));
	Barricade2.setHitBox(meshList[GEO_BARRICADE]->XCoord, meshList[GEO_BARRICADE]->YCoord, meshList[GEO_BARRICADE]->ZCoord);

	for (int b = 0; b < Generator.getNumofPiece(); b++)
	{
		switch (Generator.getType(b))
		{
		case 0:
			Generator.getTrackObject()[b].setHitBox(meshList[GEO_TRACK_B_0]->XCoord, meshList[GEO_TRACK_B_0]->YCoord, meshList[GEO_TRACK_B_0]->ZCoord);
			break;
		case 1:
			Generator.getTrackObject()[b].setHitBox(meshList[GEO_TRACK_B_1]->XCoord, meshList[GEO_TRACK_B_1]->YCoord, meshList[GEO_TRACK_B_1]->ZCoord);
			break;
		case 2:
			Generator.getTrackObject()[b].setHitBox(meshList[GEO_TRACK_B_2]->XCoord, meshList[GEO_TRACK_B_2]->YCoord, meshList[GEO_TRACK_B_2]->ZCoord);
			break;
		case 3:
			Generator.getTrackObject()[b].setHitBox(meshList[GEO_TRACK_B_3]->XCoord, meshList[GEO_TRACK_B_3]->YCoord, meshList[GEO_TRACK_B_3]->ZCoord);
			break;
		case 10:
			Generator.getTrackObject()[b].setHitBox(meshList[GEO_TRACK_S_0]->XCoord, meshList[GEO_TRACK_S_0]->YCoord, meshList[GEO_TRACK_S_0]->ZCoord);
			break;
		case 11:
			Generator.getTrackObject()[b].setHitBox(meshList[GEO_TRACK_S_1]->XCoord, meshList[GEO_TRACK_S_1]->YCoord, meshList[GEO_TRACK_S_1]->ZCoord);
			break;
		case 12:
			Generator.getTrackObject()[b].setHitBox(meshList[GEO_TRACK_S_2]->XCoord, meshList[GEO_TRACK_S_2]->YCoord, meshList[GEO_TRACK_S_2]->ZCoord);
			break;
		case 13:
			Generator.getTrackObject()[b].setHitBox(meshList[GEO_TRACK_S_3]->XCoord, meshList[GEO_TRACK_S_3]->YCoord, meshList[GEO_TRACK_S_3]->ZCoord);
			break;
		default: break;
		}
	}

	LapCounter::SetRange(Generator);

	// Text files
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_LIGHT0] = MeshBuilder::GenerateSphere("Light", Color(1, 1, 1), 1, 36, 18);
	meshList[GEO_LIGHT0]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_LIGHT0]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LIGHT0]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_LIGHT0]->material.kShininess = 1.f;

	meshList[GEO_LIGHT4] = MeshBuilder::GenerateOBJ("fire", "OBJ//fire.obj");
	meshList[GEO_LIGHT4]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_LIGHT4]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LIGHT4]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_LIGHT4]->material.kShininess = 1.f;
	meshList[GEO_LIGHT4]->textureID = LoadTGA("Image//fire.tga");

	lights[0].type = Light::LIGHT_SPOT;
	lights[0].position.Set(19.266f, 11.281f, -21.547f);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1.f;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 1.f;
	lights[0].spotDirection.Set(0.f, 1.0f, 0.f);

	Mtx44 Idk;
	Idk.SetToRotation(-45, 1, 0, 0);
	lights[0].spotDirection = Idk * lights[0].spotDirection;
	Idk.SetToRotation(-45, 0, 0, 1);
	lights[0].spotDirection = Idk * lights[0].spotDirection;
	lights[0].spotDirection.Normalize();
	
	lights[1].type = Light::LIGHT_SPOT;
	lights[1].position.Set(-19.266f, 11.281f, 21.547f);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1.f;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(35));
	lights[1].cosInner = cos(Math::DegreeToRadian(25));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.f,1.f,0.f);

	Idk.SetToRotation(45, 1, 0, 0);
	lights[1].spotDirection = Idk * lights[1].spotDirection;
	Idk.SetToRotation(45, 0, 0, 1);
	lights[1].spotDirection = Idk * lights[1].spotDirection;
	lights[1].spotDirection.Normalize();

	lights[2].type = Light::LIGHT_SPOT;
	lights[2].position.Set(-19.266f, 11.281f, -21.547f);
	lights[2].color.Set(1, 1, 1);
	lights[2].power = 1.f;
	lights[2].kC = 1.f;
	lights[2].kL = 0.01f;
	lights[2].kQ = 0.001f;
	lights[2].cosCutoff = cos(Math::DegreeToRadian(35));
	lights[2].cosInner = cos(Math::DegreeToRadian(25));
	lights[2].exponent = 3.f;
	lights[2].spotDirection.Set(0.f, 1.f, 0.f);

	Idk.SetToRotation(-45, 1, 0, 0);
	lights[2].spotDirection = Idk * lights[2].spotDirection;
	Idk.SetToRotation(45, 0, 0, 1);
	lights[2].spotDirection = Idk * lights[2].spotDirection;
	lights[2].spotDirection.Normalize();

	lights[3].type = Light::LIGHT_SPOT;
	lights[3].position.Set(19.266f, 11.281f, 21.547f);
	lights[3].color.Set(1, 1, 1);
	lights[3].power = 1.f;
	lights[3].kC = 1.f;
	lights[3].kL = 0.01f;
	lights[3].kQ = 0.001f;
	lights[3].cosCutoff = cos(Math::DegreeToRadian(35));
	lights[3].cosInner = cos(Math::DegreeToRadian(25));
	lights[3].exponent = 3.f;
	lights[3].spotDirection.Set(0.f, 1.f, 0.f);

	Idk.SetToRotation(-45, 1, 0, 0);
	lights[3].spotDirection = Idk * lights[3].spotDirection;
	Idk.SetToRotation(45, 0, 0, 1);
	lights[3].spotDirection = Idk * lights[3].spotDirection;
	lights[3].spotDirection.Normalize();

	lights[4].type = Light::LIGHT_POINT;
	lights[4].position.Set(-6.276, 7.312, -28.658);
	lights[4].color.Set(1, 1, 1);
	lights[4].power = 0.5f;
	lights[4].kC = 1.f;
	lights[4].kL = 0.01f;
	lights[4].kQ = 0.001f;
	lights[4].cosCutoff = cos(Math::DegreeToRadian(10));
	lights[4].cosInner = cos(Math::DegreeToRadian(0));
	lights[4].exponent = 3.f;
	lights[4].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

	glUniform1i(m_parameters[U_LIGHT2_TYPE], lights[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &lights[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], lights[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], lights[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], lights[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], lights[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], lights[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], lights[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], lights[2].exponent);

	glUniform1i(m_parameters[U_LIGHT3_TYPE], lights[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &lights[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], lights[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], lights[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], lights[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], lights[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], lights[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], lights[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], lights[3].exponent);

	glUniform1i(m_parameters[U_LIGHT4_TYPE], lights[4].type);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &lights[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], lights[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], lights[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], lights[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], lights[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], lights[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], lights[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], lights[4].exponent);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

}

void SceneText::Update(double dt)
{
	finalspeedZ = Car.SpeedZAxis;
	float LSPEED = 25.f;
	if (Application::IsKeyPressed(0x31))
	{
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x32))
	{
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed(0x33))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //Fill mode
	}
	if (Application::IsKeyPressed(0x34))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}
	if (Application::IsKeyPressed(0x35))
	{
		LightOn = true; // Lighting ON
	}
	if (Application::IsKeyPressed(0x36))
	{
		LightOn = false; // Lighting OFF
	}
	if (Application::IsKeyPressed(VK_BACK))
	{
		Quit_Game();
	}
	if (initialspeedZ / finalspeedZ != 1.f && finalspeedZ != 0)
	{
		mciSendString("play Music/car_sound.wav", NULL, 0, NULL);
		initialspeedZ = finalspeedZ;
	}
	else
	{
		mciSendString("stop Music/car_sound.wav", NULL, 0, NULL);
	}
	Car.Collision(Kart3);
	Car.Collision(Kart4);
	Car.Collision(Seat);
	Kart3.Collision(Kart4);
	Kart4.CheckCar();
	Kart3.CheckCar();
	Car.Update(dt);
	Kart3.Update(dt);
	Kart4.Update(dt);
	BestTime.TimeCheck();
	camera.Update(dt, Car);
	FPS = 1.0 / dt;
	ElapsedTime += dt;
	switch (Car.CheckCar())
	{
	case 1:
		Car.Collision(Barricade2);
		break;
	case 2:
		Car.Collision(Barricade);
		break;
	case 3:

		break;
	default:

		break;
	}
}
void SceneText::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y,
		camera.up.z);
	modelStack.LoadIdentity();
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();

	//Position lightPosition_cameraspace = viewStack.Top() * light[0].position;

	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[0], 1,
			&lightDirection_cameraspace.x);
	}
	else if (lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1,
			&lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() *
			lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1,
			&spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1,
			&lightPosition_cameraspace.x);
	}

	if (lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[1], 1,
			&lightDirection_cameraspace.x);
	}
	else if (lights[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1,
			&lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() *
			lights[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1,
			&spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1,
			&lightPosition_cameraspace.x);
	}

	if (lights[2].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[2].position.x, lights[2].position.y, lights[2].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[2], 1,
			&lightDirection_cameraspace.x);
	}
	else if (lights[2].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1,
			&lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() *
			lights[2].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1,
			&spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1,
			&lightPosition_cameraspace.x);
	}

	if (lights[3].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[3].position.x, lights[3].position.y, lights[3].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[3], 1,
			&lightDirection_cameraspace.x);
	}
	else if (lights[3].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1,
			&lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() *
			lights[3].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1,
			&spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[4].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1,
			&lightPosition_cameraspace.x);
	}

	if (lights[4].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[4].position.x, lights[4].position.y, lights[4].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[4], 1, &lightDirection_cameraspace.x);
	}

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	//RenderMesh(meshList[GEO_AXES], false);
	SceneText::RenderSkybox(modelStack, projectionStack, viewStack, MVP);
	//SceneText::RenderStadium(modelStack, projectionStack, viewStack, MVP);
	modelStack.PushMatrix();
		modelStack.Translate(Car.getPosition().x, Car.getPosition().y, Car.getPosition().z);
		modelStack.Rotate(Car.getRotateValue(), 0, 1, 0);
		RenderMesh(meshList[GEO_KART], LightOn);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(Seat.getPosition().x, Seat.getPosition().y, Seat.getPosition().z);
		RenderMesh(meshList[GEO_KART2], LightOn);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(Kart3.getPosition().x, Kart3.getPosition().y, Kart3.getPosition().z);
		modelStack.Rotate(Kart3.getRotateValue(), 0, 1, 0);
		RenderMesh(meshList[GEO_KART3], LightOn);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(Kart4.getPosition().x, Kart4.getPosition().y, Kart4.getPosition().z);
		modelStack.Rotate(Kart4.getRotateValue(), 0, 1, 0);
		RenderMesh(meshList[GEO_KART4], LightOn);
	modelStack.PopMatrix();
	for (int Index = 0; Index < Generator.getNumofPiece(); Index++)
	{
		modelStack.PushMatrix();
			modelStack.Translate(Generator.getTrackObject()[Index].getPosition().x, Generator.getTrackObject()[Index].getPosition().y, Generator.getTrackObject()[Index].getPosition().z);
			modelStack.Rotate(Generator.getRotateValue()[Index], 0, 1, 0);
			switch (Generator.getType(Index))
			{
			case 0:
				RenderMesh(meshList[GEO_TRACK_B_0], LightOn);
				break;
			case 1:
				RenderMesh(meshList[GEO_TRACK_B_1], LightOn);
				break;
			case 2:
				RenderMesh(meshList[GEO_TRACK_B_2], LightOn);
				break;
			case 3:
				RenderMesh(meshList[GEO_TRACK_B_3], LightOn);
				break;
			case 10:
				RenderMesh(meshList[GEO_TRACK_S_0], LightOn);
				break;
			case 11:
				RenderMesh(meshList[GEO_TRACK_S_1], LightOn);
				break;
			case 12:
				RenderMesh(meshList[GEO_TRACK_S_2], LightOn);
				break;
			case 13:
				RenderMesh(meshList[GEO_TRACK_S_3], LightOn);
				break;
			default: break;
			}
		modelStack.PopMatrix();
	}/*
	modelStack.PushMatrix();
		RenderMesh(meshList[GEO_ITEM], LightOn);
	modelStack.PopMatrix();*/
	switch (Car.CheckCar())
	{
	case 1:
		modelStack.PushMatrix();
			modelStack.Translate(Barricade2.getPosition().x, Barricade2.getPosition().y, Barricade2.getPosition().z);
			RenderMesh(meshList[GEO_BARRICADE], LightOn);
		modelStack.PopMatrix();
		break;
	case 2:
		modelStack.PushMatrix();
			modelStack.Translate(Barricade.getPosition().x, Barricade.getPosition().y, Barricade.getPosition().z);
			RenderMesh(meshList[GEO_BARRICADE], LightOn);
		modelStack.PopMatrix();
		break;
	case 3:

		break;
	default:

		break;
	}
	SceneText::RenderInformation(modelStack, projectionStack, viewStack, MVP);
}
void SceneText::RenderStadium(MS &modelStack, MS &projectionStack, MS &viewStack, Mtx44 &MVP)
{
	float SKYBOXSIZE = 1000.f;
	for (int a = 0; a < 4; a++)
	{
		modelStack.PushMatrix();
			modelStack.Translate(lights[a].position.x, lights[a].position.y, lights[a].position.z);
			modelStack.Scale(0.58f, 0.58f, 0.58f);
			RenderMesh(meshList[GEO_LIGHT0], false);
		modelStack.PopMatrix();
	}
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0, 0.f);
		modelStack.Scale(SKYBOXSIZE/ 2.f, 1, SKYBOXSIZE / 2.f);
		RenderMesh(meshList[GEO_GROUND], LightOn);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.PushMatrix();
			modelStack.Scale(1.75f, 1, 1.75f);
			RenderMesh(meshList[GEO_TRACK], LightOn);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
			modelStack.Translate(-6.276f, 0.f, -28.658f);
			RenderMesh(meshList[GEO_TORCH], LightOn);
		modelStack.PopMatrix();
		RenderMesh(meshList[GEO_SEAT], LightOn);
		RenderMesh(meshList[GEO_SEATCIRCULAR], LightOn);
		modelStack.PushMatrix();
			modelStack.Rotate(180, 0, 1, 0);
			RenderMesh(meshList[GEO_SEATCIRCULAR], LightOn);
		modelStack.PopMatrix();
		RenderMesh(meshList[GEO_LIGHTOBJ], LightOn);
	modelStack.PopMatrix(); 
	switch ((SwitchField - 1) % 3)
	{
	case 0:
		RenderMesh(meshList[GEO_MISC], LightOn);
		break;
	case 1:
		RenderMesh(meshList[GEO_GOAL], LightOn);
		break;
	case 2:
		RenderMesh(meshList[GEO_FIELDGOAL], LightOn);
		break;
	default:
		RenderMesh(meshList[GEO_MISC], LightOn);
		break;
	}
	for (int Num = 0; Num < 7; Num++)
	{
		modelStack.PushMatrix();
			modelStack.Translate(CameraOBJ[Num].getX(), CameraOBJ[Num].getY(), CameraOBJ[Num].getZ());
			modelStack.Rotate(CameraOBJ[Num].getrotateX(), 1, 0, 0);
			modelStack.Rotate(CameraOBJ[Num].getrotateY(), 0, 1, 0);
			modelStack.Rotate(CameraOBJ[Num].getrotateZ(), 0, 0, 1);
			RenderMesh(meshList[GEO_CAMERA], LightOn);
		modelStack.PopMatrix();
	}
	if (Fire)
	{
		RenderMesh(meshList[GEO_LIGHT4], false);
	}
	modelStack.PushMatrix();
	if (camera.Shoot)
	{
		modelStack.PushMatrix();
			modelStack.Rotate(ballRY, 0, 1, 0);
			modelStack.PushMatrix();
				if ((SwitchField - 1) % 3 == 1)
				{
					modelStack.Translate(0, 0.7f, ballT);
					RenderMesh(meshList[GEO_SOCCERBALL], LightOn);
				}
				else if ((SwitchField - 1) % 3 == 2)
				{
					modelStack.Translate(0, ballT / 4.0f, ballT);
					RenderMesh(meshList[GEO_FOOTBALL], LightOn);
				}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
				modelStack.Translate(0, 0.6f, 0);
				modelStack.Scale(2.f, 1.f, 9.f);
				RenderMesh(meshList[GEO_QUAD], LightOn);
			modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
}

void SceneText::RenderInformation(MS &modelStack, MS &projectionStack, MS &viewStack, Mtx44 &MVP)
{
	double InitialTime = 90.0;
	double LapTime = 0.0;
	InitialTime -= ElapsedTime;
	LapTime += ElapsedTime;
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + std::to_string(FPS), Color(1, 0, 0), 1, 2, 59);
	RenderTextOnScreen(meshList[GEO_TEXT], "Lap:" + std::to_string(Car.LapCheck.getCurrentLap()) + "/3", Color(1, 0, 0), 2, 1, 58 / 2);
	RenderTextOnScreen(meshList[GEO_TEXT], "Checkpoint num:" + std::to_string(Car.LapCheck.getCurrentCheckPoint()) , Color(1, 0, 0), 2, 1, 56 / 2);
	if (InitialTime > 0)
	{
		if (InitialTime < 10)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Time Left:" + std::to_string(InitialTime), Color(1, 0, 0), 2, 20, 58 / 2);
		}
		else if (InitialTime >= 10 && InitialTime < 100)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Time Left:" + std::to_string(InitialTime), Color(1, 0, 0), 2, 21, 58 / 2);
		}
	}
	if (LapTime < 10)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Time:" + std::to_string(LapTime), Color(1, 0, 0), 2, 27, 48 / 2);
	}
	else if ((LapTime >= 10 && LapTime < 100))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Time:" + std::to_string(LapTime), Color(1, 0, 0), 2, 26, 48 / 2);
	}
}

void SceneText::RenderSkybox(MS &modelStack, MS &projectionStack, MS &viewStack, Mtx44 &MVP)
{
	float SKYBOXSIZE = 1500.f;
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, SKYBOXSIZE / 2.0f - 0.1f);
		modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
		modelStack.Rotate(90, 1, 0, 0);
		RenderMesh(meshList[GEO_FRONT], false); 
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, -(SKYBOXSIZE / 2.0f - 0.1f));
		modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(SKYBOXSIZE / 2.0f - 0.1f, 0.f, 0.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-(SKYBOXSIZE / 2.0f - 0.1f), 0.f, 0.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	modelStack.Rotate(270, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0.f, SKYBOXSIZE / 2.0f - 0.1f, 0.f);		
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	modelStack.Rotate(0, 0, 1, 0);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -(SKYBOXSIZE / 2.0f - 0.1f), 0.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void SceneText::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
			Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneText::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneText::Exit()
{
	glDeleteProgram(m_programID);
}

void SceneText::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE,
			&modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneText::Quit_Game()
{
	closegame = true;
	nextgame = false;
}

void SceneText::GO_Game()
{
	nextgame = true;
	closegame = false;
}

bool SceneText::prev_state()
{
	return closegame;
}

bool SceneText::next_state()
{
	return nextgame;
}