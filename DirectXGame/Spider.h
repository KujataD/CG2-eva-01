#pragma once
#include <KujakuEngine.h>


class Spider {
public:

	enum State{
		kAutoMove,
		kSelfMove,
	};

public:
	Spider() = default;
	~Spider() = default;

	void Initialize(KujakuEngine::Model* spiderWalkGrid, KujakuEngine::ParticleModel* particleModelTriangle, const KujakuEngine::Camera* camera);
	void Update();
	void Draw();

private:
	void Walk();
	void UpdateParticle();

private:
	// ワールド変換
	KujakuEngine::WorldTransform worldTransform_;
	KujakuEngine::WorldTransform worldTransformGrid_;

	KujakuEngine::Model* modelSpiderWalkGrid_ = nullptr;

	// パーティクル
	// ------------------------------------------
	KujakuEngine::ParticleModel* particleModelTriangle_ = nullptr;

	// パーティクルエミッター
	KujakuEngine::ParticleEmitter particleEmitter_;

	// パーティクルのスケール
	static inline float particleAllScale_ = 0.3f;

	static inline float walkSpeed_ = 5.0f;
	
	float animTranslationTimer_ = 0.0f;

	const KujakuEngine::Camera* camera_ = nullptr;	

	State state_ = kAutoMove;
};
