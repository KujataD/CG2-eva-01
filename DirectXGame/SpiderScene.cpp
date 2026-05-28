#include "SpiderScene.h"

using namespace KujakuEngine;

void SpiderScene::Initialize() {
	// カメラ初期化
	// ------------------------------------------
	camera_.Initialize();
	camera_.translation_ = {0.0f, 23.0f, -14.0f};
	camera_.rotation_ = {1.085f, 0.0f, 0.0f};
	camera_.UpdateMatrix();
	debugCamera_.Initialize(camera_.rotation_, camera_.translation_);

	// 地形
	// ------------------------------------------
	modelGround_ = std::unique_ptr<Model>(Model::CreateFromOBJ("ground_t", ShaderModel::kHalfLambert));
	worldTransformGround_.Initialize();
	worldTransformGround_.scale_ = { 3.0f, 1.0f, 3.0f };
	worldTransformGround_.translation_.y = -1.0f;

	modelGround_->SetColor({ 0.01f, 0.01f, 0.01f, 1.0f });
	// 蝶
	// ------------------------------------------
	modelSpiderWalkGrid_ = std::unique_ptr<Model>(Model::CreateFromOBJ("spider_walk_grid"));
	particleModel_ = std::unique_ptr<ParticleModel>(ParticleModel::CreateTriangle("Resources/white1x1.png", true));
	
	spider_ = std::make_unique<Spider>();
	spider_->Initialize(modelSpiderWalkGrid_.get(), particleModel_.get(), &camera_);

	// シーンの色変更
	DirectXCommon::GetInstance()->SetClearColor({ 0.01f, 0.0f, 0.0f, 1.0f });

}

void SpiderScene::Update() {
	// カメラ更新
	// ------------------------------------------
	debugCamera_.Update();
	debugCamera_.UpdateViewMatrix();
	camera_.matView = debugCamera_.GetViewMatrix();
	camera_.UpdateProjectionMatrix();
	camera_.TransferConstBuffer();

	// 蝶更新
	// ------------------------------------------
	spider_->Update();
	worldTransformGround_.UpdateMatrix(camera_);
}

void SpiderScene::Draw() {
	Model::PreDraw();
	modelGround_->Draw(worldTransformGround_, camera_);
	spider_->Draw();
	Model::PostDraw();
}
