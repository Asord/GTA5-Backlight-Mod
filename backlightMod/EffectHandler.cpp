#include "EffectHandler.h"

char COMPORT[] = "\\\\.\\COM4";
EffectHandler* EffectHandler::instance = nullptr;
UINT8 EffectHandler::nbInstances = 0;

void EffectHandler::setHeader()
{
	if (this->buffer != nullptr)
	{
		uint8_t nbLeds = this->bufferSize / 3;
		uint8_t _h[] = {
			'A', 'd', 'a',
			uint8_t((nbLeds - 1) >> 8),
			uint8_t((nbLeds - 1) & 0xff),
			uint8_t(_h[3] ^ _h[4] ^ 0x55)
		};
		memcpy(this->buffer, _h, 6);
	}
}

EffectHandler::EffectHandler(UINT16 bufferSize): serial(COMPORT)
{
	EffectHandler::nbInstances = 0;

	this->buffer      = new uint8_t[6 + bufferSize];
	this->bufferSize  =                  bufferSize;

	this->effectColor = Color(0, 0, 0);
	this->framePos    = 0;

	this->isEffectOverrided = false;
	this->overridenFrom = 0;
	this->overridenLengthAfterCursor = 0;
	this->overridenCursor = 0;
	this->overrideColor = Color::Black;

	switchEffect(&Effects::Default);

	setHeader();
}


EffectHandler * EffectHandler::getInstance(UINT16 bufferSize)
{
	if (EffectHandler::instance == nullptr)
		EffectHandler::instance = new EffectHandler(bufferSize);
	
	EffectHandler::nbInstances++;

	return EffectHandler::instance;
}

EffectHandler::~EffectHandler()
{
	if (EffectHandler::nbInstances != 1)
	{
		EffectHandler::nbInstances--;
	}
	else
	{
		unlock();
		EffectHandler::instance = nullptr;
	}
}

void EffectHandler::unlock()
{
	if (this->buffer != nullptr)
		delete[6 + bufferSize] this->buffer;

	this->serial.disconnect();
}

void EffectHandler::update()
{
	if (this->effect->ID == 0)
	{
		memset(&this->buffer[6], 0, this->bufferSize);
	}
	else if (this->buffer != nullptr)
	{
		if (this->effect->ID < 128)
		{
			uint16_t frameSize = this->effect->data[this->framePos].size();
			if (frameSize > this->bufferSize) frameSize = this->bufferSize;

			for (int i = 0; i < frameSize; i++)
			{
				this->buffer[6 + i] = this->effect->data[this->framePos][i];
			}

			if (frameSize < this->bufferSize)
			{
				memset(&buffer[6 + frameSize], 0, bufferSize);
			}

			if (this->isEffectOverrided)
			{
				for (size_t i = this->overridenFrom; i < this->overridenCursor; ++i)
				{
					buffer[6 + 3*i + 0] = this->overrideColor.getRed();
					buffer[6 + 3*i + 1] = this->overrideColor.getGreen();
					buffer[6 + 3*i + 2] = this->overrideColor.getBlue();
				}
				memset(&buffer[6 + 3 * this->overridenCursor], 0, this->overridenLengthAfterCursor * 3);
			}

			this->framePos++;
			if (this->framePos == this->effect->data.size()) this->framePos = 0;
		}
		else // effect->ID >= 128
		{
			Color color = this->effectColor * Color(effect->data[0]);
			for (uint16_t i = 0; i < this->bufferSize; i += 3)
			{
				this->buffer[6 + i + 0] = color.getRed();
				this->buffer[6 + i + 1] = color.getGreen();
				this->buffer[6 + i + 2] = color.getBlue();
			}
		}
	}
	this->serial.writeSerialPort(this->buffer, 6 + this->bufferSize);
}

void EffectHandler::clear()
{
	this->switchEffect(&Effects::Default);

	if (this->buffer != nullptr)
	{
		memset(&this->buffer[6], 0, this->bufferSize);
		this->serial.writeSerialPort(this->buffer, 6 + this->bufferSize);
	}
}

void EffectHandler::switchEffect(Effect * e)
{
	if (this->isEffectOverrided)
		this->isEffectOverrided = false;

	this->effect = e;
	this->framePos = 0;
	this->effectColor = Color(0, 0, 0);

}

void EffectHandler::setEffectColor(Color & color)
{
	this->effectColor = color;
}

Color EffectHandler::getEffectColor(Color & color)
{
	return this->effectColor;
}

uint8_t EffectHandler::getCurrentEffectID()
{
	return this->effect->ID;
}

uint16_t EffectHandler::getCurrentEffectDeltaT()
{
	return this->effect->speed;
}


void EffectHandler::overrideEffectWithSingleColor(uint16_t basePos, uint16_t length, uint16_t currentPos, Color color)
{
	if (currentPos <= length)
	{
		this->isEffectOverrided = true;

		this->overrideColor = color.coef(1.0f, 0.42f, 0.3f);
		this->overridenFrom = basePos;
		this->overridenCursor = basePos + currentPos;
		this->overridenLengthAfterCursor = basePos + length - this->overridenCursor;
	}
}
