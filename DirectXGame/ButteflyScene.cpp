#include "ButterflyScene.h"

using namespace KujakuEngine;

void ButterflyScene::Initialize() {
	// カメラ初期化
	// ------------------------------------------
	camera_.Initialize();
	camera_.translation_.z = -10.0f;
	camera_.UpdateMatrix();
	debugCamera_.Initialize(camera_.rotation_, camera_.translation_);

	// 蝶
	// ------------------------------------------
	modelButterflyWingLeft_ = std::unique_ptr<Model>(Model::CreateFromOBJ("butterfly_left"));
	modelButterflyWingRight_ = std::unique_ptr<Model>(Model::CreateFromOBJ("butterfly_right"));
	particleModelButterflyScales_ = std::unique_ptr<ParticleModel>(ParticleModel::CreateTriangle("Resources/white1x1.png", true));
	butterfly_ = std::make_unique<Butterfly>();
	butterfly_->Initialize(modelButterflyWingLeft_.get(), modelButterflyWingRight_.get(), particleModelButterflyScales_.get(), &camera_);

	// シーンの色変更
	DirectXCommon::GetInstance()->SetClearColor({0.0f, 0.0f, 0.01f, 1.0f});
}

void ButterflyScene::Update() {
	// 蝶更新
	// ------------------------------------------
	butterfly_->Update();

	// カメラ更新
	// ------------------------------------------
	debugCamera_.Update();
	debugCamera_.UpdateViewMatrix();
	camera_.matView = debugCamera_.GetViewMatrix();
	camera_.UpdateProjectionMatrix();
	camera_.TransferConstBuffer();
}

void ButterflyScene::Draw() {
	Model::PreDraw();
	butterfly_->Draw();
	Model::PostDraw();
}
