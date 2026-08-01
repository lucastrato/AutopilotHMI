#pragma once

namespace Constants
{

// Time
constexpr int SimulationUpdateIntervalMs = 100;
constexpr int UiRefreshIntervalMs = 1000;
constexpr int StartupDelayMs = 1000;

// Navigation
constexpr double FullCircleDeg = 360.0;
constexpr double HalfCircleDeg = 180.0;
constexpr double RudderMaxAngle = 35.0;
constexpr double InitHeading = 130.0;
constexpr double HeadingRateGain = 0.05;

// Control
constexpr double HeadingControllerKp = 0.2;

// UI
constexpr int DefaultWindowWidth = 1280;
constexpr int DefaultWindowHeight = 720;

} // namespace Constants
