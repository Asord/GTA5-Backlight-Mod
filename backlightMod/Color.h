#ifndef COLOR_SLP_COLOR_H
#define COLOR_SLP_COLOR_H

#include <iostream>
#include <vector>

class Color
{
public:
    static Color Red;
    static Color Green;
    static Color Blue;
    static Color Yellow;
    static Color Cyan;
    static Color Magenta;
    static Color White;
    static Color Black;

protected:
    union {
        struct { uint8_t  _red, _green, _blue, _alpha;};
        uint32_t _color;
    };

public:
    Color();
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    Color(uint8_t red, uint8_t green, uint8_t blue);
    Color(uint32_t color);
	Color(std::vector<uint8_t>& v);

    uint8_t getRed() const;
    void setRed(uint8_t red);

    uint8_t getGreen() const;
    void setGreen(uint8_t green);

    uint8_t getBlue() const;
    void setBlue(uint8_t blue);

    uint8_t getAlpha() const;
    void setAlpha(uint8_t alpha);

    uint32_t getColor() const;
    void setColor(uint32_t color);

    Color& fromHue(float hue);
    Color& fromHSV(float hue, float saturation, float value);

    void toHSV(float* hsv) const;

    Color& random(int seed=0);
    Color& randomColor(float min=0.0f, float max=360.0f, int seed=0);

    Color& black();
    Color& white();
    Color& gray(uint8_t factor);

    Color& invert();
    Color& grayscale();

    Color& coef(float coefr, float coefg, float coefb);

    Color& operator++();
    Color& operator--();

    Color operator+(const Color& rhs) const;
    Color& operator+=(const Color& rhs);

    Color operator-(const Color& rhs) const;
    Color& operator-=(const Color& rhs);

    Color operator*(const float& rhs) const;
    Color& operator*=(const float& rhs);

	Color operator*(const Color& rhs) const;
	Color& operator*=(const Color& rhs);

    Color operator/(const float& rhs) const;
    Color& operator/=(const float& rhs);

    Color operator%(const unsigned char& rhs) const;
    Color& operator%=(const unsigned char& rhs);

    bool operator==(const Color &rhs) const;
    bool operator!=(const Color &rhs) const;

};

#define colorVector std::vector<Color>

#endif //COLOR_SLP_COLOR_H
