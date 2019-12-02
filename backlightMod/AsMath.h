#pragma once
#include <cmath>
#include <random>

namespace Asemco
{

	#define randRange(n_min, n_max) rand() % (n_max - n_min + 1) + n_min

	inline void normalize(float & num1, float & num2)
    {
        if (num1 > num2)
        {
            num2 = (1.0f / num1)*num2;
            num1 = 1.0f;
        }
        else
        {
            num1 = (1.0f / num2)*num1;
            num2 = 1.0f;
        }
    }

	inline float f3min(float f1, float f2, float f3)
    {
        float tmp = (float)fmin(f1, f2);
        return (float)fmin(tmp, f3);
    }

	inline float f3max(float f1, float f2, float f3)
    {
        float tmp = (float)fmax(f1, f2);
        return (float)fmax(tmp, f3);
    }

	inline float ufmodf(float fnum, float fmod)
    {
        float r = fmodf(fnum, fmod);
        return r = (r < 0) ? (fmod - r * -1.0f) : r;
    }


    inline unsigned char floatToChar(float f){
        if(f < 0)     return 0;
        if( f > 255 ) return 255;
        return (char)f;
	}

}