#pragma once

#include <nlohmann/json.hpp>
#include "Audio/Music.h"
#include "Core.h"
#include "Scene.h"

using namespace nlohmann;

namespace TGX
{
class Intro : public Scene
{
private:
	Unique<Music> music;
	sf::Sprite background;
	sf::Texture backgroundTexture;

public:
	Intro();
	~Intro() override;
	void Init() override;
	void Update() override;
	void Draw() override;
	void Click() override;
	void RightClick() override;
	void Release() override;
	void Close() override;
	void Free() override;
};
} // namespace TGX
