#pragma once
#include <cstdint>

namespace Eflat {
	struct Vec2 { 
		float x, y;

		Vec2() {
			x = 0.0f;
			y = 0.0f;
		}
	
		Vec2(float x, float y) {
			this->x = x;
			this->y = y;
		}

		Vec2 operator-(const Vec2& other) const {
			return Vec2(x - other.x, y - other.y);
		}

		Vec2 operator+(const Vec2& other) const {
			return Vec2(x + other.x, y + other.y);
		}

		Vec2 operator*(float scalar) const {
			return Vec2(x * scalar, y * scalar);
		}

		Vec2 operator/(float scalar) const {
			return Vec2(x / scalar, y / scalar);
		}

		Vec2& operator-=(const Vec2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vec2& operator+=(const Vec2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}
	};

	struct Vec3 { float x, y, z; };
	struct Vec4 { float x, y, z, w; };
	struct Mat3;
	struct Mat4;
	struct Rect { float x, y, w, h; };
	struct Color { uint8_t r, g, b, a; };
}
