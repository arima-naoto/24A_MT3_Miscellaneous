#pragma once
#include "Maths.h"

/// <summary>
/// Mathsクラスを継承したCameraクラスを作成
/// </summary>
class Camera : public Maths
{
public://メンバ関数

	/// インストラクタ
	Camera(Affine affine);

	/// デストラクタ
	~Camera();

	/// アフィン行列
	void MakeAffineMatrix(Affine affine);

	/// ビュー行列
	void MakeViewMatrix();

	/// プロジェクション行列
	void MakeProjectionMatrix();


	void MakeViewProjectionMatrix();

	/// ビューポート行列
	void MakeViewportMatrix();

public://メンバ変数のゲッター

	//ビュー行列のゲッター
	Matrix4x4 GetViewMatrix();
	
	//プロジェクション行列のゲッター
	Matrix4x4 GetProjectionMatrix();

	Matrix4x4 GetViewProjectionMatrix();

	//ビューポート行列のゲッター
	Matrix4x4 GetViewportMatrix();

	//画面横幅のゲッター
	static float GetKWindowWidth();

	//画面縦幅のゲッター
	static float GetKWindowHeight();

private://メンバ変数

	//アフィン構造体
	Affine affine_;

	//カメラワールド行列
	Matrix4x4 cameraWorldMatrix_;

	//ビュー行列
	Matrix4x4 viewMatrix_;

	//プロジェクション行列
	Matrix4x4 projectionMatrix_;

	Matrix4x4 viewProjectionMatrix_;

	//ビューポート行列
	Matrix4x4 viewportMatrix_;

	//画面横幅
	static inline const float kWindowWidth_ = 1280.0f;

	//画面縦幅
	static inline const float kWindowHeight_ = 720.0f;

};

