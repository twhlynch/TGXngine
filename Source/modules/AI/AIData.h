#pragma once

#include "Core.h"

namespace WoS
{

struct AIProfile
{
    // Identifies the faction/team allocation (e.g., "technology", "social-earth")
    String team;

    // Driven dynamically by demand! 
    // If "modules/Ships" isn't loaded, keys like "light_sea_offensive" simply won't exist here.
    Map<String, int> roleCount;
    Map<String, int> roleMax;

    // Auxiliary bucket for modules to inject state info 
    Map<String, Any> extras; 
};

} // namespace WoS