#include "EffectReader.h"

char COMPORT[] = "\\\\.\\COM4";
EffectReader* EffectReader::instance = nullptr;


EffectReader::EffectReader(): serial(COMPORT)
{
		n_speed = 0;
		n_framePos = 0;

		p_effect = nullptr;
		p_buffer = nullptr;

		currentLoadedEffect = 0;
}

EffectReader* EffectReader::getInstance()
{
	if (EffectReader::instance == nullptr)
		EffectReader::instance = new EffectReader();

	return EffectReader::instance;
}

EffectReader::~EffectReader()
{
	finish();
	EffectReader::instance = nullptr;
}

void EffectReader::finish()
{
	if (p_buffer != nullptr)
		delete[6 + p_effect->framelen] p_buffer;

	serial.disconnect();
}


void EffectReader::switchEffect(generic_effect * effect, bool forceSwitch)
{
	if (effect->effectID == currentLoadedEffect && !forceSwitch) 
		return;

	if (p_buffer != nullptr)
	{
		if (effect->framelen != p_effect->framelen)
		{
			delete[6 + effect->framelen] p_buffer;
			p_buffer = new UBYTE[6 + effect->framelen];

			setHeader(p_effect->framelen / 3);
		}
	}

	p_effect = effect;

	currentLoadedEffect = p_effect->effectID;
	n_speed = p_effect->speed;
	n_framePos = 0;
}

void EffectReader::setHeader(UINT8 nbLeds)
{
	if (p_buffer != nullptr)
	{
		UBYTE _h[] = {
			'A', 'd', 'a',
			UBYTE((nbLeds - 1) >> 8),
			UBYTE((nbLeds - 1) & 0xff),
			UBYTE(p_buffer[3] ^ p_buffer[4] ^ 0x55)
		};
		memcpy(p_buffer, _h, 6);
	}
}


void EffectReader::update()
{
	if (p_effect != nullptr && p_buffer != nullptr)
	{
		UINT32 shift = p_effect->framelen*n_framePos;

		memcpy(&this->p_buffer[6], &p_effect->data[shift], p_effect->framelen);

		n_framePos++;
		if (n_framePos == p_effect->nbframes)
			n_framePos = 0;

		serial.writeSerialPort(this->p_buffer, 6 + p_effect->framelen);
	}
}

void EffectReader::clear()
{
	if (p_buffer != nullptr && p_effect != nullptr)
	{
		memset(&p_buffer[6], 0, p_effect->framelen);
		serial.writeSerialPort(this->p_buffer, 6 + p_effect->framelen);
	}
	currentLoadedEffect = 0;
	n_speed = 0;
}


