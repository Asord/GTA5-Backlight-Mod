#pragma once
#include "Serial.h"
#include "effects.h"
#include "Color.h"

// 000->127 => effects effect
// 128->255 => prog effect

class EffectHandler
{
public:
	// effect vars
	Effect* effect;
	uint8_t framePos;
	Color   effectColor;

	// serial vars
	Serial serial;
	UINT8* buffer;
	UINT16  bufferSize;


	// singleton
private:
	static EffectHandler* instance;
	EffectHandler(UINT16 bufferSize);
public:
	static EffectHandler* getInstance(UINT16 bufferSize = 0);
	~EffectHandler();

private:
	void setHeader();

public:
	void unlock();

	// effects methods
	void update();
	void clear();
	void switchEffect(Effect* e);

	void setEffectColor(Color& color);
	Color getEffectColor(Color& color);

	uint8_t getCurrentEffectID();
	uint16_t getCurrentEffectDeltaT();
};