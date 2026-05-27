#pragma once
#include "Butterfly.h"
#include <KujakuEngine.h>

class CinemaScene {
public:
	enum class CinemaMode { Single, Double };

public:
	void Initialize();

	void Update();

	void Draw();

	// --- get ---

	/// <summary>
	/// シーンの再生成リクエスト
	/// </summary>
	bool GetReloadRequested() const { return KujakuEngine::Input::GetKeyTrigger(DIK_P); }

	/// <summary>
	/// シーン終了
	/// </summary>
	bool IsFinished() const { return KujakuEngine::Input::GetKeyTrigger(DIK_SPACE); }

private:
	// --- シーン ---

	// カメラ
	KujakuEngine::Camera camera_;
	KujakuEngine::DebugCamera debugCamera_;

	// --- 蝶 ---

	// 羽のモデル
	std::unique_ptr<KujakuEngine::Model> modelButterflyWingRight_ = nullptr;
	std::unique_ptr<KujakuEngine::Model> modelButterflyWingLeft_ = nullptr;

	// 鱗粉のパーティクルモデル
	std::unique_ptr<KujakuEngine::ParticleModel> particleModelButterflyScales_ = nullptr;

	std::unique_ptr<Butterfly> butterfly_ = nullptr;
};
