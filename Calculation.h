#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

/// <summary>
/// 計算クラスの定義
/// </summary>
class Calculation
{
public:

	///加算
	static Vector3 Add(const Vector3& v1, const Vector3& v2);

	///減算
	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	///乗算
	static Vector3 Multiply(float scalar, const Vector3& v2);

	///行列の積(Matrix4x4)
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// X軸回転行列
	static Matrix4x4 MakeRotateXMatrix(float radian);

	/// Y軸回転行列
	static Matrix4x4 MakeRotateYMatrix(float radian);

	/// Z軸回転行列
	static Matrix4x4 MakeRotateZMatrix(float radian);

	///計算の更新処理や描画処理をまとめるメンバ関数
	static void Main();



};

#pragma region 演算子の宣言

///加算演算子
Vector3 operator+(const Vector3& v1, const Vector3& v2);

///減算演算子
Vector3 operator-(const Vector3& v1, const Vector3& v2);

///乗算演算子(Vector3型)
Vector3 operator*(float scalar, const Vector3& v);

///乗算演算子(Vector3型)
Vector3 operator*(const Vector3& v, float scalar);

///乗算演算子(Matrix4x4型)
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

#pragma endregion

