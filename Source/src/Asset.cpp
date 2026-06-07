#include "Asset.h"
#include "Logs.h"
#include "WorldState.h"

namespace WoS
{
Asset::Asset(
	FNPTR_ASSET_AWAKE awake,
	FNPTR_ASSET_CREATE create,
	FNPTR_ASSET_UPDATE update,
	FNPTR_ASSET_RENDER_WINDOW draw,
	FNPTR_ASSET_CLEAR clear)
	: awake(awake), create(create), draw(draw), update(update), clear(clear)
{
	Log::Success("Asset Controller Created");
}

Asset::~Asset()
{
	Log::Clean("Cleaning up Asset Controller");
	sprites.clear();
	textures.clear();
	spritePtrs.clear();

	assetState = nullptr;
}

bool Asset::Create(json &data)
{
	Log::Info("Creating Asset Instance");
	String name = data.value("name", "Unnamed");

	AssetState *newState = awake(name);
	if (!newState)
	{
		Log::Error("Failed to awake asset: " + name);
		return false;
	}

	assetState = newState;

	Vector<sf::Sprite *> rawSprites;
	Vector<sf::Texture *> rawTextures;
	create(&rawSprites, &rawTextures, name);

	for (auto *s : rawSprites)
	{
		if (s)
		{
			sprites.emplace_back(Unique<sf::Sprite>(s));
			spritePtrs.emplace_back(s);
		}
	}
	for (auto *t : rawTextures)
	{
		if (t)
		{
			textures.emplace_back(Unique<sf::Texture>(t));
		}
	}

	WorldState::GetInstance().assets.emplace_back(Unique<AssetState>(newState));

	Log::Success("Asset '" + name + "' initialized and stored in WorldState.");
	return true;
}

void Asset::Draw()
{
	if (spritePtrs.empty() || !assetState || !draw)
	{
		return;
	}
	draw(&spritePtrs);
}

void Asset::Update()
{
	if (spritePtrs.empty() || !assetState || !update)
	{
		return;
	}
	update(assetState, &spritePtrs);
}

void Asset::Clear()
{
	if (clear)
	{
		clear();
	}
}

} // namespace WoS
