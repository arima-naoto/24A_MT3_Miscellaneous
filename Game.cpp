#include "Game.h"
#include <Novice.h>
#include <imgui.h>
#define GRAY 0xAAAAAAFF //色を作成

/// 初期化処理
Game::Game() 
{
#pragma region 定義しなければならない

	//ワールドアフィン
	worldAffine_ = {
		.scale{1.0f,1.0f,1.0f},
		.rotate{0,0,0},
		.translate{0,0,0},
	};

	//ワールドクラスのインスタンスを作成
	world_ = new World(worldAffine_);

	//カメラアフィン
	cameraAffine_ = {
		.scale{ 1.0f,1.0f,1.0f },//倍率
		.rotate{ 0.26f,0.0f,0.0f },//回転
		.translate{ 0.0f,0.2f,-6.77f }//座標
	};

	//カメラクラスのインスタンスを作成
	camera_ = new Camera(cameraAffine_);
	
	///コントロールポイント
	controlPoints[0] = { -0.8f,0.58f,1.0f };
	controlPoints[1] = { 1.76f,1.0f,-0.3f };
	controlPoints[2] = { 0.94f,-0.7f,2.3f };

	prevMouseX_ = 0;
	prevMouseY_ = 0;
	
	mouseX_ = 0;
	mouseY_ = 0;

#pragma endregion
}

/// delete処理
Game::~Game() 
{
	delete world_, camera_;
}

//ゲームタイトル
void Game::Title() {

	//ウィンドウバーの名前
	const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)Camera::GetKWindowWidth(), (int)Camera::GetKWindowHeight());
}

/// レンダリングパイプラインの作成
void Game::Rendering() 
{
	//ワールド行列
	world_->MakeAffineMatrix(worldAffine_);

	//カメラワールド行列
	camera_->MakeAffineMatrix(cameraAffine_);

	//ビュー行列
	camera_->MakeViewMatrix();

	//プロジェクション行列
	camera_->MakeProjectionMatrix();

	//ワールドビュープロジェクション行列
	world_->MakeWorldViewProjectionMatrix(camera_->GetViewMatrix(), camera_->GetProjectionMatrix());

	//ビューポート行列
	camera_->MakeViewportMatrix();
}

///カメラの拡大縮小処理
void Game::MoveScale() {

	 int32_t wheel = Novice::GetWheel();

	 if (wheel != 0 ) {
		 // 現在のカメラ倍率を保持
		 cameraAffine_.translate.z -= (wheel / 1024.0f);
	 }
}

///カメラの回転処理
void Game::MoveRotation(){

	// 現在のマウス座標を取得
	Novice::GetMousePosition(&mouseX_, &mouseY_);

	// 右ボタンが押されているときにのみ回転を適用
	if (Novice::IsPressMouse(1)) {
		// マウスの移動量を計算
		int deltaX = mouseX_ - prevMouseX_;
		int deltaY = mouseY_ - prevMouseY_;

		// カメラの回転を更新
		cameraAffine_.rotate.x += deltaY * 0.005f;  // マウスのY移動でカメラのX軸回転
		cameraAffine_.rotate.y += deltaX * 0.005f;  // マウスのX移動でカメラのY軸回転
	}

	// 現在のマウス座標を次のフレームのために保存
	prevMouseX_ = mouseX_;
	prevMouseY_ = mouseY_;

}

///カメラを動かす処理
void Game::CameraController() {

	///カメラの拡大縮小処理
	Game::MoveScale();

	///カメラの回転処理
	Game::MoveRotation();
}

/// 更新処理
void Game::Update()
{
	//レンダリングパイプライン
	Game::Rendering();

	///カメラを動かす処理
	Game::CameraController();

}

#pragma region //描画処理関数の定義

/// デバッグテキストの描画
void Game::DrawDebugText() 
{
	///デバッグテキストの描画
	ImGui::Begin("DebugWindow");
	///コントロールポイント
	ImGui::DragFloat3("ControlPoints[0]", &controlPoints[0].x, 0.01f);
	ImGui::DragFloat3("ControlPoints[1]", &controlPoints[1].x, 0.01f);
	ImGui::DragFloat3("ControlPoints[2]", &controlPoints[2].x, 0.01f);
	ImGui::End();
}

/// グリッド描画処理
void Game::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,uint32_t color)
{
	const float kGirdHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGirdEvery = (kGirdHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float positionX = -kGirdHalfWidth + (xIndex * kGirdEvery);

		// 奥から手前への線
		Vector3 start = { positionX, 0.0f, -kGirdHalfWidth };
		Vector3 end = { positionX, 0.0f, kGirdHalfWidth };

		// スクリーン座標系まで変換をかける
		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		// ラインの描画
		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, positionX == 0.0f ? BLACK : color);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float positionZ = -kGirdHalfWidth + (zIndex * kGirdEvery);

		// 左から右への線
		Vector3 start = { -kGirdHalfWidth, 0.0f, positionZ };
		Vector3 end = { kGirdHalfWidth, 0.0f, positionZ };

		//スクリーン座標系まで変換をかける
		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		// ラインの描画（仮の関数）
		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, positionZ == 0.0f ? BLACK : color);
	}
}

