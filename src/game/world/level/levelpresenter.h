#pragma once

#include "framework/place/presenter.h"
#include "game/components.h"
#include "levelplace.h"
#include "cog/vm/virtualmachine.h"
#include "sounds/music.h"
#include "content/flags/animflag.h"
#include "content/flags/damageflag.h"
#include "content/assets/inventory.h"
#include "game/flags/difficultymode.h"
#include "game/world/level/animations/animationpresenter.h"
#include "game/world/level/scripts/scriptpresenter.h"
#include "game/world/level/sounds/soundpresenter.h"
#include "game/world/level/keys/keypresenter.h"
#include "game/world/level/gameplay/actorcontroller.h"
#include "game/world/level/gameplay/playercontroller.h"
#include "game/world/level/gameplay/cogcontroller.h"
#include "game/world/level/gameplay/ghostcontroller.h"
#include "game/world/level/gameplay/itemcontroller.h"
#include "game/world/level/gameplay/corpsecontroller.h"

#include <memory>
#include <stack>

namespace Gorc {
namespace Game {
namespace World {
namespace Level {

class LevelModel;
class Thing;

class LevelPresenter : public Gorc::Place::Presenter {
private:
	// In-data constants seem to be roughly 8 times greater than they should be.
	// Use RateFactor to scale all rates from input data.
	static constexpr double RateFactor = 1.0 / 8.0;

	// Scratch space
	std::vector<std::tuple<unsigned int, unsigned int>> UpdatePathSectorScratch;

	Components& components;
	LevelPlace place;

	void InitializeWorld();
	void PhysicsTickUpdate(double dt);

	bool PointInsideSector(const Math::Vector<3>& position, const Content::Assets::LevelSector& sec);
	bool PointPathPassesThroughAdjoin(const Math::Vector<3>& p0, const Math::Vector<3>& p1,
			const Content::Assets::LevelSector& sec, const Content::Assets::LevelSurface& surf);
	bool UpdatePathSector(const Math::Vector<3>& p0, const Math::Vector<3>& p1,
			const Content::Assets::LevelSector& sector, std::vector<std::tuple<unsigned int, unsigned int>>& path);

	void UpdateThingSector(Id<Thing> thing_id, Thing& thing, const Math::Vector<3>& oldThingPosition);
	void UpdateCamera();

	Gameplay::ThingController& GetThingController(Flags::ThingType type);

	bool need_respawn = false;
	void DoRespawn();

public:
	std::unique_ptr<LevelModel> Model;

	Content::Assets::Inventory Inventory;

	Animations::AnimationPresenter AnimationPresenter;
	Scripts::ScriptPresenter ScriptPresenter;
	Sounds::SoundPresenter SoundPresenter;
	Keys::KeyPresenter KeyPresenter;

	Gameplay::ActorController ActorController;
	Gameplay::PlayerController PlayerController;
	Gameplay::CogController CogController;
	Gameplay::GhostController GhostController;
	Gameplay::ItemController ItemController;
	Gameplay::CorpseController CorpseController;

	LevelPresenter(Components& components, const LevelPlace& place);

	void Start(Event::EventBus& eventBus);
	void Update(double dt);

	void TranslateCamera(const Math::Vector<3>& amt);
	void YawCamera(double amt);
	void PitchCamera(double amt);
	void Respawn();
	void Jump();
	void Activate();
	void Damage();
	void ThingSighted(Id<Thing> thing_id);

	// Frame verbs
	int GetCurFrame(Id<Thing> thing_id);
	void MoveToFrame(Id<Thing> thing_id, int frame, float speed);

	// Player verbs
	Id<Thing> GetLocalPlayerThing();

	// Sector verbs
	void SetSectorAdjoins(int sector_id, bool state);
	void SetSectorLight(int sector_id, float value, float delay);
	void SetSectorThrust(int sector_id, const Math::Vector<3>& thrust);
	void SetSectorTint(int sector_id, const Math::Vector<3>& color);

	// Surface verbs
	void ClearAdjoinFlags(int surface, FlagSet<Flags::AdjoinFlag> flags);
	Math::Vector<3> GetSurfaceCenter(int surface);
	void SetAdjoinFlags(int surface, FlagSet<Flags::AdjoinFlag> flags);
	void SetFaceGeoMode(int surface, Flags::GeometryMode mode);
	void SetSurfaceFlags(int surface, FlagSet<Flags::SurfaceFlag> flags);

	// System verbs
	int LoadSound(const char* sound);

	// Thing action verbs
	Id<Thing> CreateThing(const Content::Assets::Template& tpl, unsigned int sector_num, const Math::Vector<3>& pos, const Math::Vector<3>& orientation);
	Id<Thing> CreateThing(const std::string& tpl_name, unsigned int sector_num, const Math::Vector<3>& pos, const Math::Vector<3>& orientation);
	Id<Thing> CreateThing(int tpl_id, unsigned int sector_num, const Math::Vector<3>& pos, const Math::Vector<3>& orientation);

	void AdjustThingPosition(Id<Thing> thing_id, const Math::Vector<3>& new_pos);

	Id<Thing> CreateThingAtThing(int tpl_id, Id<Thing> thing_id);
	float DamageThing(Id<Thing> thing_id, float damage, FlagSet<Flags::DamageFlag> flags, int damager_id);
	void DestroyThing(Id<Thing> thing_id);
	Math::Vector<3> GetThingPos(Id<Thing> thing_id);
	bool IsThingMoving(Id<Thing> thing_id);

	// Thing property verbs
	int GetThingSector(Id<Thing> thing_id);
	void SetThingType(Id<Thing> thing_id, Flags::ThingType type);

	static void RegisterVerbs(Cog::Verbs::VerbTable&, Components&);
};

}
}
}
}
