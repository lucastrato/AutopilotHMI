include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Required on Windows, harmless elsewhere

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(UnitTests
    HeadingControllerTest.cpp
    AutopilotControllerTest.cpp
    MockDriver.h
    MockObserver.h
)

target_link_libraries(UnitTests PRIVATE
    AutopilotCore
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(UnitTests)