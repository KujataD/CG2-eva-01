#include "TriangleScene.h"


using namespace KujakuEngine;

void TriangleScene::Initialize() {
	// 色変更
	DirectXCommon::GetInstance()->SetClearColor({ 0.0f, 0.01f, 0.0f, 1.0f });

	// カメラ初期化
	// ------------------------------------------
	camera_.Initialize();
	camera_.translation_ = { 0.0f, 0.0f, -7.0f };
	camera_.UpdateMatrix();
	debugCamera_.Initialize(camera_.rotation_, camera_.translation_);

	// 三角形
	// ------------------------------------------
	worldTransformTriangleA_.Initialize();
	worldTransformTriangleB_.Initialize();

	worldTransformTriangleB_.rotation_.y = std::numbers::pi_v<float> *0.4f;

	modelTriangleA_ = std::unique_ptr<Model>(Model::CreateTriangle("Resources/uvChecker.png"));
	modelTriangleB_ = std::unique_ptr<Model>(Model::CreateTriangle("Resources/uvChecker.png"));
	
	// テクスチャ
	textureIndexMonsterBall_ = TextureManager::GetInstance()->LoadTexture("Resources/monsterBall.png");
	textureIndexFire_ = TextureManager::GetInstance()->LoadTexture("Resources/fire.png");
	textureIndexUVChecker_ = TextureManager::GetInstance()->LoadTexture("Resources/uvChecker.png");
	
}

void TriangleScene::Update() {
	// カメラ更新
	// ------------------------------------------
	debugCamera_.Update();
	debugCamera_.UpdateViewMatrix();
	camera_.matView = debugCamera_.GetViewMatrix();
	camera_.UpdateProjectionMatrix();
	camera_.TransferConstBuffer();

	// 各ワールドトランスフォームの更新
	// ------------------------------------------
	worldTransformTriangleA_.UpdateMatrix(camera_);
	worldTransformTriangleB_.UpdateMatrix(camera_);

	// 各モデルの更新
	// ------------------------------------------
	switch (textureModeA_)
	{
	case TriangleScene::TextureMode::UVChecker:
		modelTriangleA_->SetTexture(textureIndexUVChecker_);
		break;
	case TriangleScene::TextureMode::MonsterBall:
		modelTriangleA_->SetTexture(textureIndexMonsterBall_);
		break;
	case TriangleScene::TextureMode::Fire:
		modelTriangleA_->SetTexture(textureIndexFire_);
		break;
	default:
		break;
	}

	switch (textureModeB_)
	{
	case TriangleScene::TextureMode::UVChecker:
		modelTriangleB_->SetTexture(textureIndexUVChecker_);
		break;
	case TriangleScene::TextureMode::MonsterBall:
		modelTriangleB_->SetTexture(textureIndexMonsterBall_);
		break;
	case TriangleScene::TextureMode::Fire:
		modelTriangleB_->SetTexture(textureIndexFire_);
		break;
	default:
		break;
	}

	// デバッグ
	// ------------------------------------------

#ifdef USE_IMGUI
	const char* textureModeNames[] = { "UVChecker", "MonsterBall", "Fire" };
	int textureIndexA = static_cast<int>(textureModeA_);
	int textureIndexB = static_cast<int>(textureModeB_);

	ImGui::Begin("Triangle Manager");

	if (ImGui::TreeNode("Triangle A")) {
		ImGui::DragFloat3("Translation", &worldTransformTriangleA_.translation_.x, 0.01f);
		ImGui::DragFloat3("Rotation", &worldTransformTriangleA_.rotation_.x, 0.01f);
		ImGui::DragFloat3("Scale", &worldTransformTriangleA_.scale_.x, 0.01f);
		if (ImGui::Combo("TextureMode", &textureIndexA, textureModeNames, IM_ARRAYSIZE(textureModeNames))) {
			textureModeA_ = static_cast<TextureMode>(textureIndexA);
		}
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Triangle B")) {
		ImGui::DragFloat3("Translation", &worldTransformTriangleB_.translation_.x, 0.01f);
		ImGui::DragFloat3("Rotation", &worldTransformTriangleB_.rotation_.x, 0.01f);
		ImGui::DragFloat3("Scale", &worldTransformTriangleB_.scale_.x, 0.01f);
		if (ImGui::Combo("TextureMode", &textureIndexB, textureModeNames, IM_ARRAYSIZE(textureModeNames))) {
			textureModeB_ = static_cast<TextureMode>(textureIndexB);
		}
		ImGui::TreePop();
	}

	ImGui::End();
#endif // USE_IMGUI


}

void TriangleScene::Draw() {
	Model::PreDraw();
	modelTriangleA_->Draw(worldTransformTriangleA_, camera_);
	modelTriangleB_->Draw(worldTransformTriangleB_, camera_);
	Model::PostDraw();
}
