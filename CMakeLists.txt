cmake_minimum_required(VERSION 3.16)

project(AutopilotHMI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

#
# Optional imported content (Qt Design Studio)
#
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(importedcontent)
endif()

#
# Libraries
#
add_library(AutopilotCore STATIC
    src/controllers/AutopilotController.cpp
    src/controllers/HeadingController.cpp
    src/utils/MathUtils.cpp
)

#
# Executable
#
qt_add_executable(appAutopilotHMI
    src/main.cpp
)

#
# QML Module
#
qt_add_qml_module(appAutopilotHMI
    URI AutopilotHMI

    QML_FILES
        qml/Main.qml
        qml/Dashboard.qml
        qml/components/ValueCard.qml
        qml/components/ModeSelector.qml
        qml/components/Compass.qml


    SOURCES
        src/controllers/AutopilotController.h
        src/controllers/AutopilotController.cpp
        src/controllers/ControllerState.h
        src/controllers/HeadingController.h
        src/controllers/HeadingController.cpp
        src/controllers/AutopilotMode.h

        src/viewmodels/SteeringViewModel.h
        src/viewmodels/SteeringViewModel.cpp
        src/viewmodels/DisplayState.h

        src/drivers/QtSimulationDriver.h
        src/drivers/QtSimulationDriver.cpp
        src/drivers/DriverState.h
        src/drivers/DriverCommands.h

        src/interfaces/IControllerObserver.h
        src/interfaces/IControllerDriver.h
        src/interfaces/IAutopilotCommands.h

        common/Constants.h

        src/utils/MathUtils.h
        src/utils/MathUtils.cpp

    RESOURCES
        .clang-format
        .clangd
        .clang-tidy
        QML_FILES qml/components/NavButton.qml
        QML_FILES qml/components/NumericInputDialog.qml
        QML_FILES qml/components/RudderGauge.qml
        QML_FILES
        QML_FILES qml/components/ModeButton.qml
        QML_FILES
        QML_FILES
        QML_FILES
        QML_FILES qml/components/DebugRectangle.qml
        QML_FILES qml/components/HeadingControl.qml
        QML_FILES
        QML_FILES
        QML_FILES
        SOURCES
)

#
# Include directories
#
target_include_directories(appAutopilotHMI
    PRIVATE
        src/controllers
        src/drivers
        src/viewmodels
        src/interfaces
        src/utils
        common
)

target_include_directories(AutopilotCore
    PUBLIC
        src
        src/controllers
        src/drivers
        src/interfaces
        src/utils
        common
)

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

#
# Libraries
#
target_link_libraries(appAutopilotHMI
    PRIVATE
        Qt6::Quick
        AutopilotCore
)

#
# Bundle properties
#
set_target_properties(appAutopilotHMI PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE

    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING
        ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

#
# Installation
#
install(TARGETS appAutopilotHMI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)