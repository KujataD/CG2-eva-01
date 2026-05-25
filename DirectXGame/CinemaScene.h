#pragma once
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

	// --- 蝶 ---

	// ワールド変換
	KujakuEngine::WorldTransform worldTransformButterfly_;
	KujakuEngine::WorldTransform worldTransformButterflyWingRight_;
	KujakuEngine::WorldTransform worldTransformButterflyWingLeft_;

	// 羽のモデル
	std::unique_ptr<KujakuEngine::Model> modelButterflyWingRight_;
	std::unique_ptr<KujakuEngine::Model> modelButterflyWingLeft_;

	// 鱗粉のパーティクルモデル
	std::unique_ptr<KujakuEngine::ParticleModel> particleModelButterflyScales_;

	// 右翅のパーティクルエミッター
	KujakuEngine::ParticleEmitter particleEmitterButterflyWingRight_;

	// 左翅のパーティクルエミッター
	KujakuEngine::ParticleEmitter particleEmitterButterflyWingLeft_;

};
