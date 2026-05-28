#pragma once
#include <KujakuEngine.h>

class TriangleScene {
public:
	enum class TextureMode {
		UVChecker,
		MonsterBall,
		Fire,
	};
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
public:
	// カメラ
	KujakuEngine::Camera camera_;
	KujakuEngine::DebugCamera debugCamera_;

	// 三角形
	std::unique_ptr<KujakuEngine::Model> modelTriangleA_;
	KujakuEngine::WorldTransform worldTransformTriangleA_;

	std::unique_ptr<KujakuEngine::Model> modelTriangleB_;
	KujakuEngine::WorldTransform worldTransformTriangleB_;

	// テクスチャインデックス
	uint32_t textureIndexUVChecker_;
	uint32_t textureIndexMonsterBall_;
	uint32_t textureIndexFire_;

	TextureMode textureModeA_ = TextureMode::UVChecker;
	TextureMode textureModeB_ = TextureMode::UVChecker;

};
