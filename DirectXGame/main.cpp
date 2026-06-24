#include <KujakuEngine.h>

#include "ButterflyScene.h"
#include "SpiderScene.h"

using namespace KujakuEngine;

enum class Scene {
	kUnknown = 0,
	kButtefly,
	kSpider,
};

Scene scene = Scene::kUnknown;

uint32_t textureIndexCameraInfo;
uint32_t textureIndexSceneInfoButterfly;
uint32_t textureIndexSceneInfoSpider;
std::unique_ptr<Sprite> spriteCameraInfo = nullptr;
std::unique_ptr<Sprite> spriteSceneInfo = nullptr;

std::unique_ptr<ButterflyScene> butterflyScene = nullptr;
std::unique_ptr<SpiderScene> spiderScene = nullptr;

void InitScene();
void UpdateScene();
void DrawScene();
void ChangeScene();

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	KujakuEngine::Initialize(L"ButterflyAndSpider");

	scene = Scene::kButtefly;

	textureIndexCameraInfo = TextureManager::GetInstance()->LoadTexture("Resources/camera_info.png");
	textureIndexSceneInfoButterfly = TextureManager::GetInstance()->LoadTexture("Resources/scene_info_b.png");
	textureIndexSceneInfoSpider = TextureManager::GetInstance()->LoadTexture("Resources/scene_info_s.png");
	spriteCameraInfo = std::unique_ptr<Sprite>(Sprite::Create(textureIndexCameraInfo, { 0.0f, 720.0f - 96.0f }, 480, 96));
	spriteSceneInfo = std::unique_ptr<Sprite>(Sprite::Create(textureIndexSceneInfoButterfly, { 1280.0f - 270.0f - 32.0f, 720.0f - 96.0f }, 270, 96));
	InitScene();

	while (KujakuEngine::Update()) {
		ChangeScene();
		UpdateScene();

		KujakuEngine::PreDraw();
		DrawScene();
		KujakuEngine::PostDraw();
	}

	KujakuEngine::Finalize();
	return 0;
}

void InitScene() {
	switch (scene) {
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
	case Scene::kButtefly:
		if (butterflyScene->GetReloadRequested()) {
			butterflyScene = std::make_unique<ButterflyScene>();
			butterflyScene->Initialize();
		}
		else if (butterflyScene->IsFinished()) {
			scene = Scene::kSpider;
			butterflyScene.reset();
			spiderScene = std::make_unique<SpiderScene>();
			spiderScene->Initialize();
		}
		break;
	case Scene::kSpider:
		if (spiderScene->GetReloadRequested()) {
			spiderScene = std::make_unique<SpiderScene>();
			spiderScene->Initialize();
		}
		else if (spiderScene->IsFinished()) {
			scene = Scene::kButtefly;
			spiderScene.reset();
			butterflyScene = std::make_unique<ButterflyScene>();
			butterflyScene->Initialize();
		}
		break;
	default:
		break;
	}
}

void UpdateScene() {
	switch (scene) {
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
	case Scene::kButtefly:
		butterflyScene->Draw();
		Sprite::PreDraw();
		spriteCameraInfo->Draw();
		spriteSceneInfo->SetTexture(textureIndexSceneInfoButterfly);
		spriteSceneInfo->Draw();
		Sprite::PostDraw();
		break;
	case Scene::kSpider:
		spiderScene->Draw();
		Sprite::PreDraw();
		spriteCameraInfo->Draw();
		spriteSceneInfo->SetTexture(textureIndexSceneInfoSpider);
		spriteSceneInfo->Draw();
		Sprite::PostDraw();
		break;
	default:
		break;
	}
}
