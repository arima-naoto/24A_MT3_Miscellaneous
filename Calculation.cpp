#include "Calculation.h"
#include "cmath"
#include "imgui.h"
using namespace std;

///加算
Vector3 Calculation::Add(const Vector3& v1, const Vector3& v2) {
	return { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
}

///減算
Vector3 Calculation::Subtract(const Vector3& v1, const Vector3& v2) {
	return { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
}

///乗算
Vector3 Calculation::Multiply(float scalar, const Vector3& v2)
{
	return { scalar * v2.x ,scalar * v2.y,scalar * v2.z };
}

///行列の積
Matrix4x4 Calculation::Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 MultiplyMatrix{};

	//for分を使用して、行列の積を求める
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			MultiplyMatrix.m[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				MultiplyMatrix.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return MultiplyMatrix;
}

/// X軸回転行列
Matrix4x4 Calculation::MakeRotateXMatrix(float radian)
{
	Matrix4x4 rotateXMatrix = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cosf(radian),sinf(radian),0.0f,
		0.0f,-sinf(radian),cosf(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateXMatrix;
}

/// Y軸回転行列
Matrix4x4 Calculation::MakeRotateYMatrix(float radian)
{
	Matrix4x4 rotateYMatrix = {
		cosf(radian),0.0f,-sinf(radian),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		sinf(radian),0.0f,cosf(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateYMatrix;
}

/// Z軸回転行列
Matrix4x4 Calculation::MakeRotateZMatrix(float radian)
{
	Matrix4x4 rotateZMatrix = {
		cosf(radian),sinf(radian),0.0f,0.0f,
		-sinf(radian),cosf(radian),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateZMatrix;
}

/// 加算演算子の定義
Vector3 operator+(const Vector3& v1, const Vector3& v2) {

	///Calculationクラスから加算メンバ関数を呼び出し、戻り値を設定する
	return Calculation::Add(v1, v2);

}

/// 減算演算子の定義
Vector3 operator-(const Vector3& v1, const Vector3& v2) {

	///Calculationクラスから減算メンバ関数を呼び出し、戻り値を設定する
	return Calculation::Subtract(v1, v2);

}

///乗算演算子の定義(Vector3型)
Vector3 operator*(float scalar, const Vector3& v) {

	///CalculationクラスからVector3型の乗算メンバ関数を呼び出し、戻り値を設定する
	return Calculation::Multiply(scalar, v);
}

///乗算演算子の定義(Vector3型)
Vector3 operator*(const Vector3& v, float scalar) {

	///戻り値を以下の通りで設定する
	return scalar * v;
}

///乗算演算子の定義(Matrix4x4型)
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2){

	///CalculationからMatrix4x4型のメンバ関数Multiplyを呼び出し、戻り値を設定する
	return Calculation::Multiply(m1, m2);

}

///計算の更新処理や描画処理をまとめるメンバ関数
void Calculation::Main() {

	///ベクトル1
	Vector3 v1{ 0.2f,1.0f,0.0f };
	///ベクトル2
	Vector3 v2{ 2.4f,3.1f,1.2f };

	///加算演算子を使用して,resultAddを定義する
	Vector3 resultAdd = v1 + v2;
	///減算演算子を使用して,resultSubtractを定義する
	Vector3 resultSubtract = v1 - v2;
	///Vector3型のZ乗算演算子を使用して、resultMultiplyを定義する
	Vector3 resultMultiply = v1 * 2.4f;
	///回転変数
	Vector3 rotate{ 0.4f,1.43f,-0.8f };

	///X軸回転行列
	Matrix4x4 rotateXMatrix = Calculation::MakeRotateXMatrix(rotate.x);
	///Y軸回転行列
	Matrix4x4 rotateYMatrix = Calculation::MakeRotateYMatrix(rotate.y);
	///Z軸回転行列
	Matrix4x4 rotateZMatrix = Calculation::MakeRotateZMatrix(rotate.z);
	//X軸・Y軸・Z軸行列を結合する
	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

#pragma region デバッグテキストの描画

	ImGui::Begin("DebugWindow");
	///加算
	ImGui::Text("Add:%f, %f, %f", resultAdd.x, resultAdd.y, resultAdd.z);
	///減算
	ImGui::Text("Subtract:%f, %f, %f", resultSubtract.x, resultSubtract.y, resultSubtract.z);
	///乗算
	ImGui::Text("Multiply:%f, %f, %f", resultMultiply.x, resultMultiply.y, resultMultiply.z);
	///回転行列
	ImGui::Text("matrix\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
		rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
		rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
		rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
		rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);
	ImGui::End();
#pragma endregion

}