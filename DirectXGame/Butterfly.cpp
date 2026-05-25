#include "Butterfly.h"

void Butterfly::Initialize(KujakuEngine::Model* modelWingLeft, KujakuEngine::Model* modelWingRight, const KujakuEngine::Camera* camera) { 
	assert(modelWingLeft); 
	assert(modelWingRight); 
	
	modelWingLeft_ = modelWingLeft;
	modelWingRight_ = modelWingRight;


}

void Butterfly::Update() {
	
}

void Butterfly::Draw() {}
