#pragma once

#include <set>
#include "Hacks.h"
#include "SDK.h"
#include "Interfaces.h"
#include "Entities.h"

struct Radar
{
	enum EntityShape_t : int
	{
		SHAPE_CIRCLE,
		SHAPE_SQUARE,
		SHAPE_TRIANGLE,
		SHAPE_TRIANGLE_UPSIDEDOWN
	};
	Color GetRadarPlayerColor(IClientEntity* player);
	void RenderWindow();
	void InGameRadar(IClientEntity* player);
	void BeginFrame();
	/////////////////////////////////////
	bool enabled; // initialize
	float zoom, iconsScale; //some random floats lol
	bool enemies, friendly, bomb, defuser, Ingame; //some random checks
	Color enemyColor, friendlyColor, bombColor, bombDefusingColor, defuserColor; //some random colors
};

enum class ObserverMode_t : int
{
	OBS_MODE_NONE = 0,
	OBS_MODE_DEATHCAM = 1,
	OBS_MODE_FREEZECAM = 2,
	OBS_MODE_FIXED = 3,
	OBS_MODE_IN_EYE = 4,
	OBS_MODE_CHASE = 5,
	OBS_MODE_ROAMING = 6
};
