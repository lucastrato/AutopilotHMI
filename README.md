# Autopilot HMI

Embedded Qt/QML application demonstrating a simplified marine autopilot.

## Features

- Qt 6 / QML interface
- MVC-inspired architecture
- Heading controller
- Timer-based simulation
- Observer pattern
- Hardware abstraction through interfaces

## Architecture

```
+---------------------+
|        QML          |
+----------+----------+
           |
           v
 SteeringViewModel
           |
           v
 AutopilotController
      |          |
      |          |
      v          v
HeadingController IControllerDriver
                     |
                     v
            QtSimulationDriver
```