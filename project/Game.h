#pragma once
#include "project/math/Pipeline/Rendering.h"
#include "project/view/World.h"
#include "project/view/Camera.h"
#include "project/gameObject/Sphere.h"
#include "project/gameObject/Grid.h"
#include "project/gameObject/CatmullRom.h"

#include "memory"
using namespace std;

enum GameView {
	kWorld,
	kCamera
};

class Game{

public:

	Game() = default;

	~Game() = default;

	void Initialize();

	void Update();

	void Draw();

	void Create_Unique();

	void Create_Pipeline();

	void CameraMoveScale(Affine& camera);

	void CameraMoveRotate(Affine& camera);

private:

	unique_ptr<World> world_ = nullptr;
	unique_ptr<Camera> camera_ = nullptr;
	unique_ptr<Sphere> sphere_ = nullptr;
	unique_ptr<Grid> grid_ = nullptr;
	unique_ptr<CatmullRom> catmullRom_ = nullptr;

	Affine affine_[2];

	Vector3 controlPoints[4];

};

