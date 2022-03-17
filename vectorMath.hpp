#pragma once


#ifndef USE_VECTOR_PHYS
#define USE_VECTOR_PHYS

#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <cmath>

//PHYS means Physics, not to contradict with another PI in another libraries
#define TWO_PI_PHYS (2 * PI_PHYS)
#define PI_PHYS (3.14159265359)
#define PI_TWO_PHYS (PI_PHYS / 2)
#define PI_THREE_PHYS (PI_PHYS / 3)
#define PI_SIX_PHYS (PI_PHYS / 6)


#define RAD_TO_DEGREE (180/PI_PHYS)
#define DEGREE_TO_RAD (PI_PHYS/180)

struct degree
{
	degree(): angle_deg(0) {}
	degree(float degree_angle) : angle_deg(degree_angle) {}
	float angle_deg;
};

struct radian
{
	radian(): angle_rad(0) {}
	radian(const float radian_angle) : angle_rad(radian_angle * RAD_TO_DEGREE) {}

	float angle_rad;
};

//Three type of constructors
class Vector
{

public:
	Vector(): x(0), y(0), angle(0), magnitude(0) {}

	Vector(const degree vector_angle,const float length): x(0), y(0), angle(vector_angle.angle_deg), magnitude(length)
	{
		x = this->calculate_parameters().first;
		y = this->calculate_parameters().second;
	}

	Vector(const radian vector_angle, const float length) : x(0), y(0), angle(vector_angle.angle_rad), magnitude(length)
	{
		x = this->calculate_parameters().first;
		y = this->calculate_parameters().second;
	}



	Vector(const float first_coordinate,const float second_coordinate) :
					x(first_coordinate), y{second_coordinate},
					angle(this->calculate_angle()), magnitude(this->calculate_magnitude()){}


	Vector(const float first_coordinate,const  float second_coordinate,const degree vector_angle) :
					x(first_coordinate), y{ second_coordinate },
					angle(vector_angle.angle_deg), magnitude(this->calculate_magnitude()) {}


	Vector(const float first_coordinate,const  float second_coordinate,const radian vector_angle) :
		x(first_coordinate), y{ second_coordinate },
		angle(vector_angle.angle_rad ), magnitude(this->calculate_magnitude()) {}


	Vector(const float first_coordinate,const float second_coordinate,const radian vector_angle,const float length) :
		x(first_coordinate), y{ second_coordinate },
		angle(vector_angle.angle_rad), magnitude(length) {}


	Vector(const float first_coordinate,const float second_coordinate,const degree vector_angle,const float length) :
		x(first_coordinate), y{ second_coordinate },
		angle(vector_angle.angle_deg), magnitude(length) {}

	



	Vector& operator+(const Vector& vec2)
	{
		x += vec2.x;
		y += vec2.y;
		return *this;
	}

	Vector& operator-(const Vector& vec2)
	{
		x -= vec2.x;
		y -= vec2.y;
		return *this;
	}

	Vector& operator*(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector& operator/(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector& vec)
	{
		os << "x coordinate: " << vec.x << '\n';
		os << "y coordinate: " << vec.y << '\n';
		os << "angle: " << vec.angle <<" degree\n";
		os << "magnitude: " << vec.magnitude << '\n';

		return os;
	}

	float calculate_magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	float calculate_angle() const
	{
		return atan(y / x) * RAD_TO_DEGREE;
	}

	static float degree_to_rad(float degree_angle)
	{
		return degree_angle * DEGREE_TO_RAD;
	}

	static float rad_to_degree(float radian_angle)
	{
		return radian_angle * RAD_TO_DEGREE;
	}


	std::pair<float,float> calculate_parameters()
	{
		x = magnitude * cos(degree_to_rad(angle));
		y = magnitude * sin(degree_to_rad(angle));

		return std::make_pair(x, y);
	}

	  float dot_product_param(Vector& vec2)
    	{
        	auto result = x * vec2.x + y * vec2.y;
        	return result;
    	}

    //Angle should be written in Degree
    float dot_product_mag(Vector& vec2,float between_angle)
    	{
       	 	auto result = magnitude * vec2.magnitude * cos(degree_to_rad(between_angle));
        	return result;
    	}




private:
	float x, y, angle, magnitude;

};




#endif
