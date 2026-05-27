#include <KujakuEngine.h>

#include "ButterflyScene.h"
#include "SpiderScene.h"
#include "TriangleScene.h"

using namespace KujakuEngine;

enum class Scene {
	kUnknown = 0,
	kTriangle,
	kButtefly,
	kSpider,
};

Scene scene = Scene::kUnknown;

std::unique_ptr<TriangleScene> triangleScene = nullptr;
std::unique_ptr<ButterflyScene> butterflyScene = nullptr;
std::unique_ptr<SpiderScene> spiderScene = nullptr;

void InitScene();
void UpdateScene();
void DrawScene();
void ChangeScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KujakuEngine::Initialize(L"LE2B_04_オオツカ_ダイチ_CG2_評価課題01");

	// タイトルシーンの初期化
	scene = Scene::kButtefly;

	InitScene();

	// メインループ
	while (KujakuEngine::Update()) {
		// ======================================
		// 更新処理ここから
		// ======================================

		ChangeScene();
		UpdateScene();

		// ======================================
		// 描画処理ここから
		// ======================================

		KujakuEngine::PreDraw();

		DrawScene();

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
	case Scene::kButtefly:
		if (!butterflyScene) {
			butterflyScene = std::make_unique<ButterflyScene>();
			butterflyScene->Initialize();
		}
		break;
	case Scene::kSpider:
		if (!spiderScene) {
			spiderScene = std::make_unique<SpiderScene>();
			spiderScene->Initialize();
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
			scene = Scene::kButtefly;
			// 旧シーンの解放
			triangleScene.reset();
			// 新シーンの生成と初期化
			butterflyScene = std::make_unique<ButterflyScene>();
			butterflyScene->Initialize();
		}
		break;
	case Scene::kButtefly:
		if (butterflyScene->GetReloadRequested()) {
			// シーンリロード
			butterflyScene.reset();
			butterflyScene = std::make_unique<ButterflyScene>();
			butterflyScene->Initialize();
		} else if (butterflyScene->IsFinished()) {
			// シーン変更
			scene = Scene::kSpider;
			// 旧シーンの解放
			butterflyScene.reset();
			// 新シーンの生成と初期化
			spiderScene = std::make_unique<SpiderScene>();
			spiderScene->Initialize();
		}
		break;
	case Scene::kSpider:
		if (spiderScene->GetReloadRequested()) {
			// シーンリロード
			spiderScene.reset();
			spiderScene = std::make_unique<SpiderScene>();
			spiderScene->Initialize();
		} else if (spiderScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTriangle;
			// 旧シーンの解放
			spiderScene.reset();
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
	case Scene::kButtefly:
		butterflyScene->Update();
		break;
	case Scene::kSpider:
		spiderScene->Update();
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
	case Scene::kButtefly:
		butterflyScene->Draw();
		break;
	case Scene::kSpider:
		spiderScene->Draw();
		break;
	default:
		break;
	}
}