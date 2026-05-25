#pragma once
#include <KujakuEngine.h>

class TriangleScene {
public:
	enum class TriangleMode {
		Single,
		Double
	};

public:
	void Initialize();

	void Update();

	void Draw();
	
	// --- get ---

	/// <summary>
	/// シーンの再生成リクエスト
	/// </summary>
	bool GetReloadRequested() const { return KujakuEngine::Input::GetKeyTrigger(DIK_P); }

	// シーン終了
	bool IsFinished() const { return KujakuEngine::Input::GetKeyTrigger(DIK_SPACE); }
};
