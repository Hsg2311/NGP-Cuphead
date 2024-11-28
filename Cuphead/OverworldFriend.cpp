#include "OverworldFriend.hpp"
#include "ResourceHandler.hpp"
#include "Camera.hpp"
#include "InputDeviceHandler.hpp"
#include "Timer.hpp"

#include "SendingStorage.hpp"
#include <ranges>
#include <algorithm>

OverworldFriend::OverworldFriend(const std::vector<texInfo>& info) {
	createAnimator();

	std::ranges::for_each(info, [this](const texInfo& elem) {
		auto tex = ResourceHandler::getInst().loadTexture(elem.resKey, std::wstring(L"/texture/idle/overworld/" + elem.fileName));
		textures_.push_back(tex);

		getAnimator()->createAnimation(elem.resKey, tex, Vec2(0.f, 0.f),
			elem.sliceSize, Vec2(elem.sliceSize.x, 0.f), elem.duration, elem.frameCount, elem.offset);
		});

	getAnimator()->play(info.front().resKey);

}

void OverworldFriend::update() {
	auto objPos = getObjPos();
	

	
	getAnimator()->play(L"Idle_Up");

	getAnimator()->play(L"Idle_Down");
		
	
	getAnimator()->play(L"Idle_Left");
		

	getAnimator()->play(L"Idle_Right");
		

	getAnimator()->play(L"Idle_Left_Up");
		

	getAnimator()->play(L"Idle_Right_Up");
	
	getAnimator()->play(L"Idle_Left_Down");
		
	getAnimator()->play(L"Idle_Right_Down");
		





	setObjPos(objPos);
}

void OverworldFriend::render(HDC hdc) {
	componentRender(hdc);
}


