#pragma once

#include <SFML/Graphics.hpp>
#include "Core.h"
#include "ItemInstance.h"
#include "Logs.h"
#include "ResourceInstance.h"
#include "common_export.h"

namespace TGX
{
class ImageLoader
{
private:
	inline static Map<String, std::unique_ptr<sf::Texture>> textureMap;

	ImageLoader() = default;
	~ImageLoader() = default;

public:
	COMMON_API static ImageLoader &GetInstance();

	ImageLoader(const ImageLoader &) = delete;
	ImageLoader &operator=(const ImageLoader &) = delete;

	inline static void Load(const String &asset, Instance *graphicsInstance, Vector<sf::Sprite *> *spritesRef, Vector<sf::Texture *> *texturesRef);
	inline static void Delete();
};

void ImageLoader::Load(const String &asset, Instance *instance, Vector<sf::Sprite *> *spritesRef, Vector<sf::Texture *> * /*texturesRef*/)
{
	auto it = textureMap.find(asset);
	sf::Texture *texture = nullptr;

	if (it != textureMap.end())
	{
		texture = it->second.get();
	}
	else
	{
		auto tex = std::make_unique<sf::Texture>();
		sf::Image image;

		if (!image.loadFromFile(asset))
		{
			Log::Error("Cannot load image: " + asset);
			return;
		}

		tex->loadFromImage(image);
		texture = tex.get();
		textureMap[asset] = std::move(tex);
	}

	auto *sprite = new sf::Sprite(*texture);

	float orgX = instance->GetOriginX();
	float orgY = instance->GetOriginY();

	if (orgX != 0.0f || orgY != 0.0f)
	{
		float finalOrgX = (orgX != 0.0f) ? static_cast<float>(texture->getSize().x) / orgX : 0.0f;
		float finalOrgY = (orgY != 0.0f) ? static_cast<float>(texture->getSize().y) / orgY : 0.0f;

		sprite->setOrigin(finalOrgX, finalOrgY);
	}

	instance->SetWidth(static_cast<int>(texture->getSize().x));
	instance->SetHeight(static_cast<int>(texture->getSize().y));

	spritesRef->push_back(sprite);
}

void ImageLoader::Delete()
{
	Log::Clean("Cleaning the textureMap");
	textureMap.clear();
}
} // namespace TGX
