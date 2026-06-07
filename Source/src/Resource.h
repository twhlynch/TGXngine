#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "ResourceInstance.h"

using namespace nlohmann;

namespace WoS
{
using FNPTR_RESOURCE_AWAKE = ResourceInstance *(*)(const String &);
using FNPTR_RESOURCE_CREATE = void (*)(Vector<sf::Sprite *> *, Vector<sf::Texture *> *);
using FNPTR_RESOURCE_SEND_ORDER = void (*)(ResourceInstance *);
using FNPTR_RESOURCE_PROCESS_ORDER = void (*)(ResourceInstance *);
using FNPTR_RESOURCE_RENDER_WINDOW = void (*)(ResourceInstance *, Vector<sf::Sprite *> *);
using FNPTR_RESOURCE_UPDATE = void (*)(ResourceInstance *, Vector<sf::Sprite *> *);
using FNPTR_RESOURCE_DELETE = void (*)(int);

class Resource
{
private:
	FNPTR_RESOURCE_AWAKE awake;
	FNPTR_RESOURCE_CREATE create;
	FNPTR_RESOURCE_SEND_ORDER sendOrders;
	FNPTR_RESOURCE_PROCESS_ORDER processOrders;
	FNPTR_RESOURCE_RENDER_WINDOW draw;
	FNPTR_RESOURCE_UPDATE update;
	FNPTR_RESOURCE_DELETE _delete;

	ResourceInstance *resourceInstance;
	int removeUID = 0;

	sf::Sprite *sprite;
	sf::Texture *texture;

	Vector<Unique<sf::Sprite>> sprites;
	Vector<Unique<sf::Texture>> textures;
	Vector<sf::Sprite *> spritePtrs;

public:
	Resource(
		FNPTR_RESOURCE_AWAKE,
		FNPTR_RESOURCE_CREATE,
		FNPTR_RESOURCE_SEND_ORDER,
		FNPTR_RESOURCE_PROCESS_ORDER,
		FNPTR_RESOURCE_RENDER_WINDOW,
		FNPTR_RESOURCE_UPDATE,
		FNPTR_RESOURCE_DELETE);
	~Resource();

	bool Create(json &data);
	void SendOrders(ResourceInstance *resourceInstance);
	void ProcessOrders(ResourceInstance *resourceInstance);
	void Draw();
	void Update();
	void Delete();
	ResourceInstance *GetResourceInstance();
	void SetRemoteUID(int uid);
	int GetRemoteUID() const;
	void Clear();
};
} // namespace WoS
