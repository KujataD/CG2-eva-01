#include "Spider.h"

using namespace KujakuEngine;

void Spider::Initialize(KujakuEngine::Model* spiderWalkGrid, KujakuEngine::ParticleModel* particleModelTriangle, const KujakuEngine::Camera* camera) {
	// Nullチェック
	// ------------------------------------------
	assert(spiderWalkGrid);
	assert(particleModelTriangle);
	assert(camera);

	// 引数項の代入
	// ------------------------------------------
	modelSpiderWalkGrid_ = spiderWalkGrid;
	particleModelTriangle_ = particleModelTriangle;
	camera_ = camera;

	// パーティクル
	// ------------------------------------------
	particleModelTriangle_->Initialize();

	particleEmitter_.Initialize(particleModelTriangle_);
	particleEmitter_.emitShape_ = ParticleEmitter::kEmitSegmentEdge;
	particleEmitter_.count_ = 40;
	particleEmitter_.frequency_ = 0.01f;
	particleEmitter_.particleScale_ = { particleAllScale_, particleAllScale_, particleAllScale_ };
	particleEmitter_.lifeTimeMinMax_ = { 0.1f, 0.2f };

	modelSpiderWalkGrid_->SetColor({ 0.1f, 0.1f, 0.1f, 0.5f });
	// トランスフォーム
	// ------------------------------------------
	worldTransform_.Initialize();
	worldTransform_.translation_.y = 1.0f;

	worldTransformGrid_.Initialize();
	worldTransformGrid_.scale_ = { 2.0f, 1.0f, 2.0f };
}

void Spider::Update() {
	// 移動更新
	Walk();

	// パーティクル更新
	UpdateParticle();
}

void Spider::Draw() {
	ParticleModel::PreDraw();
	particleEmitter_.Draw();
	ParticleModel::PostDraw();
}

void Spider::Walk() {
	switch (state_) {
	case Spider::kAutoMove:

		animTranslationTimer_ += Time::GetDeltaTime();
		worldTransform_.translation_.x = std::cosf(animTranslationTimer_ * 0.5f) * 6.0f;
		worldTransform_.translation_.z = std::sinf(animTranslationTimer_ * 0.5f) * 6.0f;
		break;
	case Spider::kSelfMove:
		if (Input::GetKey(DIK_UP)) {
			worldTransform_.translation_.z += walkSpeed_ * Time::GetDeltaTime();
		}

		if (Input::GetKey(DIK_DOWN)) {
			worldTransform_.translation_.z -= walkSpeed_ * Time::GetDeltaTime();
		}

		if (Input::GetKey(DIK_RIGHT)) {
			worldTransform_.translation_.x += walkSpeed_ * Time::GetDeltaTime();
		}

		if (Input::GetKey(DIK_LEFT)) {
			worldTransform_.translation_.x -= walkSpeed_ * Time::GetDeltaTime();
		}
		break;
	default:
		break;
	}

	if (Input::GetKeyTrigger(DIK_V)) {
		if (state_ == kAutoMove) {
			state_ = kSelfMove;
		}
		else if (state_ == kSelfMove) {
			state_ = kAutoMove;
		}
	}

	worldTransformGrid_.UpdateMatrix(*camera_);
	worldTransform_.UpdateMatrix(*camera_);
}

void Spider::UpdateParticle() {
	std::vector<Segment> segments;

	std::vector<VertexData> vertices = modelSpiderWalkGrid_->GetVertices();

	for (const auto& vertex : vertices) {
		Vector3 vertexPos = { vertex.position.x, vertex.position.y, vertex.position.z };
		if (Length(worldTransform_.GetWorldPosition() - Transform(vertexPos, worldTransformGrid_.matWorld_)) > 5.0f) {
			continue;
		}
		Segment seg = ShapeUtil::MakeLimitedSegment(worldTransform_.GetWorldPosition(), Transform(vertexPos, worldTransformGrid_.matWorld_), 2.5f);
		segments.push_back(seg);
	}

	particleEmitter_.SetSourceSegments(segments);

	particleEmitter_.Update(Time::GetDeltaTime(), *camera_);
}
