#pragma once

typedef unsigned char  UBYTE;
typedef unsigned char* PUBYTE;

struct generic_effect
{
	UINT8 effectID;
	UINT16 speed;
	UINT16 framelen;
	UINT16 nbframes;
	PUBYTE data;
};