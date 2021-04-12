
#pragma once

#include <math.h>


struct Color
{
	union
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
	};


	/**
     * Constructors.
     */
	inline Color(float r, float g, float b);
	inline Color(float r, float g, float b, float a);

	static inline Color Lerp(Color a, Color b, float t);
	static inline float Clamp(float t);

	static inline Color red();
	static inline Color green();
	static inline Color blue();
	static inline Color white();
	static inline Color black();
	static inline Color yellow();
	static inline Color cyan();
	static inline Color magenta();
	static inline Color gray();
	static inline Color grey();
	static inline Color clear();
};

Color Color::red() {return  Color(1, 0, 0, 1);}
Color Color::green() {return  Color(0, 1, 0, 1);}
Color Color::blue() {return  Color(0, 0, 1, 1);}
Color Color::white() {return  Color(1, 1, 1, 1);}
Color Color::black() {return  Color(0, 0, 0, 1);}
Color Color::yellow() {return  Color(1, 0.921568632f, 0.0156862754f, 1);}
Color Color::cyan() {return  Color(0, 1, 1, 1);}
Color Color::magenta() {return  Color(1, 0, 1, 1);}
Color Color::gray() {return  Color(0.5, 0.5, 0.5, 1);}
Color Color::grey() {return  Color(0.5, 0.5, 0.5, 1);}
Color Color::clear() {return  Color(0, 0, 0, 0);}

Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}
Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

Color Color::Lerp(Color a, Color b, float t)
{
	t = Color::Clamp(t);
	return Color(a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t, a.a + (b.a - a.a) * t);
}

float Color::Clamp(float value)
{
	if (value < 0)
	{
		return 0;
	}
	if (value > 1)
	{
		return 1;
	}
	return value;
}
