
#pragma once

#include <raylib.h>

struct iVector2 {
	int x;
	int y;
};

static inline iVector2 operator-(const iVector2& lhs, const iVector2& rhs) {
	return { lhs.x - rhs.x, lhs.y - rhs.y };
}

static inline iVector2& operator-=(iVector2& self, const iVector2& other) {
	self.x = self.x - other.x;
	self.y = self.y - other.x;
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