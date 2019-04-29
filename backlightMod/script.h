#pragma once

#ifndef _DEBUG
#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"

#include "..\..\inc\main.h"
#endif

enum monoEffectID { DEAD, ARESTED, NEON, ABILITY, NONE };

void switchEffectPlayerNeon(Ped, int&, int&, int&);
void switchEffectPlayerAbility(Ped, int&, int&, int&);
void ScriptMain();