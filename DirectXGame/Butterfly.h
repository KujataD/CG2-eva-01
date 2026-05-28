#pragma once
#include <KujakuEngine.h>


class Butterfly {
public:
	Butterfly() = default;
	~Butterfly() = default;

	void Initialize(KujakuEngine::Model* modelWingLeft, KujakuEngine::Model* modelWingRight, KujakuEngine::ParticleModel* particleModelTriangle, const KujakuEngine::Camera* camera);
	void Update();
	void Draw();

private:
	void UpdateAnim();
	void UpdateParticle();

private:
	// ワールド変換
	KujakuEngine::WorldTransform worldTransformButterfly_;
	KujakuEngine::WorldTransform worldTransformButterflyWingRight_;
	KujakuEngine::WorldTransform worldTransformButterflyWingLeft_;

	KujakuEngine::Model* modelWingLeft_ = nullptr;
	KujakuEngine::Model* modelWingRight_ = nullptr;

	// パーティクル
	// ------------------------------------------
	KujakuEngine::ParticleModel* particleModelTriangle_ = nullptr;

	// 右翅のパーティクルエミッター
	KujakuEngine::ParticleEmitter particleEmitterButterflyWingRight_;

	// 左翅のパーティクルエミッター
	KujakuEngine::ParticleEmitter particleEmitterButterflyWingLeft_;

	// パーティクルのスケール
	static inline float particleAllScale_ = 0.05f;

	// アニメーション
	float animWingRotationTimer_ = 0.0f;
	float animTranslationTimer_ = 0.0f;

	static inline float animWingRotationDuration_ = 1.0f;
	static inline float animWingRotationMax_ = std::numbers::pi_v<float> * 0.45f;
	static inline float animWingRotationMin_ = -std::numbers::pi_v<float> * 0.3f;

	const KujakuEngine::Camera* camera_ = nullptr;

};
