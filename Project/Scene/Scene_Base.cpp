#include "Scene_Base.hpp"

void Scene_Base::__changeScene(Scene_List next) {
	_isSceneEnd = true;
	_NextScene = next;
}

Scene_Base::Scene_Base()
	: _isSceneEnd(false)
	, _NextScene(Scene_List::Title)
{
}
