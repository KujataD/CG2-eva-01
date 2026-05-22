#include <KujakuEngine.h>

#include "TriangleScene.h"

using namespace KujakuEngine;

enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
};

Scene scene = Scene::kUnknown;

//std::unique_ptr<TriangleScene> triangleScene = nullptr;

void InitScene();
void UpdateScene();
void DrawScene();
void ChangeScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KujakuEngine::Initialize(L"LE2B_04_オオツカ_ダイチ_CG2_評価課題01", { 0.0f, 0.0f, 0.01f, 1.0f });
	
	//triangleScene = std::make_unique<TriangleScene>();

	Camera camera;
	camera.Initialize();
	camera.translation_.z = -10.0f;
	camera.UpdateMatrix();

	WorldTransform worldTransformTetrahedron;
	worldTransformTetrahedron.Initialize();

	std::unique_ptr<Model> tetrahedronModel = std::unique_ptr<Model>(Model::CreateTriangle("Resources/white1x1.png"));

	std::unique_ptr<ParticleModel> particleModel = std::unique_ptr<ParticleModel>(ParticleModel::CreateTriangle("Resources/white1x1.png", true));
	particleModel->Initialize();

	ParticleEmitter particleEmitter;
	particleEmitter.Initialize(particleModel.get());
	particleEmitter.emitShape_ = ParticleEmitter::kEmitShapeModelEdge;
	particleEmitter.count_ = 20;
	particleEmitter.SetSourceModel(tetrahedronModel.get(), &worldTransformTetrahedron);
	particleEmitter.particleScale_ = {0.05f, 0.05f, 0.05f};
	
	// メインループ
	while (KujakuEngine::Update()) {
		// ======================================
		// 更新処理ここから
		// ======================================

		//worldTransformTetrahedron.rotation_.y += 0.02f;
		worldTransformTetrahedron.UpdateMatrix(camera);

		particleEmitter.Update(Time::GetDeltaTime(), camera);
		camera.UpdateMatrix();

#ifdef USE_IMGUI
		ImGui::Begin("LightManager");
		auto& light = DirectionalLight::GetInstance()->GetData();
		ImGui::ColorEdit3("Light Color", &light.color.x);
		ImGui::SliderFloat3("Direction", &light.direction.x, -1.0f, 1.0f);
		ImGui::DragFloat("Intensity", &light.intensity, 0.01f);

		ImGui::End();
#endif // USE_IMGUI


		// ======================================
		// 描画処理ここから
		// ======================================

		KujakuEngine::PreDraw();

		ParticleModel::PreDraw();
		particleEmitter.Draw();
		ParticleModel::PostDraw();

		Model::PreDraw();
		tetrahedronModel->Draw(worldTransformTetrahedron, camera, kFillModeWireframe);
		Model::PostDraw();


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
		//if (!triangleScene) {
		//	triangleScene = std::make_unique<TriangleScene>();
		//	triangleScene->Initialize();
		//}
		break;
	case Scene::kGame:
		break;
	default:
		break;
	}
}

void ChangeScene() {
	//switch (scene) {
	//case Scene::kTitle:
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
	//case Scene::kGame:
	//	if (gameScene->GetReloadRequested()) {
	//		// シーンリロード
	//		delete gameScene;
	//		gameScene = nullptr;
	//		gameScene = new GameScene;
	//		gameScene->Init(stageManager);
	//	}
	//	break;
	//}
}

void UpdateScene() {
	//switch (scene) {
	//case Scene::kTitle:
	//	titleScene->Update();
	//	break;
	//case Scene::kGame:
	//	gameScene->Update();
	//	break;
	//default:
	//	break;
	//}
}

void DrawScene() {
	//switch (scene) {
	//case Scene::kTitle:
	//	titleScene->Draw();
	//	break;
	//case Scene::kGame:
	//	gameScene->Draw();
	//	break;
	//default:
	//	break;
	//}
}