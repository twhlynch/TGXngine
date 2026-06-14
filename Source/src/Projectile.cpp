#include "Projectile.h"
#include "Logs.h"
#include "WorldState.h"

namespace TGX
{
Projectile::Projectile(
	FNPTR_PROJECTILE_AWAKE awake,
	FNPTR_PROJECTILE_CREATE create,
	FNPTR_PROJECTILE_UPDATE update,
	FNPTR_PROJECTILE_RENDER_WINDOW draw,
	FNPTR_PROJECTILE_CLEAR clear)
	: awake(awake), create(create), draw(draw), update(update), clear(clear)
{
	Log::Success("Projectile Created");
}

Projectile::~Projectile()
{
	Log::Clean("Delete Projectile");

	if (clear)
	{
		clear();
	}

	spritePtrs.clear();
	sprites.clear();
	textures.clear();

	projectileInstance = nullptr;
	Log::Success("Projectile memory cleared");
}

bool Projectile::Create(json &data)
{
	Log::Info("Projectile Create");
	String name = data["name"];

	WorldState &world = WorldState::GetInstance();

	if (world.projectileRegistry.contains(name))
	{
		Log::Info("Projectile asset '" + name + "' already exists. Skipping.");
		return true;
	}

	projectileInstance = awake(name);
	if (!projectileInstance)
	{
		return false;
	}

	projectileInstance->spriteIndex = static_cast<int>(spritePtrs.size());

	Vector<sf::Sprite *> rawSprites;
	Vector<sf::Texture *> rawTextures;
	create(&rawSprites, &rawTextures, name);

	for (auto *s : rawSprites)
	{
		sprites.emplace_back(Unique<sf::Sprite>(s));
		spritePtrs.emplace_back(s);
	}
	for (auto *t : rawTextures)
	{
		textures.emplace_back(Unique<sf::Texture>(t));
	}

	world.projectileRegistry.insert({name,
									 Unique<ProjectileInstance>(projectileInstance)});

	Log::Success("Projectile Registered: " + name);
	return true;
}

void Projectile::Draw()
{
	if (spritePtrs.empty() || !projectileInstance)
	{
		return;
	}

	draw(&spritePtrs, projectileInstance->GetName());
}

void Projectile::Update()
{
	if (spritePtrs.empty() || !projectileInstance)
	{
		return;
	}

	update(projectileInstance, &spritePtrs);
}

ProjectileInstance *Projectile::GetProjectileInstance()
{
	return projectileInstance;
}

void Projectile::Clear()
{
	clear();
}
} // namespace TGX
