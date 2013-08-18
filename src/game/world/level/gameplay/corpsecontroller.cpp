#include "corpsecontroller.h"
#include "game/world/level/levelpresenter.h"
#include "game/world/level/levelmodel.h"

void Gorc::Game::World::Level::Gameplay::CorpseController::Update(int thing_id, double dt) {
	return;
}

void Gorc::Game::World::Level::Gameplay::CorpseController::CreateControllerData(int thing_id) {
	return;
}

void Gorc::Game::World::Level::Gameplay::CorpseController::RemoveControllerData(int thing_id) {
	return;
}

void Gorc::Game::World::Level::Gameplay::CorpseController::HandleAnimationMarker(int thing_id, enum Flags::KeyMarkerType marker) {
	if(marker == Flags::KeyMarkerType::Death) {
		// Play death thud
		presenter.SoundPresenter.PlaySoundClass(thing_id, Flags::SoundSubclassType::CorpseHit);
	}
}