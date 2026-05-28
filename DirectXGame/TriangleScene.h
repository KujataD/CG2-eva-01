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
	bool GetReloadRequested() const { return KujakuEngine::Input::GetKeyTrigger(DIK_R); }

	/// <summary>
	/// シーン終了
	/// </summary>
	bool IsFinished() const { return KujakuEngine::Input::GetKeyTrigger(DIK_F); }
public:

};
