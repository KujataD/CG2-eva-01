#include "Butterfly.h"

using namespace KujakuEngine;

void Butterfly::Initialize(KujakuEngine::Model* modelWingLeft, KujakuEngine::Model* modelWingRight, KujakuEngine::ParticleModel* particleModelTriangle, const KujakuEngine::Camera* camera) {
	// Nullチェック
	// ------------------------------------------
	assert(modelWingLeft);
	assert(modelWingRight);
	assert(particleModelTriangle);
	assert(camera);

	// 引数項の代入
	// ------------------------------------------
	modelWingLeft_ = modelWingLeft;
	modelWingRight_ = modelWingRight;
	particleModelTriangle_ = particleModelTriangle;
	camera_ = camera;

	// ワールド変換の初期化・設定
	// ------------------------------------------
	worldTransformButterfly_.Initialize();
	worldTransformButterfly_.rotation_.x = -std::numbers::pi_v<float> * 0.25f;

	worldTransformButterflyWingLeft_.Initialize();
	worldTransformButterflyWingLeft_.parent_ = &worldTransformButterfly_;

	worldTransformButterflyWingRight_.Initialize();
	worldTransformButterflyWingRight_.parent_ = &worldTransformButterfly_;

	// パーティクルの初期化・設定
	// ------------------------------------------
	particleModelTriangle_->Initialize();
	particleModelTriangle_->SetBlendMode(BlendMode::kAdd);

	particleEmitterButterflyWingLeft_.Initialize(particleModelTriangle_);
	particleEmitterButterflyWingLeft_.emitShape_ = ParticleEmitter::kEmitShapeModelEdge;
	particleEmitterButterflyWingLeft_.count_ = 20;
	particleEmitterButterflyWingLeft_.frequency_ = 0.02f;
	particleEmitterButterflyWingLeft_.particleScale_ = {particleAllScale_, particleAllScale_, particleAllScale_};
	particleEmitterButterflyWingLeft_.lifeTimeMinMax_ = {0.1f, 1.0f};
	particleEmitterButterflyWingLeft_.SetSourceVertices(modelWingLeft_->GetVertices(), &worldTransformButterflyWingLeft_);

	particleEmitterButterflyWingRight_.Initialize(particleModelTriangle_);
	particleEmitterButterflyWingRight_.emitShape_ = particleEmitterButterflyWingLeft_.emitShape_;
	particleEmitterButterflyWingRight_.count_ = particleEmitterButterflyWingLeft_.count_;
	particleEmitterButterflyWingRight_.frequency_ = particleEmitterButterflyWingLeft_.frequency_;
	particleEmitterButterflyWingRight_.particleScale_ = particleEmitterButterflyWingLeft_.particleScale_;
	particleEmitterButterflyWingRight_.lifeTimeMinMax_ = particleEmitterButterflyWingLeft_.lifeTimeMinMax_;
	particleEmitterButterflyWingRight_.SetSourceVertices(modelWingRight_->GetVertices(), &worldTransformButterflyWingRight_);

	animWingRotationTimer_ = 0.0f;
	animTranslationTimer_ = 0.0f;

	modelWingLeft_->SetColor({1.0f, 1.0f, 1.0f, 0.05f});
	modelWingRight_->SetColor({1.0f, 1.0f, 1.0f, 0.05f});
}

void Butterfly::Update() {
	// アニメーション更新
	UpdateAnim();

	// パーティクル更新
	UpdateParticle();
}

void Butterfly::Draw() {
	//modelWingLeft_->Draw(worldTransformButterflyWingLeft_, *camera_, kFillModeWireframe);
	//modelWingRight_->Draw(worldTransformButterflyWingRight_, *camera_, kFillModeWireframe);

	ParticleModel::PreDraw();
	particleEmitterButterflyWingLeft_.Draw();
	ParticleModel::PostDraw();
}

void Butterfly::UpdateAnim() {

	// 羽根を回転させるアニメーション
	// ------------------------------------------
	animWingRotationTimer_ += Time::GetDeltaTime();
	if (animWingRotationTimer_ < animWingRotationDuration_ * 0.5f) {
		// tを求める
		float t = animWingRotationTimer_ / (animWingRotationDuration_ * 0.5f);

		// 最小→最大回転までイーズラープ
		worldTransformButterflyWingLeft_.rotation_.y = EaseUtil::EaseLerp(animWingRotationMin_, animWingRotationMax_, t, EaseUtil::EaseType::InOutQuad);
		worldTransformButterflyWingRight_.rotation_.y = EaseUtil::EaseLerp(-animWingRotationMin_, -animWingRotationMax_, t, EaseUtil::EaseType::InOutQuad);
	} else if (animWingRotationTimer_ >= animWingRotationDuration_ * 0.5f && animWingRotationTimer_ < animWingRotationDuration_) {
		// tを求める
		float t = (animWingRotationTimer_ - animWingRotationDuration_ * 0.5f) / (animWingRotationDuration_ * 0.5f);

		// 最小→最大回転までイーズラープ
		worldTransformButterflyWingLeft_.rotation_.y = EaseUtil::EaseLerp(animWingRotationMax_, animWingRotationMin_, t, EaseUtil::EaseType::InOutQuad);
		worldTransformButterflyWingRight_.rotation_.y = EaseUtil::EaseLerp(-animWingRotationMax_, -animWingRotationMin_, t, EaseUtil::EaseType::InOutQuad);
	} else {
		// リセット
		animWingRotationTimer_ = 0.0f;
	}

	// ふわふわ浮かぶアニメーション
	// ------------------------------------------
	animTranslationTimer_ += Time::GetDeltaTime();
	worldTransformButterfly_.translation_.x = std::cosf(animTranslationTimer_ * 0.5f);
	worldTransformButterfly_.translation_.y = std::sinf(animTranslationTimer_);
	if (animTranslationTimer_ >= std::numbers::pi_v<float> * 4.0f) {
		animTranslationTimer_ = 0.0f;
	}

	// 各ワールドトランスフォームの更新
	// ------------------------------------------
	worldTransformButterfly_.UpdateMatrix(*camera_);
	worldTransformButterflyWingLeft_.UpdateMatrix(*camera_);
	worldTransformButterflyWingRight_.UpdateMatrix(*camera_);
}

void Butterfly::UpdateParticle() {
	particleEmitterButterflyWingLeft_.Update(Time::GetDeltaTime(), *camera_);
	particleEmitterButterflyWingRight_.Update(Time::GetDeltaTime(), *camera_);
}
