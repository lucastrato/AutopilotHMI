/**
 * @file AutopilotMode.h
 * @brief Operating modes supported by the autopilot system.
 *
 * The selected mode determines which control commands are accepted by the
 * system and which controller logic is active.
 */

#pragma once

enum class AutopilotMode
{
    Standby,
    Auto,
    Manual
};
