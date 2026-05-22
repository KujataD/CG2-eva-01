#include <KujakuEngine.h>

#include "TriangleScene.h"

using namespace KujakuEngine;

enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
};

Scene scene = Scene::kUnknown;

// std::unique_ptr<TriangleScene> triangleScene = nullptr;

void InitScene();
void UpdateScene();
void DrawScene();
void ChangeScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KujakuEngine::Initialize(L"LE2B_04_オオツカ_ダイチ_CG2_評価課題01", {0.0f, 0.0f, 0.01f, 1.0f});

	// triangleScene = std::make_unique<TriangleScene>();

	Camera camera;
	camera.Initialize();
	camera.translation_.z = -10.0f;
	camera.UpdateMatrix();

	WorldTransform worldTransformButterfly;
	worldTransformButterfly.Initialize();

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

	ParticleEmitter particleEmitter;
	particleEmitter.Initialize(particleModel.get());
	particleEmitter.emitShape_ = ParticleEmitter::kEmitShapeModelEdge;
	particleEmitter.count_ = 10;
	particleEmitter.frequency_ = 0.01f;
	particleEmitter.particleScale_ = {0.02f, 0.02f, 0.02f};
	particleEmitter.lifeTimeMinMax_ = {0.1f, 0.2f};
	particleEmitter.SetSourceModel(modelButterflyRight.get(), &worldTransformButterfly_right);

	ParticleEmitter particleEmitter2;
	particleEmitter2.Initialize(particleModel.get());
	particleEmitter2.emitShape_ = particleEmitter.emitShape_;
	particleEmitter2.count_ = particleEmitter.count_;
	particleEmitter2.frequency_ = particleEmitter.frequency_;
	particleEmitter2.particleScale_ = particleEmitter.particleScale_;
	particleEmitter2.lifeTimeMinMax_ = particleEmitter.lifeTimeMinMax_;
	particleEmitter2.SetSourceModel(modelButterflyLeft.get(), &worldTransformButterfly_left);

	// メインループ
	while (KujakuEngine::Update()) {
		// ======================================
		// 更新処理ここから
		// ======================================

		worldTransformButterfly.UpdateMatrix(camera);
		worldTransformButterfly_left.UpdateMatrix(camera);
		worldTransformButterfly_right.UpdateMatrix(camera);

		particleEmitter.Update(Time::GetDeltaTime(), camera);
		//particleEmitter2.Upd?ate(Time::GetDeltaTime(), camera);
		camera.UpdateMatrix();

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
		int particleCount = 30;
		ImGui::DragInt("ParticleEmitter count", &particleCount, 1, 0, 1000);
		ImGui::DragFloat("ParticleEmitter frequency", &particleEmitter.frequency_, 0.01f);

		particleEmitter.count_ = static_cast<uint32_t>(particleCount);

		particleEmitter2.lifeTimeMinMax_ = particleEmitter.lifeTimeMinMax_;
		particleEmitter2.count_ = particleEmitter.count_;
		particleEmitter2.frequency_ = particleEmitter.frequency_;
		particleEmitter2.particleScale_ = particleEmitter.particleScale_;
		ImGui::End();
#endif // USE_IMGUI

		// ======================================
		// 描画処理ここから
		// ======================================

		KujakuEngine::PreDraw();

		Model::PreDraw();
		Model::PostDraw();

		ParticleModel::PreDraw();
		particleEmitter.Draw();
		//particleEmitter2.Draw();
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
	case Scene::kTitle:
		// if (!triangleScene) {
		//	triangleScene = std::make_unique<TriangleScene>();
		//	triangleScene->Initialize();
		// }
		break;
	case Scene::kGame:
		break;
	default:
		break;
	}
}

void ChangeScene() {
	// switch (scene) {
	// case Scene::kTitle:
	//	if (titleScene->IsFinished()) {
	//		// シーン変更
	//		scene = Scene::kGame;
	//		// 旧シーンの解放
	//		delete titleScene;
	//		titleScene = nullptr;
	//		// 新シーンの生成と初期化
	//		gameScene = new GameScene;
	//		gameScene->Init(stageManager);
	//	}
	//	break;
	// case Scene::kGame:
	//	if (gameScene->GetReloadRequested()) {
	//		// シーンリロード
	//		delete gameScene;
	//		gameScene = nullptr;
	//		gameScene = new GameScene;
	//		gameScene->Init(stageManager);
	//	}
	//	break;
	// }
}

void UpdateScene() {
	// switch (scene) {
	// case Scene::kTitle:
	//	titleScene->Update();
	//	break;
	// case Scene::kGame:
	//	gameScene->Update();
	//	break;
	// default:
	//	break;
	// }
}

void DrawScene() {
	// switch (scene) {
	// case Scene::kTitle:
	//	titleScene->Draw();
	//	break;
	// case Scene::kGame:
	//	gameScene->Draw();
	//	break;
	// default:
	//	break;
	// }
}