/// 球体描画処理
void Game::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) 
{
	const uint32_t kSubdivision = 10; // 分割数
	const float kLonEvery = (2.0f * float(M_PI)) / kSubdivision; // 経度分割1つ分の角度
	const float kLatEvery = float(M_PI) / kSubdivision; // 緯度分割1つ分の角度

	// 緯度の方向に分割 -π/2～π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex; // 現在の緯度
		float nextLat = lat + kLatEvery; // 次の緯度

		// 経度の方向に分割 0～2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度
			float nextLon = lon + kLonEvery; // 次の経度

			// ワールド座標系のa, b, cを求める
			Vector3 a = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};
			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(nextLat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(nextLat),
				sphere.center.z + sphere.radius * cosf(nextLat) * sinf(lon)
			};
			Vector3 c = {
				sphere.center.x + sphere.radius * cosf(nextLat) * cosf(nextLon),
				sphere.center.y + sphere.radius * sinf(nextLat),
				sphere.center.z + sphere.radius * cosf(nextLat) * sinf(nextLon)
			};

			// ワールド座標系のa, b, cをスクリーン座標系まで変換
			Vector3 ScreenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 ScreenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 ScreenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			// abで線を引く
			Novice::DrawLine((int)ScreenA.x, (int)ScreenA.y, (int)ScreenB.x, (int)ScreenB.y, color);

			// bcで線を引く
			Novice::DrawLine((int)ScreenB.x, (int)ScreenB.y, (int)ScreenC.x, (int)ScreenC.y, color);
		}
	}
}

/// 平面描画処理
void Game::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 center = Maths::Multiply(plane.distance, plane.normal);

	Vector3 perpendiculars[4];
	perpendiculars[0] = Maths::Normalize(Maths::Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Maths::Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; index++) {
		Vector3 extend = Maths::Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Maths::Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	///pointsをそれぞれ結んで、DrawLineで平面を描画する
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
}

/// 2次ベジエ曲線描画処理
void Game::DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	int segments = 32; // ベジエ曲線を分割するセグメント数
	Vector3 previousPoint = Maths::Transform(controlPoint0, viewProjectionMatrix);
	previousPoint = Maths::Transform(previousPoint, viewportMatrix);

	for (int i = 1; i <= segments; i++) {
		float t = static_cast<float>(i) / static_cast<float>(segments);

		// ベジエ曲線の各点を計算
		Vector3 p0p1 = Maths::Lerp(controlPoint0, controlPoint1, t);
		Vector3 p1p2 = Maths::Lerp(controlPoint1, controlPoint2, t);
		Vector3 currentPoint = Maths::Lerp(p0p1, p1p2, t);

		currentPoint = Maths::Transform(currentPoint, viewProjectionMatrix);
		currentPoint = Maths::Transform(currentPoint, viewportMatrix);

		// 座標を整数に変換して線を描画
		Novice::DrawLine(static_cast<int>(previousPoint.x), static_cast<int>(previousPoint.y),
			static_cast<int>(currentPoint.x), static_cast<int>(currentPoint.y),
			color);

		// 現在の点を次の線の始点として設定
		previousPoint = currentPoint;
	}
}

/// 描画処理(これまで定義した描画処理をDraw関数の中で呼び出す)
void Game::Draw()
{
	Game::DrawDebugText();

	//グリッドを描画する色
	uint32_t gridColor = GRAY;
	uint32_t sphereColor = BLACK;
	uint32_t bezierColor = BLUE;

	//グリッド線を描画する
	Game::DrawGrid(world_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), gridColor);

	//ベジエ曲線を描画する
	Game::DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], 
		world_->GetViewProjectionMatrix(),camera_->GetViewportMatrix(), bezierColor);

	Sphere pointSphere[3];

	///0.01fの球体を3つ描画する
	for (int32_t i = 0; i < 3; i++) {
		pointSphere[i] = { controlPoints[i],0.01f };
		
		Game::DrawSphere(pointSphere[i], world_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), sphereColor);
	}
}

#pragma endregion

/// Main関数で処理を一つにまとめる
void Game::Main() 
{
	///メンバ関数Titleを呼び出す
	Game::Title();
	
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//更新の処理をまとめたメンバ関数Updateを呼び出す
		Game::Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//描画の処理をまとめたメンバ関数Drawを呼び出す
		Game::Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
}