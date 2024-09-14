#pragma once
#include "Novice.h"

struct Vector2 {
	int x;
	int y;
};

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {

	float m[4][4];

};

struct Affine{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

template<typename Ty_>
struct Fov {

	Ty_ fovY;
	Ty_ aspectRatio;
	Ty_ nearClip;
	Ty_ farClip;
};

template<typename Ty_>
struct ViewRect {

	Ty_ left;
	Ty_ top;
	Ty_ width;
	Ty_ height;
	Ty_ minDepth;
	Ty_ maxDepth;

};

struct Spherical {

	Vector3 center;
	float radius;

};