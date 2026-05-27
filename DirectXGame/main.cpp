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
	KujakuEngine::Initialize(L"LE2B_04_オオツカ_ダイチ_CG2_評価課題01");

	// タイトルシーンの初期化
	scene = Scene::kCinema;

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