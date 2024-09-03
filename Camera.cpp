#include "Camera.h"

/// 初期化処理
Camera::Camera(Affine affine) 
{
#pragma region 定義しなければならない

	//アフィン構造体
	affine_ = affine;

	//カメラワールド行列
	cameraWorldMatrix_ = {};

	//ビュー行列
	viewMatrix_ = {};

	//プロジェクション行列
	projectionMatrix_ = {};

	viewProjectionMatrix_ = {};

	//ビューポート行列
	viewportMatrix_ = {};

#pragma endregion
}

/// delete処理
Camera::~Camera(){}

/// アフィン行列の作成
void Camera::MakeAffineMatrix(Affine affine){ cameraWorldMatrix_ = Maths::STRAffineMatrix(affine);}

void Camera::MakeViewMatrix() { viewMatrix_ = Maths::Inverse(cameraWorldMatrix_);}

void Camera::MakeProjectionMatrix() {
	projectionMatrix_ = Maths::MakePerspectiveFovMatrix(0.45f, kWindowWidth_ / kWindowHeight_, 0.1f, 100.0f);}

void Camera::MakeViewProjectionMatrix() { viewProjectionMatrix_ = Multiply(viewMatrix_, projectionMatrix_);}

void Camera::MakeViewportMatrix() { viewportMatrix_ = Maths::ViewportMatrix(0, 0, kWindowWidth_, kWindowHeight_, 0.0f, 1.0f);}

Matrix4x4 Camera::GetViewMatrix() { return viewMatrix_; }

Matrix4x4 Camera::GetProjectionMatrix() { return projectionMatrix_; }

Matrix4x4 Camera::GetViewProjectionMatrix() { return viewProjectionMatrix_; }

Matrix4x4 Camera::GetViewportMatrix() { return viewportMatrix_; }

float Camera::GetKWindowWidth() { return kWindowWidth_; }

float Camera::GetKWindowHeight() { return kWindowHeight_; }