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

	// overrides parametters
	bool isEffectOverrided;
	size_t overridenFrom;
	size_t overridenLengthAfterCursor;
	size_t overridenCursor;
	Color overrideColor;



	// singleton
private:
	static EffectHandler* instance;
	static UINT8          nbInstances;
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

	void overrideEffectWithSingleColor(uint16_t basePos, uint16_t length, uint16_t currentPos, Color color);
};