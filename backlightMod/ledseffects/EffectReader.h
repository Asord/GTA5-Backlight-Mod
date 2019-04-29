#pragma once
#include "Serial.h"
#include "generic_effect.h"


class EffectReader
{
public:
	UINT16 n_speed;
	UINT8 currentLoadedEffect;

private:
	PUBYTE p_buffer;
	UINT16 n_framePos;

	Serial serial;
	generic_effect* p_effect;

	// singleton constructor
	static EffectReader* instance;
	EffectReader();

public:
	static EffectReader* getInstance();
	~EffectReader();
	void finish();

	void switchEffect(generic_effect* effect, bool force = true);
	void setHeader(UINT8 nbLeds);

	void update();
	void clear();

};
