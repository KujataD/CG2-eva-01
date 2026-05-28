#pragma once
#include "Spider.h"
#include <KujakuEngine.h>

class SpiderScene {
public:
	enum class CinemaMode { Buttefly };

public:
	void Initialize();

	void Update();

	void Draw();

	// --- get ---

	/// <summary>
	/// シーンの再生成リクエスト
	/// </summary>
	bool GetReloadRequested() const { return KujakuEngine::Input::GetKeyTrigger(DIK_R); }

	/// <summary>
	/// シーン終了
	/// </summary>
	bool IsFinished() const { return KujakuEngine::Input::GetKeyTrigger(DIK_F); }

private:
	// --- シーン ---

	// カメラ
	KujakuEngine::Camera camera_;
	KujakuEngine::DebugCamera debugCamera_;

	// --- 蜘蛛 ---
	std::unique_ptr<KujakuEngine::ParticleModel> particleModel_ = nullptr;
	std::unique_ptr<Spider> spider_ = nullptr;

	// --- 地形 ---
	std::unique_ptr<KujakuEngine::Model> modelSpiderWalkGrid_ = nullptr;
	std::unique_ptr<KujakuEngine::Model> modelGround_ = nullptr;
	KujakuEngine::WorldTransform worldTransformGround_;
};
