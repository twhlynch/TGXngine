#pragma once
#include <cstdint>
#include <functional>

namespace TGX
{
enum class TraversalType : uint8_t
{
	Normal,
	Soft,
};

inline std::function<bool(int, int)> GetTraversalPredicate(TraversalType type)
{
	switch (type)
	{
		case TraversalType::Soft:
			return [](int cellMode, int gridValue) {
				if (cellMode == 1)
				{
					return gridValue <= 1;
				}
				return gridValue == 0;
			};
		case TraversalType::Normal:
		default:
			return [](int /*cellMode*/, int gridValue) {
				return gridValue == 0;
			};
	}
}
} // namespace TGX
