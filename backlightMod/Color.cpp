//
// Created by Killian on 11/11/2019.
//

#include "Color.h"
#include "AsMath.h"
#include <time.h>

Color Color::Red(255, 0, 0);
Color Color::Green(0, 255, 0);
Color Color::Blue(0, 0, 255);
Color Color::Yellow(255, 255, 0);
Color Color::Cyan(0, 255, 255);
Color Color::Magenta(255, 0, 255);
Color Color::White(255, 255, 255);
Color Color::Black(0, 0, 0);



Color::Color() {
    this->_color = 0xff000000;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    this->_red = red;
    this->_green = green;
    this->_blue = blue;
    this->_alpha = alpha;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
    this->_red = red;
    this->_green = green;
    this->_blue = blue;
    this->_alpha = 255;
}

Color::Color(uint32_t color) {
    this->_color = color;
}

Color::Color(std::vector<uint8_t>& v)
{
	if (v.size() >= 3) { this->_red   = v[0];
						 this->_green = v[1];
						 this->_blue  = v[2]; }
	if (v.size() == 4) { this->_alpha = v[3]; }
}


uint8_t Color::getRed() const {
    return _red;
}

void Color::setRed(uint8_t red) {
    _red = red;
}

uint8_t Color::getGreen() const {
    return _green;
}

void Color::setGreen(uint8_t green) {
    _green = green;
}

uint8_t Color::getBlue() const {
    return _blue;
}

void Color::setBlue(uint8_t blue) {
    _blue = blue;
}

uint8_t Color::getAlpha() const {
    return _alpha;
}

void Color::setAlpha(uint8_t alpha) {
    _alpha = alpha;
}

uint32_t Color::getColor() const {
    return _color;
}

void Color::setColor(uint32_t color) {
    _color = color;
}


Color &Color::fromHue(float hue) {
    float h60 = hue / 60.0f;
    uint8_t h60f = (uint8_t)h60;

    float f = h60 - h60f;

    switch (h60f)
    {
        case 0:
            this->_color = 0xff0000ff | (uint32_t)(f * 255) << 8;
            break;
        case 1:
            this->_color = 0xff00ff00 | (255 - (uint32_t)(f * 255));
            break;
        case 2:
            this->_color = 0xff00ff00 | (uint32_t)(f * 255) << 16;
            break;
        case 3:
            this->_color = 0xffff0000 | (255 - (uint32_t)(f * 255)) << 8;
            break;
        case 4:
            this->_color = 0xffff0000 | (uint32_t)(f * 255);
            break;
        case 5:
            this->_color = 0xff0000ff | (255 - (uint32_t)(f * 255)) << 16;
            break;
        default:
            break;
    }

    return *this;
}

Color &Color::fromHSV(float h, float s, float v) {
    float h60 = h / 60.0f;
    uint32_t h60f = (uint32_t)h60;

    float f = h60 - h60f;

    float p = v * (1.0f - s);
    float q = v * (1.0f - f * s);
    float t = v * (1.0f - (1.0f - f) * s);

    switch (h60f)
    {
        case 0:
            this->_color = 0xff000000
                           | (uint8_t)(v * 255)
                           | (uint8_t)(t * 255) << 8
                           | (uint8_t)(p * 255) << 16;
            break;
        case 1:
            this->_color = 0xff000000
                           | (uint8_t)(q * 255)
                           | (uint8_t)(v * 255) << 8
                           | (uint8_t)(p * 255) << 16;
            break;
        case 2:
            this->_color = 0xff000000
                           | (uint8_t)(p * 255)
                           | (uint8_t)(v * 255) << 8
                           | (uint8_t)(t * 255) << 16;
            break;
        case 3:
            this->_color = 0xff000000
                           | (uint8_t)(p * 255)
                           | (uint8_t)(q * 255) << 8
                           | (uint8_t)(v * 255) << 16;
            break;
        case 4:
            this->_color = 0xff000000
                           | (uint8_t)(t * 255)
                           | (uint8_t)(p * 255) << 8
                           | (uint8_t)(v * 255) << 16;
            break;
        case 5:
            this->_color = 0xff000000
                           | (uint8_t)(v * 255)
                           | (uint8_t)(p * 255) << 8
                           | (uint8_t)(q * 255) << 16;
            break;
        default: break;
    }

    return *this;
}

void Color::toHSV(float *hsv) const
{
    float & h = hsv[0];
    float & s = hsv[1];
    float & v = hsv[2];

    float r = (float)this->_red / 255.0f;
    float g = (float)this->_green / 255.0f;
    float b = (float)this->_blue / 255.0f;

    float mx = Asemco::f3max(r, g, b);
    float mn = Asemco::f3min(r, g, b);

    float df = mx - mn;

    float _t;

    if (mx == mn) h = 0;

    else if (mx == r)
    {
        _t = 60.0f * ((g - b) / df) + 360.0f;
        h = (float)Asemco::ufmodf(_t, 360.0f);
    }
    else if (mx == g)
    {
        _t = 60.0f * ((b - r) / df) + 120.0f;
        h = (float)Asemco::ufmodf(_t, 360.0f);
    }
    else if (mx == b)
    {
        _t = 60.0f * ((r - g) / df) + 240.0f;
        h = (float)Asemco::ufmodf(_t, 360.0f);
    }

    if ((uint32_t)mx == 0) s = 0.0f;
    else s = df / mx;

    v = mx;
}

