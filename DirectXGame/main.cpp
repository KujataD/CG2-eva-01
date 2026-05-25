#include <KujakuEngine.h>

#include "CinemaScene.h"
#include "TriangleScene.h"

using namespace KujakuEngine;

enum class Scene {
	kUnknown = 0,
	kTriangle,
	kCinema,
};

Scene scene = Scene::kUnknown;

std::unique_ptr<TriangleScene> triangleScene = nullptr;
std::unique_ptr<CinemaScene> cinemaScene = nullptr;

void InitScene();
void UpdateScene();
void DrawScene();
void ChangeScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KujakuEngine::Initialize(L"LE2B_04_オオツカ_ダイチ_CG2_評価課題01", {0.0f, 0.0f, 0.01f, 1.0f});

	// タイトルシーンの初期化
	scene = Scene::kTriangle;

	InitScene();

	Camera camera;
	camera.Initialize();
	camera.translation_.z = -10.0f;
	camera.UpdateMatrix();

	DebugCamera debugCamera;
	debugCamera.Initialize(camera.rotation_, camera.translation_);

	WorldTransform worldTransformButterfly;
	worldTransformButterfly.Initialize();
	worldTransformButterfly.rotation_.x = -std::numbers::pi_v<float> * 0.25f;

	WorldTransform worldTransformButterfly_right;
	worldTransformButterfly_right.Initialize();
	worldTransformButterfly_right.parent_ = &worldTransformButterfly;

	WorldTransform worldTransformButterfly_left;
	worldTransformButterfly_left.Initialize();
	worldTransformButterfly_left.parent_ = &worldTransformButterfly;

	std::unique_ptr<Model> modelButterflyRight = std::unique_ptr<Model>(Model::CreateFromOBJ("enemy"));
	std::unique_ptr<Model> modelButterflyLeft = std::unique_ptr<Model>(Model::CreateFromOBJ("butterfly_left"));

	std::unique_ptr<ParticleModel> particleModel = std::unique_ptr<ParticleModel>(ParticleModel::CreateTriangle("Resources/white1x1.png", true));
	particleModel->Initialize();
	particleModel->SetBlendMode(BlendMode::kAdd);

	ParticleEmitter particleEmitter;
	particleEmitter.Initialize(particleModel.get());
	particleEmitter.emitShape_ = ParticleEmitter::kEmitShapeModelEdge;
	particleEmitter.count_ = 20;
	particleEmitter.frequency_ = 0.02f;
	float particleAllSize = 0.02f;
	particleEmitter.particleScale_ = {particleAllSize, particleAllSize, particleAllSize};
	particleEmitter.lifeTimeMinMax_ = {0.1f, 1.5f};
	particleEmitter.SetSourceVertices(modelButterflyRight->GetVertices(), &worldTransformButterfly_right);

	ParticleEmitter particleEmitter2;
	particleEmitter2.Initialize(particleModel.get());
	particleEmitter2.emitShape_ = particleEmitter.emitShape_;
	particleEmitter2.count_ = particleEmitter.count_;
	particleEmitter2.frequency_ = particleEmitter.frequency_;
	particleEmitter2.particleScale_ = particleEmitter.particleScale_;
	particleEmitter2.lifeTimeMinMax_ = particleEmitter.lifeTimeMinMax_;
	particleEmitter2.SetSourceVertices(modelButterflyLeft->GetVertices(), &worldTransformButterfly_left);

	float timer = 0.0f;
	float timerTranslation = 0.0f;
	float duration = 1.0f;
	float rotationMax = std::numbers::pi_v<float> * 0.45f;
	float rotationMin = -std::numbers::pi_v<float> * 0.3f;

	// メインループ
	while (KujakuEngine::Update()) {
		// ======================================
		// 更新処理ここから
		// ======================================

		timer += Time::GetDeltaTime();
		timerTranslation += Time::GetDeltaTime();
		if (timer < duration * 0.5f) {
			float t = timer / (duration * 0.5f);
			worldTransformButterfly_left.rotation_.y = EaseUtil::EaseLerp(rotationMin, rotationMax, t, EaseUtil::EaseType::InOutQuad);
			worldTransformButterfly_right.rotation_.y = EaseUtil::EaseLerp(-rotationMin, -rotationMax, t, EaseUtil::EaseType::InOutQuad);
		} else if (timer >= duration * 0.5f && timer < duration) {
			float t = (timer - duration * 0.5f) / (duration * 0.5f);
			worldTransformButterfly_left.rotation_.y = EaseUtil::EaseLerp(rotationMax, rotationMin, t, EaseUtil::EaseType::InOutQuad);
			worldTransformButterfly_right.rotation_.y = EaseUtil::EaseLerp(-rotationMax, -rotationMin, t, EaseUtil::EaseType::InOutQuad);
		} else {
			timer = 0.0f;
		}
		worldTransformButterfly.translation_.x = std::cosf(timerTranslation * 0.5f);
		worldTransformButterfly.translation_.y = std::sinf(timerTranslation);

		worldTransformButterfly.UpdateMatrix(camera);
		worldTransformButterfly_left.UpdateMatrix(camera);
		worldTransformButterfly_right.UpdateMatrix(camera);
		particleEmitter.Update(Time::GetDeltaTime(), camera);
		particleEmitter2.Update(Time::GetDeltaTime(), camera);

		debugCamera.Update();
		debugCamera.UpdateViewMatrix();
		camera.matView = debugCamera.GetViewMatrix();
		camera.UpdateProjectionMatrix();
		camera.TransferConstBuffer();


#ifdef USE_IMGUI
		ImGui::Begin("LightManager");
		auto& light = DirectionalLight::GetInstance()->GetData();
		ImGui::ColorEdit3("Light Color", &light.color.x);
		ImGui::SliderFloat3("Direction", &light.direction.x, -1.0f, 1.0f);
		ImGui::DragFloat("Intensity", &light.intensity, 0.01f);

		ImGui::End();
		ImGui::Begin("ButterFlyManager");
		ImGui::DragFloat3("left", &worldTransformButterfly_left.rotation_.x, 0.01f);
		ImGui::DragFloat3("right", &worldTransformButterfly_right.rotation_.x, 0.01f);
		ImGui::DragFloat3("parent", &worldTransformButterfly.translation_.x, 0.01f);
		ImGui::DragFloat2("ParticleEmitter lifeTime", &particleEmitter.lifeTimeMinMax_.x, 0.01f);
		int particleCount = particleEmitter.count_;
		ImGui::DragInt("ParticleEmitter count", &particleCount, 1, 0, 1000);
		ImGui::DragFloat("ParticleEmitter frequency", &particleEmitter.frequency_, 0.01f);
		ImGui::DragFloat("ParticleEmitter size", &particleAllSize, 0.01f);

		particleEmitter.count_ = static_cast<uint32_t>(particleCount);

		particleEmitter2.lifeTimeMinMax_ = particleEmitter.lifeTimeMinMax_;
		particleEmitter2.count_ = particleEmitter.count_;
		particleEmitter2.frequency_ = particleEmitter.frequency_;
		particleEmitter.particleScale_ = {particleAllSize, particleAllSize, particleAllSize};
		particleEmitter2.particleScale_ = particleEmitter.particleScale_;
		ImGui::End();
#endif // USE_IMGUI

		// ======================================
		// 描画処理ここから
		// ======================================

		KujakuEngine::PreDraw();

		Model::PreDraw();
		//modelButterflyLeft->Draw(worldTransformButterfly_left, camera, kFillModeWireframe);
		//modelButterflyRight->Draw(worldTransformButterfly_right, camera, kFillModeWireframe);
		Model::PostDraw();

		ParticleModel::PreDraw();
		particleEmitter.Draw();
		ParticleModel::PostDraw();

		KujakuEngine::PostDraw();
	}

	// 解放処理
	// ------------------------------------------

	// エンジンの終了処理
	KujakuEngine::Finalize();

	return 0;
}

