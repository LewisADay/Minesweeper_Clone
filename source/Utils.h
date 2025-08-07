
#pragma once

#include <raylib.h>
#include <vector>

struct iVector2 {
	int x;
	int y;
};


static inline bool operator==(const iVector2& lhs, const iVector2& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

static inline iVector2 operator-(const iVector2& lhs, const iVector2& rhs) {
	return { lhs.x - rhs.x, lhs.y - rhs.y };
}

static inline iVector2& operator-=(iVector2& self, const iVector2& other) {
	self.x = self.x - other.x;
	self.y = self.y - other.x;
	return self;
}

static inline iVector2 operator+(const iVector2& lhs, const iVector2& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

static inline iVector2& operator+=(iVector2& self, const iVector2& other) {
	self.x = self.x + other.x;
	self.y = self.y + other.x;
	return self;
}

static inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
	return { lhs.x - rhs.x, lhs.y - rhs.y };
}

static inline Vector2& operator-=(Vector2& self, const Vector2& other) {
	self.x = self.x - other.x;
	self.y = self.y - other.x;
	return self;
}

static inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

static inline Vector2& operator+=(Vector2& self, const Vector2& other) {
	self.x = self.x + other.x;
	self.y = self.y + other.x;
	return self;
}

namespace Utils {
	/// <summary>
	/// Get vector of grid coordinate possibilities for a width * height grid, 0 indexed
	/// </summary>
	/// <param name="width">Width of grid to get coords for</param>
	/// <param name="height">Height of grid to get coords for</param>
	/// <returns></returns>
	static inline std::vector<iVector2> GetCoordCombinations(unsigned int width, unsigned int height) {
		std::vector<iVector2> combinations;
		combinations.reserve(width * height);
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				combinations.emplace_back(x, y);
			}
		}
		return combinations;
	}
}
