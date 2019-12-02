#pragma once

#ifdef _DEBUG
typedef int Player;
typedef int Ped;
typedef unsigned long Hash;
#define WAIT(t) Sleep(t);

static int wantedLevel = 0;
static int specialAbility = false;
static int beingArrested = false;
static int beingDead = false;

namespace PLAYER
{
	inline int PLAYER_ID() { return 1; }
	inline int PLAYER_PED_ID() { return 2; }

	inline bool IS_PLAYER_DEAD(int p) { return beingDead; }
	inline bool IS_PLAYER_BEING_ARRESTED(int p, bool t) { return beingArrested; }
	inline bool IS_SPECIAL_ABILITY_ACTIVE(int p) { return specialAbility; }
	inline int  GET_PLAYER_WANTED_LEVEL(int p) { return wantedLevel; }

};

namespace ENTITY
{
	inline bool DOES_ENTITY_EXIST(int e) { return true; }
	inline Hash GET_ENTITY_MODEL(int p) { return 0xff000001; }

};

namespace GAMEPLAY
{
	inline Hash GET_HASH_KEY(char* model) { return 0xff000001; }
};

#else
#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"
#include "..\..\inc\main.h"
#endif

#include "EffectHandler.h"
#include "Color.h"
#include <string>

#define NBLEDS 21

enum effects
{
	dead,
	arrested,
	ability,
	siren,
	wanted,
	none
};

void ScriptMain();

class configHandler
{
private:

	Player          player;
	Ped             ped;
	Vehicle         vehicle;
	uint16_t        deltaTime;
	effects         previousEffect;
	EffectHandler*  serialHandler;



public:
	configHandler();

	void switchEffectPlayerAbility(Color& color);
	void update();
	
	uint16_t getDeltaT();
};