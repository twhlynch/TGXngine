#pragma once

#include "Instance.h"

namespace TGX
{
class ResourceInstance : public Instance
{
public:
	virtual int GetFrames() const override
	{
		return 1;
	}
};
} // namespace TGX
