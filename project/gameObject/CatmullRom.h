#pragma once
#include "project/math/Pipeline/Rendering.h"
class CatmullRom : public Rendering{

	CatmullRom() = default;

	~CatmullRom() = default;

	void Draw(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Vector3 &controlPoint3,const Matrix4x4 &viewProjectionMatrix,const Matrix4x4 &viewportMatrix,uint32_t color);

};

