#include "Resource.h"
#include "Config.h"
#include "Logs.h"
#include "Lookup.h"
#include "WorldState.h"

namespace TGX
{

Resource::Resource(
	FNPTR_RESOURCE_AWAKE awake,
	FNPTR_RESOURCE_CREATE create,
	FNPTR_RESOURCE_SEND_ORDER sendOrders,
	FNPTR_RESOURCE_PROCESS_ORDER processOrders,
	FNPTR_RESOURCE_RENDER_WINDOW draw,
	FNPTR_RESOURCE_UPDATE update,
	FNPTR_RESOURCE_DELETE _delete)
	: awake(awake), create(create), sendOrders(sendOrders), processOrders(processOrders), draw(draw), update(update), _delete(_delete)
{
	Log::Info("Create Game Resource");

	if (awake == nullptr)
	{
		Log::Error("Awake is Null Pointer");
	}
}

Resource::~Resource()
{
	Log::Clean("Delete Game Resource");

	Log::Success("Delete Game Resource");
}

bool Resource::Create(json &data)
{
	Log::Info("Resource Create");

	String name = data["name"];
	String type = data["type"];
	int uid = data["uid"];

	Log::Print(name);
	Log::Print(uid);

	if (awake == nullptr)
	{
		Log::Error("Awake function pointer is null - cannot create item: " + name);
		return false;
	}

	resourceInstance = awake(data["name"]);

	if (resourceInstance == nullptr)
	{
		Log::Error("Awake returned nullptr - failed to create item: " + name);
		return false;
	}

	resourceInstance->SetUid(uid);
	resourceInstance->SetType(type);
	resourceInstance->SetName(name);

	if (data["x"] != nullptr)
	{
		resourceInstance->SetX(data["x"]);
		resourceInstance->SetY(data["y"]);
	}
	else
	{
		WorldState &world = WorldState::GetInstance();
		Log::Print(world.GetTeam());
	}

	Vector<sf::Sprite *> rawSprites;
	Vector<sf::Texture *> rawTextures;
	create(&rawSprites, &rawTextures);

	sprites.reserve(rawSprites.size());
	spritePtrs.reserve(rawSprites.size());
	for (auto *s : rawSprites)
	{
		sprites.emplace_back(Unique<sf::Sprite>(s));
		spritePtrs.emplace_back(s);
	}

	WorldState &world = WorldState::GetInstance();

	world.resources.emplace_back(resourceInstance);

	String lastUid = std::to_string(world.resources.back()->GetUid());
	Log::Print("Last UID: " + lastUid);

	Log::Success("Resource Created");

	return true;
}

void Resource::SendOrders(ResourceInstance *inResourceInstance)
{
	sendOrders(inResourceInstance);
}

void Resource::ProcessOrders(ResourceInstance *inResourceInstance)
{
	processOrders(inResourceInstance);
}

void Resource::Draw()
{
	if (spritePtrs.empty() || !resourceInstance)
	{
		return;
	}

	draw(resourceInstance, &spritePtrs);
}

void Resource::Update()
{
	update(this->resourceInstance, &spritePtrs);
}

ResourceInstance *Resource::GetResourceInstance()
{
	return resourceInstance;
}

void Resource::SetRemoteUID(int uid)
{
	this->removeUID = uid;
}

int Resource::GetRemoteUID() const
{
	return this->removeUID;
}

void Resource::Clear()
{
}

void Resource::Delete()
{
}
} // namespace TGX