void InitScene() {
	switch (scene) {
	case Scene::kUnknown:
		break;
	case Scene::kTriangle:
		if (!triangleScene) {
			triangleScene = std::make_unique<TriangleScene>();
			triangleScene->Initialize();
		}
		break;
	case Scene::kCinema:
		if (!cinemaScene) {
			cinemaScene = std::make_unique<CinemaScene>();
			cinemaScene->Initialize();
		}
		break;
	default:
		break;
	}
}

void ChangeScene() {
	switch (scene) {
	case Scene::kTriangle:
		if (triangleScene->GetReloadRequested()) {
			// シーンリロード
			triangleScene.reset();
			triangleScene = std::make_unique<TriangleScene>();
			triangleScene->Initialize();
		} else if (triangleScene->IsFinished()) {
			// シーン変更
			scene = Scene::kCinema;
			// 旧シーンの解放
			triangleScene.reset();
			// 新シーンの生成と初期化
			cinemaScene = std::make_unique<CinemaScene>();
			cinemaScene->Initialize();
		}
		break;
	case Scene::kCinema:
		if (cinemaScene->GetReloadRequested()) {
			// シーンリロード
			cinemaScene.reset();
			cinemaScene = std::make_unique<CinemaScene>();
			cinemaScene->Initialize();
		} else if (cinemaScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTriangle;
			// 旧シーンの解放
			cinemaScene.reset();
			// 新シーンの生成と初期化
			triangleScene = std::make_unique<TriangleScene>();
			triangleScene->Initialize();
		}
		break;
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTriangle:
		triangleScene->Update();
		break;
	case Scene::kCinema:
		cinemaScene->Update();
		break;
	default:
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTriangle:
		triangleScene->Draw();
		break;
	case Scene::kCinema:
		cinemaScene->Draw();
		break;
	default:
		break;
	}
}