Color &Color::random(int seed) {
    if(seed == 0) srand(time(NULL));
    else          srand(seed);

    this->_color = rand();
    return *this;
}

Color &Color::randomColor(float min, float max, int seed) {
    uint32_t n_min = 0;
    uint32_t n_max = 36000;

    if (min > 0.0f && min < 360.0f) n_min = (uint32_t)(min * 100.0f);
    if (max > 0.0f && max < 360.0f) n_max = (uint32_t)(max * 100.0f);

    if(seed == 0) srand(time(NULL));
    else          srand(seed);

    uint32_t r = randRange(n_min, n_max);
    float h = (float)r / 100.0f;

    this->fromHue(h);
    return *this;
}

Color &Color::black() {
    this->_color = 0xff000000;
    return *this;
}

Color &Color::white() {
    this->_color = 0xffffffff;
    return *this;
}

Color &Color::gray(uint8_t factor) {
    this->_red   = factor;
    this->_green = factor;
    this->_blue  = factor;
    return *this;
}

Color &Color::invert() {
    this->_red =   255 - this->_red;
    this->_green = 255 - this->_green;
    this->_blue =  255 - this->_blue;
    return *this;
}

Color &Color::grayscale() {
    unsigned char gs = (this->_red + this->_green + this->_blue) / 3;
    this->gray(gs);
    return *this;
}

Color &Color::coef(float coefr, float coefg, float coefb) {
    this->_red   = (uint8_t)(this->_red   * coefr);
    this->_green = (uint8_t)(this->_green * coefg);
    this->_blue  = (uint8_t)(this->_blue  * coefb);

    return *this;
}

bool Color::operator==(const Color &rhs) const {
    return _color == rhs._color;
}

bool Color::operator!=(const Color &rhs) const {
    return !(rhs == *this);
}

Color &Color::operator++() {
    if (this->_red < 255)
        this->_red++;
    if(this->_green < 255)
        this->_green++;
    if(this->_blue < 255)
        this->_blue++;

    return *this;
}

Color &Color::operator--() {
    if (this->_red > 0)
        this->_red--;
    if (this->_green > 0)
        this->_green--;
    if (this->_blue > 0)
        this->_blue--;

    return *this;
}

Color Color::operator+(const Color &rhs) const {
    uint32_t red =   (this->_red   + rhs._red);
    uint32_t green = (this->_green + rhs._green);
    uint32_t blue =  (this->_blue  + rhs._blue);

    if (red > 255)   red = 255;
    if (green > 255) green = 255;
    if (blue > 255)  blue = 255;

    return Color((uint8_t)red, (uint8_t)green, (uint8_t)blue);
}

Color &Color::operator+=(const Color &rhs) {
    *this = *this + rhs;
    return *this;
}

Color Color::operator-(const Color &rhs) const {
    short red =   (this->_red   - rhs._red);
    short green = (this->_green - rhs._green);
    short blue =  (this->_blue  - rhs._blue);

    if (red < 0)   red = 0;
    if (green < 0) green = 0;
    if (blue < 0)  blue = 0;

    return Color((uint8_t)red, (uint8_t)green, (uint8_t)blue);
}

Color &Color::operator-=(const Color &rhs) {
    *this = *this - rhs;
    return *this;
}

Color Color::operator*(const float &rhs) const {
    if (rhs > 0)
    {
        uint32_t red =   (uint32_t)(this->_red   * rhs);
        uint32_t green = (uint32_t)(this->_green * rhs);
        uint32_t blue =  (uint32_t)(this->_blue  * rhs);

        if (red > 255)   red = 255;
        if (green > 255) green = 255;
        if (blue > 255)  blue = 255;

        return Color((uint8_t)red, (uint8_t)green, (uint8_t)blue);
    }
    return Color::Black;
}

Color &Color::operator*=(const float &rhs) {
    *this = *this * rhs;
    return *this;
}

Color Color::operator*(const Color & rhs) const
{
	float coefr = rhs._red   / 255.0f;
	float coefg = rhs._green / 255.0f;
	float coefb = rhs._blue  / 255.0f;

	return Color(_color).coef(coefr, coefg, coefb);
}

Color & Color::operator*=(const Color & rhs)
{
	float coefr = rhs._red   / 255.0f;
	float coefg = rhs._green / 255.0f;
	float coefb = rhs._blue  / 255.0f;

	this->coef(coefr, coefg, coefb);
	return *this;
}

Color Color::operator/(const float &rhs) const {
    if (rhs > 0)
    {
        uint32_t red =   (uint32_t)(this->_red   / rhs);
        uint32_t green = (uint32_t)(this->_green / rhs);
        uint32_t blue =  (uint32_t)(this->_blue  / rhs);

        if (red > 255) red = 255;
        if (green > 255) green = 255;
        if (blue > 255) blue = 255;

        return Color((uint8_t)red, (uint8_t)green, (uint8_t)blue);
    }
    return Color::Black;
}

Color &Color::operator/=(const float &rhs) {
    *this = *this / rhs;
    return *this;
}

Color Color::operator%(const unsigned char &rhs) const {
    return Color(this->_red % rhs, this->_green % rhs, this->_blue % rhs);
}

Color &Color::operator%=(const unsigned char &rhs) {
    *this = *this % rhs;
    return *this;
}
