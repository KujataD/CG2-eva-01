#include <KujakuEngine.h>
#include <Windows.h>
#include <cassert>
#include <fstream>

using namespace KujakuEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KujakuEngine::Initialize(L"LE2B_04_オオツカ_ダイチ_CG2_評価課題01", {0.0f, 0.0f, 0.01f, 1.0f});

	// メインループ
	while (KujakuEngine::Update()) {
		// ======================================
		// 更新処理ここから
		// ======================================



		// ======================================
		// 描画処理ここから
		// ======================================

		KujakuEngine::PreDraw();


		KujakuEngine::PostDraw();
	}

	// 解放処理
	// ------------------------------------------

	// エンジンの終了処理
	KujakuEngine::Finalize();

	return 0;
}