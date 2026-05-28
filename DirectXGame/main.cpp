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
std::unique_ptr<Sprite> spriteCameraInfo = nullptr;
std::unique_ptr<Sprite> spriteSceneInfoButterfly = nullptr;
std::unique_ptr<Sprite> spriteSceneInfoSpider = nullptr;
std::unique_ptr<Sprite> spriteSceneInfoTriangle = nullptr;

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
	KujakuEngine::Initialize(L"リテラシー");

	// タイトルシーンの初期化
	scene = Scene::kButtefly;

	uint32_t textureIndexCameraInfo = TextureManager::GetInstance()->LoadTexture("Resources/camera_info.png");
	uint32_t textureIndexSceneInfoButterfly = TextureManager::GetInstance()->LoadTexture("Resources/scene_info_b.png");
	uint32_t textureIndexSceneInfoSpider = TextureManager::GetInstance()->LoadTexture("Resources/scene_info_s.png");
	uint32_t textureIndexSceneInfoTriangle = TextureManager::GetInstance()->LoadTexture("Resources/scene_info_t.png");
	spriteCameraInfo = std::unique_ptr<Sprite>(Sprite::Create(textureIndexCameraInfo, { 0.0f, 720.0f - 96.0f }, 480, 96));
	spriteSceneInfoButterfly = std::unique_ptr<Sprite>(Sprite::Create(textureIndexSceneInfoButterfly, { 1280.0f - 270.0f - 32.0f, 720.0f - 96.0f }, 270, 96));
	spriteSceneInfoSpider = std::unique_ptr<Sprite>(Sprite::Create(textureIndexSceneInfoSpider, { 1280.0f - 270.0f - 32.0f, 720.0f - 96.0f }, 270, 96));
	spriteSceneInfoTriangle = std::unique_ptr<Sprite>(Sprite::Create(textureIndexSceneInfoTriangle, { 1280.0f - 270.0f - 32.0f,720.0f - 96.0f }, 270, 96));

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
		}
		else if (triangleScene->IsFinished()) {
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
		}
		else if (butterflyScene->IsFinished()) {
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
		}
		else if (spiderScene->IsFinished()) {
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
		Sprite::PreDraw();
		spriteCameraInfo->Draw();
		spriteSceneInfoTriangle->Draw();
		Sprite::PostDraw();
		break;
	case Scene::kButtefly:
		butterflyScene->Draw();
		Sprite::PreDraw();
		spriteCameraInfo->Draw();
		spriteSceneInfoButterfly->Draw();
		Sprite::PostDraw();
		break;
	case Scene::kSpider:
		spiderScene->Draw();
		Sprite::PreDraw();
		spriteCameraInfo->Draw();
		spriteSceneInfoSpider->Draw();
		Sprite::PostDraw();
		break;
	default:
		break;
	}
}