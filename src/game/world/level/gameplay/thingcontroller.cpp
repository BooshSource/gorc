#include "thingcontroller.h"

Gorc::Game::World::Level::Gameplay::ThingController::ThingController(LevelPresenter& presenter)
	: presenter(presenter) {
	return;
}

Gorc::Game::World::Level::Gameplay::ThingController::~ThingController() {
	return;
}

void Gorc::Game::World::Level::Gameplay::ThingController::HandleAnimationMarker(Id<Thing> thing_id, Flags::KeyMarkerType marker) {
	return;
}
