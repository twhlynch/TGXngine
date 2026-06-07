#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "ProjectileInstance.h"

namespace WoS
{
using FNPTR_PROJECTILE_AWAKE = ProjectileInstance *(*)(String);
using FNPTR_PROJECTILE_CREATE = void (*)(Vector<sf::Sprite *> *, Vector<sf::Texture *> *, String);
using FNPTR_PROJECTILE_RENDER_WINDOW = void (*)(Vector<sf::Sprite *> *, String);
using FNPTR_PROJECTILE_UPDATE = void (*)(ProjectileInstance *, Vector<sf::Sprite *> *);
using FNPTR_PROJECTILE_CLEAR = void (*)();

using namespace nlohmann;

class Projectile
{
private:
	FNPTR_PROJECTILE_AWAKE awake;
	FNPTR_PROJECTILE_CREATE create;
	FNPTR_PROJECTILE_RENDER_WINDOW draw;
	FNPTR_PROJECTILE_UPDATE update;
	FNPTR_PROJECTILE_CLEAR clear;

	ProjectileInstance *projectileInstance;

	Vector<Unique<sf::Sprite>> sprites;
	Vector<Unique<sf::Texture>> textures;
	Vector<sf::Sprite *> spritePtrs;

public:
	Projectile(
		FNPTR_PROJECTILE_AWAKE,
		FNPTR_PROJECTILE_CREATE,
		FNPTR_PROJECTILE_UPDATE,
		FNPTR_PROJECTILE_RENDER_WINDOW,
		FNPTR_PROJECTILE_CLEAR);
	~Projectile();

	bool Create(json &data);
	void Draw();
	void Update();
	ProjectileInstance *GetProjectileInstance();
	void Clear();
};
} // namespace WoS
