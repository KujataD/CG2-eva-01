#pragma once
#include <KujakuEngine.h>


class Butterfly {
public:
	Butterfly() = default;
	~Butterfly() = default;

	void Initialize(KujakuEngine::Model* modelWingLeft, KujakuEngine::Model* modelWingRight, const KujakuEngine::Camera* camera);
	void Update();
	void Draw();

private:
	// ワールド変換
	KujakuEngine::WorldTransform worldTransformButterfly_;
	KujakuEngine::WorldTransform worldTransformButterflyWingRight_;
	KujakuEngine::WorldTransform worldTransformButterflyWingLeft_;

	KujakuEngine::Model* modelWingLeft_ = nullptr;
	KujakuEngine::Model* modelWingRight_ = nullptr;

	// 右翅のパーティクルエミッター
	KujakuEngine::ParticleEmitter particleEmitterButterflyWingRight_;

	// 左翅のパーティクルエミッター
	KujakuEngine::ParticleEmitter particleEmitterButterflyWingLeft_;

	// アニメーション
	float animWingTimer_ = 0.0f;
	float animFlappingTimer_ = 0.0f;

	static inline float animWingDuration_ = 1.0f;
	static inline float animFlappingDuration_ = 1.0f;
	static inline float animWingRotationMax_ = std::numbers::pi_v<float> * 0.45f;
	static inline float animWingRotationMin_ = -std::numbers::pi_v<float> * 0.3f;

	const KujakuEngine::Camera* camera_ = nullptr;

};
