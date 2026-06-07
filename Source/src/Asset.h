#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "AssetState.h"
#include "Core.h"

namespace WoS
{
using FNPTR_ASSET_AWAKE = AssetState *(*)(String);
using FNPTR_ASSET_CREATE = void (*)(Vector<sf::Sprite *> *, Vector<sf::Texture *> *, String);
using FNPTR_ASSET_RENDER_WINDOW = void (*)(Vector<sf::Sprite *> *);
using FNPTR_ASSET_UPDATE = void (*)(AssetState *, Vector<sf::Sprite *> *);
using FNPTR_ASSET_CLEAR = void (*)();

using namespace nlohmann;

class Asset
{
private:
	FNPTR_ASSET_AWAKE awake;
	FNPTR_ASSET_CREATE create;
	FNPTR_ASSET_RENDER_WINDOW draw;
	FNPTR_ASSET_UPDATE update;
	FNPTR_ASSET_CLEAR clear;

	AssetState *assetState = nullptr;

	Vector<Unique<sf::Sprite>> sprites;
	Vector<Unique<sf::Texture>> textures;
	Vector<sf::Sprite *> spritePtrs;

public:
	Asset(
		FNPTR_ASSET_AWAKE,
		FNPTR_ASSET_CREATE,
		FNPTR_ASSET_UPDATE,
		FNPTR_ASSET_RENDER_WINDOW,
		FNPTR_ASSET_CLEAR);
	~Asset();

	Asset(const Asset &) = delete;
	Asset &operator=(const Asset &) = delete;

	bool Create(json &data);
	void Draw();
	void Update();
	void Clear();

	AssetState *GetAssetState() { return assetState; }
};
} // namespace WoS
