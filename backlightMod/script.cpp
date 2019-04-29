#include "script.h"
#include "ledseffects/effect_police.h"
#include "ledseffects/effect_mono.h"
#include "ledseffects/EffectReader.h"

#define setcolor(red, gre, blu) col_red = red; col_gre = gre; col_blu = blu;
#define color col_red, col_gre, col_blu

#define isNotActif(_effect) _effect.effectID != effectReader->currentLoadedEffect
#define notLast(id) lastMonoCase != monoEffectID::id
#define effectSwitcher(_effect) \
	effect = dynamic_cast<generic_effect*>(&_effect); \
	effectReader->switchEffect(effect, true);


int main()
{
	Player player = PLAYER::PLAYER_ID(); 
	
	Ped   player_ped;
	UINT8 player_wantedLevel = 0;
	bool  player_isInVehicle = false;

	int col_red = 0; int col_gre = 0; int col_blu = 0;

	EffectReader*   effectReader = EffectReader::getInstance();

	generic_effect* effect;
	effect_police   effectPolice  = effect_police();
	effect_mono     effectAbility = effect_mono();

	monoEffectID lastMonoCase = monoEffectID::NONE;

	while (true)
	{

		// IS PLAYER IN VEHICLE TEST
		player_ped = PLAYER::PLAYER_PED_ID();
		if (ENTITY::DOES_ENTITY_EXIST(player_ped))
			player_isInVehicle = PED::IS_PED_IN_ANY_VEHICLE(player_ped, false);
		else player_isInVehicle = false;

		player_wantedLevel = PLAYER::GET_PLAYER_WANTED_LEVEL(player);


		/* TESTS */
		if (PLAYER::IS_PLAYER_DEAD(player))
		{
			if (notLast(DEAD) && isNotActif(effectAbility))
			{
				setcolor(0x80, 0x00, 0x00);
				effectAbility.setColor(color);

				effectSwitcher(effectAbility);
			}
		}

		else if (PLAYER::IS_PLAYER_BEING_ARRESTED(player, true))
		{
			if (notLast(ARESTED) && isNotActif(effectAbility))
			{
				setcolor(0x00, 0x80, 0x00);
				effectAbility.setColor(color);

				effectSwitcher(effectAbility);
			}
		}

		else if (PLAYER::IS_SPECIAL_ABILITY_ACTIVE(player))
		{
			if (notLast(ABILITY) && isNotActif(effectAbility))
			{
				switchEffectPlayerAbility(player_ped, color);
				effectAbility.setColor(color);

				effectSwitcher(effectAbility);
			}
		}

		else if (player_wantedLevel > 0)
		{	
			if (isNotActif(effectPolice))
			{
				effectSwitcher(effectPolice);
			}
			effectReader->n_speed = effectPolice.speed - (75 * player_wantedLevel);
		}

		else if (player_isInVehicle)
		{
			if (notLast(NEON) && isNotActif(effectAbility))
			{
				switchEffectPlayerNeon(player_ped, color);
				effectAbility.setColor(color);

				effectSwitcher(effectAbility);
			}
		}

		else
		{
			if (effectReader->currentLoadedEffect != 0)
			{
				effectReader->clear();
			}
		}

		effectReader->update();
		WAIT(effectReader->n_speed);
	}
}


void switchEffectPlayerNeon(Ped playerPed, int& r, int& g, int& b)
{
	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
	
	Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
	bool hasNeon = VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 0);

	if (hasNeon)
	{
		r = 0; g = 0; b = 0;
		VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, &r, &b, &g);
	}
}


void switchEffectPlayerAbility(Ped playerPed, int& r, int& g, int& b)
{
	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	Hash model = ENTITY::GET_ENTITY_MODEL(playerPed);
	if (model == GAMEPLAY::GET_HASH_KEY((char*)"player_zero"))
	{
		r = 0; b = 0; g = 255;  return;
	}
	if (model == GAMEPLAY::GET_HASH_KEY((char*)"player_one"))
	{
		r = 0; b = 255;  g = 0; return;
	}
	if (model == GAMEPLAY::GET_HASH_KEY((char*)"player_two"))
	{
		r = 255; b = 80; g = 0; return;
	}
	
	r = 255; g = 255; b = 255;

		
}

void ScriptMain()
{
	main();
}
