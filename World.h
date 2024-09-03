#pragma once
#include "Maths.h"

/// Mathsクラスを継承したWorldクラスを作成
class World : public Maths
{
public://メンバ関数

	/// インストラクタ
	World(Affine affine);

	/// デストラクタ
	~World();

	/// アフィン行列
	void MakeAffineMatrix(Affine affine);
	void MakeElbowAffineMatrix(Affine affine);

	Matrix4x4 GetShoulderMatrix() { return this->shoulderMatrix_; }
	Matrix4x4 GetElbowMatrix() { return this->elbowMatrix_; }

private://メンバ変数

	//アフィン構造体
	Affine affine_;

	//ワールド行列
	Matrix4x4 shoulderMatrix_;

	Matrix4x4 elbowMatrix_;

};


