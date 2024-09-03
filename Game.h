#pragma once
#include "World.h"
#include "Camera.h"
#include "Maths.h"

/// <summary>
/// Mathsクラスを継承したGameクラスを作成
/// </summary>
class Game : public Maths
{
public://メンバ関数

	/// インストラクタ
	Game();

	/// デストラクタ
	~Game();

	///ゲームタイトル
	void Title();

	/// レンダリングパイプライン
	void Rendering();

	///カメラの拡大縮小
	void MoveScale();

	///カメラの回転処理
	void MoveRotation();

	///カメラを動かす処理
	void CameraController();

	/// 更新処理
	void Update();

	/// デバッグテキスト描画メンバ関数
	void DrawDebugText();

	/// グリッド線描画メンバ関数
	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,uint32_t color);

	/// 球体描画メンバ関数
	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	///平面描画メンバ関数
	void DrawPlane(const Plane& plane,const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	//2次ベジエ曲線描画処理
	void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	/// 描画処理
	void Draw();

	/// 処理を一つにまとめるメンバ関数
	void Main();


private://メンバ変数

	//ワールドアフィン
	Affine worldAffine_;
	Affine elbowAffine_;
	Affine handAffine_;

	//ワールドクラス
	World* world_;

	//カメラアフィン
	Affine cameraAffine_;

	//カメラクラス
	Camera* camera_;

	///コントローラポイント
	Vector3 controlPoints[3];

	Matrix4x4 handMatrix_;

	int prevMouseX_;
	int prevMouseY_;

	int mouseX_;
	int mouseY_;

};

