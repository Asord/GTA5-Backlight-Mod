#include "script.h"
#include <sstream>


void ScriptMain()
{
	configHandler handler;

#ifdef _DEBUG
	char conf[100];

	std::cin.getline(conf, 100);
	if (strcmp(conf, "pol0") == 0) wantedLevel = 0;
	if (strcmp(conf, "pol1") == 0) wantedLevel = 1;
	if (strcmp(conf, "pol2") == 0) wantedLevel = 2;
	if (strcmp(conf, "pol3") == 0) wantedLevel = 3;
	if (strcmp(conf, "pol4") == 0) wantedLevel = 4;
	if (strcmp(conf, "pol5") == 0) wantedLevel = 5;
	if (strcmp(conf, "dead") == 0) beingDead = true;
	if (strcmp(conf, "ndead") == 0) beingDead = false;
	if (strcmp(conf, "arr") == 0) beingArrested = true;
	if (strcmp(conf, "narr") == 0) beingArrested = false;

	if (strcmp(conf, "sab") == 0) specialAbility = true;
	if (strcmp(conf, "nsab") == 0) specialAbility = false;
#endif

	while (true)
	{

		handler.update();
		WAIT(handler.getDeltaT());
	}
}

uint16_t configHandler::getDeltaT()
{
	return deltaTime;
}

configHandler::configHandler()
{
	player         = PLAYER::PLAYER_ID();
	ped            = PLAYER::PLAYER_PED_ID();
	deltaTime      = Effects::Default.speed;
	previousEffect = effects::none;
	serialHandler  = EffectHandler::getInstance(NBLEDS * 3);

}

void configHandler::switchEffectPlayerAbility(Color& color)
{
	if (ENTITY::DOES_ENTITY_EXIST(ped))
	{
		Hash model = ENTITY::GET_ENTITY_MODEL(ped);

		if      (model == GAMEPLAY::GET_HASH_KEY((char*)"player_zero")) color = Color::Blue;
		else if (model == GAMEPLAY::GET_HASH_KEY((char*)"player_one"))  color = Color::Green;
		else if (model == GAMEPLAY::GET_HASH_KEY((char*)"player_two"))  color = Color(255, 80, 0);
		else                                                            color = Color::White;
	}
}

void configHandler::update()
{
	ped = PLAYER::PLAYER_PED_ID();

	// dead
	if (PLAYER::IS_PLAYER_DEAD(player))
	{
		if (previousEffect != effects::dead)
		{
			serialHandler->switchEffect(&Effects::Color);
			deltaTime = serialHandler->getCurrentEffectDeltaT();
				
			serialHandler->setEffectColor(Color::Red);

			previousEffect = effects::dead;
		}
	}
	// arrested
	else if (PLAYER::IS_PLAYER_BEING_ARRESTED(player, true))
	{
		if (previousEffect != effects::arrested)
		{
			serialHandler->switchEffect(&Effects::Color);
			deltaTime = serialHandler->getCurrentEffectDeltaT();

			serialHandler->setEffectColor(Color::Blue);

			previousEffect = effects::arrested;

		}
	}
	// use ability
	else if (PLAYER::IS_SPECIAL_ABILITY_ACTIVE(player))
	{
		if (previousEffect != effects::ability)
		{

			serialHandler->switchEffect(&Effects::Color);
			deltaTime = serialHandler->getCurrentEffectDeltaT();

			Color color;
			switchEffectPlayerAbility(color);
			serialHandler->setEffectColor(color);

			previousEffect = effects::ability;

		}
	}
	else if (PED::IS_PED_IN_ANY_VEHICLE(this->ped, 0))
	{
		vehicle = PED::GET_VEHICLE_PED_IS_USING(this->ped);
		if (VEHICLE::IS_VEHICLE_SIREN_ON(vehicle))
		{
			if (previousEffect != effects::siren)
			{
				serialHandler->switchEffect(&Effects::Police);
				previousEffect = effects::siren;
				deltaTime = serialHandler->getCurrentEffectDeltaT() - 200;
			}
		}
		else
		{
			if (previousEffect == effects::siren)
			{
				serialHandler->switchEffect(&Effects::Default);
				previousEffect = effects::none;
				deltaTime = serialHandler->getCurrentEffectDeltaT();
			}
		}
	}
	// is wanted
	else if (PLAYER::GET_PLAYER_WANTED_LEVEL(player) > 0)
	{
		if (previousEffect != effects::wanted)
		{
			serialHandler->switchEffect(&Effects::Police);
			previousEffect = effects::wanted;
		}

		deltaTime = serialHandler->getCurrentEffectDeltaT() - (40 * PLAYER::GET_PLAYER_WANTED_LEVEL(player));
	}
	else
	{
		if (previousEffect != effects::none)
		{
			serialHandler->switchEffect(&Effects::Default);
			deltaTime = serialHandler->getCurrentEffectDeltaT();

			previousEffect = effects::none;
		}
	}


	serialHandler->update();
}