#pragma once

namespace TGX
{
class Settings
{
private:
	Settings();
	~Settings() = default;

public:
	static Settings &GetInstance();

	Settings(const Settings &) = delete;
	Settings &operator=(const Settings &) = delete;

	Settings(Settings &&) = delete;
	Settings &operator=(Settings &&) = delete;
};
} // namespace TGX
