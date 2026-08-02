include(FetchContent)

cmake_minimum_required(VERSION 3.16)

project(AutopilotHMI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# Core sources
#
set(AUTOPILOT_CORE_SOURCES

    src/controllers/AutopilotController.cpp
    src/controllers/HeadingController.cpp
    src/utils/MathUtils.cpp

)

set(AUTOPILOT_CORE_HEADERS
    src/controllers/AutopilotController.h
    src/controllers/HeadingController.h
)

set(QML_SOURCES
    qml/Main.qml
    qml/Dashboard.qml
    qml/components/ValueCard.qml
    qml/components/ModeSelector.qml
    qml/components/Compass.qml
    qml/components/NavButton.qml
    qml/components/NumericInputDialog.qml
    qml/components/RudderGauge.qml
    qml/components/ModeButton.qml
    qml/components/DebugRectangle.qml
    qml/components/HeadingControl.qml
)

set(UI_SOURCES

    src/main.cpp

    src/viewmodels/SteeringViewModel.cpp
    src/drivers/QtSimulationDriver.cpp

)

set(UI_HEADERS

    src/viewmodels/SteeringViewModel.h
    src/controllers/ControllerState.h
    src/controllers/AutopilotMode.h

    src/drivers/DriverState.h
    src/drivers/DriverCommands.h
    src/drivers/QtSimulationDriver.h

    src/interfaces/IControllerDriver.h
    src/interfaces/IControllerObserver.h
    src/interfaces/IAutopilotCommands.h

    src/viewmodels/DisplayState.h

    src/utils/MathUtils.h

    common/Constants.h
)

#
# All C++ source files
#
set(ALL_SOURCE_FILES
    ${AUTOPILOT_CORE_SOURCES}
    ${AUTOPILOT_CORE_HEADERS}
    ${UI_SOURCES}
    ${UI_HEADERS}
)

find_program(CLANG_FORMAT_EXECUTABLE clang-format)

if(NOT CLANG_FORMAT_EXECUTABLE)
    message(WARNING "clang-format not found")
endif()

find_program(CLANG_TIDY_EXECUTABLE clang-tidy)

if(NOT CLANG_TIDY_EXECUTABLE)
    message(WARNING "clang-tidy not found")
endif()

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
    message(WARNING "Doxygen not found")
endif()

#
# Optional imported content (Qt Design Studio)
#
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(importedcontent)
endif()

#
# Libraries
#
add_library(AutopilotCore
    STATIC
        ${AUTOPILOT_CORE_SOURCES}
)

#
# Headers
#
target_sources(AutopilotCore
    PRIVATE
        ${AUTOPILOT_CORE_HEADERS}
)

#
# Executable
#
qt_add_executable(appAutopilotHMI
    ${UI_SOURCES}
)

#
# QML Module
#
qt_add_qml_module(appAutopilotHMI
    URI AutopilotHMI

    QML_FILES
        ${QML_SOURCES}

    SOURCES
        ${UI_HEADERS}

    RESOURCES
        .clang-format
        .clangd
        .clang-tidy
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

if(CLANG_FORMAT_EXECUTABLE)

    add_custom_target(check-format
        COMMAND
            ${CLANG_FORMAT_EXECUTABLE}
            --dry-run
            --Werror
            ${ALL_SOURCE_FILES}

        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}

        COMMENT "Checking source formatting with clang-format"
    )
endif()

if(CLANG_FORMAT_EXECUTABLE)

    add_custom_target(format
        COMMAND
            ${CLANG_FORMAT_EXECUTABLE}
            -i
            ${ALL_SOURCE_FILES}

        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}

        COMMENT "Formatting source files"
    )
endif()

if(CLANG_TIDY_EXECUTABLE)

    add_custom_target(clang-tidy
        COMMAND
            ${CLANG_TIDY_EXECUTABLE}
            -p ${CMAKE_BINARY_DIR}
            ${AUTOPILOT_CORE_SOURCES}
            ${UI_SOURCES}

        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running clang-tidy"
    )
endif()

if(DOXYGEN_FOUND)

    add_custom_target(docs
        COMMAND
            ${DOXYGEN_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/Doxyfile

        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}

        COMMENT "Generating Doxygen documentation"
    )

endif()

#
# Installation
#
install(TARGETS appAutopilotHMI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)