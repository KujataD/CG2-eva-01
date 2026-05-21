#pragma once

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
};
