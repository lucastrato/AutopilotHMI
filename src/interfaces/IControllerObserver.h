#pragma once

#include "ControllerState.h"

/**
 * @class IControllerObserver
 * @brief Interface for receiving controller state updates.
 *
 * The IControllerObserver interface defines the observer contract used by the
 * controller to notify interested components whenever the controller state
 * changes.
 *
 * Implementations can use this mechanism to react to new data without creating
 * a direct dependency on the controller implementation.
 *
 * Typical observers may include user interfaces, logging components,
 * diagnostics modules, or monitoring services.
 */
class IControllerObserver
{
public:
    /**
     * @brief Virtual destructor.
     *
     * Ensures that derived observer implementations are properly destroyed when
     * accessed through an IControllerObserver pointer.
     */
    virtual ~IControllerObserver() = default;

    /**
     * @brief Callback invoked when the controller state changes.
     *
     * The controller calls this method to notify observers about a new state
     * snapshot. The observer must not modify the provided state object.
     *
     * @param state Updated controller state information.
     */
    virtual void onStateChanged(const ControllerState& state) = 0;
};