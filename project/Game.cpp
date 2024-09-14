#define NOMINMAX
#include "Game.h"

#include "algorithm"
#include "imgui.h"

#define GRAY 0xAAAAAAFF

void Game::Initialize() {

	Create_Unique();

	// ワールド
	affine_[GameView::kWorld] = {
		.scale{1,1,1},
		.rotate{0,0,0},
		.translate{0,0,0}
	};

	// カメラ
	affine_[GameView::kCamera] = {
		.scale{ 1.0f,1.0f,1.0f },
		.rotate{ 0.26f,0.0f,0.0f },
		.translate{ 0.0f,0.2f,-6.77f }
	};

	

}

void Game::Update(){

	Create_Pipeline();

	CameraMoveScale(affine_[GameView::kCamera]);
	CameraMoveRotate(affine_[GameView::kCamera]);

}

void Game::Draw(){

	enum ObjectColor {
		kGrid = GRAY,
		kSphere = BLACK
	};

	Spherical sphere = {
		.center{0.0f,0.0f,0.0f},
		.radius{0.6f}
	};

	grid_->Draw(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), uint32_t(ObjectColor::kGrid));

	sphere_->Draw(sphere, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), uint32_t(ObjectColor::kSphere));

}

void Game::Create_Unique() {

	world_ = make_unique<World>();
	world_->Initailize(affine_[GameView::kWorld]);

	camera_ = make_unique<Camera>();
	camera_->Initialize(affine_[GameView::kCamera]);

	sphere_ = make_unique<Sphere>();

	grid_ = make_unique<Grid>();

}

void Game::Create_Pipeline() {

	///ワールド行列
	world_->CreateWorldMatrix(affine_[GameView::kWorld]);

	///カメラワールド行列
	camera_->CreateCameraMatrix(affine_[GameView::kCamera]);

	///ビュー行列
	camera_->CreateViewMatrix();

	///プロジェクション行列
	camera_->CreateProjectionMatrix();

	///ビュープロジェクション行列
	camera_->CreateViewProjectionMatrix();

	///ビューポート行列
	camera_->CreateViewportMatrix();

}

void Game::CameraMoveScale(Affine& camera){

	int32_t wheelScroll = Novice::GetWheel();

	//スクロール量の最小値と最大値
	float scroll[2] = { 0.5f,1.0f };

	if (wheelScroll != 0) {
		camera.scale.z -= (wheelScroll / (1024.f * 2));
		camera.scale.z = std::clamp(camera.scale.z, scroll[0], scroll[1]);
	}

}

void Game::CameraMoveRotate(Affine& camera) {

	static Vector2 prevMouse = { 0,0 };
	static Vector2 mouse = { 0,0 };

	Novice::GetMousePosition(&mouse.x, &mouse.y);
	
	int mouseClickLeft = 1;

	if (Novice::IsPressMouse(mouseClickLeft)) {
		Vector2 delta = mouse - prevMouse;
		camera.rotate.x += delta.y * 0.0025f;
		camera.rotate.y += delta.x * 0.0025f;
	}

	prevMouse = mouse;

}



