#pragma once

#include <algorithm>
#include <string>

int static RoundGridDown(float value, int offset = 0, int scale = 1)
{
	return (static_cast<int>(value) + offset) / scale;
}

bool static IsNumber(const std::string &str)
{
	return std::ranges::all_of(str, isdigit);
}
