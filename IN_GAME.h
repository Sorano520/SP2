#ifndef IN_GAME_H
#define IN_GAME_H

#include "Scene.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Player.h"
#include "Light.h"
#include "Vehicle.h"
#include "GameObject.h"
#include "Environment.h"
#include "AIKart.h"

class IN_GAME : public Scene
{
public:
	IN_GAME();
	~IN_GAME();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	virtual bool prev_state();
	virtual bool next_state();
	MS modelStack, viewStack, projectionStack;
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		//	GEO_SPHERE,
		GEO_QUAD,
		GEO_MENU,
		GEO_KART,
		GEO_KART2,
		GEO_KART3,
		GEO_KART4,
		GEO_TEXT,
		NUM_GEOMETRY,
	};
	// New to Scene 2
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		U_LIGHT4_POSITION,
		U_LIGHT4_COLOR,
		U_LIGHT4_POWER,
		U_LIGHT4_KC,
		U_LIGHT4_KL,
		U_LIGHT4_KQ,
		U_LIGHT4_TYPE,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT4_COSINNER,
		U_LIGHT4_EXPONENT,

		U_NUMLIGHTS,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
	void RenderMenu(MS &modelStack, MS &projectionStack, MS &viewStack, Mtx44 &MVP);

	bool CarMenu;
	bool InMenu;

private:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	// New to scene 2
	unsigned m_parameters[U_TOTAL];
	bool LightOn;
	Mesh* meshList[NUM_GEOMETRY];
	Light lights[5];
	void RenderMesh(Mesh *mesh, bool enableLight);

	bool MenuChange;

	double ElapsedTime;
	double BounceTime;
	bool closegame = true;
	bool nextgame = true;

	int rotateAngle;

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void GO_Game();
	void Quit_Game();

	Player Car;
	AIKart Kart3, Kart4;
	Environment Seat;
};

#endif